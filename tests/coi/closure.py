#!/usr/bin/env python3
"""Derive a fixture's expected_coi.json from its hand-written edges.txt (H4).

edges.txt lists only DIRECT dependencies between visible signals, written by hand from the RTL:
    <target> <- <source> @<delay>       (delay = registers crossed on that direct path)
Paths through signals HARM cannot see are written as one edge with their total delay.
Header lines:  design / top / vcd_scope / vcd_recursion / clock / max_depth  (key = value)
               target <name>            (a visible signal with no sources, e.g. an input)
The closure is mechanical: every path depth up to max_depth is listed, and a source is
'saturated' if it also reaches the target through a deeper path (D-005).

Usage: closure.py <edges.txt> > expected_coi.json
"""
import json
import sys
from pathlib import Path


def main():
    meta, edges, targets = {}, {}, set()
    for line in Path(sys.argv[1]).read_text().splitlines():
        line = line.split("#")[0].strip()
        if not line:
            continue
        if "<-" in line:
            t, rest = [x.strip() for x in line.split("<-")]
            s, d = [x.strip() for x in rest.split("@")]
            edges.setdefault(t, []).append((s, int(d)))
            targets.add(t)
        elif line.startswith("target "):
            targets.add(line.split(None, 1)[1].strip())
        else:
            k, v = [x.strip() for x in line.split("=", 1)]
            meta[k] = v
    max_depth = int(meta["max_depth"])
    limit = max_depth + max((d for es in edges.values() for _, d in es), default=0) + 1
    out = {}
    for t in sorted(targets):
        reach = set()  # (source, depth)
        frontier = [(s, d) for s, d in edges.get(t, []) if d <= limit]
        while frontier:
            s, d = frontier.pop()
            if (s, d) in reach:
                continue
            reach.add((s, d))
            for s2, d2 in edges.get(s, []):
                if d + d2 <= limit:
                    frontier.append((s2, d + d2))
        sources = []
        for s in sorted({s for s, _ in reach}):
            depths = sorted(d for x, d in reach if x == s and d <= max_depth)
            entry = {"sig": s, "depths": depths}
            if any(x == s and d > max_depth for x, d in reach):
                entry["saturated"] = True
            sources.append(entry)
        out[t] = {"sources": sources}
    doc = {"version": "1",
           "meta": {"design": meta["design"], "top": meta["top"], "vcd_scope": meta["vcd_scope"],
                    "vcd_recursion": int(meta["vcd_recursion"]), "clock": meta["clock"],
                    "max_depth": max_depth, "generator": {"name": "hand-written", "version": "edges.txt"}},
           "targets": out, "unknown": [], "predicates": []}
    print(json.dumps(doc, indent=2))


if __name__ == "__main__":
    main()
