"""Why the cone filter costs kills: HARM's configurations R and R+F (eval/run_eval.py) on eval/mutants' prepared
designs, compared mutant by mutant.

  filter_check.py <prepared dir> <R dir> <R+F dir> [--out filter.csv]

Each dir holds <design>/... : <prepared dir>/<design>/prepared.json, and <R dir>/<design>/harm/info.json (HARM's
--dump-assertion-info of `mutants_eval.py --configs R`; likewise R+F). A kill is scored as in eval/mutants/score.py.
Each mutant R kills and R+F does not is put in one class, from the assertions of R that kill it:
- reset: every one of them has the reset input as its consequent (a property of the testbench, not of the design);
- delay: one has all its antecedent atoms inside the consequent's cone (coiFrac 1) at a delay the exact-depth filter
  rejects (coiDepthFit below 1);
- out_of_cone: otherwise, an atom outside the cone."""

from __future__ import annotations

import argparse
import csv
import json
import os
import re
from pathlib import Path
from typing import Any

FIELDS = ["design", "killed_R", "killed_RF", "lost", "gained", "reset", "delay", "out_of_cone"]


def _kills(info: Path, prep: dict[str, Any]) -> list[tuple[dict[str, Any], set[str]]]:
    gold = {os.path.basename(g) for g in prep["goldens"]}
    t2m = {os.path.basename(f): m for m, (_, _, fs) in prep["mutants"].items() for f in fs}
    act = {m for m, (a, _, _) in prep["mutants"].items() if a != "none"}
    out = []
    for r in json.loads(info.read_text())["assertions"]:
        fs = {os.path.basename(f) for f in r["faults"]}
        if fs & gold:  # a false positive kills nothing
            continue
        out.append((r, {t2m[f] for f in fs if f in t2m} & act))
    return out


def _consequent(text: str) -> str:
    return re.split(r"\|->|\|=>", text)[-1].strip(" )")


def classify(design: str, prepared: Path, r_dir: Path, rf_dir: Path, reset: str = "rst_ni") -> dict[str, Any]:
    prep = json.loads((prepared / design / "prepared.json").read_text())
    r = _kills(r_dir / design / "harm" / "info.json", prep)
    rf = _kills(rf_dir / design / "harm" / "info.json", prep)
    k_r = set().union(*[m for _, m in r]) if r else set()
    k_rf = set().union(*[m for _, m in rf]) if rf else set()
    row = {"design": design, "killed_R": len(k_r), "killed_RF": len(k_rf), "lost": len(k_r - k_rf),
           "gained": len(k_rf - k_r), "reset": 0, "delay": 0, "out_of_cone": 0}  # fmt: skip
    for m in k_r - k_rf:
        killers = [a for a, ms in r if m in ms]
        own = [a for a in killers if not _consequent(a["text"]).endswith(reset)]
        if not own:
            row["reset"] += 1
        elif any(a["metrics"]["coiFrac"] >= 0.999 and a["metrics"]["coiDepthFit"] < 0.999 for a in own):
            row["delay"] += 1
        else:
            row["out_of_cone"] += 1
    return row


def main(argv: list[str] | None = None) -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("prepared", type=Path)
    ap.add_argument("r_dir", type=Path)
    ap.add_argument("rf_dir", type=Path)
    ap.add_argument("--out", type=Path, default=Path("filter.csv"))
    a = ap.parse_args(argv)
    designs = sorted(p.parent.parent.name for p in a.r_dir.glob("*/harm/info.json")
                     if (a.rf_dir / p.parent.parent.name / "harm" / "info.json").exists())  # fmt: skip
    rows = [classify(d, a.prepared, a.r_dir, a.rf_dir) for d in designs]
    with open(a.out, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=FIELDS)
        w.writeheader()
        w.writerows(rows)
    tot = {k: sum(r[k] for r in rows) for k in FIELDS[3:]}
    print(f"{len(rows)} designs: {tot}")


if __name__ == "__main__":
    main()
