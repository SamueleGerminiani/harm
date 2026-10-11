#!/usr/bin/env python3
"""H22 B4: an independent check of harm-coi's hints (hints v1, D-036), from coi.json alone.

Written from the H22 plan, not from harm-coi's code. What coi.json cannot tell (a top input port from a
parameter, which input is a reset) is taken from hints.json, but only among the signals coi.json shows to be
free (no sources); everything else is recomputed:
  - free (input, reset, const, clock) <=> a target without sources, not unknown; clock <=> its last name is the clock;
  - unknown <=> listed as unknown;
  - comb <=> some source that is not a reset has depth 0 in its cone; state otherwise;
  - a predicate may be a consequent <=> it reads a comb, state or unknown signal; its classes are theirs
    (unknown counts as comb); its loc has c and the classes' domains then, and is "a, dt" otherwise;
  - each class lists exactly the targets of its roles.

  hints_oracle.py COI.json HINTS.json      exit 1 and a line per disagreement"""
import json
import re
import sys

FREE = {"input", "reset", "const", "clock"}
_LIT = re.compile(r"\d+'[bdhoBDHO][0-9a-fA-FxzXZ_]+")
_TOKEN = re.compile(r"[A-Za-z_][A-Za-z0-9_$]*(?:\[[0-9]+\])?(?:::[A-Za-z_][A-Za-z0-9_$]*(?:\[[0-9]+\])?)*")


def signals(expr, names):
    """the visible signals an expression reads: tokens that are names, or names with a bit select"""
    out = set()
    for tok in _TOKEN.findall(_LIT.sub(" ", expr)):
        if tok in names:
            out.add(tok)
        elif re.sub(r"\[[0-9]+\]$", "", tok) in names:
            out.add(re.sub(r"\[[0-9]+\]$", "", tok))
    return out


def check(coi, hints):
    bad = []
    t, unknown = coi["targets"], set(coi["unknown"])
    clock = coi["meta"]["clock"]
    roles = {k: v["role"] for k, v in hints["roles"].items()}
    names = set(t) | unknown
    if set(roles) != names:
        bad.append(f"roles for {sorted(set(roles) ^ names)}: expected exactly coi.json's signals")
    resets = {k for k, r in roles.items() if r == "reset"}
    want = {}
    for k in sorted(names):
        if k in unknown:
            want[k] = "unknown"
        elif not t[k]["sources"]:
            want[k] = "clock" if k.split("::")[-1] == clock else roles.get(k) if roles.get(k) in FREE - {"clock"} else "free"
        elif any(0 in s["depths"] and s["sig"] not in resets for s in t[k]["sources"]):
            want[k] = "comb"
        else:
            want[k] = "state"
    for k, w in want.items():
        if roles.get(k) != w:
            bad.append(f"role of {k}: {roles.get(k)}, expected {w}")
    cls = {"comb": "comb", "unknown": "comb", "state": "state"}
    for c, d in hints["classes"].items():
        exp = sorted(k for k, w in want.items() if cls.get(w) == c)
        if sorted(d["targets"]) != exp:
            bad.append(f"class {c}: targets {d['targets']}, expected {exp}")
    dom = {c: str(d["domain"]) for c, d in hints["classes"].items()}
    props = {p["expr"]: p for p in hints["propositions"]}
    for p in coi.get("predicates", []):
        h = props.get(p["expr"])
        if h is None:
            bad.append(f"predicate {p['expr']!r} has no placement")
            continue
        sig = signals(p["expr"], names)
        if sorted(sig) != sorted(h["signals"]):
            bad.append(f"{p['expr']!r} reads {sorted(sig)}, hints say {h['signals']}")
        classes = sorted({cls[want[s]] for s in sig if want.get(s) in cls})
        loc = ["a", "c", "dt"] + sorted(dom[c] for c in classes) if classes else ["a", "dt"]
        if h["consequent"] != classes or h["loc"] != loc:
            bad.append(f"{p['expr']!r}: consequent {h['consequent']} loc {h['loc']}, expected {classes} {loc}")
    if len(props) != len(coi.get("predicates", [])):
        bad.append("hints place propositions that coi.json does not list")
    return bad


def main(argv):
    coi, hints = (json.loads(open(p).read()) for p in argv[1:3])
    bad = check(coi, hints)
    for b in bad:
        print(b)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
