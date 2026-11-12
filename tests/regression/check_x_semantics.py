#!/usr/bin/env python3
"""H1b (D-011 option a): pin HARM's documented x/z semantics (README, "x and z values").

Each proposition of tests/input/h1b/x_values.xml with HARM's value (on both rows of the trace) and
the SystemVerilog value (IEEE 1800-2017 §11.4.4, §11.4.5, §11.4.7, §16.6; checked with iverilog 12),
written by hand. HARM must mine G(p) exactly for the propositions whose HARM value is true.
Usage: check_x_semantics.py <harm> <csv> <config>
"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

# proposition: (HARM, SystemVerilog)   with a=10x1 b=1001 c=0001 p=x v=01x0 w=00x0
CASES = {
    "a == b": (False, "x"), "a != b": (False, "x"), "!(a == b)": (True, "x"),
    "a == c": (False, "0"), "a != c": (False, "1"), "!(a == c)": (True, "1"),
    "a < c": (False, "x"), "!(a < c)": (True, "x"),
    "a === b": (False, "0"), "a !== b": (True, "1"),
    "p": (False, "x"), "!p": (True, "x"), "p || !p": (True, "x"),
    "p && 1'b0": (False, "0"), "p || 1'b1": (True, "1"),
    "v": (True, "1"), "!v": (False, "0"), "v != 4'b0": (False, "1"),
    "w": (False, "x"), "!w": (True, "x"), "!(w == 4'b0)": (True, "x"),
    "a[1]": (False, "x"), "!a[1]": (True, "x"),
}


def norm(t):
    return t.replace(" ", "").replace("4'b0", "4'b0")


harm, csv, conf = sys.argv[1:4]
with tempfile.TemporaryDirectory() as d:
    info = Path(d) / "info.json"
    r = subprocess.run([harm, "--csv", csv, "--conf", conf, "--max-threads", "1", "--psilent", "--isilent",
                        "--dump-assertion-info", str(info)], cwd=d, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(r.stdout + r.stderr)
    mined = {norm(a["text"][2:-1]) for a in json.loads(info.read_text())["assertions"]}
ok, gap = True, 0
for p, (h, sv) in CASES.items():
    got = norm(p) in mined
    if got != h:
        ok = False
        print(f"  {p}: HARM gives {got}, documented {h}")
    gap += h != (sv == "1")
print(f"{len(CASES)} propositions; HARM differs from SystemVerilog on {gap} (documented)")
print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
