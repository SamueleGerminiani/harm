#!/usr/bin/env python3
"""H45-mutant-eval amendment, T11: with --fd, a fault trace of another length than the mining trace is checked over
its own length (an assertion is switched to the fault trace with the trace's length, cuts and caches), with one
mining trace (--csv) and with a directory of them (--csv-dir: cuts).
Fixture tests/input/h45/lengths: ft/long.csv (40 rows) breaks G({a} |-> b) only at row 37, past the mining trace's
length; ft/short.csv (4 rows) breaks G({a} |-> c) only; ft/ok.csv breaks neither.
Usage: check_h45_lengths.py <harm> <fixture dir>"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, fix = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve()
expected = {"G({a} |-> b)": ["ft/long.csv"], "G({a} |-> c)": ["ft/short.csv"]}
ok = True
for mining in (["--csv", "golden.csv"], ["--csv-dir", "gdir"]):
    with tempfile.TemporaryDirectory() as d:
        info = Path(d) / "info.json"
        args = [harm, *mining, "--conf", "conf.xml", "--fd", "ft", "--find-min-subset", "--max-threads", "2",
                "--psilent", "--dump-assertion-info", str(info)]
        r = subprocess.run(args, cwd=fix, capture_output=True, text=True)
        if r.returncode != 0 or not info.exists():
            print(mining, f"HARM failed (exit {r.returncode}):", (r.stdout + r.stderr)[-1500:])
            ok = False
            continue
        recs = {a["text"]: a for a in json.loads(info.read_text())["assertions"]}
    if sorted(recs) != sorted(expected):
        print(mining, "assertions:", sorted(recs))
        ok = False
        continue
    for text, faults in expected.items():
        if recs[text].get("faults") != faults:
            print(mining, f"{text}: faults {recs[text].get('faults')!r}, expected {faults}")
            ok = False
print("OK" if ok else "FAILED")
sys.exit(0 if ok else 1)
