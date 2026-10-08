#!/usr/bin/env python3
"""H14, acceptance A3: the runnable examples of the v4 documentation run and print what they show.

An example is a code block marked as runnable:
  - Markdown (README, migration guide, developer guide, harm-coi README): a fenced block right after `<!-- example -->`;
  - LaTeX (doc/report/**/*.tex): an `lstlisting` environment right after a `% example` line.
In the block, a line starting with `$ ` is a command (a trailing `\\` continues it on the next line);
every other non-empty line, except `...`, is expected output: after the ANSI colours are removed and
runs of blank space are collapsed, it must appear in what the block's commands print (stdout and
stderr). The commands run with bash in a scratch directory that links every top-level entry of the
repository (so `examples/ex3/ex3.csv` works, and the log files HARM writes stay out of the checkout),
with `harm` (and `harm-coi`, if given) first on PATH and `$OUT` set to an empty directory shared by
the block's commands. Every command must exit with 0.
Each document must have at least one example. An example that needs harm-coi is skipped, and said so,
when --harm-coi is not given.
Usage: run_examples.py <repository root> --harm <path> [--harm-coi <path>]
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ap = argparse.ArgumentParser()
ap.add_argument("root")
ap.add_argument("--harm", required=True)
ap.add_argument("--harm-coi")
args = ap.parse_args()
root = Path(args.root).resolve()

DOCS = [root / "README.md", root / "doc/MIGRATING_v3_to_v4.md", root / "doc/DEVELOPER_GUIDE.md",
        root / "tools/harm-coi/README.md"]
DOCS += sorted((root / "doc/report").rglob("*.tex"))
MD_RE = re.compile(r"<!-- example -->\s*\n```[^\n]*\n(.*?)```", re.S)
TEX_RE = re.compile(r"^%\s*example\s*\n\\begin\{lstlisting\}[^\n]*\n(.*?)\\end\{lstlisting\}", re.S | re.M)
ANSI = re.compile(r"\x1b\[[0-9;]*m")


def norm(s):
    return " ".join(s.split())


def parse(block):
    cmds, expect, cur = [], [], None
    for line in block.splitlines():
        if cur is not None:
            cur += "\n" + line
            if not line.rstrip().endswith("\\"):
                cmds.append(cur)
                cur = None
        elif line.startswith("$ "):
            if line.rstrip().endswith("\\"):
                cur = line[2:]
            else:
                cmds.append(line[2:])
        elif line.strip() and line.strip() != "...":
            expect.append(line)
    return cmds, expect


failures, counts, skipped = [], {}, 0
with tempfile.TemporaryDirectory() as bindir:
    os.symlink(Path(args.harm).resolve(), Path(bindir) / "harm")
    if args.harm_coi:
        os.symlink(Path(args.harm_coi).resolve(), Path(bindir) / "harm-coi")
    for doc in DOCS:
        rel = doc.relative_to(root)
        if not doc.exists():
            failures.append(f"{rel}: missing")
            continue
        text = doc.read_text(encoding="utf-8")
        blocks = (TEX_RE if doc.suffix == ".tex" else MD_RE).findall(text)
        counts[str(rel)] = len(blocks)
        for i, block in enumerate(blocks, 1):
            cmds, expect = parse(block)
            where = f"{rel}, example {i}"
            if not cmds:
                failures.append(f"{where}: no command")
                continue
            if any(re.search(r"(^|\s)harm-coi\s", c) for c in cmds) and not args.harm_coi:
                print(f"skipped (needs --harm-coi): {where}")
                skipped += 1
                continue
            out = ""
            with tempfile.TemporaryDirectory() as work:
                for entry in root.iterdir():
                    if not entry.name.startswith("."):
                        os.symlink(entry, Path(work) / entry.name)
                out_dir = Path(work) / "OUT"
                out_dir.mkdir()
                env = dict(os.environ, PATH=f"{bindir}:{os.environ['PATH']}", OUT=str(out_dir))
                for c in cmds:
                    r = subprocess.run(["bash", "-c", c], cwd=work, env=env, capture_output=True,
                                       text=True, timeout=600)
                    out += r.stdout + r.stderr
                    if r.returncode != 0:
                        failures.append(f"{where}: exit {r.returncode}: {c}\n{ANSI.sub('', out)[-2000:]}")
                        break
                else:
                    got = norm(ANSI.sub("", out))
                    for e in expect:
                        if norm(e) not in got:
                            failures.append(f"{where}: expected output not printed: {e.strip()}\n"
                                            f"--- printed:\n{ANSI.sub('', out)[-3000:]}")
                            break
                    else:
                        print(f"ok: {where} ({len(cmds)} command(s), {len(expect)} expected line(s))")

# every document has at least one runnable example (the report as a whole)
report = sum(n for d, n in counts.items() if d.endswith(".tex"))
for d, n in counts.items():
    if not d.endswith(".tex") and n == 0:
        failures.append(f"{d}: no runnable example")
if report == 0:
    failures.append("doc/report: no runnable example")
for f in failures:
    print("FAIL:", f)
print(f"{sum(counts.values())} example(s), {skipped} skipped, {len(failures)} failure(s)")
sys.exit(1 if failures else 0)
