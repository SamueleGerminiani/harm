"""H40 (doc/plan/H40_PLAN.md) T1: `cone.closure` gives the H39 version's output (kept here as the reference) on random
graphs, and is fast on a wide cone (pci_bridge's domain map spent 474 s in it)."""

from __future__ import annotations

import random
import time

from harm_coi import cone


def reference(names, direct, unknown, max_depth):  # H39's closure, with CR1's clip (C9-3)
    limit = max_depth + max((d for es in direct.values() for _, d in es), default=0) + 1
    targets, unknown = {}, set(unknown)
    for t in sorted(names - unknown):
        reach = set()
        # CR1 (C9-3): the reference clips a path at max_depth + 1, as the closure now does (H39 cut it)
        cap = max_depth + 1
        frontier = [(s, min(d, cap)) for s, d in direct.get(t, ())]
        while frontier:
            s, d = frontier.pop()
            if (s, d) in reach:
                continue
            reach.add((s, d))
            for s2, d2 in direct.get(s, ()):
                frontier.append((s2, min(d + d2, cap)))
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
    changed = True
    while changed:
        changed = False
        for t in list(targets):
            if any(s["sig"] in unknown and s["depths"] for s in targets[t]["sources"]):
                del targets[t]
                unknown.add(t)
                changed = True
    return targets, unknown


def _graph(rng: random.Random, n: int, edges: int):  # type: ignore[no-untyped-def]
    names = {f"s{i}" for i in range(n)}
    direct: dict[str, list[tuple[str, int]]] = {}
    for _ in range(edges):
        a, b = rng.sample(sorted(names), 2) if rng.random() < 0.9 else (f"s{rng.randrange(n)}",) * 2
        direct.setdefault(a, []).append((b, rng.choice((0, 1, 1, 2))))
    unknown = {f"s{i}" for i in rng.sample(range(n), rng.randrange(0, 3))}
    return names, direct, unknown


def test_t1_same_as_h39() -> None:
    rng = random.Random(40)
    for _ in range(300):
        names, direct, unknown = _graph(rng, rng.randrange(2, 25), rng.randrange(0, 60))
        for max_depth in (0, 1, 2, 4):
            assert cone.closure(set(names), {k: list(v) for k, v in direct.items()}, set(unknown), max_depth) == \
                reference(set(names), {k: list(v) for k, v in direct.items()}, set(unknown), max_depth)  # fmt: skip


def test_t1_wide_cone_is_fast() -> None:
    # 40 targets that each reach 2,000 registers within the depth: the H39 version is quadratic in the reach
    n, w = 40, 2000
    direct = {f"t{i}": [(f"r{j}", 1 + j % 2) for j in range(w)] for i in range(n)}
    direct |= {f"r{j}": [(f"r{(j + 1) % w}", 1)] for j in range(w)}
    names = set(direct)
    t = time.time()
    out = cone.closure(names, direct, set(), 3)
    assert time.time() - t < 10  # CR1 (C9-3; the user, 2026-10-31): every source at any depth is listed, clipped (8 s on the Mac; H39 cut them, < 3 s)
    assert out == reference(names, direct, set(), 3)
