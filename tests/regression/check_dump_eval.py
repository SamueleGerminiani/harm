#!/usr/bin/env python3
"""H16: --check-dump-eval writes unique, bounded, mappable files (D-030).
A1 colliding assertions get distinct files; A2 a name over 255 bytes neither exits nor
loses the dump; A3 index.json maps every file to its exact assertion text; A4 every row is
recomputed from the trace here, independently of HARM, and compared with the mapped file.
Usage: check_dump_eval.py <harm> <tests/input/h16>"""
import csv
import json
import subprocess
import sys
import tempfile
from pathlib import Path

harm, inp = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve()
rows = [{k.split()[-1]: int(v) for k, v in r.items()}  # "bool a" -> a
        for r in csv.DictReader(open(inp / "trace.csv", encoding="utf-8-sig"))]
L = "a_rather_long_signal_name_for_h16"
long_ant = " && ".join(f"{L} != {k}" for k in range(20))

# (context, Spot text, SVA text, antecedent, consequent, shift), in the order HARM checks them
c = lambda r: r["c"]
expected = [
    ("c1", "G(x != y -> c)", "always (x != y |-> c)", lambda r: r["x"] != r["y"], c, 0),
    ("c1", "G(x <= y -> c)", "always (x <= y |-> c)", lambda r: r["x"] <= r["y"], c, 0),
    ("c1", "G(a && b -> c)", "always (a && b |-> c)", lambda r: r["a"] and r["b"], c, 0),
    ("c1", "G({a & b} -> c)", "always (a and b |-> c)", lambda r: r["a"] and r["b"], c, 0),
    ("c1", "G(ab -> c)", "always (ab |-> c)", lambda r: r["ab"], c, 0),
    ("c1", "G(!a -> c)", "always (!a |-> c)", lambda r: not r["a"], c, 0),
    ("c1", "G(a -> c)", "always (a |-> c)", lambda r: r["a"], c, 0),
    ("c1", "G({a} |-> c)", "always (a |-> c)", lambda r: r["a"], c, 0),
    ("c1", "G({a} |=> c)", "always (a |=> c)", lambda r: r["a"], c, 1),
    ("c1", f"G({long_ant} -> c)", f"always ({long_ant} |-> c)",
     lambda r: all(r[L] != k for k in range(20)), c, 0),
    ("c1", "G(b -> c)", "always (b |-> c)", lambda r: r["b"], c, 0),
    ("c2", "G(a -> c)", "always (a |-> c)", lambda r: r["a"], c, 0),
]
assert len(long_ant) > 255


def sanitize(s):  # the pre-H16 character set, kept for the readable part of the name
    return "".join(ch for ch in s if ch.isascii() and (ch.isalnum() or ch in "-_.+()[]#=>|:"))


tf = lambda b: "T" if b else "F"
errors = []
with tempfile.TemporaryDirectory() as d:
    out = Path(d) / "dump"
    r = subprocess.run([harm, "--csv", str(inp / "trace.csv"), "--conf", str(inp / "check.xml"),
                        "--max-threads", "1", "--check-dump-eval", str(out)],
                       cwd=d, capture_output=True, text=True)
    if r.returncode != 0:
        errors.append(f"A2: HARM exited with {r.returncode}: {(r.stdout + r.stderr)[-800:]}")
    index_file = out / "index.json"
    if not index_file.exists():
        errors.append("A3: no index.json")
        index = {"version": None, "assertions": []}
    else:
        index = json.loads(index_file.read_text())
    if index.get("version") != "1":
        errors.append(f"A3: index version {index.get('version')!r}, expected '1'")
    entries = index.get("assertions", [])
    if len(entries) != len(expected):
        errors.append(f"A1/A3: {len(entries)} index entries, expected {len(expected)}")
    files = sorted(p.name for p in out.glob("*.csv")) if out.exists() else []
    if len(files) != len(expected):
        errors.append(f"A1: {len(files)} files, expected {len(expected)}: {files}")
    named = [e.get("file") for e in entries]
    if sorted(n for n in named if n) != files:
        errors.append(f"A3: the index's files {named} are not the directory's {files}")
    for k, (exp, e) in enumerate(zip(expected, entries)):
        ctx, spot, sva, ant, con, shift = exp
        name = f"{k}_{sanitize(spot)[:100]}.csv"
        for key, want in (("file", name), ("context", ctx), ("spot", spot), ("sva", sva)):
            if e.get(key) != want:
                errors.append(f"A3: entry {k} {key} = {e.get(key)!r}, expected {want!r}")
        if len(name.encode()) > 255:
            errors.append(f"A2: {name} is over 255 bytes")
        p = out / name
        if not p.exists():
            continue
        lines = p.read_text().splitlines()
        if lines[0] != "t, Ant, Shift, Con, Ass":
            errors.append(f"A4: {name}: header {lines[0]!r}")
        body = [[f.strip() for f in ln.split(",")] for ln in lines[1:]]
        if len(body) != len(rows):
            errors.append(f"A4: {name}: {len(body)} rows, expected {len(rows)}")
            continue
        for t, fields in enumerate(body):
            a = bool(ant(rows[t]))
            ok_at = t + shift < len(rows)
            want = [str(t), tf(a), None, tf(con(rows[t])),
                    tf((not a) or (ok_at and con(rows[t + shift])))]
            if len(fields) != 5:
                errors.append(f"A4: {name} row {t}: {len(fields)} fields: {fields}")
                continue
            if shift == 0 and fields[2] != "0":
                errors.append(f"A4: {name} row {t}: Shift {fields[2]}, expected 0")
            if shift and a and fields[2] != str(shift):
                errors.append(f"A4: {name} row {t}: Shift {fields[2]}, expected {shift}")
            for i in (0, 1, 3, 4):
                if fields[i] != want[i]:
                    errors.append(f"A4: {name} row {t} column {i}: {fields[i]}, expected {want[i]}")

for e in errors:
    print(e)
print("ok" if not errors else "FAIL")
sys.exit(0 if not errors else 1)
