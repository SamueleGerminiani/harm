#!/usr/bin/env python3
"""Independent check of HARM's SystemVerilog output (H1 validation, D-002).

HARM mines assertions on a 2-valued CSV trace and prints them with --sva --sva-assert. A generated
testbench replays the same trace and checks every printed assertion in Verilator:
  1. lint: each assertion must be valid SystemVerilog for Verilator; constructs Verilator reports
     as unsupported are counted separately (not errors of HARM's printer);
  2. simulation: every supported mined assertion must have zero failures (HARM says it holds);
  3. negative control: the same assertion with its consequent negated must fail at least once,
     which shows that the replay actually exercises the assertion.

Verilator is 2-state, so the trace must contain only 0/1 values.

Usage: verilator_replay.py --harm <bin> --csv <trace.csv> --conf <config.xml> [--keep <dir>]
Exit status: 0 if all checks pass.
"""
import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

DECL = re.compile(r"^\s*(?:logic|reg|wire|bool)\s*(?:\[(\d+):(\d+)\])?\s*([A-Za-z_][\w:.]*)\s*$")


def read_csv(path):
    lines = [l.strip() for l in Path(path).read_text().splitlines() if l.strip()]
    header = [h.strip().lstrip("﻿") for h in lines[0].split(",")]
    sigs = []
    for h in header:
        m = DECL.match(h)
        if not m:
            sys.exit(f"unsupported declaration in CSV header: '{h}' (logic/reg/wire/bool only)")
        width = int(m.group(1)) - int(m.group(2)) + 1 if m.group(1) else 1
        sigs.append((m.group(3), width))
    rows = []
    for l in lines[1:]:
        vals = [v.strip() for v in l.split(",")]
        for v in vals:
            if set(v) - set("01"):
                sys.exit(f"the trace must be 2-valued for Verilator, found '{v}'")
        rows.append(vals)
    return sigs, rows


def split_implication(body):
    """(antecedent, operator, consequent) for a top-level |-> or |=>, else None."""
    depth = 0
    for i in range(len(body) - 2):
        c = body[i]
        if c in "({[":
            depth += 1
        elif c in ")}]":
            depth -= 1
        elif depth == 0 and body[i:i + 3] in ("|->", "|=>"):
            return body[:i].strip(), body[i:i + 3], body[i + 3:].strip()
    return None


def split_top(text, sep):
    """split 'text' at top-level occurrences of 'sep' (outside brackets)"""
    parts, depth, start, i = [], 0, 0, 0
    while i < len(text):
        c = text[i]
        if c in "({[":
            depth += 1
        elif c in ")}]":
            depth -= 1
        elif depth == 0 and text.startswith(sep, i):
            parts.append(text[start:i].strip())
            i += len(sep)
            start = i
            continue
        i += 1
    parts.append(text[start:].strip())
    return parts


def delay_free(text):
    return not re.search(r"##|until|eventually|nexttime|\bnot\b|\bor\b|\band\b", text)


def past_encoding(body):
    """Verilator 5 does not support '##' in properties. For an assertion made of boolean steps,
    'b0 ##1 b1 ... ##1 bk |-> ##n q' (or '|=>') fails at t iff b0..bk held at t-k-s..t-s and q is
    false at t, with s = n (+1 for |=>). Encode it as
    'cyc >= k+s && $past(b0, k+s) && ... && $past(bk, s) |-> q' (an independent encoding, used only
    to check HARM's printing). Returns None if the assertion is not of this form."""
    imp = split_implication(body)
    if imp is None:
        return None
    ant, op, cons = imp
    steps = split_top(ant, "##1")
    m = re.match(r"^##(\d+)\s+(.*)$", cons)
    n, q = (int(m.group(1)), m.group(2)) if m else (0, cons)
    if not all(delay_free(x) for x in steps + [q]):
        return None
    shift = n + (1 if op == "|=>" else 0)
    k = len(steps) - 1
    conds = [f"cyc >= {k + shift}"]
    for j, b in enumerate(steps):
        d = k - j + shift
        conds.append(f"({b})" if d == 0 else f"$past({b}, {d})")
    return " && ".join(conds) + f" |-> ({q})"


def property_body(line):
    m = re.match(r"^assert property \(@\(posedge clk\) \((.*)\)\)$", line.strip())
    if not m:
        sys.exit(f"unexpected --sva-assert line: {line}")
    return m.group(1)


def testbench(sigs, rows, props):
    """props: list of (label, property body)."""
    decl = "\n".join(f"  logic [{w - 1}:0] {n};" if w > 1 else f"  logic {n};" for n, w in sigs)
    drive = []
    for r in rows:
        drive.append("    " + " ".join(f"{n} = {w}'b{v};" for (n, w), v in zip(sigs, r)))
        drive.append("    #5 clk = 1; #5 clk = 0;")
    checks = "\n".join(
        f'  {label}: assert property (@(posedge clk) ({body})) else $display("FAIL {label} %0t", $time);'
        for label, body in props)
    counter = "  logic [31:0] cyc = 0;\n  always @(posedge clk) cyc <= cyc + 1;\n"
    return (f"module tb;\n  logic clk = 0;\n{decl}\n{counter}{checks}\n  initial begin\n" + "\n".join(drive) +
            "\n    #1 $finish;\n  end\nendmodule\n")


def verilator(args, cwd):
    return subprocess.run(["verilator"] + args, cwd=cwd, capture_output=True, text=True)


def classify(sigs, rows, body, work):
    """'ok', 'unsupported' or 'error: <message>' from a Verilator lint of one assertion."""
    (work / "lint.sv").write_text(testbench(sigs, rows[:1], [("a", body)]))
    r = verilator(["--lint-only", "--timing", "-Wno-fatal", "-Wno-lint", "--top-module", "tb", "lint.sv"], work)
    errors = [l for l in r.stderr.splitlines()
              if l.startswith("%Error") and not l.startswith("%Error: Exiting due to")]
    if not errors:
        return "ok"
    if all("Unsupported" in l or "UNSUPPORTED" in l for l in errors):
        return "unsupported"
    return "error: " + errors[0]


def simulate(sigs, rows, props, work, name):
    (work / f"{name}.sv").write_text(testbench(sigs, rows, props))
    r = verilator(["--binary", "--timing", "--assert", "-Wno-fatal", "-Wno-lint", "--top-module", "tb",
                   "-o", name, "--Mdir", f"obj_{name}", f"{name}.sv"], work)
    if r.returncode != 0:
        sys.exit(f"Verilator build failed for {name}:\n{r.stderr[-2000:]}")
    out = subprocess.run([str(work / f"obj_{name}" / name)], capture_output=True, text=True).stdout
    fails = {}
    for l in out.splitlines():
        m = re.match(r"FAIL (\S+) (\d+)", l.strip())
        if m:
            fails.setdefault(m.group(1), []).append(int(m.group(2)))
    return fails


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--harm", required=True)
    ap.add_argument("--csv", required=True)
    ap.add_argument("--conf", required=True)
    ap.add_argument("--keep", help="keep the generated files in this directory")
    a = ap.parse_args()

    sigs, rows = read_csv(a.csv)
    work = Path(a.keep) if a.keep else Path(tempfile.mkdtemp())
    if a.keep:
        shutil.rmtree(work, ignore_errors=True)
    (work / "dump").mkdir(parents=True)
    r = subprocess.run([str(Path(a.harm).resolve()), "--csv", str(Path(a.csv).resolve()), "--conf", str(Path(a.conf).resolve()),
                        "--clk", "clk", "--sva", "--sva-assert", "--max-threads", "1", "--isilent", "--psilent",
                        "--dump-to", str(work / "dump") + "/"], cwd=work, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"HARM failed:\n{r.stdout[-2000:]}{r.stderr[-2000:]}")
    lines = []
    for f in sorted((work / "dump").iterdir()):
        if not f.name.endswith("_faultCov.txt"):
            lines += [l for l in f.read_text().splitlines() if l.strip()]
    bodies = [property_body(l) for l in lines]

    status, checked = {}, {}
    for i, b in enumerate(bodies):
        status[i] = classify(sigs, rows, b, work)
        if status[i] == "ok":
            checked[i] = b
        elif status[i] == "unsupported":
            enc = past_encoding(b)
            if enc is not None and classify(sigs, rows, enc, work) == "ok":
                status[i] = "encoded"
                checked[i] = enc
    supported = sorted(checked)

    props, controls = [], []
    for i in supported:
        props.append((f"a{i}", checked[i]))
        imp = split_implication(checked[i])
        # 'not', the property negation (IEEE 1800): '!' is Boolean and invalid on a sequence or a
        # property consequent (##1 b, s_eventually, until), which Verilator >= 5.052 rejects (F-L6)
        neg = f"{imp[0]} {imp[1]} not ({imp[2]})" if imp else f"not ({checked[i]})"
        controls.append((f"a{i}", neg))
    fails = simulate(sigs, rows, props, work, "sim") if props else {}
    control_fails = simulate(sigs, rows, controls, work, "ctl") if controls else {}

    ok = True
    print(f"{a.conf}: {len(bodies)} assertions; Verilator: "
          f"{sum(s == 'ok' for s in status.values())} checked as printed, "
          f"{sum(s == 'encoded' for s in status.values())} checked through the $past encoding, "
          f"{sum(s == 'unsupported' for s in status.values())} unsupported, "
          f"{sum(s.startswith('error') for s in status.values())} lint errors")
    for i, s in status.items():
        if s.startswith("error"):
            ok = False
            print(f"  LINT ERROR  {lines[i]}\n              {s}")
        elif s == "unsupported":
            print(f"  unsupported {lines[i]}")
    for i in supported:
        if f"a{i}" in fails:
            ok = False
            print(f"  FAILS IN VERILATOR (HARM says it holds) at {fails[f'a{i}'][:5]}: {lines[i]}")
        if f"a{i}" not in control_fails:
            ok = False
            print(f"  CONTROL DID NOT FIRE (negated consequent never failed): {lines[i]}")
    print("  result:", "PASS" if ok else "FAIL")
    if not a.keep:
        shutil.rmtree(work, ignore_errors=True)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
