#!/usr/bin/env python3
"""H39 at the command line (tests/input/h29/reduce.xml):
  T1  --deadline 0 with mining left to finish (--mine-deadline far away): the implication step
      checks no pair, so the kept set is --reduce equiv's; the record says the deadline was hit
      and every pair is unchecked
  T1b a deadline far away: the output equals the run without one, and the record says so
  T3  --mine-deadline 0: mining starts no permutation, HARM exits 0, and info.json's "deadline"
      record says mining was cut (0 permutations done of more than 0)
  T3b --deadline S alone: mining's deadline is 0.75 S (the record's mineDeadline)
Usage: check_deadline.py <harm> <csv> <config>
"""
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
        return (json.loads(info.read_text()) if info.exists() else {}), r.stdout + r.stderr


ok = True
equiv, _ = run("equiv")
equiv_kept = {a["text"] for a in equiv["assertions"]}
plain, _ = run("implies")
plain_texts = [a["text"] for a in plain["assertions"]]
ok &= len(plain_texts) < len(equiv_kept)  # the fixture's reduction drops something

info, out = run("implies", "--deadline", "0", "--mine-deadline", "1000")
rec = info.get("implication", {}).get("default")
kept = {a["text"] for a in info["assertions"]}
print(f"T1 deadline 0: {len(kept)} kept (equiv {len(equiv_kept)}), record {rec}")
ok &= kept == equiv_kept
ok &= rec is not None and rec["deadlineHit"] is True and rec["unchecked"] == rec["pairs"] > 0
ok &= rec is not None and rec["dropped"] == 0

info, out = run("implies", "--deadline", "1000")
rec = info.get("implication", {}).get("default")
dl = info.get("deadline")
print(f"T1b deadline 1000: record {rec}, deadline {dl}")
ok &= [a["text"] for a in info["assertions"]] == plain_texts
ok &= rec is not None and rec["deadlineHit"] is False and rec["unchecked"] == 0
ok &= dl is not None and dl["mineCut"] is False and dl["permutationsDone"] == dl["permutationsTotal"] > 0
ok &= dl is not None and abs(dl["mineDeadline"] - 750) < 1e-6

info, out = run("implies", "--mine-deadline", "0")
dl = info.get("deadline")
print(f"T3 mine-deadline 0: {len(info.get('assertions', []))} assertions, deadline {dl}")
ok &= dl is not None and dl["mineCut"] is True and dl["permutationsDone"] == 0 < dl["permutationsTotal"]
ok &= len(info.get("assertions", [])) == 0
ok &= "Deadline: mining cut" in out

info, out = run("implies", "--deadline", "8")
dl = info.get("deadline")
print(f"T3b deadline 8: {dl}")
ok &= dl is not None and abs(dl["mineDeadline"] - 6) < 1e-6 and abs(dl["deadline"] - 8) < 1e-6

info, out = run("implies")
print(f"no deadline: deadline record {info.get('deadline')}")
ok &= "deadline" not in info

print("OK" if ok else "FAIL")
sys.exit(0 if ok else 1)
