#!/usr/bin/env python3
"""H11c, F-L4 acceptance A2: a vector declared [1:10] in the VCD mines the same assertions as the
same values declared [9:0] (a VCD writes the left declared index first, so the bit strings are
identical). Usage: check_vcd_ranges.py <harm> <ranges.vcd>"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

harm, vcd = sys.argv[1], Path(sys.argv[2])


def mine(trace, d):
    conf = d / "conf.xml"
    subprocess.run([harm, "--vcd", str(trace), "--clk", "clk", "--vcd-ss", "tb", "--conf", str(conf),
                    "--generate-config", "--psilent", "--isilent"], cwd=d, capture_output=True)
    if not conf.exists():
        sys.exit(f"--generate-config failed on {trace.name}")
    dump = d / "out.txt"
    r = subprocess.run([harm, "--vcd", str(trace), "--clk", "clk", "--vcd-ss", "tb", "--conf", str(conf),
                        "--max-threads", "1", "--dump-to", str(dump), "--psilent", "--isilent"],
                       cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not dump.exists():
        sys.exit(f"HARM failed on {trace.name}:\n{re.sub(chr(27) + r'[[0-9;]*m', '', r.stdout + r.stderr)[-800:]}")
    return sorted(l for l in dump.read_text().splitlines() if l.strip())


with tempfile.TemporaryDirectory() as t:
    d = Path(t)
    desc = d / "desc.vcd"
    desc.write_text(vcd.read_text().replace("asc [1:10] $end", "asc [9:0] $end"))
    (d / "a").mkdir()
    (d / "b").mkdir()
    a, b = mine(vcd, d / "a"), mine(desc, d / "b")
    print(f"[1:10]: {len(a)} assertions, [9:0]: {len(b)} assertions")
    if a != b or not a:
        print("FAIL: the outputs differ" if a != b else "FAIL: nothing mined")
        sys.exit(1)
    print("PASS")
