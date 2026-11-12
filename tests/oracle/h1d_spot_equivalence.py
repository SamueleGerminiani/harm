#!/usr/bin/env python3
"""H1d, independent check of the printing fixes F7 and F8 with Spot's ltlfilt (not HARM's code).

F7: for each case of tests/printingTests.cc, the meaning of the SVA that HARM now prints, written
    by hand in Spot syntax ({s}[]-> p is SVA's s |-> p, {s}[]=> p is s |=> p; $past(p, k) at the
    end of s is p k cycles before that end), must be equivalent to HARM's formula. As a control,
    the meaning of the SVA printed before the fix must not be.
F8: each Spot string HARM now prints must parse to the intended formula; the old string must not.
Usage: h1d_spot_equivalence.py <ltlfilt>      (exit 0 if every check passes)
"""
import os
import subprocess
import sys
from pathlib import Path

ltlfilt = sys.argv[1]
env = dict(os.environ, DYLD_LIBRARY_PATH=str(Path(ltlfilt).resolve().parent.parent / "lib"),
           LD_LIBRARY_PATH=str(Path(ltlfilt).resolve().parent.parent / "lib"))


def equivalent(f, g):
    r = subprocess.run([ltlfilt, "-f", f, "--equivalent-to", g], capture_output=True, text=True, env=env)
    if r.returncode not in (0, 1) or "error" in r.stderr.lower():
        sys.exit(f"ltlfilt failed on {f} / {g}: {r.stderr}")
    return r.returncode == 0 and r.stdout.strip() != ""


# HARM formula (Spot syntax), meaning of the new SVA, meaning of the old SVA
F7 = [
    ("G({a;b} -> X w)", "G({a;b} []-> w)", "G({a;b} []=> w)"),             # a ##1 b |-> w (was |=>)
    ("G({a;b} -> X X w)", "G({a;b} []=> w)", "G({a;b} []-> X X w)"),       # |=> (was |-> ##2)
    ("G({a;b;e} -> X X X w)", "G({a;b;e} []=> w)", "G({a;b;e} []-> X X X w)"),
    ("G({a;b} -> X X X w)", "G({a;b} []-> X X w)", "G({a;b} []-> X X X w)"),  # |-> ##2 (was ##3)
    ("G({a;b} -> w)", "G(a && X b -> w)", "G({a;b} []-> w)"),              # $past(w, 1) (was |-> w)
    ("G({a;1;b} -> X w)", "G(a && X X b -> X w)", "G({a;1;b} []=> w)"),    # a ##2 b |-> $past(w, 1)
]
# string HARM prints now, intended formula, string printed before
F8 = [
    ("G(a -> X(b && e))", "G(a -> X(b & e))", "G(a -> Xb && e)"),
    ("G(a -> X(b || e))", "G(a -> X(b | e))", "G(a -> Xb || e)"),
    ("G((a || b) && Xe -> w)", "G(((a | b) & X e) -> w)", "G(a || b && Xe -> w)"),
]

ok = True
for harm, new, old in F7:
    good, control = equivalent(harm, new), not equivalent(harm, old)
    print(f"F7 {harm:24} new SVA {'equivalent' if good else 'NOT EQUIVALENT'}; "
          f"old SVA {'differs (control ok)' if control else 'EQUIVALENT (control fails)'}")
    ok &= good and control
for printed, intended, old in F8:
    good, control = equivalent(printed, intended), not equivalent(old, intended)
    print(f"F8 {printed:24} {'parses as intended' if good else 'DOES NOT parse as intended'}; "
          f"old string {'differs (control ok)' if control else 'SAME (control fails)'}")
    ok &= good and control
print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
