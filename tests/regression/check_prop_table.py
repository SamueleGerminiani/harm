#!/usr/bin/env python3
"""H15: --dump-prop-table, the proposition table (prop-table v1, D-031).
xz  (A1): tests/input/h1b; every cell equals --check-dump-eval's Ant column for G(p -> k) and the
          HARM values written by hand in check_x_semantics.py.
vcd (A2-A4): the counter VCD twice (--vcd-dir), --clk clk, --reset rst; every cell equals
          --check-dump-eval and a VCD reader written here (no HARM code); the header equals the
          hand-written expectation; HARM's stdout is the same with and without the option.
Usage: check_prop_table.py <harm> <repository> xz|vcd"""
import ast
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

harm, repo, mode = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve(), sys.argv[3]
errors = []


def run(args, cwd):
    r = subprocess.run([harm] + args + ["--max-threads", "1"], cwd=cwd, capture_output=True, text=True)
    if r.returncode != 0:
        errors.append(f"HARM {args} exited with {r.returncode}: {(r.stdout + r.stderr)[-600:]}")
    return r


def check_dump(trace_args, props, consequent, d):
    """values of each proposition from --check-dump-eval (the Ant column of G(p -> consequent))"""
    conf = Path(d) / "check.xml"
    tpl = "\n".join(f'<template check="1" exp="G({esc(p)} -> {consequent})"/>' for p in props)
    conf.write_text(f'<harm><context name="check">\n{tpl}\n</context></harm>\n')
    out = Path(d) / "dump"
    run(trace_args + ["--conf", str(conf), "--check-dump-eval", str(out)], d)
    got = {}
    for e in json.loads((out / "index.json").read_text())["assertions"]:
        rows = (out / e["file"]).read_text().splitlines()[1:]
        got[len(got)] = "".join("1" if r.split(",")[1].strip() == "T" else "0" for r in rows)
    return [got[i] for i in range(len(props))]


def esc(s):
    return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace('"', "&quot;")


def table(trace_args, conf, d, extra=()):
    out = Path(d) / "table.json"
    r = run(trace_args + ["--conf", str(conf), "--dump-prop-table", str(out)] + list(extra), d)
    if not out.exists():
        errors.append("no table written")
        return None, r
    return json.loads(out.read_text()), r


def compare(name, got, want):
    if got != want:
        diff = [t for t, (a, b) in enumerate(zip(got, want)) if a != b]
        errors.append(f"{name}: {len(diff)} cells differ (first cycles {diff[:5]}), lengths {len(got)}/{len(want)}")


# ---- A1: x/z values, CSV ------------------------------------------------------------------------------
if mode == "xz":
    h1b = repo / "tests/input/h1b"
    src = (repo / "tests/regression/check_x_semantics.py").read_text()
    cases = ast.literal_eval(re.search(r"CASES = (\{.*?\n\})", src, re.S).group(1))
    norm = lambda t: t.replace(" ", "")
    hand = {norm(p): h for p, (h, _) in cases.items()}
    with tempfile.TemporaryDirectory() as d:
        args = ["--csv", str(h1b / "x_values.csv")]
        t, _ = table(args, h1b / "x_values.xml", d)
        if t:
            props = t["contexts"][0]["propositions"]
            if len(props) != len(cases):
                errors.append(f"A1: {len(props)} propositions, expected {len(cases)}")
            oracle = check_dump(args, [p["text"] for p in props], "k", d)
            for p, o in zip(props, oracle):
                compare(f"A1 {p['text']} vs --check-dump-eval", p["values"], o)
                h = hand.get(norm(p["text"]))
                if h is None:
                    errors.append(f"A1: {p['text']} is not in check_x_semantics.py")
                else:
                    compare(f"A1 {p['text']} vs check_x_semantics.py", p["values"], ("1" if h else "0") * t["length"])

# ---- A2-A4: VCD, two traces, reset --------------------------------------------------------------------
def read_vcd(path, scope, clock):
    """values of scope's own variables just before each rising edge of clock (D-005), as ints or None (x/z)"""
    tokens = Path(path).read_text().split()
    ids, depth, i = {}, [], 0
    while tokens[i] != "$enddefinitions":
        if tokens[i] == "$scope":
            depth.append(tokens[i + 2]); i += 3
        elif tokens[i] == "$upscope":
            depth.pop(); i += 1
        elif tokens[i] == "$var":
            if depth == [scope]:
                ids.setdefault(tokens[i + 3], tokens[i + 4])
            i += 5
        else:
            i += 1
    cur, step, rows = {}, {}, []

    def end_of_step():
        if step.get(clock) == 1 and cur.get(clock) != 1:
            rows.append(dict(cur))  # the values before this time step: the preponed view
        cur.update(step)
        step.clear()

    i += 2
    while i < len(tokens):
        tok = tokens[i]
        if tok.startswith("#"):
            end_of_step()
        elif tok.startswith("$"):
            pass  # $dumpvars, $end, ...
        else:
            if tok[0] in "bB":
                val, ident = tok[1:], tokens[i + 1]; i += 1
            else:
                val, ident = tok[0], tok[1:]
            if ident in ids:
                step[ids[ident]] = None if re.search("[xzXZ]", val) else int(val, 2)
        i += 1
    end_of_step()
    return rows


def py_value(text, row):
    """evaluate a proposition printed by HARM on integer signal values (no x/z in this trace)"""
    e = re.sub(r"(\d+)'([bdh])([0-9a-fA-F_]+)",
               lambda m: str(int(m.group(3).replace("_", ""), {"b": 2, "d": 10, "h": 16}[m.group(2)])), text)
    e = e.replace("&&", " and ").replace("||", " or ")
    e = re.sub(r"!(?!=)", " not ", e)
    return bool(eval(e, {}, dict(row)))


if mode == "vcd":
    vcd = repo / "tests/input/coi/counter/trace.vcd"
    conf = repo / "tests/input/h15/counter.xml"
    with tempfile.TemporaryDirectory() as d:
        tr = Path(d) / "traces"
        tr.mkdir()
        for n in ("t0.vcd", "t1.vcd"):
            shutil.copy(vcd, tr / n)
        args = ["--vcd-dir", str(tr), "--vcd-ss", "tb", "--clk", "clk", "--reset", "rst"]
        t, with_table = table(args, conf, d)
        if t:
            rows = read_vcd(vcd, "tb", "clk")
            n = len(rows)
            files = [Path(x["file"]).name for x in t.get("traces", [])]
            # ---- A3: the header
            exp_traces = [{"first": 0, "last": n - 1}, {"first": n, "last": 2 * n - 1}]
            if sorted(files) != ["t0.vcd", "t1.vcd"] or \
                    [{k: x[k] for k in ("first", "last")} for x in t["traces"]] != exp_traces:
                errors.append(f"A3: traces {t.get('traces')}")
            for key, want in (("format", "prop-table"), ("version", "1"), ("length", 2 * n),
                              ("sampling", {"input": "vcd", "clock": "clk", "edge": "posedge",
                                            "values": "preponed"})):
                if t.get(key) != want:
                    errors.append(f"A3: {key} = {t.get(key)!r}, expected {want!r}")
            if not str(t.get("harm", "")).strip():
                errors.append("A3: no harm version")
            segs = []
            for base in (0, n):  # a segment ends at the last cycle of each run of reset, and at each trace's end
                start = base
                for c in range(n):
                    if rows[c]["rst"] and (c + 1 == n or not rows[c + 1]["rst"]):
                        segs.append([start, base + c]); start = base + c + 1
                if start <= base + n - 1:
                    segs.append([start, base + n - 1])
            if t.get("segments") != segs:
                errors.append(f"A3: segments {t.get('segments')}, expected {segs}")
            ctx = {c["name"]: c for c in t["contexts"]}
            if list(ctx) != ["default", "c2"]:
                errors.append(f"A3: contexts {list(ctx)}")
            want_props = {
                "default": [("en", ["a", "c", "dt"], "prop", None, "rtl"), ("wrap", ["c"], "prop", None, None)],
                "c2": [("rst", ["a"], "prop", None, None), ("cnt == 4'b1001", ["c"], "prop", None, None)],
            }
            for name, want in want_props.items():
                props = ctx.get(name, {}).get("propositions", [])
                got = [(p["text"], p["domains"], p["source"], p.get("numeric"), p["origin"]) for p in props[:len(want)]]
                if got != want:
                    errors.append(f"A3: {name} propositions {got}, expected {want}")
                if [p["id"] for p in props] != list(range(len(props))):
                    errors.append(f"A3: {name} ids are not 0..{len(props) - 1}")
            num = ctx.get("default", {}).get("propositions", [])[2:]
            if not num or any((p["source"], p.get("numeric"), p["domains"], p["origin"]) != ("numeric", "cnt", ["a"], None)
                              for p in num):
                errors.append(f"A3: the numeric's expansion {[(p['text'], p['source']) for p in num]}")
            if len({p["text"] for p in num}) != len(num):
                errors.append("A3: a numeric's expansion repeats a text")
            if ctx.get("default", {}).get("unexpanded_numerics") != [{"text": "cnt", "domains": ["dt"]}] or \
                    ctx.get("c2", {}).get("unexpanded_numerics") != []:
                errors.append(f"A3: unexpanded_numerics {[c.get('unexpanded_numerics') for c in t['contexts']]}")
            # ---- A2: every cell, against check mode and against the VCD reader here
            for name, c in ctx.items():
                props = c["propositions"]
                oracle = check_dump(args, [p["text"] for p in props], "wrap", d)
                for p, o in zip(props, oracle):
                    compare(f"A2 {name} {p['text']} vs --check-dump-eval", p["values"], o)
                    mine = "".join("1" if py_value(p["text"], r) else "0" for r in rows) * 2
                    compare(f"A2 {name} {p['text']} vs the VCD reader", p["values"], mine)
            # ---- A4: the rest of HARM's output does not change
            plain = run(args + ["--conf", str(conf)], d)
            strip = lambda s: [l for l in s.splitlines() if not re.search(r"\d\d:\d\d:\d\d|Time to mine", l)]
            if strip(plain.stdout) != strip(with_table.stdout):
                errors.append("A4: stdout differs with --dump-prop-table")

for e in errors:
    print(e)
print("ok" if not errors else "FAIL")
sys.exit(0 if not errors else 1)
