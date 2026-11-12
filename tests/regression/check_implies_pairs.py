#!/usr/bin/env python3
"""H29 at the command line (tests/input/h29/reduce.xml):
  T1  --reduce implies checks only the pairs that share a consequent atom (bool variables here, no
      facts): the info.json record's pair count equals that count, computed from --reduce equiv's
      assertions, and is below the count of pairs sharing any atom
  T3  --implies-max-pairs 1: the step is skipped and recorded; the kept set is --reduce equiv's
  T4  --implies-max-pairs 0, or a cap at the count: the same as without a cap
  H33 without --implies-max-pairs there is no cap (the record's maxPairs is 0)
Usage: check_implies_pairs.py <harm> <csv> <config>
"""
import itertools
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, csv, conf = sys.argv[1:4]


def run(reduce, *extra):
    with tempfile.TemporaryDirectory() as d:
        info = Path(d) / "i.json"
        r = subprocess.run([harm, "--csv", csv, "--conf", conf, "--max-threads", "1", "--psilent",
                            "--reduce", reduce, "--dump-assertion-info", str(info), *extra],
                           cwd=d, capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(r.stdout + r.stderr)
        return json.loads(info.read_text()), r.stdout + r.stderr


def variables(a, consequent_only):
    return {v for l in a["leaves"] if not (consequent_only and l["antecedent"]) for v in l["variables"]}


ok = True
equiv, _ = run("equiv")
before = equiv["assertions"]
pairs = lambda cons: sum(1 for a, b in itertools.combinations(before, 2)
                         if variables(a, cons) & variables(b, cons))  # fmt: skip
cons_pairs, any_pairs = pairs(True), pairs(False)
equiv_kept = {a["text"] for a in before}
print(f"equiv: {len(before)} assertions; pairs sharing a consequent atom {cons_pairs}, any atom {any_pairs}")
ok &= cons_pairs < any_pairs

info, out = run("implies")
rec = info.get("implication", {}).get("default")
kept = {a["text"] for a in info["assertions"]}
print(f"T1 implies: {len(kept)} kept, record {rec}")
ok &= rec is not None and rec["pairs"] == cons_pairs and rec["skipped"] is False
ok &= rec is not None and rec["dropped"] == len(before) - len(kept) and len(kept) < len(before)
# H33: no cap by default (the reduction costs far less than proving what it drops)
ok &= rec is not None and rec["maxPairs"] == 0

info, out = run("implies", "--implies-max-pairs", "1")
rec1 = info.get("implication", {}).get("default")
kept1 = {a["text"] for a in info["assertions"]}
print(f"T3 cap 1: {len(kept1)} kept, record {rec1}")
ok &= rec1 is not None and rec1["skipped"] is True and rec1["maxPairs"] == 1 and rec1["dropped"] == 0
ok &= rec1 is not None and rec1["pairs"] == cons_pairs
ok &= kept1 == equiv_kept
ok &= f"Implication: skipped, {cons_pairs} pairs > 1" in out

for cap in ("0", str(cons_pairs)):
    info, _ = run("implies", "--implies-max-pairs", cap)
    r = info.get("implication", {}).get("default")
    k = {a["text"] for a in info["assertions"]}
    print(f"T4 cap {cap}: {len(k)} kept, record {r}")
    ok &= k == kept and r is not None and r["skipped"] is False and r["maxPairs"] == int(cap)

print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
