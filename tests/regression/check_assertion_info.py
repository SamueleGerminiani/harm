#!/usr/bin/env python3
"""H6, A4: compare --dump-assertion-info values with a hand-derived expectation.
Usage: check_assertion_info.py <harm> <expected.txt> <harm args...>"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, expected_file, args = sys.argv[1], sys.argv[2], sys.argv[3:]
expected = {}
for line in Path(expected_file).read_text().splitlines():
    if line.strip() and not line.startswith("#"):
        text, frac, fit, unknown = [x.strip() for x in line.split("|")]
        expected[text] = (float(frac), float(fit), int(unknown))
with tempfile.TemporaryDirectory() as d:
    info = Path(d) / "info.json"
    r = subprocess.run([harm] + args + ["--max-threads", "1", "--psilent", "--isilent",
                                        "--dump-assertion-info", str(info)],
                       cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not info.exists():
        print("HARM failed:", (r.stdout + r.stderr)[-2000:])
        sys.exit(1)
    records = json.loads(info.read_text())["assertions"]
got = {rec["text"]: (rec["metrics"]["coiFrac"], rec["metrics"]["coiDepthFit"],
                     int(rec["metrics"]["coiUnknown"])) for rec in records}
ok = True
for text, values in expected.items():
    if text not in got:
        print(f"MISSING: {text}")
        ok = False
    elif got[text] != values:
        print(f"WRONG: {text}: expected {values}, got {got[text]}")
        ok = False
for text in got:
    if text not in expected:
        print(f"UNEXPECTED: {text} {got[text]}")
        ok = False
print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
