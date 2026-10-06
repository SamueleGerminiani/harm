#!/usr/bin/env python3
"""H8, acceptance A4: cycle offsets of the leaves of a mined assertion, parsed from the text HARM
prints by default (Spot LTL), independently of HARM's leafOffsets; and the D-020 depth rule, from
coi.json. The SVA text (--sva) cannot be used: it prints {s} -> X c as s |=> c, which anchors c at
the end of s instead of its start (H8 finding F7).

Supported: G(<antecedent> (|-> | |=> | ->) <consequent>) and G(<consequent>), where an antecedent
or consequent is a SERE {..} of items joined by ##k, ';' (##1) or ':' (##0), or Boolean items
joined by '&&', each possibly prefixed by X (one cycle each). A leading X applies to the rest of
the operand, as HARM prints it ("Xen && wrap" is X(en && wrap), finding F8); so a template like
G(X P0 && P1 -> ...) is not supported. Offsets count from the first cycle
of the antecedent:
  |->  the consequent starts at the antecedent's last cycle;  |=>  one cycle later;
  ->   the consequent starts with the antecedent (HARM's semantics, H8 finding F6).
Anything else raises ValueError, so an unexpected output shape fails loudly.
"""
import re

from restrict_config import variables

OPEN, CLOSE = "({", ")}"


def _split_top(text, pattern):
    """split on a regex outside () and {}; returns (parts, separators)"""
    parts, seps, depth, last, i = [], [], 0, 0, 0
    rx = re.compile(pattern)
    while i < len(text):
        ch = text[i]
        if ch in OPEN:
            depth += 1
        elif ch in CLOSE:
            depth -= 1
        elif depth == 0:
            m = rx.match(text, i)
            if m and m.end() > i:
                parts.append(text[last:i])
                seps.append(m.group(0))
                i = last = m.end()
                continue
        i += 1
    parts.append(text[last:])
    return [p.strip() for p in parts], [s.strip() for s in seps]


def _strip(t):
    """remove enclosing () or {} pairs that span the whole text"""
    t = t.strip()
    while len(t) >= 2 and t[0] in OPEN and t[-1] == CLOSE[OPEN.index(t[0])]:
        depth = 0
        for i, ch in enumerate(t):
            depth += ch in OPEN
            depth -= ch in CLOSE
            if depth == 0 and i < len(t) - 1:
                return t
        t = t[1:-1].strip()
    return t


def _part(text, start, leaves, ant):
    """leaves of a SERE or Boolean/X expression starting at 'start'; returns its last cycle"""
    text = _strip(text)
    if re.search(r"\[\*|\[->|\[=|\bF\b|\bU\b|\bR\b|\bW\b|##\[", text):
        raise ValueError(f"offsets not fixed: {text}")
    items, seps = _split_top(text, r"##\d+|;|(?<!:):(?!:)")  # ':' is fusion, '::' a scope
    if len(items) > 1:
        t = start
        for k, item in enumerate(items):
            if k > 0:
                sep = seps[k - 1]
                t += 1 if sep == ";" else 0 if sep == ":" else int(sep[2:])
            if item:
                t = _part(item, t, leaves, ant)
        return t
    # HARM prints X(p) without parentheses ("Xen && wrap" is X(en && wrap), finding F8): a
    # leading X applies to the rest of the operand; otherwise a conjunction with an X in a later
    # conjunct ("a && Xb") is split
    xm = re.match(r"X(?=[\s({A-Za-z!])\s*", text)
    if xm:
        return _part(text[xm.end():], start + 1, leaves, ant)
    conj, _ = _split_top(text, r"&&")
    if len(conj) > 1 and any(re.match(r"X(?=[\s({A-Za-z!])", c) for c in conj):
        return max(_part(c, start, leaves, ant) for c in conj)
    leaves.append((text, ant, start))
    return start


def leaves(text):
    """[(leaf text, in antecedent, offset)] of 'G(A op C)' or 'G(C)'"""
    m = re.fullmatch(r"\s*G\((.*)\)\s*", text)
    if not m:
        raise ValueError(f"not 'G(...)': {text}")
    parts, ops = _split_top(m.group(1), r"\|->|\|=>|(?<![|\]])->")
    out = []
    if len(parts) == 1:
        _part(parts[0], 0, out, False)  # an invariant
        return out
    if len(parts) != 2:
        raise ValueError(f"more than one implication: {text}")
    end = _part(parts[0], 0, out, True)
    _part(parts[1], {"|->": end, "|=>": end + 1, "->": 0}[ops[0]], out, False)
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
