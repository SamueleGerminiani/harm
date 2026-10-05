#!/usr/bin/env python3
"""Pairs for H1c's A4: safety assertions whose SVA end-of-trace strength differs.

'!X p' (s_nexttime !p) is strong and 'X !p' weak; '!(p W q)' (a strong until) and '!q W (!p && !q)'
(weak) are equivalent on infinite words but not at the end of a trace with --trace-end sva.
Each pair swaps one strong form for its weak twin, possibly with a stronger antecedent or an extra
conjunct. No labels: the oracle checks every claim against HARM's evaluator. Writes
generated_strong_pairs.txt (format: <A> ||| <B>).
"""
import random
from pathlib import Path

r = random.Random(7)


def lit():
    x = r.choice("abc")
    return f"!{x}" if r.random() < 0.3 else x


def strong_weak():
    p, q = r.choice("abc"), r.choice("abc")
    k = r.randrange(3)
    if k == 0:
        return f"!X {p}", f"X !{p}"
    if k == 1:
        return f"!({p} W {q})", f"(!{q} W (!{p} && !{q}))"
    return f"!X !X {p}", f"X X {p}"


def ant():
    return r.choice([f"{lit()} ->", f"{lit()} |=>", f"{{{lit()} ##1 {lit()}}} |->",
                     f"{{{lit()} && {lit()}}} |->"])


pairs = []
for _ in range(150):
    s, w = strong_weak()
    a = ant()
    k = r.randrange(3)
    if k == 0:
        pairs.append((f"G({a} {s})", f"G({a} {w})"))
    elif k == 1:  # the strong form under a stronger antecedent
        a2 = a.replace("->", f"&& {lit()} ->", 1) if a.endswith(" ->") and "{" not in a else a
        pairs.append((f"G({a2} {s})", f"G({a} {w})"))
    else:  # an extra conjunct on the weak side
        pairs.append((f"G({a} {s})", f"G({a} ({w}) && ({lit()}))"))
Path(__file__).with_name("generated_strong_pairs.txt").write_text(
    "".join(f"{x} ||| {y}\n" for x, y in pairs))
print(f"wrote {len(pairs)} pairs")
