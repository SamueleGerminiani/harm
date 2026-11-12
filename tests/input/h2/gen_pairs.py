#!/usr/bin/env python3
"""Generate proposition pairs for H2's brute-force equivalence test (acceptance test A3).

No labels: the test computes the truth by evaluating both propositions with HARM's evaluator on
every 4-valued assignment (small variables) or on random assignments (wide variables), and checks
that Z3 never claims an equivalence that the evaluation refutes.

Writes small_pairs.txt (variables v1 [1 bit], v2 [2 bits], v3 [3 bits]: 4^6 assignments) and
wide_pairs.txt (variables q4, r8, t13, u32: random assignments). Format: <p1> ||| <p2>
Regenerate only with approval (the files are test fixtures).
"""
import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "oracle"))
import gen_iverilog_fixture as g  # noqa: E402

HERE = Path(__file__).resolve().parent


def comparisons(gen, n):
    """atomic comparisons A op B and their 'negated operator' twins (equivalent only without x/z)"""
    neg = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
    out = []
    for _ in range(n):
        a, w, _ = gen.num(1, True)
        b, _, _ = gen.num_of_width(w, 1, True)
        op = gen.r.choice(list(neg))
        out.append((f"{a} {op} {b}", f"!({a} {neg[op]} {b})"))
        out.append((f"{a} {op} {b}", f"{b} {dict(zip(['<', '<=', '>', '>=', '==', '!='], ['>', '>=', '<', '<=', '==', '!=']))[op]} {a}"))
    return out


def respellings(gen, n):
    """the same constant written in different bases"""
    out = []
    for _ in range(n):
        name, w = gen.r.choice(g.VARS)
        v = gen.r.randrange(0, 2 ** w)
        spellings = [f"{w}'d{v}", f"{w}'b{v:0{w}b}", f"{w}'h{v:x}"]
        a, b = gen.r.sample(spellings, 2)
        out.append((f"{name} == {a}", f"{name} == {b}"))
    return out


def structural(gen, n):
    out = []
    for _ in range(n):
        p, _, _ = gen.boolean(2, True)
        q, _, _ = gen.boolean(2, True)
        out += [
            (p, f"!(!({p}))"),                               # double negation
            (f"({p}) && ({q})", f"({q}) && ({p})"),          # commutativity
            (f"({p}) && ({q})", f"!((!({p})) || (!({q})))"),  # De Morgan
            (f"({p}) || ({p})", p),                           # idempotence
            (p, q),                                           # unrelated (mostly not equivalent)
        ]
    return out


def write(name, vars_, seed, n):
    g.VARS = vars_
    gen = g.Gen(random.Random(seed))
    pairs = comparisons(gen, n) + respellings(gen, n) + structural(gen, n)
    (HERE / name).write_text("".join(f"{a} ||| {b}\n" for a, b in pairs))
    print(f"wrote {len(pairs)} pairs to {name}")


if __name__ == "__main__":
    write("small_pairs.txt", [("v1", 1), ("v2", 2), ("v3", 3)], 11, 120)
    write("wide_pairs.txt", [("q4", 4), ("r8", 8), ("t13", 13), ("u32", 32)], 12, 80)
