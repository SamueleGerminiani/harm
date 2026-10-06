"""From the extracted design to HARM's names and cones (D-005, D-013).

1. The sampling clock: --clock, or the single signal that every register's clock comes from
   through wires and ports. Registers on another clock (or a derived one) are unknown.
2. Visible names: the VCD's, when a trace is given (signals of the trace that the RTL does not
   produce are unknown); otherwise every atom at most `recursion` sub-scopes below the top.
3. Direct edges between visible names: paths through invisible signals are collapsed, their
   delays summed.
4. The closure up to max_depth, with the same rule as tests/coi/closure.py: every path depth up
   to max_depth, and `saturated` when the source also reaches the target through a deeper path.
   A target whose cone reaches an unknown signal within max_depth is itself unknown.
"""
from collections import defaultdict

from .frontend import FrontendError


def name(path):
    return "::".join(path)


def clock_root(atom, edges):
    """Follow a clock back through single-source zero-delay edges (wires, ports) to its root."""
    seen = [atom]
    while True:
        srcs = edges.get(atom, set())
        if len(srcs) != 1:
            return atom, seen
        (s, d), = srcs
        if d != 0 or s in seen:
            return atom, seen
        atom = s
        seen.append(s)


def resolve_clocks(design, clock_name):
    """Fix the register delays; returns (clock atom, set of atoms on clock paths)."""
    edges = design.edges
    roots = {}
    chain_nodes = set()
    for p in design.processes:
        r, chain = clock_root(p.clock, edges)
        roots[id(p)] = r
    if clock_name is not None:
        clk = tuple(clock_name.split("::"))
        if clk not in design.signals:
            raise FrontendError(f"clock '{clock_name}' is not a signal of the design")
    else:
        cands = set(roots.values())
        if not cands:
            raise FrontendError("no clocked process found: give the sampling clock with --clock")
        if len(cands) > 1:
            raise FrontendError("several clocks (" + ", ".join(sorted(name(c) for c in cands))
                                + "): give the sampling clock with --clock")
        clk = cands.pop()
    for p in design.processes:
        if roots[id(p)] == clk and p.edge in ("pos", "neg"):
            chain_nodes.update(clock_root(p.clock, edges)[1])
            delays = (1,) if p.edge == "pos" else (0, 1)
            for t in p.targets:
                new = set()
                for s, d in edges[t]:
                    if d == "reg":
                        new |= {(s, x) for x in delays}
                    else:
                        new.add((s, d))
                edges[t] = new
        else:
            reason = "register on another clock" if roots[id(p)] != clk else "register on both clock edges"
            for t in p.targets:
                design.unknown.setdefault(t, reason)
                edges[t] = set()
    chain_nodes.add(clk)
    return clk, chain_nodes


def visible_names(design, recursion, vcd_names, clk):
    """{atom: visible name} and the set of trace names the RTL does not produce."""
    atoms = design.signals | design.params
    if vcd_names is None:
        return {a: name(a) for a in atoms if len(a) - 1 <= recursion}, set()
    m = {}
    for a in atoms:
        for n in range(len(a), 0, -1):   # a struct dumped as one vector: its fields map to it
            if name(a[:n]) in vcd_names:
                m[a] = name(a[:n])
                break
    orphan = set(vcd_names) - set(m.values()) - {name(clk)}
    return m, orphan


def direct_edges(design, vis, clock_nodes, max_depth):
    """Edges between visible names, collapsing invisible atoms; and the unknown visible names."""
    edges = design.edges
    limit = max_depth + 1
    out = defaultdict(set)
    unknown = {vis[a] for a in design.unknown if a in vis}
    by_name = defaultdict(list)
    for a, n in vis.items():
        by_name[n].append(a)
    for n, atoms in by_name.items():
        if n in unknown or any(a in clock_nodes for a in atoms):
            continue                        # an alias of the clock (a clock port): no sources
        stack = [(s, d) for a in atoms for s, d in edges.get(a, ())]
        seen = set()
        while stack:
            s, d = stack.pop()
            if (s, d) in seen or s in clock_nodes:
                continue
            seen.add((s, d))
            if s in vis:
                out[n].add((vis[s], min(d, limit)))
            elif s in design.unknown:
                if d <= max_depth:
                    unknown.add(n)          # the cone goes through a signal we cannot model
            elif d <= limit:
                stack += [(s2, d + d2) for s2, d2 in edges.get(s, ())]
    for n in unknown:
        out.pop(n, None)
    return out, unknown


def closure(names, direct, unknown, max_depth):
    """D-005 cones; targets whose cone reaches an unknown name within max_depth become unknown."""
    limit = max_depth + max((d for es in direct.values() for _, d in es), default=0) + 1
    targets, unknown = {}, set(unknown)
    for t in sorted(names - unknown):
        reach = set()
        frontier = [(s, d) for s, d in direct.get(t, ()) if d <= limit]
        while frontier:
            s, d = frontier.pop()
            if (s, d) in reach:
                continue
            reach.add((s, d))
            for s2, d2 in direct.get(s, ()):
                if d + d2 <= limit:
                    frontier.append((s2, d + d2))
        if any(s in unknown and d <= max_depth for s, d in reach):
            unknown.add(t)
            continue
        sources = []
        for s in sorted({s for s, _ in reach}):
            depths = sorted(d for x, d in reach if x == s and d <= max_depth)
            entry = {"sig": s, "depths": depths}
            if any(x == s and d > max_depth for x, d in reach):
                entry["saturated"] = True
            sources.append(entry)
        targets[t] = {"sources": sources}
    # a target that became unknown may be in the cone of one processed earlier: repeat until stable
    changed = True
    while changed:
        changed = False
        for t in list(targets):
            if any(s["sig"] in unknown and s["depths"] for s in targets[t]["sources"]):
                del targets[t]
                unknown.add(t)
                changed = True
    return targets, unknown
