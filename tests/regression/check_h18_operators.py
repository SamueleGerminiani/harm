#!/usr/bin/env python3
"""H18, acceptance tests A1 and A3 (D-034).
fixture  (A1, A3): every expression of tests/oracle/fixture_h18/cases.txt: HARM's value equals the
         SystemVerilog value (Icarus Verilog, cross-checked with IEEE 1800-2017) on every row where the
         case is 'ok'; 'H19:...' cases are known evaluation differences, reported only. Every
         expression HARM accepts prints to a text that re-parses to the same values and prints the same.
examples (A3): every <prop> and numeric expansion of the example configurations (the H0 regression
         cases) prints to a text that re-parses to the same values and prints the same.
Usage: check_h18_operators.py <harm> <repository> fixture|examples"""
import json
import re
import shlex
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

harm, repo, mode = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve(), sys.argv[3]
errors, notes = [], []


def esc(s):
    return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace('"', "&quot;")


def table(trace_args, props, d):
    """values and printed texts of props (one context each), or the error message"""
    d = Path(d)
    ctx = "".join(f'<context name="e{i}"><prop exp="{esc(p)}" loc="a"/></context>' for i, p in enumerate(props))
    (d / "c.xml").write_text(f"<harm>{ctx}</harm>")
    r = subprocess.run([harm] + trace_args + ["--conf", str(d / "c.xml"), "--dump-prop-table", str(d / "t.json")],
                       capture_output=True, text=True, cwd=d)
    if r.returncode != 0 or not (d / "t.json").exists():
        m = re.findall(r"Message: (.*)", re.sub(r"\x1b\[[0-9;]*m", "", r.stdout + r.stderr))
        return "ERROR: " + (m[-1] if m else "exit " + str(r.returncode))
    t = json.loads((d / "t.json").read_text())
    return [(c["propositions"][0]["values"], c["propositions"][0]["text"]) for c in t["contexts"]]


def round_trip(trace_args, exp, values, text, d):
    """the printed text re-parses to the same values and prints the same"""
    again = table(trace_args, [text], d)
    if isinstance(again, str):
        return f"{exp!r} prints {text!r}, which HARM rejects: {again}"
    v2, t2 = again[0]
    if v2 != values:
        return f"{exp!r} prints {text!r}, which re-parses to other values"
    if t2 != text:
        return f"{exp!r} prints {text!r}, which re-prints as {t2!r}"
    return None


if mode == "fixture":
    fx = repo / "tests/oracle/fixture_h18"
    args = ["--csv", str(fx / "trace.csv")]
    cases = [l.split("|", 3) for l in (fx / "cases.txt").read_text().splitlines()]

    def one(c):
        expect, cat, sv, exp = c
        with tempfile.TemporaryDirectory() as d:
            got = table(args, [exp], d)
            if isinstance(got, str):
                return c, got, None
            values, text = got[0]
            return c, values, round_trip(args, exp, values, text, d)

    with ThreadPoolExecutor(8) as ex:
        results = list(ex.map(one, cases))
    known = 0
    for (expect, cat, sv, exp), values, rt in results:
        if values != sv:
            if expect == "ok":
                errors.append(f"A1 [{cat}] {exp!r}: HARM {values}, SystemVerilog {sv}")
            else:
                known += 1
        elif expect != "ok":
            notes.append(f"{expect} {exp!r} now agrees (H19 can drop it)")
        if rt:
            errors.append("A3 " + rt)
    print(f"{len(cases)} cases: {sum(1 for c in cases if c[0] == 'ok')} must agree; "
          f"{known} known H19 differences; {len(notes)} known differences that now agree")

if mode == "examples":
    # the H0 regression cases with a configuration: their propositions, on their traces
    text = (repo / "tests/regression/cases.cmake").read_text().replace("${EX}", str(repo / "examples")) \
        .replace("${CMAKE_SOURCE_DIR}", str(repo))
    for k, v in re.findall(r"set\((\w+) ([^)\s]+)\)", text):
        text = text.replace("${" + k + "}", v)
    runs = []
    for m in re.finditer(r"harm_case\((\w+)[^)]*?ARGS ([^)]*)\)", text):
        a = shlex.split(m.group(2))
        if "--conf" not in a:
            continue
        keep = []
        i = 0
        while i < len(a):  # the trace options only
            if a[i] in ("--vcd", "--csv", "--vcd-dir", "--csv-dir", "--clk", "--vcd-ss", "--vcd-r"):
                keep += a[i:i + 2]
                i += 2
            else:
                i += 1
        runs.append((m.group(1), keep, a[a.index("--conf") + 1]))
    checked = 0
    for name, targs, conf in runs:
        with tempfile.TemporaryDirectory() as d:
            out = Path(d) / "t.json"
            r = subprocess.run([harm] + targs + ["--conf", conf, "--dump-prop-table", str(out)],
                               capture_output=True, text=True, cwd=d)
            if not out.exists():
                notes.append(f"{name}: no table ({r.returncode})")
                continue
            props = [p for c in json.loads(out.read_text())["contexts"] for p in c["propositions"]]
            for p in props:
                rt = round_trip(targs, p["text"], p["values"], p["text"], d)
                checked += 1
                if rt:
                    errors.append(f"A3 {name}: {rt}")
    print(f"{len(runs)} example configurations, {checked} propositions checked")

import collections
for k, v in sorted(collections.Counter(re.match(r"A\d( \[\w+\])?", e).group(0) for e in errors).items()):
    print(f"  {v:4} {k}")
import os
shown = len(errors) if os.environ.get("H18_ALL") else 60
for e in errors[:shown]:
    print(e)
if len(errors) > shown:
    print(f"... {len(errors) - shown} more (H18_ALL=1 shows all)")
for n in notes[:20]:
    print("note:", n)
print("ok" if not errors else f"FAIL ({len(errors)})")
sys.exit(0 if not errors else 1)
