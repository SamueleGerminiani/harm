#!/usr/bin/env python3
"""H3, A3: compare --dump-implications with a hand-derived expectation.
Usage: check_implications.py <harm> <expected.txt> <harm args...>"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, expected_file, args = sys.argv[1], sys.argv[2], sys.argv[3:]
expected = {}
for line in Path(expected_file).read_text().splitlines():
    if line.strip() and not line.startswith("#"):
        dropped, kept = [x.strip() for x in line.split("|||")]
        expected[dropped] = sorted(k.strip() for k in kept.split(","))
with tempfile.TemporaryDirectory() as d:
    out = Path(d) / "impl.json"
    r = subprocess.run([harm] + args + ["--max-threads", "1", "--psilent", "--isilent",
                                        "--reduce", "implies", "--dump-implications", str(out)],
                       cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not out.exists():
        print("HARM failed:", (r.stdout + r.stderr)[-2000:])
        sys.exit(1)
    got = {rec["dropped"]: sorted(rec["kept"]) for rec in json.loads(out.read_text())["implications"]}
ok = got == expected
for k in sorted(set(got) | set(expected)):
    if got.get(k) != expected.get(k):
        print(f"DIFF {k}: expected {expected.get(k)}, got {got.get(k)}")
print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
