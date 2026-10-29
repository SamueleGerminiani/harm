#!/usr/bin/env python3
"""H39 T2: the implication step's result is unchanged by H39's faster reduction. For each fixture and
mode below, the kept assertions (in order) and --dump-implications' records equal the files written
at H38 (tests/input/h39/reduce_<case>.json, by --write).
Usage: check_reduce_same.py <harm> <tests/input> [--write]
"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, inp = sys.argv[1], Path(sys.argv[2])
write = "--write" in sys.argv[3:]
CASES = {
    "h29": ("h29", []),
    "h3": ("h3", []),
    "h3_weaker": ("h3", ["--keep", "weaker"]),
    "h3_ranked": ("h3", ["--keep", "ranked"]),
    "h3b_premises": ("h3b", ["--atom-premises"]),
    "h29_premises": ("h29", ["--atom-premises"]),
}


def run(fixture, extra):
    with tempfile.TemporaryDirectory() as d:
        r = subprocess.run([harm, "--csv", str(inp / fixture / "reduce.csv"), "--conf", str(inp / fixture / "reduce.xml"),
                            "--max-threads", "1", "--psilent", "--reduce", "implies", "--dump-implications", "imp.json",
                            "--dump-assertion-info", "info.json", *extra], cwd=d, capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(r.stdout + r.stderr)
        info = json.loads((Path(d) / "info.json").read_text())
        imp = json.loads((Path(d) / "imp.json").read_text()) if (Path(d) / "imp.json").exists() else {}
        return {"kept": [a["text"] for a in info["assertions"]], "implications": imp.get("implications", [])}


ok = True
for name, (fixture, extra) in CASES.items():
    got = run(fixture, extra)
    f = inp / "h39" / f"reduce_{name}.json"
    if write:
        f.write_text(json.dumps(got, indent=1) + "\n")
        print(f"{name}: written, {len(got['kept'])} kept, {len(got['implications'])} dropped")
        continue
    want = json.loads(f.read_text())
    same = got == want
    print(f"{name}: {'same' if same else 'DIFFERENT'} ({len(got['kept'])} kept, {len(got['implications'])} dropped)")
    ok &= same
print("OK" if ok else "FAIL")
sys.exit(0 if ok else 1)
