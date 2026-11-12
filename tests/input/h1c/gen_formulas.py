#!/usr/bin/env python3
"""Generate assertions for H1c's independent oracle (acceptance test A2).

Random HARM-shaped assertions over the boolean atoms a, b, c, G(antecedent -> consequent), whose
consequents mix weak operators (X, W) with strong ones (F) and negations (which turn X into
s_nexttime and W into a strong until). No labels: the oracle recomputes HARM's verdicts from
IEEE 1800 Annex F on every short trace. Writes formulas.txt.
"""
import random
from pathlib import Path

r = random.Random(11)


def lit():
    x = r.choice("abc")
    return f"!{x}" if r.random() < 0.3 else x


def prop(depth):
    if depth == 0:
        return lit()
    k = r.randrange(9)
    if k == 0:
        return lit()
    if k == 1:
        return f"X {prop(depth - 1)}"
    if k == 2:
        return f"F {prop(depth - 1)}"
    if k == 3:
        return f"!X {prop(depth - 1)}"
    if k == 4:
        return f"({prop(depth - 1)} W {lit()})"
    if k == 5:
        return f"!({lit()} W {lit()})"
    if k == 6:
        return f"({prop(depth - 1)}) || ({prop(depth - 1)})"
    if k == 7:
        return f"({prop(depth - 1)}) && ({prop(depth - 1)})"
    return f"X X {prop(depth - 1)}"


def antecedent():
    k = r.randrange(4)
    if k == 0:
        return f"{lit()} ->"
    if k == 1:
        return f"{lit()} |=>"
    if k == 2:
        return f"{{{lit()} ##1 {lit()}}} |->"
    return f"{{{lit()} && {lit()}}} |->"


seen, out = set(), []
while len(out) < 300:
    f = f"G({antecedent()} {prop(r.randrange(1, 4))})"
    if f not in seen:
        seen.add(f)
        out.append(f)
Path(__file__).with_name("formulas.txt").write_text("".join(f + "\n" for f in out))
print(f"wrote {len(out)} formulas")
