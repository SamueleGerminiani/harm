#!/usr/bin/env python3
"""Generate assertion pairs in the shapes HARM's decision trees mine (acceptance test A2, second set).

Mined antecedents are SERE conjunctions and sequences of leaves ('{a && b} -> c',
'{a && b ##1 c} |-> X d', '{{a ##1 b} & c} |-> d'), which the first set (gen_pairs.py) does not
produce. Each formula is paired with a mutation; there are no labels: the test checks every
implication H3 claims against HARM's own evaluation on every boolean trace up to a bounded length.
Writes generated_mined_pairs.txt (format: <A> ||| <B>).
"""
import random
from pathlib import Path

ATOMS = ["a", "b", "c"]
r = random.Random(5)


def lit():
    x = r.choice(ATOMS)
    return f"!{x}" if r.random() < 0.25 else x


def conj(n):
    return " && ".join(lit() for _ in range(n))


def antecedent():
    """(text without braces, overlapping implication)"""
    k = r.randrange(6)
    if k == 0:
        return conj(2), "->"
    if k == 1:
        return conj(3), "->"
    if k == 2:
        return f"{conj(2)} ##1 {conj(r.randrange(1, 3))}", "|->"
    if k == 3:
        return f"{conj(r.randrange(1, 3))} ##2 {conj(2)}", "|=>"
    if k == 4:
        return f"{{{lit()} ##1 {lit()}}} & {lit()}", "|->"
    return f"{{{lit()} ##1 {lit()}}} && {{{lit()} ##1 {lit()}}}", "|->"


def consequent():
    return r.choice([lit(), f"X {lit()}", f"X X {lit()}", f"({lit()} || {lit()})",
                     f"({lit()} && {lit()})", f"{lit()} W {lit()}", f"{lit()} R {lit()}"])


def formula(ant, imp, con):
    return f"G({{{ant}}} {imp} {con})"


def mutate(ant, imp, con):
    k = r.randrange(7)
    if k == 0:  # one more conjunct on the last cycle of the antecedent
        return formula(f"{ant} && {lit()}", imp, con)
    if k == 1:  # one leaf less (the first conjunct of the first cycle)
        parts = ant.split(" && ", 1)
        return formula(parts[1] if len(parts) == 2 and "{" not in parts[0] else ant, imp, con)
    if k == 2:
        return formula(ant, imp, f"({con} || {lit()})")
    if k == 3:
        return formula(ant, imp, f"({con} && {lit()})")
    if k == 4:
        return formula(ant, imp, f"X {con}")
    if k == 5:
        a2, i2 = antecedent()
        return formula(a2, i2, con)
    return formula(ant, imp, consequent())


pairs = []
for _ in range(200):
    ant, imp = antecedent()
    con = consequent()
    pairs.append((formula(ant, imp, con), mutate(ant, imp, con)))
Path(__file__).with_name("generated_mined_pairs.txt").write_text(
    "".join(f"{a} ||| {b}\n" for a, b in pairs))
print(f"wrote {len(pairs)} pairs")
