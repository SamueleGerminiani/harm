#!/usr/bin/env python3
"""H23 R2 and R5: HARM mines on a design whose signals are named after HARM keywords.

harm-coi (with --hints all) writes the configuration; HARM mines with it, exit 0. Then:
- every proposition in the configuration names a keyword-named signal escaped ('\\W '), never bare;
- every mined assertion's SVA (info.json's text) reads only the design's signals, by their plain names, and
  SystemVerilog's own operators: no escape, no HARM operator word left in it;
- (keywords only) the expected relations of the hand-written RTL are found: W |=> next (the register next <= W),
  and assertions whose consequent reads F, R and true.

With --no-predicates (hier: pure dataflow, no RTL condition): harm-coi's default configuration has no proposition,
so HARM cannot mine; it must get past the variable declarations (no "is reserved" error) and stop as on any design
without predicates ("DT placeholder domain is empty!", multipath).

  check_keywords_mine.py FIXTURE_DIR --python PY --harm HARM --out DIR [--expect-relations | --no-predicates]"""
import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
KEYWORDS = {"X", "W", "G", "F", "R", "next", "substr", "true", "false"}
# SystemVerilog words that may appear in HARM's SVA output besides signal names
SVA_WORDS = {"always", "nexttime", "s_nexttime", "s_eventually", "eventually", "until", "s_until", "until_with",
             "s_until_with", "not", "and", "or", "intersect", "first_match", "throughout", "within", "implies",
             "iff", "disable", "posedge", "negedge", "assert", "property", "inside", "strong", "weak"}
IDENT = re.compile(r"(?<![\w'$\\])[A-Za-z_][A-Za-z0-9_$]*")


def signals(vcd: Path, scope: str) -> set[str]:
    """The variable and scope names the trace declares in `scope` and below (tb::dut -> tb, dut); a generate
    scope's index (g[0]) gives its name (g)."""
    path, names, want = [], set(), scope.split("::")
    for line in vcd.read_text(errors="ignore").splitlines():
        t = line.split()
        if t[:1] == ["$scope"]:
            path.append(t[2])
            if path[: len(want)] == want and len(path) > len(want):
                names.add(re.sub(r"\[\d+\]$", "", t[2]))
        elif t[:1] == ["$upscope"]:
            path.pop()
        elif t[:1] == ["$var"] and path[: len(want)] == want:
            names.add(t[4])
        elif t[:1] == ["$enddefinitions"]:
            break
    return names


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("fixture")
    ap.add_argument("--python", required=True)
    ap.add_argument("--harm", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--expect-relations", action="store_true")
    ap.add_argument("--no-predicates", action="store_true")
    a = ap.parse_args()
    f = Path(a.fixture)
    meta = (f / ("meta.txt" if (f / "meta.txt").exists() else "edges.txt")).read_text()
    name = re.search(r"^top = (\S+)", meta, re.M).group(1)
    r = re.search(r"^vcd_recursion = (\d+)", meta, re.M).group(1)
    out = Path(a.out) / f"h23_{name}"
    out.mkdir(parents=True, exist_ok=True)
    (out / "info.json").unlink(missing_ok=True)
    env = {**os.environ, "PYTHONPATH": str(ROOT / "tools" / "harm-coi" / "src")}
    if a.no_predicates:
        subprocess.run([a.python, "-m", "harm_coi", "--top", name, "--files",
                        *map(str, sorted((f / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut", "--vcd-recursion", r,
                        "--vcd", str(f / "trace.vcd"), "--emit-config", str(out / "cfg.xml"),
                        "-o", str(out / "coi.json")], check=True, env=env)  # fmt: skip
        h = subprocess.run([a.harm, "--vcd", str(f / "trace.vcd"), "--clk", "clk", "--vcd-ss", "tb::dut", "--vcd-r", r,
                            "--conf", str(out / "cfg.xml"), "--max-threads", "1", "--psilent", "--isilent"],
                           capture_output=True, text=True)  # fmt: skip
        log = re.sub(r"\x1b\[[0-9;]*m", "", h.stdout + h.stderr)
        (out / "harm.log").write_text(log)
        ok = "is reserved" not in log and "DT placeholder domain is empty" in log
        print(f"{name}: {'ok' if ok else 'FAIL'}: {(re.findall(r'Message: (.*)', log) or ['no message'])[0]}")
        return 0 if ok else 1
    subprocess.run([a.python, "-m", "harm_coi", "--top", name, "--files", *map(str, sorted((f / "rtl").glob("*.sv"))),
                    "--vcd-scope", "tb::dut", "--vcd-recursion", r, "--vcd", str(f / "trace.vcd"),
                    "--hints", str(out / "hints.json"), "--hints-use", "all", "--emit-config", str(out / "cfg.xml"),
                    "-o", str(out / "coi.json")], check=True, env=env)
    bad = []
    cfg = (out / "cfg.xml").read_text()
    for prop in re.findall(r'<prop exp="([^"]*)"', cfg):
        bare = {w for w in IDENT.findall(prop.replace("&amp;", "&")) if w in KEYWORDS}
        if bare:
            bad.append(f"proposition {prop!r} names {sorted(bare)} bare (expected \\name )")
    h = subprocess.run([a.harm, "--vcd", str(f / "trace.vcd"), "--clk", "clk", "--vcd-ss", "tb::dut", "--vcd-r", r,
                        "--conf", str(out / "cfg.xml"), "--max-threads", "1", "--psilent", "--isilent", "--sva",
                        "--dump-assertion-info", str(out / "info.json")], capture_output=True, text=True)
    (out / "harm.log").write_text(h.stdout + h.stderr)
    if h.returncode != 0 or not (out / "info.json").exists():
        print(f"{name}: HARM exit {h.returncode}, see {out / 'harm.log'}")
        return 1
    texts = [x["text"] for x in json.loads((out / "info.json").read_text())["assertions"]]
    known = signals(f / "trace.vcd", "tb::dut")
    for t in texts:
        if "\\" in t:
            bad.append(f"SVA with an escape: {t}")
        stray = {w for w in IDENT.findall(re.sub(r"\d+'[bodhBODH][0-9a-fA-FxzXZ_?]+", " ", t))} - known - SVA_WORDS
        if stray:
            bad.append(f"SVA reads {sorted(stray)}, not signals of the design: {t}")
    if not texts:
        bad.append("no assertion mined")
    if a.expect_relations:
        cons = lambda t: re.split(r"\|->|\|=>", t, maxsplit=1)[-1]  # noqa: E731
        if not any(re.search(r"\bW\b", t.split("|=>")[0]) and re.search(r"\bnext\b", cons(t)) for t in texts
                   if "|=>" in t):
            bad.append("W |=> next not found")
        for sig in ("F", "R", "true"):
            if not any(re.search(rf"\b{sig}\b", cons(t)) for t in texts):
                bad.append(f"no assertion with {sig} in its consequent")
    for b in bad:
        print(f"{name}: {b}")
    print(f"{name}: {len(texts)} assertions, {'FAIL' if bad else 'ok'}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
