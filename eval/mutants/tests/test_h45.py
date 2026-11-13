"""H45-mutant-eval (doc/plan/H45_PLAN.md): the mutator, the activation check and the scoring, tests T1-T6.
Fixtures: tests/input/h45/rtl (counter.sv, fsm.sv, tb_counter.sv). Needs pyslang; T2 and T4 need Verilator."""

from __future__ import annotations

import collections
import json
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "eval" / "mutants"))
import mutate  # noqa: E402
import score  # noqa: E402
import traces  # noqa: E402

RTL = ROOT / "tests" / "input" / "h45" / "rtl"
COUNTER, FSM, TB = RTL / "counter.sv", RTL / "fsm.sv", RTL / "tb_counter.sv"
needs_verilator = pytest.mark.skipif(shutil.which("verilator") is None, reason="no verilator on PATH")


def changed_lines(a: str, b: str) -> list[int]:
    la, lb = a.splitlines(), b.splitlines()
    assert len(la) == len(lb), "a mutant keeps the line structure"
    return [i + 1 for i, (x, y) in enumerate(zip(la, lb)) if x != y]


# T1: every mutant is one fault, compiles, and is what it says
def test_t1_sites_are_single_faults(tmp_path: Path) -> None:
    for src, top in ((COUNTER, "counter"), (FSM, "fsm")):
        sites = mutate.sites([src], top)
        ops = collections.Counter(s.op for s in sites)
        assert {"sa0", "sa1", "inv", "op", "cond", "const"} <= set(ops), (top, ops)
        assert len({s.id for s in sites}) == len(sites), "ids are unique"
        orig = src.read_text()
        for s in sites:
            out = mutate.apply(s, [src], tmp_path / s.id)[0]
            text = out.read_text()
            assert text != orig, s
            lines = changed_lines(orig, text)
            if s.op in ("sa0", "sa1", "inv"):
                # the bit is forced at every assignment to that signal in its module, and nowhere else
                assert s.signal and s.bit is not None
                assert set(lines) == set(s.lines), (s, lines)
            else:
                assert lines == s.lines and len(lines) == 1, (s, lines)


def test_t1_kinds_on_counter() -> None:
    sites = mutate.sites([COUNTER], "counter")
    by = collections.defaultdict(list)
    for s in sites:
        by[s.op].append(s)
    # q is assigned twice (reset and enable): its stuck-at edits both; q_next once
    q3 = [s for s in by["sa1"] if s.signal == "q" and s.bit == 3]
    assert len(q3) == 1 and len(q3[0].lines) == 2
    # inputs are not mutated at their driver (they have none here)
    assert not any(s.signal in ("en", "load", "din", "clk", "rst_n") for s in by["sa0"] + by["sa1"])
    # operators: '+' of q + 8'd1, '==' of q == 8'd255, '&&' of the wrap condition
    assert {s.detail for s in by["op"]} >= {"+ -> -", "== -> !=", "&& -> ||"}
    # constants (k -> k+1, or k-1 at the top of its width), the reset value 8'd0 included
    assert {s.detail for s in by["const"]} >= {"8'd0 -> 8'd1", "8'd1 -> 8'd2", "8'd255 -> 8'd254"}
    # conditions: the ternary's load, if (!rst_n), if (en)
    assert len(by["cond"]) >= 3


@needs_verilator
def test_t1_every_mutant_compiles(tmp_path: Path) -> None:
    for src, top in ((COUNTER, "counter"), (FSM, "fsm")):
        for s in mutate.sites([src], top):
            out = mutate.apply(s, [src], tmp_path / s.id)
            r = subprocess.run(["verilator", "--lint-only", "-Wno-fatal", "-Wno-lint", "-Wno-style",
                                "--top-module", top, *map(str, out)], capture_output=True, text=True)
            assert r.returncode == 0, (s, r.stderr[-600:])


# T2: stuck-at semantics in simulation
@needs_verilator
@pytest.mark.parametrize("op,value", [("sa1", "1"), ("sa0", "0")])
def test_t2_stuck_at_holds_in_simulation(tmp_path: Path, op: str, value: str) -> None:
    s = next(x for x in mutate.sites([COUNTER], "counter") if x.op == op and x.signal == "q" and x.bit == 2)
    files = mutate.apply(s, [COUNTER], tmp_path / "m")
    vcd = tmp_path / "m.vcd"
    traces.simulate(files + [TB], "tb", tmp_path / "build", seed=5, cycles=300, vcd=vcd)
    q = traces.sample(vcd, "tb.dut", "clk")["q"]
    after_reset = q[3:]
    assert after_reset and all(v[-1 - 2] == value for v in after_reset), after_reset[:10]


# T3: sampling is deterministic and keeps the proportions
def test_t3_sampling() -> None:
    sites = mutate.sites([COUNTER], "counter") + mutate.sites([FSM], "fsm")
    a = mutate.sample(sites, 20, seed=7)
    b = mutate.sample(sites, 20, seed=7)
    c = mutate.sample(sites, 20, seed=8)
    assert [s.id for s in a] == [s.id for s in b]
    assert [s.id for s in a] != [s.id for s in c]
    assert len(a) == 20 and len({s.id for s in a}) == 20
    n = collections.Counter(mutate.GROUP[s.op] for s in a)
    want = {g: round(20 * p) for g, p in mutate.PROPORTIONS.items()}
    assert sum(want.values()) == 20
    for g, k in want.items():  # every group has enough sites here, so each gets exactly its share
        assert sum(1 for s in sites if mutate.GROUP[s.op] == g) >= k
        assert n[g] == k, (g, n, want)
    assert mutate.sample(sites, 10**6, seed=1).__len__() == len(sites)  # more than exist: all of them


# T4: activation
@needs_verilator
def test_t4_activation(tmp_path: Path) -> None:
    gold = tmp_path / "g.vcd"
    traces.simulate([COUNTER, TB], "tb", tmp_path / "bg", seed=5, cycles=300, vcd=gold)
    outs = {"q", "wrap"}
    sites = mutate.sites([COUNTER], "counter")
    # a stuck-at of q's bit 0 shows on an output
    s = next(x for x in sites if x.op == "sa0" and x.signal == "q" and x.bit == 0)
    m = tmp_path / "m.vcd"
    traces.simulate(mutate.apply(s, [COUNTER], tmp_path / "m") + [TB], "tb", tmp_path / "bm", seed=5, cycles=300, vcd=m)
    assert traces.activation(gold, m, "tb.dut", "clk", outs) == "output"
    # the same trace is not activated
    assert traces.activation(gold, gold, "tb.dut", "clk", outs) == "none"
    # a difference only in q_next while en is low would be internal: checked on hand-made samples
    g = {"q": ["00", "01"], "wrap": ["0", "0"], "q_next": ["01", "02"]}
    h = {"q": ["00", "01"], "wrap": ["0", "0"], "q_next": ["01", "03"]}
    assert traces.classify(g, h, outs) == "internal"
    assert traces.classify(g, dict(g), outs) == "none"


# T5: scoring
def test_t5_score(tmp_path: Path) -> None:
    info = {"version": "1", "assertions": [
        {"text": "A1", "faults": ["f/golden2.vcd", "f/m1.vcd"], "faultsComplete": True},  # a false positive
        {"text": "A2", "faults": ["f/m2.vcd"], "faultsComplete": True},
        {"text": "A3", "faults": ["f/m2.vcd", "f/m4.vcd"], "faultsComplete": True},
        {"text": "A4", "faults": [], "faultsComplete": True},
    ]}
    p = tmp_path / "info.json"
    p.write_text(json.dumps(info))
    mutants = {"f/m1.vcd": ("output", "sa0"), "f/m2.vcd": ("output", "op"), "f/m3.vcd": ("internal", "sa1"),
               "f/m4.vcd": ("internal", "cond"), "f/m5.vcd": ("none", "const")}
    r = score.score(p, "f/golden2.vcd", mutants)
    assert r["assertions"] == 4 and r["false_positives"] == 1
    assert r["activated"] == 4 and r["not_activated"] == 1
    assert r["killed"] == 2  # m2 (A2, A3) and m4 (A3); m1 only by the false positive
    assert r["score"] == pytest.approx(0.5)
    assert r["activated_output"] == 2 and r["killed_output"] == 1
    assert r["by_op"]["sa0"] == {"activated": 1, "killed": 0}
    assert r["by_op"]["op"] == {"activated": 1, "killed": 1}
    assert r["by_op"]["cond"] == {"activated": 1, "killed": 1}
    with pytest.raises(ValueError, match="complete"):
        info["assertions"][0]["faultsComplete"] = False
        p.write_text(json.dumps(info))
        score.score(p, "f/golden2.vcd", mutants)


# T6: run_eval.py's configurations are unchanged (the driver H44 used)
def test_t6_run_eval_configurations_unchanged() -> None:
    src = (ROOT / "eval" / "run_eval.py").read_text()
    for name in ('cfg["R"]', 'cfg["R+F"]', 'cfg["R+F+X"]', 'cfg["RR"]', 'cfg["RR+F+X"]'):
        assert name in src
    import mutants_eval  # noqa: E402  (the H45 driver reuses run_eval's configurations)
    assert mutants_eval.CONFIGS == ["C0", "R", "R+F", "R+F+X", "RR", "RR+F+X"]
    assert mutants_eval.configs_for is mutants_eval.run_eval.configs_for


# ---- H45 amendment (2026-11-13): verification-quality traces ---------------------------------------------------------
# T8: Verilator coverage of the design (not the testbench), per seed set
@needs_verilator
def test_t8_coverage(tmp_path: Path) -> None:
    import vcov  # noqa: E402
    rnd = vcov.measure([COUNTER], TB, "tb.dut", tmp_path / "rnd", seeds=[1, 2], cycles=600)
    idle = vcov.measure([COUNTER], TB, "tb.dut", tmp_path / "idle", seeds=[1], cycles=600, plusargs=["+idle=1"])
    for r in (rnd, idle):
        assert set(r) >= {"line", "toggle", "branch"}
        for hit, total in (r["line"], r["toggle"], r["branch"]):
            assert 0 < total and 0 <= hit <= total
    # only the design's points: the testbench's own lines are not counted
    assert all(f.endswith("counter.sv") for f in rnd["files"]), rnd["files"]
    assert rnd["line"][0] == rnd["line"][1], rnd  # random stimulus reaches every line of the counter
    assert idle["toggle"][0] < rnd["toggle"][0]  # en held low: q never moves
    assert idle["branch"][0] < rnd["branch"][0]


# T9: several held-out seeds: activation is the strongest over the seeds; a kill on any seed counts; a failure on any
# held-out golden trace makes a false positive
def test_t9_activation_over_seeds() -> None:
    assert traces.combine(["none", "none"]) == "none"
    assert traces.combine(["none", "internal"]) == "internal"
    assert traces.combine(["internal", "output", "none"]) == "output"


def test_t9_score_over_seeds(tmp_path: Path) -> None:
    info = {"version": "1", "assertions": [
        {"text": "A1", "faults": ["f/g102.vcd", "f/m1_s101.vcd"], "faultsComplete": True},  # false positive
        {"text": "A2", "faults": ["f/m2_s102.vcd"], "faultsComplete": True},  # m2 killed on seed 102 only
        {"text": "A3", "faults": [], "faultsComplete": True},
    ]}
    p = tmp_path / "info.json"
    p.write_text(json.dumps(info))
    mutants = {"m1": ("output", "sa0", ["f/m1_s101.vcd", "f/m1_s102.vcd"]),
               "m2": ("internal", "op", ["f/m2_s102.vcd"]),
               "m3": ("internal", "const", ["f/m3_s101.vcd"]),
               "m4": ("none", "cond", [])}
    r = score.score_multi(p, ["f/g101.vcd", "f/g102.vcd"], mutants)
    assert r["false_positives"] == 1 and r["assertions"] == 3
    assert r["activated"] == 3 and r["not_activated"] == 1
    assert r["killed"] == 1 and r["score"] == pytest.approx(1 / 3)
    assert r["activated_output"] == 1 and r["killed_output"] == 0
    assert r["by_op"]["op"] == {"activated": 1, "killed": 1}


@needs_verilator
def test_t9_prepare_seeds(tmp_path: Path) -> None:
    import mutants_eval  # noqa: E402
    corpus = ROOT / "tests" / "input" / "h45" / "corpus.json"
    d = json.loads(corpus.read_text())[0]
    prep = mutants_eval.prepare(d, corpus.parent, tmp_path / "w", 4, 1, 2, mining_seeds=[1, 2], heldout_seeds=[101, 102])
    mining = sorted(Path(prep["mining_dir"]).glob("*.vcd"))
    assert [m.name for m in mining] == ["golden_s1.vcd", "golden_s2.vcd"]
    assert [Path(g).name for g in prep["goldens"]] == ["golden_s101.vcd", "golden_s102.vcd"]
    assert all(Path(g).parent == Path(prep["faults"]) for g in prep["goldens"])
    assert len(prep["mutants"]) == 4
    for mid, (act, op, files) in prep["mutants"].items():
        assert act in ("none", "internal", "output") and op
        assert (act == "none") == (not files)  # only activated seeds' traces go to the fault directory
        for f in files:
            assert Path(f).parent == Path(prep["faults"]) and Path(f).exists()
            assert Path(f).name.startswith(mid + "_s") and Path(f).name[len(mid) + 2:-4] in ("101", "102")


# T10: HARM gets the design's reset, so reset-fixed (L2) assertions are mined
@needs_verilator
def test_t10_reset(tmp_path: Path) -> None:
    import os
    import mutants_eval  # noqa: E402
    harm = os.environ.get("HARM_BIN")
    if not harm:
        pytest.skip("HARM_BIN not set (ctest sets it)")
    assert mutants_eval.reset_args({"reset": "!rst_n"}) == ["--reset", "!rst_n"]
    assert mutants_eval.reset_args({}) == []
    corpus = ROOT / "tests" / "input" / "h45" / "corpus.json"
    out = tmp_path / "out"
    r = subprocess.run([sys.executable, str(ROOT / "eval" / "mutants" / "mutants_eval.py"), str(corpus), str(out),
                        "--harm", harm, "--python", sys.executable, "--configs", "RR", "--mutants", "4",
                        "--mining-seeds", "1", "--heldout-seeds", "101"], capture_output=True, text=True)
    assert r.returncode == 0, r.stdout + r.stderr
    texts = [a["text"] for a in json.loads((out / "counter" / "harm" / "info.json").read_text())["assertions"]]
    assert "G({!rst_n} |=> q == 8'b0)" in texts, texts[:20]
