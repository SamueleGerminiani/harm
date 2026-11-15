"""The hint-level study's scripts (eval/hint-levels, doc/plan/H46_PLAN.md, H47_PLAN.md): T1-T6.

T2 compares the arms with the wrapper they were extracted from: tests/fixtures/adapter_reference.json holds, per
harm-coi fixture and arm, the configuration files, HARM's command lines and the kept and dropped assertions that the
wrapper wrote (machine paths replaced by <WORK>, <HARM>, <HARM_BIN>, <PY>; the deadline's value by <D>)."""

from __future__ import annotations

import ast
import csv
import json
import os
import re
import shutil
import sys
import tempfile
from pathlib import Path

import pytest

HERE = Path(__file__).resolve().parents[1]
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))

SCRIPTS = ("arms.py", "cut.py", "run_arms.py", "tables.py", "filter_check.py", "sizes.py")
FIXTURES = {"counter": "tests/input/coi/counter", "fsm": "tests/input/coi/fsm"}
HARM_BIN = os.environ.get("HARM_BIN")
needs_harm = pytest.mark.skipif(not HARM_BIN, reason="HARM_BIN not set (ctest sets it)")


# T1: only the standard library, pyslang and this directory's modules; nothing private, nothing internal
def test_t1_standalone() -> None:
    local = {Path(s).stem for s in SCRIPTS} | {"mutate", "score", "traces"}
    for s in SCRIPTS:
        tree = ast.parse((HERE / s).read_text())
        for node in ast.walk(tree):
            names = [a.name for a in node.names] if isinstance(node, ast.Import) else \
                [node.module] if isinstance(node, ast.ImportFrom) and node.module and node.level == 0 else []
            for n in names:
                top = n.split(".")[0]
                assert top in sys.stdlib_module_names or top in local | {"pyslang", "__future__"}, f"{s} imports {n}"
    bad = re.compile(r"trivergence|/Users/|/home/|/private/|\b(DD1|HL1|RV1|CR1|BR1|HX1|MC1[ab]?|D-0\d\d|RQ3b|"
                     r"miner.portfolio)\b", re.I)
    for p in sorted(HERE.rglob("*")):
        if p.is_file() and p.suffix in (".py", ".sh", ".md", ".csv", ".json") and p != Path(__file__).resolve():
            m = bad.search(p.read_text(errors="replace"))
            assert not m, f"{p.relative_to(HERE)}: {m.group(0)!r}"


def _entry(name: str):  # type: ignore[no-untyped-def]
    root = ROOT / FIXTURES[name]
    e = {"id": name, "vcd_recursion": 0, "design": {"id": name, "root": str(root), "rtl_files": [f"rtl/{name}.sv"],
         "top": name, "clock": {"name": "clk", "edge": "posedge"}, "reset": {"name": "rst", "active_low": False},
         "include_dirs": [], "defines": {}}}  # fmt: skip
    return e, [{"vcd_paths": [str(root / "trace.vcd")], "scope": "tb::dut"}]


# T2: the configuration files, HARM's command lines and the kept and dropped assertions equal the wrapper's
@needs_harm
@pytest.mark.parametrize("arm", ["L0", "L0+roles", "rel", "deep"])
@pytest.mark.parametrize("name", sorted(FIXTURES))
def test_t2_same_as_the_wrapper(name: str, arm: str) -> None:
    import arms

    ref = json.loads((HERE / "tests" / "fixtures" / "adapter_reference.json").read_text())[f"{name}/{arm}"]
    tools = arms.Tools(Path(HARM_BIN).resolve(), Path(sys.executable), ROOT)

    def norm(s: str, work: Path) -> str:
        s = s.replace(str(work), "<WORK>").replace(str(ROOT), "<HARM>").replace(str(tools.harm), "<HARM_BIN>")
        s = s.replace(str(tools.python), "<PY>")
        return re.sub(r"--deadline', '[0-9.]+'", "--deadline', '<D>'", s)

    with tempfile.TemporaryDirectory() as td:
        work = Path(td) / "w"
        e, tr = _entry(name)
        spec = arms.ARMS[arm]
        r = arms.mine(e, tr, work, tools, timeout_s=300, threads=2, hints=spec["hints"], knobs=dict(spec["knobs"]))
        confs = {str(p.relative_to(work)): norm(p.read_text(), work) for p in sorted(work.rglob("config.xml"))}
        cmds = [norm(repr(r.stats["command"]), work)] if "command" in r.stats else []
        if isinstance(r.stats.get("cut_pass"), dict) and "command" in r.stats["cut_pass"]:
            cmds.append(norm(repr(r.stats["cut_pass"]["command"]), work))
        assert r.status == ref["status"]
        assert confs == ref["configs"]
        assert cmds == ref["commands"]
        assert [[c["provenance"]["harm_text"], c["provenance"]["rtl_level"], c["provenance"].get("pass", "")]
                for c in r.candidates] == ref["candidates"]  # fmt: skip
        assert sorted(d["harm_text"] for d in r.dropped) == ref["dropped"]


# T3: the level rule, the trivial long-range forms and the cut, on hand-made cases
def test_t3_rules(tmp_path: Path) -> None:
    import arms
    import cut

    def leaf(text: str, ant: bool, origin: str = "rtl") -> dict:
        return {"text": text, "antecedent": ant, "variables": re.findall(r"[a-z_]+", text), "origin": origin}

    lv = lambda leaves: arms.level({"leaves": leaves}, "rst_ni", active_low=True)  # noqa: E731
    assert lv([leaf("rst_ni", True), leaf("q == 1'b0", False)]) == "L2"
    assert lv([leaf("$rose(rst_ni)", True), leaf("q == 1'b0", False)]) == "L2"
    assert lv([leaf("en", True), leaf("q == $past(d)", False, "rtl-relation")]) == "L1"
    assert lv([leaf("en", True), leaf("q == 1'b0", False)]) == "L0"
    assert arms.needs_reset_active([leaf("!rst_ni", True)], "rst_ni", active_low=True)
    assert not arms.needs_reset_active([leaf("rst_ni", True)], "rst_ni", active_low=True)
    assert arms.trivial_long_range("a |-> q until q")
    assert arms.trivial_long_range("a |-> !r until r")
    assert not arms.trivial_long_range("a |-> !w until r")
    # the cut: of each run of cycles in which the atom does not change, the first two are kept
    vcd = tmp_path / "t.vcd"
    lines = ["$scope module tb $end", "$scope module dut $end", "$var wire 1 ! clk $end", "$var wire 1 \" a $end",
             "$upscope $end", "$upscope $end", "$enddefinitions $end", "#0", "0!", "0\""]
    for c in range(10):
        lines += [f"#{10 * c + 5}", "1!"] + (["1\""] if c == 6 else []) + [f"#{10 * c + 10}", "0!"]
    vcd.write_text("\n".join(lines) + "\n")
    info = cut.cut(vcd, tmp_path / "c.vcd", "tb::dut", "clk", ["a"])
    assert info["cycles_in"] == 10 and info["cycles_out"] < info["cycles_in"]


# T4 (slow): end to end on two prepared designs, the killed mutants of the letter's runs
@needs_harm
@pytest.mark.skipif(not os.environ.get("HINT_LEVELS_PREPARED"), reason="HINT_LEVELS_PREPARED (a prepared dir) not set")
@pytest.mark.parametrize("name", ["lossy_valid_to_stream", "id_queue"])
def test_t4_end_to_end(tmp_path: Path, name: str) -> None:
    import run_arms

    prepared = Path(os.environ["HINT_LEVELS_PREPARED"])
    out = tmp_path / "out"
    run_arms.main([str(ROOT / "eval" / "mutants" / "corpus.json"), str(prepared), str(out), "--designs", name,
                   "--arms", "L0+roles,deep", "--repeats", "deep=1", "--machine", "test", "--harm", HARM_BIN,
                   "--python", sys.executable, "--threads", "4", "--jobs", "2"])  # fmt: skip
    got = {r["arm"]: set(json.loads(r["killed_ids"])) for r in csv.DictReader(open(out / "results.csv"))}
    ref = {r["arm"]: set(json.loads(r["killed_ids"])) for r in csv.DictReader(open(HERE / "results" / "rq3.csv"))
           if r["design"] == name and r["repeat"] == "0"}  # fmt: skip
    assert got == ref


# T5: the letter's tables from results/
def test_t5_tables() -> None:
    import tables

    t = tables.build(HERE / "results")
    assert t["kills"]["all"] == {"L0": (427, 839), "L0+roles": (429, 839), "rel": (697, 839), "deep": (433, 839)}
    assert t["kills"]["fp"] == {"L0": 22, "L0+roles": 26, "rel": 75, "deep": 26}
    assert t["configs"]["pulp"]["RR+F+X"] == {"finished": 10, "assertions": 3200, "killed": 718}
    assert t["configs"]["assertllm2"]["R+F+X"] == {"finished": 9, "assertions": 15834}
    assert t["rq3"]["lossy_valid_to_stream"]["deep_only"] == 7
    assert t["filter"] == {"lost": 61, "gained": 2, "reset": 32, "delay": 20, "out_of_cone": 9}


# T6: the design sizes of the letter's Table IV, and results/sizes.csv equal to sizes.py's output
@pytest.mark.skipif(not (ROOT / "build" / "h45" / "common_cells").is_dir(), reason="common_cells not fetched")
def test_t6_sizes(tmp_path: Path) -> None:
    import sizes

    out = tmp_path / "sizes.csv"
    sizes.main([str(ROOT / "eval" / "mutants" / "corpus.json"), "--out", str(out)])
    got = {r["design"]: r for r in csv.DictReader(open(out))}
    table4 = {"spill_register": (5, 3, 91), "fall_through_register": (6, 3, 135), "fifo_v3": (6, 4, 99),
              "rr_arb_tree": (6, 4, 273), "id_queue": (11, 8, 420), "lfsr": (3, 1, 225), "plru_tree": (3, 1, 62),
              "delta_counter": (8, 2, 65), "exp_backoff": (4, 1, 44), "credit_counter": (5, 4, 35)}  # fmt: skip
    for d, (i, o, loc) in table4.items():
        assert (int(got[d]["inputs"]), int(got[d]["outputs"]), int(got[d]["loc"])) == (i, o, loc), d
    assert sum(int(got[d]["loc"]) for d in table4) == 1449
    assert len(got) == 20
    assert list(csv.DictReader(open(HERE / "results" / "sizes.csv"))) == list(csv.DictReader(open(out)))
