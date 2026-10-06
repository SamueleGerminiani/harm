#!/usr/bin/env python3
"""harm-coi on an H4 fixture, compared with the hand-written ground truth (H5, A1 and A2).

  A1  coi.json equals the fixture's expected_coi.json, order-insensitive; meta.generator aside.
      The output must also pass check_coi.py (schema, names against the trace, with --harm).
  A2  the direct edges (--edges) equal the fixture's edges.txt.

The generator's arguments come from the edges.txt header (top, vcd_scope, vcd_recursion, max_depth).

Usage: check_generator.py <fixture dir> --python <python with pyslang> [--harm <bin>] [--out <dir>]
"""
import argparse
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOL = HERE.parent.parent / "tools" / "harm-coi" / "src"


def read_edges(path):
    meta, lines = {}, set()
    for line in Path(path).read_text().splitlines():
        line = line.split("#")[0].strip()
        if not line:
            continue
        if "<-" in line or line.startswith("target ") or line.startswith("unknown "):
            lines.add(" ".join(line.split()))
        else:
            k, v = [x.strip() for x in line.split("=", 1)]
            meta[k] = v
    return meta, lines


def normalise(coi):
    targets = {t: sorted((json.dumps(s, sort_keys=True) for s in c["sources"]))
               for t, c in coi["targets"].items()}
    meta = {k: v for k, v in coi["meta"].items() if k != "generator"}
    return {"version": coi["version"], "meta": meta, "targets": targets,
            "unknown": sorted(coi.get("unknown", [])), "predicates": coi.get("predicates", [])}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("fixture")
    ap.add_argument("--python", required=True)
    ap.add_argument("--harm")
    ap.add_argument("--out")
    a = ap.parse_args()
    fx = Path(a.fixture).resolve()
    out = Path(a.out or tempfile.mkdtemp())
    out.mkdir(parents=True, exist_ok=True)
    meta, hand_edges = read_edges(fx / "edges.txt")
    coi_path, edges_path = out / f"{fx.name}_coi.json", out / f"{fx.name}_edges.txt"
    cmd = [a.python, "-m", "harm_coi", "--top", meta["top"],
           "--files", *[str(p) for p in sorted((fx / "rtl").glob("*.sv"))],
           "--vcd-scope", meta["vcd_scope"], "--vcd-recursion", meta["vcd_recursion"],
           "--vcd", str(fx / "trace.vcd"), "--max-depth", meta["max_depth"],
           "--edges", str(edges_path), "-o", str(coi_path)]
    r = subprocess.run(cmd, env={**os.environ, "PYTHONPATH": str(TOOL)}, capture_output=True, text=True)
    sys.stderr.write(r.stderr)
    if r.returncode != 0:
        print(f"[{fx.name}] harm-coi failed (exit {r.returncode})")
        sys.exit(1)
    ok = True

    # A2: direct edges
    _, mine = read_edges(edges_path)
    if mine != hand_edges:
        ok = False
        print(f"[{fx.name}] A2 edges differ:")
        for x in sorted(hand_edges - mine):
            print(f"  missing: {x}")
        for x in sorted(mine - hand_edges):
            print(f"  extra:   {x}")

    # A1: the closed cones
    got = json.loads(coi_path.read_text())
    want = json.loads((fx / "expected_coi.json").read_text())
    g, w = normalise(got), normalise(want)
    if g != w:
        ok = False
        print(f"[{fx.name}] A1 coi.json differs from expected_coi.json:")
        for k in ("version", "meta", "unknown", "predicates"):
            if g[k] != w[k]:
                print(f"  {k}: got {g[k]} want {w[k]}")
        for t in sorted(set(g["targets"]) | set(w["targets"])):
            if g["targets"].get(t) != w["targets"].get(t):
                print(f"  target {t}: got {g['targets'].get(t)} want {w['targets'].get(t)}")
    if got.get("meta", {}).get("generator", {}).get("name") != "harm-coi":
        ok = False
        print(f"[{fx.name}] meta.generator.name is not harm-coi")

    # the output is a valid coi.json for this trace
    chk = [sys.executable, str(HERE / "check_coi.py"), str(coi_path), "--vcd", str(fx / "trace.vcd")]
    if a.harm:
        chk += ["--harm", a.harm]
    r = subprocess.run(chk, capture_output=True, text=True)
    if r.returncode != 0:
        ok = False
        print(f"[{fx.name}] check_coi.py rejects the output:\n{r.stdout}{r.stderr}")
    print(f"[{fx.name}] {'OK' if ok else 'FAIL'}")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
