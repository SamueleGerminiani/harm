#!/usr/bin/env python3
"""H45-mutant-eval, T7: with --fd, --dump-assertion-info gives each assertion the fault traces it fails on.
Fixture tests/input/h45/faults: f1 breaks G({a} |-> b) only, f2 breaks G({a} |-> c) only, f3 breaks neither.
Usage: check_h45_faults.py <harm> <fixture dir>"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, fix = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve()
expected = {"G({a} |-> b)": ["ft/f1.csv"], "G({a} |-> c)": ["ft/f2.csv"]}
ok = True
for complete in (True, False):
    with tempfile.TemporaryDirectory() as d:
        info = Path(d) / "info.json"
        args = [harm, "--csv", "golden.csv", "--conf", "conf.xml", "--fd", "ft", "--max-threads", "1",
                "--psilent", "--dump-assertion-info", str(info)] + (["--find-min-subset"] if complete else [])
        r = subprocess.run(args, cwd=fix, capture_output=True, text=True)
        if r.returncode != 0 or not info.exists():
            print("HARM failed:", (r.stdout + r.stderr)[-2000:])
            sys.exit(1)
        recs = {a["text"]: a for a in json.loads(info.read_text())["assertions"]}
    if sorted(recs) != sorted(expected):
        print("assertions:", sorted(recs))
        ok = False
        continue
    for text, faults in expected.items():
        rec = recs[text]
        if rec.get("faultsComplete") is not complete:
            print(f"{text}: faultsComplete {rec.get('faultsComplete')!r}, expected {complete}")
            ok = False
        if complete and rec.get("faults") != faults:
            print(f"{text}: faults {rec.get('faults')!r}, expected {faults}")
            ok = False
        if not complete and not set(rec.get("faults", [None])) <= set(faults):
            print(f"{text}: faults {rec.get('faults')!r} not within {faults}")
            ok = False
    if complete:
        covered = sorted({f for rec in recs.values() for f in rec.get("faults", [])})
        if covered != ["ft/f1.csv", "ft/f2.csv"]:
            print("covered:", covered)
            ok = False
# without --fd the field is absent
with tempfile.TemporaryDirectory() as d:
    info = Path(d) / "info.json"
    subprocess.run([harm, "--csv", "golden.csv", "--conf", "conf.xml", "--max-threads", "1", "--psilent", "--isilent",
                    "--dump-assertion-info", str(info)], cwd=fix, capture_output=True, text=True)
    for a in json.loads(info.read_text())["assertions"]:
        if "faults" in a or "faultsComplete" in a:
            print("fault fields without --fd:", a["text"])
            ok = False
print("OK" if ok else "FAILED")
sys.exit(0 if ok else 1)
