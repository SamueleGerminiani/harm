"""H45-mutant-eval: the mutation score of one HARM run (doc/plan/H45_PLAN.md).

Input: HARM's --dump-assertion-info, written with --fd and --find-min-subset, so each assertion lists every fault trace
it fails on. One of the fault traces is a second golden run (another stimulus seed): an assertion that fails on it is
a false positive and kills nothing. A mutant is killed when an assertion that is not a false positive fails on it.
"""

from __future__ import annotations

import json
from pathlib import Path


def score(info: Path, golden_fault: str, mutants: dict[str, tuple[str, str]]) -> dict:
    """mutants: fault trace (as HARM names it) -> (activation: none/internal/output, operator)."""
    return score_multi(info, [golden_fault], {m: (a, op, [m] if a != "none" else []) for m, (a, op) in mutants.items()})


def score_multi(info: Path, goldens: list[str], mutants: dict[str, tuple[str, str, list[str]]]) -> dict:
    """Several held-out seeds (H45 amendment). goldens: the held-out golden traces (a failure on any of them makes a
    false positive); mutants: id -> (activation over the seeds, operator, its fault traces as HARM names them); a
    mutant is killed when an assertion that is not a false positive fails on any of its traces."""
    recs = json.loads(Path(info).read_text())["assertions"]
    if any(r.get("faultsComplete") is not True for r in recs):
        raise ValueError("the fault lists are not complete: run HARM with --fd and --find-min-subset")
    gold = set(goldens)
    fp = [r for r in recs if gold & set(r["faults"])]
    kills = {f for r in recs if not gold & set(r["faults"]) for f in r["faults"]}
    act = {m: a for m, (a, _, _) in mutants.items() if a != "none"}
    killed = {m for m in act if kills & set(mutants[m][2])}
    out_act = {m for m, a in act.items() if a == "output"}
    by_op: dict[str, dict[str, int]] = {}
    for m, (a, op, _) in mutants.items():
        d = by_op.setdefault(op, {"activated": 0, "killed": 0})
        if a != "none":
            d["activated"] += 1
            d["killed"] += m in killed
    return {
        "assertions": len(recs),
        "false_positives": len(fp),
        "activated": len(act),
        "not_activated": len(mutants) - len(act),
        "killed": len(killed),
        "score": len(killed) / len(act) if act else None,
        "activated_output": len(out_act),
        "killed_output": len(killed & out_act),
        "by_op": by_op,
    }
