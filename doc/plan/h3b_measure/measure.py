#!/usr/bin/env python3
"""H3b measurement (spike, not a test): a lower bound on how many assertions that survive
`--reduce implies` would be dropped with atom facts.

For two surviving assertions A, B of the same shape (the text with each proposition blanked), A
implies B if, position by position, every antecedent proposition of B implies A's and every
consequent proposition of A implies B's (G(ant -> con) is antitone in the antecedent, monotone in
the consequent). Implication between two propositions is decided exactly for propositions over
ONE variable built from ==, !=, <, <=, >, >= with constants, &&, ||, ! (the forms numeric
clustering and H10 produce), with HARM's x/z rule (D-011): a comparison is false on a value with
x/z bits, ! then makes it true. Other propositions only imply themselves (identical text).
This is a sufficient condition, so the count is a lower bound for H3b.
"""
import json
import re
import sys
from pathlib import Path


# ---- one-variable propositions as value sets: (frozenset of disjoint [lo, hi] intervals, x flag)
class Unparsed(Exception):
    pass


def lit(tok):
    m = re.fullmatch(r"(\d+)'([bdh])([0-9a-fA-F_]+)", tok)
    if not m:
        if re.fullmatch(r"\d+", tok):
            return None, int(tok)
        raise Unparsed(tok)
    w, base, v = int(m.group(1)), m.group(2), m.group(3).replace("_", "")
    return w, int(v, {"b": 2, "d": 10, "h": 16}[base])


def norm(ivs):
    ivs = sorted(i for i in ivs if i[0] <= i[1])
    out = []
    for lo, hi in ivs:
        if out and lo <= out[-1][1] + 1:
            out[-1] = (out[-1][0], max(out[-1][1], hi))
        else:
            out.append((lo, hi))
    return tuple(out)


def complement(ivs, top):
    out, cur = [], 0
    for lo, hi in ivs:
        if lo > cur:
            out.append((cur, lo - 1))
        cur = hi + 1
    if cur <= top:
        out.append((cur, top))
    return tuple(out)


def intersect(a, b):
    out = []
    for lo1, hi1 in a:
        for lo2, hi2 in b:
            lo, hi = max(lo1, lo2), min(hi1, hi2)
            if lo <= hi:
                out.append((lo, hi))
    return norm(out)


class Prop:
    """parse a proposition over one variable into (var, width, intervals, x)"""

    def __init__(self, text, widths=None):
        self.toks = re.findall(r"\d+'[bdhBDH][0-9a-fA-F_]+|[A-Za-z_][\w]*(?:\[\d+\])?(?:::[A-Za-z_][\w]*(?:\[\d+\])?)*"
                               r"|==|!=|>=|<=|&&|\|\||[<>!()]|\d+", text)
        self.i, self.var, self.widths = 0, None, widths
        ivs, x = self.expr()
        if self.i != len(self.toks) or self.var is None:
            raise Unparsed(text)
        self.ivs, self.x = ivs, x

    def peek(self):
        return self.toks[self.i] if self.i < len(self.toks) else None

    def take(self):
        t = self.peek()
        self.i += 1
        return t

    def top(self):
        return (1 << self.width) - 1

    def use(self, v, w):
        """the variable and its width (from the sized literal it is compared with; 1 if alone)"""
        if self.var is not None and (v != self.var or w != self.width):
            raise Unparsed("two variables, or two widths")
        self.var, self.width = v, w

    def expr(self):
        a = self.conj()
        while self.peek() == "||":
            self.take()
            b = self.conj()
            a = (norm(a[0] + b[0]), a[1] or b[1])
        return a

    def conj(self):
        a = self.unary()
        while self.peek() == "&&":
            self.take()
            b = self.unary()
            a = (intersect(a[0], b[0]), a[1] and b[1])
        return a

    def unary(self):
        t = self.peek()
        if t == "!":
            self.take()
            ivs, x = self.unary()
            return complement(ivs, self.top()), not x
        if t == "(":
            self.take()
            r = self.expr()
            if self.take() != ")":
                raise Unparsed(")")
            return r
        a = self.take()
        if self.peek() in ("==", "!=", "<", "<=", ">", ">="):
            op, b = self.take(), self.take()
            if re.match(r"\d", a):          # constant on the left
                a, b = b, a
                op = {"<": ">", ">": "<", "<=": ">=", ">=": "<="}.get(op, op)
            w, k = lit(b)
            if w is None:
                raise Unparsed("unsized constant")
            self.use(a, w)
            top = self.top()
            sets = {"==": ((k, k),), "!=": ((0, k - 1), (k + 1, top)), "<": ((0, k - 1),),
                    "<=": ((0, k),), ">": ((k + 1, top),), ">=": ((k, top),)}
            return norm(sets[op]), False      # a comparison is false on x/z (D-011)
        if not re.fullmatch(r"[A-Za-z_][\w:\[\]]*", a or ""):
            raise Unparsed(str(a))
        self.use(a, 1)                        # a 1-bit variable used as a condition
        return ((1, 1),), False


def implies(p, q):
    """p => q for parsed propositions over the same variable (x included)"""
    if p.var != q.var:
        return False
    if p.x and not q.x:
        return False
    return intersect(p.ivs, complement(q.ivs, p.top())) == ()


# ---- assertions
def shape(rec):
    text, pos, out = rec["text"], 0, ""
    for leaf in rec["leaves"]:
        k = text.find(leaf["text"], pos)
        if k < 0:
            return None
        out += text[pos:k] + ("§A" if leaf["antecedent"] else "§C")
        pos = k + len(leaf["text"])
    return out + text[pos:]


def leaf_implies(a, b, widths, cache):
    if a == b:
        return True
    key = (a, b)
    if key not in cache:
        try:
            cache[key] = implies(Prop(a, widths), Prop(b, widths))
        except (Unparsed, KeyError, ValueError):
            cache[key] = False
    return cache[key]


def measure(records, widths):
    groups = {}
    for r in records:
        s = shape(r)
        if s is not None:
            groups.setdefault(s, []).append(r)
    cache, dropped, examples = {}, set(), []
    for recs in groups.values():
        for A in recs:
            for B in recs:
                if A is B or A["text"] == B["text"] or B["text"] in dropped:
                    continue
                ok = True
                for la, lb in zip(A["leaves"], B["leaves"]):
                    if la["antecedent"]:
                        ok &= leaf_implies(lb["text"], la["text"], widths, cache)
                    else:
                        ok &= leaf_implies(la["text"], lb["text"], widths, cache)
                    if not ok:
                        break
                if ok:
                    # A => B: B is redundant, unless B => A too (equivalent: keep one)
                    if A["text"] not in dropped:
                        dropped.add(B["text"])
                        if len(examples) < 4:
                            examples.append((A["text"], B["text"]))
    return dropped, examples


if __name__ == "__main__":
    recs = json.loads(Path(sys.argv[1]).read_text())["assertions"]
    dropped, ex = measure(recs, None)
    print(json.dumps({"kept": len(recs), "droppable": len(dropped), "examples": ex}))
