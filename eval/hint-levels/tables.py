"""The letter's tables from the CSVs in results/ (or another directory with the same files).

  tables.py [results dir]

- arms.csv: per design and arm, kills, false positives, assertions and time; deep as the median of its repeats;
- configurations-pulp.csv and configurations-assertllm2.csv: HARM's configurations (eval/run_eval.py), 600 s per run;
  AssertLLM2 without fault traces (assertion counts and times only);
- rq3.csv: the four designs where the deep arm kills more, raw rows (3 deep repeats each);
- rq3-depth.csv: the depth variants (L0+roles and deep);
- filter.csv: the cone filter's lost kills by class (filter_check.py);
- sizes.csv (when present): each design's ports and lines of RTL (sizes.py)."""

from __future__ import annotations

import csv
import json
import statistics
import sys
from pathlib import Path
from typing import Any

ARMS = ("L0", "L0+roles", "rel", "deep")
CONFIGS = ("C0", "R", "R+F", "R+F+X", "RR", "RR+F+X")


def _rows(p: Path) -> list[dict[str, str]]:
    return list(csv.DictReader(open(p)))


def build(results: Path) -> dict[str, Any]:
    out: dict[str, Any] = {}
    raw = [r for r in _rows(results / "arms.csv") if r["status"] == "ok"]
    arms = []  # one row per design and arm: a repeated arm (deep) by its median repeat, raw run_arms.py rows or not
    for key in sorted({(r["design"], r["arm"]) for r in raw}):
        group = sorted((r for r in raw if (r["design"], r["arm"]) == key), key=lambda r: int(r["killed"]))
        arms.append(group[len(group) // 2])
    out["kills"] = {
        "all": {a: (sum(int(r["killed"]) for r in arms if r["arm"] == a),
                    sum(int(r["activated"]) for r in arms if r["arm"] == a)) for a in ARMS},
        "fp": {a: sum(int(r["false_positives"]) for r in arms if r["arm"] == a) for a in ARMS},
        "assertions": {a: sum(int(r["assertions"]) for r in arms if r["arm"] == a) for a in ARMS},
        "per_design": {(r["design"], r["arm"]): (int(r["killed"]), int(r["activated"]), int(r["false_positives"]))
                       for r in arms},
    }  # fmt: skip
    out["configs"] = {}
    for name, f, kills in (("pulp", "configurations-pulp.csv", True),
                           ("assertllm2", "configurations-assertllm2.csv", False)):  # fmt: skip
        rows = _rows(results / f)
        t = {}
        for c in CONFIGS:
            ok = [r for r in rows if r["config"] == c and r["status"] == "ok"]
            t[c] = {"finished": len(ok), "assertions": sum(int(r["assertions"]) for r in ok)}
            if kills:
                t[c]["killed"] = sum(int(r["killed"]) for r in ok)
        out["configs"][name] = t
    rq3 = _rows(results / "rq3.csv")
    out["rq3"] = {}
    for d in sorted({r["design"] for r in rq3}):
        base = [r for r in rq3 if r["design"] == d and r["arm"] == "L0+roles"][0]
        deep = [r for r in rq3 if r["design"] == d and r["arm"] == "deep"]
        bk = set(json.loads(base["killed_ids"]))
        only = [len(set(json.loads(r["killed_ids"])) - bk) for r in deep]
        out["rq3"][d] = {"l0roles": int(base["killed"]), "activated": int(base["activated"]),
                         "deep": statistics.median(int(r["killed"]) for r in deep), "deep_only": min(only),
                         "time": (round(float(base["wall_s"])), round(statistics.median(float(r["wall_s"]) for r in deep))),
                         "fp": max(int(r["false_positives"]) for r in deep)}  # fmt: skip
    filt = _rows(results / "filter.csv")
    out["filter"] = {k: sum(int(r[k]) for r in filt) for k in ("lost", "gained", "reset", "delay", "out_of_cone")}
    if (results / "sizes.csv").exists():
        out["sizes"] = {r["design"]: (int(r["inputs"]), int(r["outputs"]), int(r["loc"])) for r in _rows(results / "sizes.csv")}
    return out


def main(argv: list[str] | None = None) -> None:
    results = Path((argv or sys.argv[1:] or [str(Path(__file__).resolve().parent / "results")])[0])
    t = build(results)
    print("Kills by arm (of activated mutants), false positives, assertions:")
    for a in ARMS:
        k, n = t["kills"]["all"][a]
        print(f"  {a:9} {k}/{n} ({100 * k / n:.0f}%)  fp {t['kills']['fp'][a]}  assertions {t['kills']['assertions'][a]}")
    for name in ("pulp", "assertllm2"):
        print(f"HARM's configurations, {name}:")
        for c in CONFIGS:
            print(f"  {c:7} {t['configs'][name][c]}")
    print("Where the deep arm kills more:")
    for d, r in t["rq3"].items():
        print(f"  {d:22} L0+roles {r['l0roles']}/{r['activated']}  deep {r['deep']}  only deep {r['deep_only']}  "
              f"time {r['time'][0]} / {r['time'][1]} s")
    print(f"The cone filter's lost kills: {t['filter']}")
    if "sizes" in t:
        print("Design sizes (inputs/outputs, lines of RTL), the arms' designs:")
        for d in sorted({d for d, _ in t["kills"]["per_design"]}):
            i, o, n = t["sizes"][d]
            print(f"  {d:22} {i}/{o}  {n}")


if __name__ == "__main__":
    main()
