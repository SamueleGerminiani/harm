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


# T12 (H45 amendment): a mutant that stalls the testbench still ends. The shared testbench part stops the run after
# +cycles plus a fixed margin (WATCHDOG_MARGIN cycles: far above every directed phase); traces.run has a wall-clock
# limit as a backstop, and prepare() sets a mutant that reaches it aside as hung (replaced like an uncompiled one).
def test_t12_run_timeout(tmp_path: Path) -> None:
    exe = tmp_path / "Vtb"
    exe.write_text("#!/bin/sh\nsleep 30\n")
    exe.chmod(0o755)
    with pytest.raises(traces.SimTimeout):
        traces.run(exe, 1, 10, tmp_path / "t.vcd", timeout_s=1)


@needs_verilator
def test_t12_watchdog_ends_a_stalled_mutant(tmp_path: Path) -> None:
    import time
    corpus = ROOT / "eval" / "mutants" / "corpus.json"
    d = next(x for x in json.loads(corpus.read_text()) if x["name"] == "exp_backoff")
    base = corpus.parent
    files = [base / f for f in d["files"]]
    if not files[0].exists():
        pytest.skip("PULP common_cells not fetched (eval/mutants/fetch.sh)")
    incs = [str(base / i) for i in d["includes"]]
    site = next(s for s in mutate.sites(files, d["top"], d["defines"], incs) if s.id == "sa1-exp_backoff-cnt_q-b6")
    src = mutate.apply(site, files, tmp_path / "src")
    extra = [f"+define+{x}" for x in d["defines"]] + [f"-I{i}" for i in incs]
    exe = traces.build(src + [base / d["tb"]], "tb", tmp_path / "build", extra)
    t0 = time.time()
    vcd = traces.run(exe, 101, 200, tmp_path / "m.vcd", timeout_s=120)
    assert time.time() - t0 < 60
    last = max(int(line[1:]) for line in vcd.read_text().splitlines() if line.startswith("#"))
    assert last // 10 <= 200 + traces.WATCHDOG_MARGIN + 10


# HL1's RQ3 amendment (miner-portfolio doc/plan/HL1_PLAN.md): depth variants of four designs.
BASE_GOLDEN_SHA256 = {  # seed 101, 300 cycles, $date removed; recorded before the variants were added
    "fifo_v3": "04470597f826713990e55ea872efaad0944fcfbd3810636e494449c4572c2307",
    "delta_counter": "211bc7011fc8eb7a971704bf0cc52bc33715191296dcc2b1c8ede4704406a850",
    "exp_backoff": "c7d3fa04a472dc62df48b723550db99482808ba9d0df3b91072d34dc8d2fa2a3",
    "credit_counter": "295a4b8cb867961e4d070f54299c97e52e7e552a8e3eb6bbc0c37b49d13c7a43",
}
VARIANTS = {"exp_backoff": ("H45_MAXEXP", (10, 14)), "delta_counter": ("H45_WIDTH", (10, 14)),
            "credit_counter": ("H45_NUMCREDITS", (16, 64)), "fifo_v3": ("H45_DEPTH", (16, 64))}


def _vcd_body(vcd: Path) -> bytes:
    out, skip = [], False
    for line in vcd.read_text().splitlines():
        if line.startswith("$date"):
            skip = True
        if not skip:
            out.append(line)
        if skip and "$end" in line:
            skip = False
    return "\n".join(out).encode()


def _corpus() -> tuple[Path, dict]:
    corpus = ROOT / "eval" / "mutants" / "corpus.json"
    return corpus.parent, {d["name"]: d for d in json.loads(corpus.read_text())}


def _build(d: dict, base: Path, out: Path) -> Path:
    extra = [f"+define+{x}" for x in d.get("defines", [])] + [f"-I{base / i}" for i in d.get("includes", [])]
    return traces.build([base / f for f in d["files"]] + [base / d["tb"]], "tb", out, extra)


# T5: each variant is a corpus entry with one more define and builds; the base entries' golden traces are unchanged
@needs_verilator
@pytest.mark.parametrize("name", sorted(VARIANTS))
def test_t5_depth_variants(tmp_path: Path, name: str) -> None:
    import hashlib
    base, entries = _corpus()
    if not (base / entries[name]["files"][0]).exists():
        pytest.skip("PULP common_cells not fetched (eval/mutants/fetch.sh)")
    vcd = traces.run(_build(entries[name], base, tmp_path / "base"), 101, 300, tmp_path / "base.vcd")
    assert hashlib.sha256(_vcd_body(vcd)).hexdigest() == BASE_GOLDEN_SHA256[name]
    define, depths = VARIANTS[name]
    for n in depths:
        v = entries[f"{name}_d{n}"]
        assert v["files"] == entries[name]["files"] and v["tb"] == entries[name]["tb"]
        assert v["defines"] == entries[name]["defines"] + [f"{define}={n}"]
        assert v["cycles"] >= entries[name]["cycles"]
        traces.run(_build(v, base, tmp_path / f"d{n}"), 101, 300, tmp_path / f"d{n}.vcd",
                   plusargs=[f"+watchdog={v['watchdog']}"] if v.get("watchdog") else [])


# T6: the watchdog margin is a plusarg (+watchdog=), 10000 cycles without it
@needs_verilator
def test_t6_watchdog_plusarg(tmp_path: Path) -> None:
    base, entries = _corpus()
    d = entries["exp_backoff"]
    files = [base / f for f in d["files"]]
    if not files[0].exists():
        pytest.skip("PULP common_cells not fetched (eval/mutants/fetch.sh)")
    incs = [str(base / i) for i in d["includes"]]
    site = next(s for s in mutate.sites(files, d["top"], d["defines"], incs) if s.id == "sa1-exp_backoff-cnt_q-b6")
    src = mutate.apply(site, files, tmp_path / "src")
    exe = traces.build(src + [base / d["tb"]], "tb", tmp_path / "build",
                       [f"+define+{x}" for x in d["defines"]] + [f"-I{i}" for i in incs])

    def last(vcd: Path) -> int:
        return max(int(line[1:]) for line in vcd.read_text().splitlines() if line.startswith("#")) // 10

    assert last(traces.run(exe, 101, 200, tmp_path / "a.vcd", plusargs=["+watchdog=500"])) <= 200 + 500 + 10
    assert 200 + 500 + 10 < last(traces.run(exe, 101, 200, tmp_path / "b.vcd")) <= 200 + 10000 + 10


# T16 (miner-portfolio HL1's RQ3 amendment 2): two more entries, lossy_valid_to_stream and stream_delay, where
# harm-deep's long-range relations between 1-bit state bits can matter. Each builds, its golden trace is the same on two
# runs of a seed and differs between seeds, and its directed phase stays inside the watchdog margin.
@needs_verilator
@pytest.mark.parametrize("name", ["lossy_valid_to_stream", "stream_delay"])
def test_t16_rq3_entries(tmp_path: Path, name: str) -> None:
    base, entries = _corpus()
    d = entries[name]
    if not (base / d["files"][0]).exists():
        pytest.skip("PULP common_cells not fetched (eval/mutants/fetch.sh)")
    assert d["top"] == f"h45_{name}" and d["reset"] == "!rst_ni" and d["cycles"] == 5000
    exe = _build(d, base, tmp_path / "b")
    a = _vcd_body(traces.run(exe, 101, 500, tmp_path / "a.vcd"))
    assert a == _vcd_body(traces.run(exe, 101, 500, tmp_path / "b.vcd"))
    assert a != _vcd_body(traces.run(exe, 102, 500, tmp_path / "c.vcd"))
    out = subprocess.run([str(exe), "+seed=101", "+cycles=500", f"+vcd={tmp_path / 'd.vcd'}"], capture_output=True,
                         text=True, check=True).stdout
    assert "H45 watchdog" not in out
