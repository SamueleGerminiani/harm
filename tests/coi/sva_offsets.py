#!/usr/bin/env python3
"""H8, acceptance A4: cycle offsets of the leaves of a mined assertion, parsed from the SVA text HARM
prints (--sva), independently of HARM's leafOffsets; and the D-020 depth rule, from coi.json.

Supported: always (<sequence> |-> | |=> | -> <consequent>), where a sequence is items joined by
##k, and 'intersect'/'and' join sequences that start together; the consequent may start with
nexttime / nexttime[k] / ##k. Offsets count from the first cycle of the antecedent:
  |->  the consequent starts at the antecedent's last cycle;  |=>  one cycle later;
  ->   the consequent starts with the antecedent (HARM's semantics, H8 finding F6).
Anything else raises ValueError, so an unexpected output shape fails loudly.
"""
import re

from restrict_config import variables


def _split_top(text, pattern):
    """split on a regex at parenthesis depth 0; returns (parts, separators)"""
    parts, seps, depth, last, i = [], [], 0, 0, 0
    rx = re.compile(pattern)
    while i < len(text):
        ch = text[i]
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif depth == 0:
            m = rx.match(text, i)
            if m:
                parts.append(text[last:i])
                seps.append(m.group(0))
                i = last = m.end()
                continue
        i += 1
    parts.append(text[last:])
    return [p.strip() for p in parts], [s.strip() for s in seps]


def _strip_parens(t):
    t = t.strip()
    while t.startswith("(") and t.endswith(")"):
        depth = 0
        for i, ch in enumerate(t):
            depth += ch == "("
            depth -= ch == ")"
            if depth == 0 and i < len(t) - 1:
                return t
        t = t[1:-1].strip()
    return t


def _sequence(text, start, leaves, ant):
    """leaves of a sequence starting at 'start'; returns its last cycle"""
    text = _strip_parens(text)
    par, _ = _split_top(text, r"\s(?:intersect|and)\s")
    if len(par) > 1:
        ends = [_sequence(p, start, leaves, ant) for p in par]
        if len(set(ends)) != 1:
            raise ValueError(f"intersect of different lengths: {text}")
        return ends[0]
    items, seps = _split_top(text, r"##\d+")
    t = start
    for k, item in enumerate(items):
        if k > 0:
            t += int(seps[k - 1][2:])
        if not item:
            if k == 0:
                continue  # a leading ##k
            raise ValueError(f"empty item in {text}")
        if re.search(r"##|\bnexttime\b|\b(s_)?eventually\b|\buntil\b|\[\*|\[->|\[=", item):
            raise ValueError(f"unsupported item '{item}' in {text}")
        leaves.append((item, ant, t))
    return t


def leaves(text):
    """[(leaf text, in antecedent, offset)] of 'always (A op C)'"""
    m = re.fullmatch(r"\s*always\s*\((.*)\)\s*", text)
    if not m:
        raise ValueError(f"not 'always (...)': {text}")
    body = m.group(1)
    parts, ops = _split_top(body, r"\|->|\|=>|(?<![|<])->")
    if len(parts) == 1:
        out = []
        _sequence(body, 0, out, False)  # an invariant
        return out
    if len(parts) != 2:
        raise ValueError(f"more than one implication: {text}")
    out = []
    end = _sequence(parts[0], 0, out, True)
    con = parts[1]
    start = {"|->": end, "|=>": end + 1, "->": 0}[ops[0]]
    while True:
        con = _strip_parens(con)
        nm = re.match(r"nexttime(?:\s*\[(\d+)\])?\s*", con)
        if nm:
            start += int(nm.group(1) or 1)
            con = con[nm.end():]
            continue
        dm = re.match(r"##(\d+)\s*", con)
        if dm:
            start += int(dm.group(1))
            con = con[dm.end():]
            continue
        break
    _sequence(con, start, out, False)
    return out


def fits(coi, prop_vars, consequent, mode):
    """D-020. consequent = [(variables, distance or None)]"""
    targets, unknown, max_depth = coi["targets"], set(coi.get("unknown", [])), coi["meta"]["max_depth"]
    known = lambda v: v in targets and v not in unknown
    src = lambda c, v: next((s for s in targets[c]["sources"] if s["sig"] == v), None)
    for v in prop_vars:
        if not known(v):
            continue
        ok = False
        for qvars, d in consequent:
            for c in qvars:
                if not known(c):
                    ok = True
                    continue
                s = src(c, v)
                if s is None:
                    continue
                if mode == "any" or d is None:
                    ok = True
                elif mode == "exact":
                    ok |= d in s["depths"] or (s.get("saturated", False) and d > max_depth)
                elif mode == "bounded":
                    ok |= d >= 0 and ((s["depths"] and d <= max(s["depths"])) or s.get("saturated", False))
                else:
                    raise ValueError(mode)
        if not ok:
            return False
    return True


def violations(coi, text, mode):
    """antecedent leaves of an assertion that do not fit under 'mode'"""
    ls = leaves(text)
    con = [(variables(t), off) for t, ant, off in ls if not ant]
    bad = []
    for t, ant, off in ls:
        if ant:
            dist = [(vs, None if off is None or o is None else o - off) for vs, o in con]
            if not fits(coi, variables(t), dist, mode):
                bad.append(t)
    return bad


if __name__ == "__main__":
    import sys
    for line in sys.argv[1:]:
        print(leaves(line))
