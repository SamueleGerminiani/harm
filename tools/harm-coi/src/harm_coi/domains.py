"""The clock-domain map of a design (H35, D-043), from the extracted design before any clock is chosen.

1. A domain is a clock root (a process's clock followed back through single-source wires and ports) with every
   register it clocks, on either edge. A root driven by logic or by a register is derived, `from` the domains it is
   made from.
2. A crossing is a register of another domain that reaches a domain's register through wires and logic.
3. A synchronizer is a register whose sources (not itself, not its asynchronous controls) lead through wires only to
   one foreign register, followed by a register whose only such source is the first.
4. A domain's resets are its registers' asynchronous controls, followed back to their roots; with `resets`, also
   which of them its registers read at all.
"""
from .cone import clock_root, name

UNCLOCKED = "cannot tell the clock from the asynchronous controls"


def build(design, top, resets=()):
    edges = design.edges
    root = {}                                  # register atom -> its domain's root
    asyncs = {}                                # register atom -> its process's asynchronous controls
    doms = {}                                  # root -> {"edges", "registers", "resets"}
    for p in design.processes:
        r = clock_root(p.clock, edges)[0]
        d = doms.setdefault(r, {"edges": set(), "registers": set(), "resets": set()})
        d["edges"].add(p.edge)
        d["resets"] |= {clock_root(a, edges)[0] for a in p.asyncs}
        for t in p.targets:
            root[t] = r
            asyncs[t] = p.asyncs
            d["registers"].add(t)

    def reached(t):
        """The registers (and the reset atoms) that reach register t through wires and logic."""
        regs, atoms, seen = set(), set(), {t}
        stack = [s for s, _ in edges.get(t, ())]
        while stack:
            s = stack.pop()
            if s in seen:
                continue
            seen.add(s)
            atoms.add(s)
            if s in root:
                regs.add(s)
            else:
                stack += [x for x, _ in edges.get(s, ())]
        return regs, atoms

    def wired(t):
        """The roots of t's sources through wires only, leaving out t itself and its asynchronous controls."""
        return {clock_root(s, edges)[0] for s, _ in edges.get(t, ()) if s != t and s not in asyncs.get(t, ())}

    want = {tuple(n.split("::")): n for n in resets}
    clocks, crossings, syncs = [], [], []
    for r in sorted(doms, key=name):
        d = doms[r]
        frm = set()
        if r in root:                                         # a register's output used as a clock
            frm = {root[r]}
        elif edges.get(r) and r not in design.top_inputs:     # a clock made by logic
            frm = {clock_root(s, edges)[0] for s, _ in edges[r]} & set(doms)
        reads = set()
        for t in sorted(d["registers"]):
            regs, atoms = reached(t)
            for s in sorted(regs - {t}):
                if root[s] != r:
                    crossings.append({"signal": name(s), "from": name(root[s]), "to": name(r), "into": name(t)})
            reads |= {want[a] for a in atoms if a in want}
            first = wired(t)
            if len(first) == 1 and (f := next(iter(first))) in root and root[f] != r:
                for t2 in sorted(d["registers"]):
                    if t2 != t and wired(t2) == {t}:
                        syncs.append({"clock": name(r), "from": name(f), "first": name(t), "second": name(t2)})
        clocks.append({"name": name(r), "edges": sorted(d["edges"]), "derived": bool(frm),
                       "from": sorted(name(x) for x in frm), "registers": sorted(name(x) for x in d["registers"]),
                       "resets": sorted(name(x) for x in d["resets"]), "reads_resets": sorted(reads)})
    crossings.sort(key=lambda c: (c["to"], c["into"], c["signal"]))
    syncs.sort(key=lambda s: (s["clock"], s["first"], s["second"]))
    unclocked = sorted(name(a) for a, why in design.unknown.items() if why == UNCLOCKED)
    return {"version": "1", "top": top, "clocks": clocks, "crossings": crossings, "synchronizers": syncs,
            "unclocked": unclocked}
