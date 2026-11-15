#!/usr/bin/env python3
"""H48-none-arm, T7: the fault check (--fd) runs on --max-threads threads and gives the same --dump-assertion-info
as on one thread, with and without --find-min-subset.
Fixture tests/input/h45/faults (f1 breaks G({a} |-> b), f2 breaks G({a} |-> c), f3 neither), its three fault traces
copied 8 times each, interleaved, so that the threads' shares hold every kind.
Usage: check_h48_parallel_fd.py <harm> <fixture dir>"""
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

harm, fix = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve()
ok = True
with tempfile.TemporaryDirectory() as d:
    d = Path(d)
    ft = d / "ft"
    ft.mkdir()
    for i in range(24):
        shutil.copy(fix / "ft" / f"f{i % 3 + 1}.csv", ft / f"f{i:02d}_{i % 3 + 1}.csv")
    for complete in (True, False):
        out = {}
        for threads in (1, 4):
            info = d / f"info{threads}.json"
            args = [harm, "--csv", str(fix / "golden.csv"), "--conf", str(fix / "conf.xml"), "--fd", str(ft),
                    "--max-threads", str(threads), "--psilent", "--dump-assertion-info", str(info)]
            args += ["--find-min-subset"] if complete else []
            r = subprocess.run(args, cwd=d, capture_output=True, text=True)
            log = re.sub(r"\x1b\[[0-9;]*m", "", r.stdout + r.stderr)
            if r.returncode != 0 or not info.exists():
                print("HARM failed:", log[-2000:])
                sys.exit(1)
            m = re.search(r"Fault check on (\d+) threads", log)
            if not m or int(m.group(1)) != threads:
                print(f"--max-threads {threads}: no 'Fault check on {threads} threads' message")
                ok = False
            out[threads] = json.loads(info.read_text())["assertions"]
        if out[1] != out[4]:
            print(f"find-min-subset={complete}: one thread and four threads differ")
            print(json.dumps(out[1], indent=1)[:1500])
            print(json.dumps(out[4], indent=1)[:1500])
            ok = False
        if complete:
            b = {a["text"]: a["faults"] for a in out[1]}
            if [Path(f).name for f in b.get("G({a} |-> b)", [])] != [f"f{i:02d}_1.csv" for i in range(0, 24, 3)]:
                print("G({a} |-> b):", b.get("G({a} |-> b)"))
                ok = False
print("OK" if ok else "FAILED")
sys.exit(0 if ok else 1)
