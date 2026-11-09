#!/usr/bin/env python3
"""CR1 (the miner portfolio's correctness review): C7a-1, VCD times past 2^31 units are read exactly (they were parsed
with atoi); C7a-3, --dump-trace-as-csv keeps every character of a row's last column.
Usage: check_cr1_trace.py <harm> <vcd>
"""
import csv
import subprocess
import sys
import tempfile
from pathlib import Path

harm, vcd = sys.argv[1:3]
with tempfile.TemporaryDirectory() as d:
    out = Path(d) / "t.csv"
    r = subprocess.run([harm, "--vcd", vcd, "--clk", "clk", "--vcd-ss", "tb", "--dump-trace-as-csv", str(out),
                        "--psilent", "--isilent", "--max-threads", "1"], cwd=d, capture_output=True, text=True)
    if not out.exists():
        sys.exit(r.stdout + r.stderr)
    rows = list(csv.reader(out.read_text().splitlines()))
head = [h.split()[-1] for h in rows[0]]
d = [r[head.index("d")] for r in rows[1:]]
if d != ["0", "1", "1", "1", "1", "0"]:
    sys.exit(f"d sampled {d}, expected 0,1,1,1,1,0 (times past 2^31)")
last = [r[-1] for r in rows[1:]]
if head[-1] != "zz" or any(len(x) != 4 for x in last):  # zz, 4 bits, is the trace's last variable
    sys.exit(f"the last column lost a character: header {rows[0][-1]!r}, values {last}")
print("ok")
