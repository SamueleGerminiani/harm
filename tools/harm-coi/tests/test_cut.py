"""H36 tests (`--cut-domains`, D-044): mine one clock domain of a design with several. Without the flag, a register on
another clock is `unknown`, which HARM treats as in every cone (D-017, D-019): its propositions are mined on the
sampling clock (two_counters on clk_a gave `... ##1 en_a |-> cnt_b == 4'b0`). With it, every signal of another domain
is cut: no target, no source, no predicate, no hint, no relation, and the cones stop at it (the miner portfolio's
MC1, the user's D1: a domain reads no other domain's register). Cut: the other domains' registers, the other clocks,
the top inputs read only by other domains, and the signals computed only from those.
T1 two_counters on clk_a; T2 cdc_fifo on rclk (its synchronizer registers are mined targets); T3 without the flag
and on single-clock designs nothing changes; T4 determinism."""
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import pytest

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
SRC = Path(__file__).resolve().parents[1] / "src"
MC = ROOT / "tests" / "input" / "mc"
PROP = re.compile(r'<prop exp="([^"]*)"')
WORD = re.compile(r"[A-Za-z_][\w:]*")
UNESC = {"&amp;": "&", "&lt;": "<", "&gt;": ">", "&quot;": '"'}
SINGLE = {"counter": "coi", "arbiter": "coi", "fsm": "coi", "hier": "coi", "multipath": "coi", "structs": "coi",
          "constructs": "h5"}


def un(s):
    for k, v in UNESC.items():
        s = s.replace(k, v)
    return s


def meta(d):
    text = next(p for p in (d / "meta.txt", d / "edges.txt") if p.exists()).read_text()
    return {l.split("=", 1)[0].strip(): l.split("=", 1)[1].strip() for l in text.splitlines() if "=" in l}


def run(tmp_path, d, *extra, tag="out", clock=None):
    m = meta(d)
    out, xml, hints = tmp_path / f"{tag}_coi.json", tmp_path / f"{tag}.xml", tmp_path / f"{tag}_hints.json"
    args = ["--top", m["top"], "--files", *map(str, sorted((d / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
            "--vcd-recursion", m["vcd_recursion"], "--vcd", str(d / "trace.vcd"), "--clock", clock or m["clock"],
            "--emit-config", str(xml), "--hints", str(hints), "--relations", "-o", str(out), *extra]
    assert cli.main(args) == 0
    return json.loads(out.read_text()), xml.read_text(), json.loads(hints.read_text())


def named(doc, xml, hints):
    """Every name in the targets, sources, unknown list, propositions and hints."""
    names = set(doc["targets"]) | set(doc["unknown"])
    names |= {s["sig"] for t in doc["targets"].values() for s in t["sources"]}
    names |= {w for p in PROP.findall(xml) for w in WORD.findall(un(p))}
    names |= {w for w in WORD.findall(json.dumps(hints))}
    return names


# T1: two_counters mined on clk_a: nothing of clk_b's domain remains
def test_t1_two_counters(tmp_path):
    doc, xml, hints = run(tmp_path, MC / "two_counters", "--cut-domains")
    clk_b = {"clk_b", "cnt_b", "wrap_b", "en_b", "rst_b"}
    assert doc["cut"] == sorted(clk_b)
    assert not named(doc, xml, hints) & clk_b
    assert {"cnt_a", "wrap_a", "neg_a"} <= set(doc["targets"]) and not doc["unknown"]


# T2: cdc_fifo mined on rclk: the write side is cut, the read side's synchronizer and logic are mined
def test_t2_cdc_fifo(tmp_path):
    doc, xml, hints = run(tmp_path, MC / "cdc_fifo", "--cut-domains", "--aliases")
    write_side = {"mem0", "mem1", "mem2", "mem3", "wbin", "wfull", "wptr", "u_r2w::q", "u_r2w::q1", "wclk", "winc",
                  "wdata", "wrst_n", "wbin_next", "wq2_rptr", "u_w2r::d"}
    read_side = {"rbin", "rptr", "rempty", "rdata", "u_w2r::q", "u_w2r::q1"}
    assert write_side <= set(doc["cut"]) and not read_side & set(doc["cut"])
    assert not named(doc, xml, hints) & write_side
    assert read_side <= set(doc["targets"]), sorted(set(doc["unknown"]) & read_side)   # today: all unknown


# T3: without the flag nothing changes; with it, a single-clock design gives the same bytes as without it
def test_t3_without_flag(tmp_path):
    doc, _, _ = run(tmp_path, MC / "two_counters")
    assert "cut" not in doc and {"cnt_b", "wrap_b"} <= set(doc["unknown"])


@pytest.mark.parametrize("name", sorted(SINGLE))
def test_t3_single_clock(tmp_path, name):
    d = ROOT / "tests" / "input" / SINGLE[name] / name
    a = run(tmp_path, d, tag="off", clock="clk")
    b = run(tmp_path, d, "--cut-domains", tag="on", clock="clk")
    assert a[0] == b[0] and a[2] == b[2]
    assert a[1] == b[1].replace('file="on_coi.json"', 'file="off_coi.json"')


# T4: the same bytes under two hash seeds
def test_t4_deterministic(tmp_path):
    outs = []
    for seed in ("1", "2"):
        d = tmp_path / seed
        d.mkdir()
        m = meta(MC / "cdc_fifo")
        cmd = [sys.executable, "-m", "harm_coi", "--top", "cdc_fifo", "--files",
               *map(str, sorted((MC / "cdc_fifo" / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
               "--vcd-recursion", m["vcd_recursion"], "--vcd", str(MC / "cdc_fifo" / "trace.vcd"), "--clock", "rclk",
               "--cut-domains", "--relations", "--emit-config", "c.xml", "--hints", "h.json", "-o", "coi.json"]
        r = subprocess.run(cmd, cwd=d, capture_output=True, text=True,
                           env={**os.environ, "PYTHONHASHSEED": seed, "PYTHONPATH": str(SRC)})
        assert r.returncode == 0, r.stderr
        outs.append([(d / f).read_bytes() for f in ("coi.json", "c.xml", "h.json")])
    assert outs[0] == outs[1]
