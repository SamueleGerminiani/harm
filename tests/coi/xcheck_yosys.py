#!/usr/bin/env python3
"""Independent signal-level cross-check of harm-coi against yosys (H5 validation).

yosys elaborates the same RTL with its own SystemVerilog front end (read_slang, yosys >= 0.67),
lowers it to single-bit gates (proc; flatten; techmap) and writes a JSON netlist. A signal's yosys
cone is everything that reaches one of its bits backwards through cells (clock ports excluded),
with every alias of a net bit counting as a name of it. Depths are not compared.

Both sides are compared at yosys' granularity: a packed struct is one wire in yosys, so harm-coi's
fields (c::mode, c::val) are merged into c. Parameters are not wires and are skipped.

  FAIL  a source yosys finds that harm-coi's cone lacks (harm-coi would claim non-influence wrongly)
  note  a source only harm-coi has (it over-approximates, or yosys folded a constant away)

Usage: xcheck_yosys.py --yosys <bin> --edges <harm-coi --edges output> --top T --recursion R
                       [--clock clk] <file.sv>...
"""
import argparse
import json
import subprocess
import sys
import tempfile
from collections import defaultdict
from pathlib import Path

CLOCK_PORTS = {"C", "CLK"}


def harm_edges(path):
    edges, names, unknown = defaultdict(set), set(), set()
    for line in Path(path).read_text().splitlines():
        line = line.split("#")[0].strip()
        if "<-" in line:
            t, rest = [x.strip() for x in line.split("<-")]
            s = rest.split("@")[0].strip()
            edges[t].add(s)
            names |= {t, s}
        elif line.startswith("target "):
            names.add(line.split()[1])
        elif line.startswith("unknown "):
            unknown.add(line.split()[1])
    return edges, names, unknown


def reach(start, graph):
    seen, stack = set(), list(graph.get(start, ()))
    while stack:
        x = stack.pop()
        if x not in seen:
            seen.add(x)
            stack += graph.get(x, ())
    return seen


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--yosys", required=True)
    ap.add_argument("--edges", required=True)
    ap.add_argument("--top", required=True)
    ap.add_argument("--recursion", type=int, required=True)
    ap.add_argument("--clock", default="clk")
    ap.add_argument("files", nargs="+")
    a = ap.parse_args()

    with tempfile.TemporaryDirectory() as tmp:
        nl = Path(tmp) / "nl.json"
        r = subprocess.run([a.yosys, "-q", "-p", f"read_slang --top {a.top} {' '.join(a.files)}; "
                            f"proc; flatten; techmap; write_json {nl}"], capture_output=True, text=True)
        if r.returncode != 0:
            print(r.stdout + r.stderr)
            sys.exit(f"yosys failed on {a.top}")
        mod = json.loads(nl.read_text())["modules"][a.top]

    # net bit -> yosys wire names (HARM spelling); only names HARM could see at this recursion
    bit_names = defaultdict(set)
    for n, w in mod["netnames"].items():
        if n.startswith("$"):
            continue
        hn = n.replace(".", "::")
        if hn.count("::") > a.recursion or hn == a.clock:
            continue
        for b in w["bits"]:
            if not isinstance(b, str):
                bit_names[b].add(hn)
    drivers = defaultdict(set)                # bit -> the bits its driving cell reads
    for c in mod["cells"].values():
        dirs = c["port_directions"]
        ins = {b for p, bs in c["connections"].items() if dirs[p] == "input" and p not in CLOCK_PORTS
               for b in bs if not isinstance(b, str)}
        for p, bs in c["connections"].items():
            if dirs[p] == "output":
                for b in bs:
                    if not isinstance(b, str):
                        drivers[b] |= ins
    wires = {n for ns in bit_names.values() for n in ns}

    def coarse(name):                         # harm-coi name -> the yosys wire that holds it
        parts = name.split("::")
        for k in range(len(parts), 0, -1):
            if "::".join(parts[:k]) in wires:
                return "::".join(parts[:k])
        return None

    edges, names, unknown = harm_edges(a.edges)
    hg = defaultdict(set)                     # harm-coi direct edges at yosys granularity
    for t, ss in edges.items():
        for s in ss:
            ct, cs = coarse(t), coarse(s)
            if ct and cs:
                hg[ct].add(cs)
    harm_wires = {coarse(n) for n in names | unknown} - {None}
    unknown_w = {coarse(n) for n in unknown} - {None}

    fails, notes = 0, 0
    for w in sorted(wires & harm_wires):
        bits = [b for b, ns in bit_names.items() if w in ns]
        seen, stack = set(), [x for b in bits for x in drivers.get(b, ())]
        while stack:
            b = stack.pop()
            if b not in seen:
                seen.add(b)
                stack += drivers.get(b, ())
        ys = {n for b in seen for n in bit_names.get(b, ())}
        # names on w's own net bits are aliases (assign y = x can merge nets): the netlist does not
        # say which way they depend, so they are neither required nor counted
        aliases = {n for b in bits for n in bit_names[b]} - {w}
        mine = reach(w, hg)
        if w in unknown_w or (mine & unknown_w):
            continue                          # harm-coi made no claim
        # a reached net bit is covered if harm-coi names any of its aliases
        missing = set()
        for b in seen:
            ns = bit_names.get(b, set()) - aliases
            if ns and not ns & (mine | {w} | aliases):
                missing |= ns
        extra = mine - ys - aliases
        if missing:
            fails += 1
            print(f"FAIL {w}: yosys finds {sorted(missing)} that harm-coi lacks")
        if extra:
            notes += 1
            print(f"note {w}: only harm-coi has {sorted(extra)}")
    skipped = sorted(n for n in names if coarse(n) is None)
    if skipped:
        print(f"not compared (no yosys wire): {', '.join(skipped)}")
    print(f"[{a.top}] {'FAIL' if fails else 'OK'}: {len(wires & harm_wires)} signals, "
          f"{fails} unsound, {notes} over-approximated")
    sys.exit(1 if fails else 0)


if __name__ == "__main__":
    main()
