#!/usr/bin/env python3
"""H3b, A4/A5 at the command line (tests/input/h3b/reduce.xml, expected sets written by hand):
  --reduce implies                      keeps the 3 assertions (H3 unchanged)
  --reduce implies --atom-premises      keeps only G(cnt > 4'd8 -> a); the dump of the 2 dropped
                                        ones lists the facts they needed
  ... --atom-premises-max 0             keeps the 3 (no fact), and says that the cap was reached
Usage: check_atom_premises.py <harm> <csv> <config>
"""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, csv, conf = sys.argv[1:4]
ALL = {"G(cnt > 4'b1000 -> a)", "G(cnt > 4'b1001 -> a)", "G(cnt == 4'b1001 -> a)"}


def run(*extra):
    with tempfile.TemporaryDirectory() as d:
        info, imp = Path(d) / "i.json", Path(d) / "imp.json"
        r = subprocess.run([harm, "--csv", csv, "--conf", conf, "--max-threads", "1", "--psilent",
                            "--reduce", "implies", "--dump-assertion-info", str(info),
                            "--dump-implications", str(imp), *extra], cwd=d, capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(r.stdout + r.stderr)
        kept = {a["text"] for a in json.loads(info.read_text())["assertions"]}
        return kept, json.loads(imp.read_text()), r.stdout + r.stderr


ok = True
kept, _, _ = run()
print(f"implies: {sorted(kept)}")
ok &= kept == ALL
kept, dump, _ = run("--atom-premises")
print(f"implies + atom premises: {sorted(kept)}")
ok &= kept == {"G(cnt > 4'b1000 -> a)"}
recs = dump["implications"]
with_premises = [r for r in recs if r.get("premises")]
print(f"dropped records with premises: {len(with_premises)} of {len(recs)}")
ok &= len(recs) == 2 and len(with_premises) == 2
kept, _, out = run("--atom-premises", "--atom-premises-max", "0")
print(f"capped at 0: {sorted(kept)}; cap message: {'cap' in out}")
ok &= kept == ALL and "atom premises: query cap" in out
print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
