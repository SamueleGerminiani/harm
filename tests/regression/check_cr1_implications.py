#!/usr/bin/env python3
"""CR1 (the miner portfolio's correctness review, C7b-4): every record of --dump-implications names what it was dropped
for: an assertion dropped as equivalent to a class representative that was itself dropped by an implication names
the kept assertions that implied the representative.
Usage: check_cr1_implications.py <harm> <vcd> <config> <assertions>
"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, vcd, conf, ass = sys.argv[1:5]
with tempfile.TemporaryDirectory() as d:
    imp = Path(d) / "imp.json"
    r = subprocess.run([harm, "--vcd", vcd, "--clk", "clk", "--vcd-ss", "tb::dut", "--conf", conf, "--include-ass", ass,
                        "--reduce", "implies", "--atom-premises", "--dump-implications", str(imp), "--psilent",
                        "--isilent", "--max-threads", "1"], cwd=d, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(r.stdout + r.stderr)
    recs = json.loads(imp.read_text())["implications"]
empty = [x["dropped"] for x in recs if not x["kept"]]
if empty:
    sys.exit(f"records with no kept assertion: {empty}")
eq = next((x for x in recs if x["dropped"] == "G({a} |-> !c || b)"), None)
if eq is None or eq["kept"] != ["G({a} |-> b)"]:
    sys.exit(f"G({{a}} |-> !c || b): expected kept [G({{a}} |-> b)], got {eq}")
print("ok")
