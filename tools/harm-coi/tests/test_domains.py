"""H35 tests (`--domains`, D-043): the clock-domain map of a design. Every expected map is written by hand from the
fixture's RTL (tests/input/mc):
  - a domain is a clock root (followed back through wires and ports), with every register it clocks, on either edge;
  - a derived clock (driven by logic or a register) is a domain of its own, `from` the domains it is made from;
  - a crossing is a register of another domain that reaches a domain's register through wires and logic;
  - a synchronizer is a register fed only by a foreign register through wires, followed by a register fed only by it;
  - a domain's resets are the asynchronous controls of its registers, followed back to their roots.
T1 the four fixtures' maps; T2 single-clock designs: one domain, and coi.json unchanged by --domains; T3 --reset gives
the resets each domain reads; T4 determinism."""
import json
import os
import subprocess
import sys
from pathlib import Path

import pytest

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
SRC = Path(__file__).resolve().parents[1] / "src"
MC = ROOT / "tests" / "input" / "mc"


def dom(name, edges=("pos",), registers=(), resets=(), derived=False, frm=(), reads=()):
    return {"name": name, "edges": list(edges), "derived": derived, "from": list(frm), "registers": list(registers),
            "resets": list(resets), "reads_resets": list(reads)}


EXPECTED = {
    "two_counters": {
        "clocks": [dom("clk_a", ("neg", "pos"), ["cnt_a", "neg_a", "wrap_a"], ["rst_a"]),
                   dom("clk_b", ("pos",), ["cnt_b", "wrap_b"], ["rst_b"])],
        "crossings": [], "synchronizers": [], "unclocked": []},
    "cdc_fifo": {
        "clocks": [dom("rclk", ("pos",), ["rbin", "rdata", "rempty", "rptr", "u_w2r::q", "u_w2r::q1"], ["rrst_n"]),
                   dom("wclk", ("pos",), ["mem0", "mem1", "mem2", "mem3", "u_r2w::q", "u_r2w::q1", "wbin", "wfull",
                                          "wptr"], ["wrst_n"])],
        "crossings": [  # sorted by (to, into, signal)
            {"signal": "mem0", "from": "wclk", "to": "rclk", "into": "rdata"},
            {"signal": "mem1", "from": "wclk", "to": "rclk", "into": "rdata"},
            {"signal": "mem2", "from": "wclk", "to": "rclk", "into": "rdata"},
            {"signal": "mem3", "from": "wclk", "to": "rclk", "into": "rdata"},
            {"signal": "wptr", "from": "wclk", "to": "rclk", "into": "u_w2r::q1"},
            {"signal": "rptr", "from": "rclk", "to": "wclk", "into": "u_r2w::q1"}],
        "synchronizers": [{"clock": "rclk", "from": "wptr", "first": "u_w2r::q1", "second": "u_w2r::q"},
                          {"clock": "wclk", "from": "rptr", "first": "u_r2w::q1", "second": "u_r2w::q"}],
        "unclocked": []},
    "derived": {
        "clocks": [dom("clk", ("pos",), ["clk_div2", "fast"]),
                   dom("clk_div2", ("pos",), ["slow"], derived=True, frm=["clk"]),
                   dom("gclk", ("pos",), ["gated"], derived=True, frm=["clk"])],
        "crossings": [], "synchronizers": [], "unclocked": []},
    "raw_cross": {
        "clocks": [dom("clk_a", ("pos",), ["flag_a"]),
                   dom("clk_b", ("pos",), ["cnt_b", "hit_b", "seen_b"])],
        "crossings": [{"signal": "flag_a", "from": "clk_a", "to": "clk_b", "into": "hit_b"},
                      {"signal": "flag_a", "from": "clk_a", "to": "clk_b", "into": "seen_b"}],
        "synchronizers": [],  # seen_b is a single flop: cnt_b reads it with rst, so no second stage
        "unclocked": []},
}
SINGLE = {"counter": "coi", "arbiter": "coi", "fsm": "coi", "hier": "coi", "multipath": "coi", "structs": "coi",
          "constructs": "h5"}


def base(d, top):
    return ["--top", top, "--files", *map(str, sorted((d / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
            "--vcd-recursion", "2"]


def domains(tmp_path, name, *extra):
    out = tmp_path / f"{name}_domains.json"
    assert cli.main([*base(MC / name, name), "--domains", str(out), *extra]) == 0
    return json.loads(out.read_text())


# T1: the four fixtures' maps (no --clock and no -o: a design with several clocks is mapped, not refused)
@pytest.mark.parametrize("name", sorted(EXPECTED))
def test_t1_maps(tmp_path, name):
    doc = domains(tmp_path, name)
    assert doc.pop("version") == "1"
    assert doc.pop("top") == name
    assert doc == EXPECTED[name]


# T2: a single-clock design is one domain, and adding --domains changes nothing else
@pytest.mark.parametrize("name", sorted(SINGLE))
def test_t2_single_clock(tmp_path, name):
    d = ROOT / "tests" / "input" / SINGLE[name] / name
    meta = next(p for p in (d / "meta.txt", d / "edges.txt") if p.exists()).read_text()
    top = next(l.split("=", 1)[1].strip() for l in meta.splitlines() if l.startswith("top ="))
    rec = next(l.split("=", 1)[1].strip() for l in meta.splitlines() if l.startswith("vcd_recursion ="))
    args = ["--top", top, "--files", *map(str, sorted((d / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
            "--vcd-recursion", rec, "--vcd", str(d / "trace.vcd"), "--clock", "clk"]
    assert cli.main([*args, "-o", str(tmp_path / "plain.json")]) == 0
    assert cli.main([*args, "-o", str(tmp_path / "with.json"), "--domains", str(tmp_path / "d.json")]) == 0
    assert (tmp_path / "plain.json").read_bytes() == (tmp_path / "with.json").read_bytes()
    doc = json.loads((tmp_path / "d.json").read_text())
    assert [c["name"] for c in doc["clocks"]] == ["clk"] and not doc["crossings"] and not doc["synchronizers"]


# T3: --reset names the resets each domain reads (asynchronously or in its logic), for D2's choice
def test_t3_reads_resets(tmp_path):
    doc = domains(tmp_path, "two_counters", "--reset", "rst_a", "--reset", "rst_b")
    assert {c["name"]: c["reads_resets"] for c in doc["clocks"]} == {"clk_a": ["rst_a"], "clk_b": ["rst_b"]}
    doc = domains(tmp_path, "derived", "--reset", "rst")
    assert {c["name"]: c["reads_resets"] for c in doc["clocks"]} == {"clk": ["rst"], "clk_div2": ["rst"],
                                                                      "gclk": ["rst"]}
    doc = domains(tmp_path, "cdc_fifo", "--reset", "!wrst_n")
    assert {c["name"]: c["reads_resets"] for c in doc["clocks"]} == {"rclk": [], "wclk": ["wrst_n"]}


# T4: the same bytes under two hash seeds
def test_t4_deterministic(tmp_path):
    outs = []
    for seed in ("1", "2"):
        out = tmp_path / f"{seed}.json"
        cmd = [sys.executable, "-m", "harm_coi", *base(MC / "cdc_fifo", "cdc_fifo"), "--domains", str(out)]
        r = subprocess.run(cmd, capture_output=True, text=True,
                           env={**os.environ, "PYTHONHASHSEED": seed, "PYTHONPATH": str(SRC)})
        assert r.returncode == 0, r.stderr
        outs.append(out.read_bytes())
    assert outs[0] == outs[1]
