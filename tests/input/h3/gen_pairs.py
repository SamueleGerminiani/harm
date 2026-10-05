#!/usr/bin/env python3
"""Generate assertion pairs for H3's bounded-trace oracle (acceptance test A2).

Random HARM-shaped templates over the boolean atoms a, b, c, each paired with a mutation that
usually strengthens, weakens or changes it, plus a few liveness formulas (never reduced). There are
no labels: the test checks every implication H3 claims against HARM's own evaluation on every
boolean trace up to a bounded length. Writes generated_pairs.txt (format: <A> ||| <B>).
"""
import random
from pathlib import Path

ATOMS = ["a", "b", "c"]
r = random.Random(3)


def lit():
    x = r.choice(ATOMS)
    return f"!{x}" if r.random() < 0.25 else x


def antecedent():
    k = r.randrange(5)
    if k == 0:
        return lit(), False
    if k == 1:
        return f"{lit()} && {lit()}", False
    if k == 2:
        return f"{{{lit()} ##1 {lit()}}}", True
    if k == 3:
        return f"{{{lit()} ##2 {lit()}}}", True
    return f"{{{lit()} && {lit()} ##1 {lit()}}}", True


def consequent():
    k = r.randrange(6)
    return [lit(), f"X {lit()}", f"X X {lit()}", f"{lit()} W {lit()}",
            f"({lit()} || {lit()})", f"({lit()} && {lit()})"][k]


def formula(ant, sere, con):
    return f"G({ant} {'|->' if sere else '->'} {con})"


def mutate(ant, sere, con):
    k = r.randrange(8)
    if k == 0:  # extra conjunct in the antecedent
        if sere:
            return formula(ant[:-1] + f" && {lit()}}}", True, con)
        return formula(f"{ant} && {lit()}", False, con)
    if k == 1:  # weaker consequent
        return formula(ant, sere, f"({con} || {lit()})")
    if k == 2:  # stronger consequent
        return formula(ant, sere, f"({con} && {lit()})")
    if k == 3:  # one more cycle
        return formula(ant, sere, f"X {con}")
    if k == 4:  # an invariant of the consequent
        return f"G({con})"
    if k == 5:  # another antecedent
        a2, s2 = antecedent()
        return formula(a2, s2, con)
    if k == 6:  # another consequent
        return formula(ant, sere, consequent())
    return formula(ant, sere, con)  # the same formula


pairs = []
for _ in range(300):
    ant, sere = antecedent()
    con = consequent()
    pairs.append((formula(ant, sere, con), mutate(ant, sere, con)))
for _ in range(10):  # liveness: must be SKIPPED
    pairs.append((f"G({lit()} -> F {lit()})", f"G({lit()} -> X {lit()})"))
Path(__file__).with_name("generated_pairs.txt").write_text("".join(f"{a} ||| {b}\n" for a, b in pairs))
print(f"wrote {len(pairs)} pairs")
