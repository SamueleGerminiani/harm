#!/usr/bin/env python3
"""H11e acceptance A2: a fixture testbench's stimulus does not depend on the simulator.

The testbench is built with Verilator (the fixture's build.sh) and with Icarus, and the values of
the signals the testbench drives (assignment targets in tb.sv, except the clock) are compared at
every rising clock edge. They must be equal: the stimulus comes from tests/input/stim.svh, not
from a simulator's own $urandom (finding F-L7).
Usage: check_stim.py <fixture dir> [--iverilog <bin>]"""
import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

INPUT = Path(__file__).resolve().parent.parent / "input"


def driven(tb):
    """names the testbench assigns (blocking or non-blocking), except clk"""
    names = set(re.findall(r"(?:^|;)\s*(?:\{([^}]*)\}|(\w+))\s*<?=(?!=)", tb.read_text(), re.M))
    out = set()
    for group, name in names:
        out |= {n.strip() for n in group.split(",")} if group else {name}
    return {n for n in out if n and n != "clk" and not n.startswith("seed")}


def samples(vcd, names):
    """value of each tb-level signal in names at every rising edge of tb.clk"""
    ids, scope, cur, rows, clk = {}, [], {}, [], None
    for line in vcd.read_text().splitlines():
        w = line.split()
        if not w:
            continue
        if w[0] == "$scope":
            scope.append(w[2])
        elif w[0] == "$upscope":
            scope.pop()
        elif w[0] == "$var" and scope == ["tb"] and (w[4] in names or w[4] == "clk"):
            ids.setdefault(w[3], []).append(w[4])
        elif w[0][0] in "01xzXZ" and len(w) == 1 and w[0][1:] in ids:
            for n in ids[w[0][1:]]:
                if n == "clk":
                    if clk == "0" and w[0][0] == "1":
                        rows.append(dict(cur))
                    clk = w[0][0]
                else:
                    cur[n] = w[0][0]
        elif w[0][0] in "bB" and len(w) == 2 and w[1] in ids:
            for n in ids[w[1]]:
                cur[n] = w[0][1:].lstrip("0") or "0"
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("fixture")
    ap.add_argument("--iverilog", default="iverilog")
    a = ap.parse_args()
    fx = Path(a.fixture).resolve()
    names = driven(fx / "tb.sv")
    with tempfile.TemporaryDirectory() as t:
        d = Path(t)
        r = subprocess.run(["bash", str(fx / "build.sh"), str(d / "v"), "trace.vcd"], capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(f"Verilator build failed:\n{r.stdout[-800:]}{r.stderr[-800:]}")
        iv = d / "i"
        iv.mkdir()
        r = subprocess.run([a.iverilog, "-g2012", f"-I{INPUT}", '-DVCD="trace.vcd"', "-o", str(iv / "sim"),
                            *map(str, sorted((fx / "rtl").glob("*.sv"))), str(fx / "tb.sv")],
                           capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(f"Icarus build failed:\n{r.stdout[-800:]}{r.stderr[-800:]}")
        r = subprocess.run(["vvp", str(iv / "sim")], cwd=iv, capture_output=True, text=True)
        if r.returncode != 0 or not (iv / "trace.vcd").exists():
            sys.exit(f"Icarus run failed:\n{r.stdout[-800:]}{r.stderr[-800:]}")
        a_rows, b_rows = samples(d / "v" / "trace.vcd", names), samples(iv / "trace.vcd", names)
    n = min(len(a_rows), len(b_rows))
    print(f"[{fx.name}] driven signals {sorted(names)}; {len(a_rows)} Verilator / {len(b_rows)} Icarus edges")
    if n < 50:
        sys.exit("FAIL: too few clock edges")
    for i in range(n):
        if a_rows[i] != b_rows[i]:
            print(f"FAIL: edge {i}: Verilator {a_rows[i]} vs Icarus {b_rows[i]}")
            sys.exit(1)
    print("PASS: the same stimulus on both simulators")


if __name__ == "__main__":
    main()
