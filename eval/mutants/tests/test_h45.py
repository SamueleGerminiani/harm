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
