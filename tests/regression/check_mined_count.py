#!/usr/bin/env python3
"""H12 A1 (finding F-M2): a design mines the same number of assertions on every platform.
The configuration is HARM's own (--generate-config), as in the evaluation's C0. The expected count is
Linux x86_64's (eval/results/linux-fixtures); before H12, macOS arm64 gave another one (structs: 1,800
instead of 1,839), because the compiler fused the decision-tree score (FMA).
Usage: check_mined_count.py <harm> <vcd> <scope> <expected count>
"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, vcd, scope, expected = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4])
trace = ["--vcd", vcd, "--clk", "clk", "--vcd-ss", scope, "--vcd-r", "1"]
with tempfile.TemporaryDirectory() as d:
    conf, info = Path(d) / "gen.xml", Path(d) / "info.json"
    r = subprocess.run([harm, *trace, "--conf", str(conf), "--generate-config", "--psilent", "--isilent"],
                       cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not conf.exists():
        sys.exit("--generate-config failed:\n" + r.stdout + r.stderr)
    r = subprocess.run([harm, *trace, "--conf", str(conf), "--max-threads", "1", "--psilent",
                        "--dump-assertion-info", str(info)], cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not info.exists():
        sys.exit("mining failed:\n" + r.stdout + r.stderr)
    got = len(json.loads(info.read_text())["assertions"])
if got != expected:
    sys.exit(f"FAIL: {got} assertions, expected {expected} (Linux x86_64)")
print(f"ok: {got} assertions")
