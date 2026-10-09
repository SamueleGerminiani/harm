#!/usr/bin/env python3
"""H17, acceptance tests A3 and A5.
exclusion (A3): a float <numeric>'s excluded values (<N>E) are compared with the values, not the
               cycle index; integers unchanged. Expected propositions written by hand.
order     (A5): --vcd-dir and --csv-dir read the files in path order (D-033).
Usage: check_h17.py <harm> <repository> exclusion|order"""
import json
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

harm, repo, mode = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve(), sys.argv[3]
errors = []


def table(args, conf_text, d):
    conf, out = Path(d) / "conf.xml", Path(d) / "table.json"
    conf.write_text(conf_text)
    out.unlink(missing_ok=True)
    r = subprocess.run([harm] + args + ["--conf", str(conf), "--max-threads", "1", "--dump-prop-table", str(out)],
                       cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not out.exists():
        errors.append(f"HARM {args} failed: {(r.stdout + r.stderr)[-500:]}")
        return None
    return json.loads(out.read_text())


if mode == "exclusion":
    # f: 1.5, 2.0, 2.0, 3.0, 9.5, 7.25 (7.25 only at cycle 5); i: 7, 5, 5, 7, 5, 7
    ALL = {"f == 1.5", "f == 2", "f == 3", "f == 9.5", "f == 7.25"}
    cases = [  # (float option, int option, expected f propositions, expected i propositions)
        ("", "", ALL, {"i == 5", "i == 7"}),
        (",2E", "", ALL - {"f == 2"}, {"i == 5", "i == 7"}),
        (",2.0E", "", ALL - {"f == 2"}, {"i == 5", "i == 7"}),
        (",5E", "", ALL, {"i == 5", "i == 7"}),          # no value 5.0: nothing excluded (cycle 5 holds 7.25)
        (",2E,9.5E", ",5E", ALL - {"f == 2", "f == 9.5"}, {"i == 7"}),
    ]
    with tempfile.TemporaryDirectory() as d:
        for fopt, iopt, want_f, want_i in cases:
            t = table(["--csv", str(repo / "tests/input/h17/floats.csv")],
                      f'<harm><context name="t">'
                      f'<numeric exp="f" loc="a" clustering="K,10Max,0.01WCSS,=={fopt}"/>'
                      f'<numeric exp="i" loc="a" clustering="K,10Max,0.01WCSS,=={iopt}"/>'
                      f'</context></harm>', d)
            if t is None:
                continue
            got = {p["text"] for p in t["contexts"][0]["propositions"]}
            got_f = {x for x in got if x.startswith("f ")}
            got_i = {x for x in got if x.startswith("i ")}
            if got_f != want_f or got_i != want_i:
                errors.append(f"A3 f{fopt!r} i{iopt!r}: got {sorted(got)}, expected {sorted(want_f | want_i)}")

if mode == "order":
    ex = repo / "examples"
    with tempfile.TemporaryDirectory() as d:
        for args, conf in (
                (["--csv-dir", str(ex / "multiTrace/csv")], '<harm><context name="t"><prop exp="1" loc="a"/></context></harm>'),
                (["--csv-dir", str(ex / "process/traces")], '<harm><context name="t"><prop exp="1" loc="a"/></context></harm>')):
            t = table(args, conf, d)
            if t:
                files = [x["file"] for x in t["traces"]]
                if files != sorted(files):
                    errors.append(f"A5 {args[1]}: not in path order: {[Path(f).name for f in files]}")
        vcd = Path(d) / "vcds"
        vcd.mkdir()
        for n in ("t1.vcd", "t0.vcd", "t2.vcd"):  # written out of order
            shutil.copy(repo / "tests/input/coi/counter/trace.vcd", vcd / n)
        t = table(["--vcd-dir", str(vcd), "--vcd-ss", "tb", "--clk", "clk"],
                  '<harm><context name="t"><prop exp="en" loc="a"/></context></harm>', d)
        if t:
            names = [Path(x["file"]).name for x in t["traces"]]
            if names != ["t0.vcd", "t1.vcd", "t2.vcd"]:
                errors.append(f"A5 --vcd-dir: {names}")

for e in errors:
    print(e)
print("ok" if not errors else "FAIL")
sys.exit(0 if not errors else 1)
