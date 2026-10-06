#!/usr/bin/env python3
"""H10, acceptance A1, A2 and A4 for harm-coi --predicates / --emit-config (D-023).

  expected <fixture dir> <labels.json> --python <py> [--harm <bin>]
      A1: the harvested predicates (expr -> targets) equal the hand-labelled list; every one has
          origin "rtl" and a src "<file>:<line>" inside the fixture's RTL
      A4: the coi.json with predicates passes check_coi.py (schema, names against the trace)
  harm <fixture dir> --python <py> --harm <bin>
      A2: HARM loads the emitted configuration on the fixture's trace, without
          --skip-invalid-props, and mines to the end
      report: predicates that are constant on the trace (mined as invariants G(p) or G(!(p)))

The harm-coi arguments come from the fixture's edges.txt (or meta.txt) header.
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
sys.path.insert(0, str(HERE))
from check_generator import read_edges  # noqa: E402


def harm_coi(fx, py, out, *extra):
    meta, _ = read_edges(fx / ("edges.txt" if (fx / "edges.txt").exists() else "meta.txt"))
    coi = out / "coi.json"
    cmd = [py, "-m", "harm_coi", "--top", meta["top"],
           "--files", *[str(p) for p in sorted((fx / "rtl").glob("*.sv"))],
           "--vcd-scope", meta["vcd_scope"], "--vcd-recursion", meta["vcd_recursion"],
           "--vcd", str(fx / "trace.vcd"), "--max-depth", meta["max_depth"], "-o", str(coi), *extra]
    r = subprocess.run(cmd, env={**os.environ, "PYTHONPATH": str(TOOL)}, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"harm-coi failed:\n{r.stdout}{r.stderr}")
    return meta, coi


def trace_args(fx, meta):
    return ["--vcd", str(fx / "trace.vcd"), "--clk", meta["clock"], "--vcd-ss", meta["vcd_scope"],
            "--vcd-r", meta["vcd_recursion"]]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", choices=["expected", "harm"])
    ap.add_argument("fixture")
    ap.add_argument("labels", nargs="?")
    ap.add_argument("--python", required=True)
    ap.add_argument("--harm")
    a = ap.parse_args()
    fx = Path(a.fixture).resolve()
    ok = True
    with tempfile.TemporaryDirectory() as d:
        d = Path(d)
        if a.mode == "expected":
            meta, coi = harm_coi(fx, a.python, d, "--predicates")
            doc = json.loads(coi.read_text())
            got = {}
            for p in doc.get("predicates", []):
                got[p["expr"]] = sorted(p.get("targets", []))
                if p.get("origin") != "rtl":
                    print(f"  origin of '{p['expr']}' is {p.get('origin')}")
                    ok = False
                srcs = p.get("src", "").split(", ")
                for s in srcs:
                    f, _, line = s.rpartition(":")
                    path = fx / "rtl" / f
                    if not path.exists() or not line.isdigit() or not \
                            1 <= int(line) <= len(path.read_text().splitlines()):
                        print(f"  bad src '{s}' for '{p['expr']}'")
                        ok = False
            want = {p["expr"]: sorted(p["targets"]) for p in json.loads(Path(a.labels).read_text())["predicates"]}
            for e in sorted(set(got) | set(want)):
                if got.get(e) != want.get(e):
                    print(f"  {e}: harvested {got.get(e)}, labelled {want.get(e)}")
                    ok = False
            print(f"[{fx.name}] A1: {len(got)} predicates harvested, {len(want)} labelled")
            chk = [sys.executable, str(HERE / "check_coi.py"), str(coi), "--vcd", str(fx / "trace.vcd")]
            if a.harm:
                chk += ["--harm", a.harm]
            r = subprocess.run(chk, capture_output=True, text=True)
            if r.returncode != 0:
                print(f"  A4: check_coi.py rejects the coi.json:\n{r.stdout}{r.stderr}")
                ok = False
        else:
            xml = d / "emitted.xml"
            meta, coi = harm_coi(fx, a.python, d, "--predicates", "--emit-config", str(xml))
            preds = [p["expr"] for p in json.loads(coi.read_text()).get("predicates", [])]
            if not preds:
                print(f"[{fx.name}] A2: no predicates, nothing for HARM to load")
                print("ok")
                sys.exit(0)
            r = subprocess.run([a.harm, *trace_args(fx, meta), "--conf", str(xml), "--max-threads", "1",
                                "--psilent", "--isilent"], cwd=d, capture_output=True, text=True)
            out = r.stdout + r.stderr
            if r.returncode != 0 or "Invalid proposition" in out:
                print(f"  A2: HARM fails on the emitted configuration:\n{out[-3000:]}")
                ok = False
            print(f"[{fx.name}] A2: HARM ran on {len(preds)} emitted predicates: {'ok' if ok else 'FAIL'}")
            # report: constant predicates
            if preds:
                inv = d / "invariants.xml"
                props = "".join(f'<prop exp="{p}" loc="c"/><prop exp="!({p})" loc="c"/>'
                                for p in (x.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
                                          for x in preds))
                inv.write_text(f'<harm><context name="default">{props}<template exp="G(P0)"/>'
                               f'<sort name="f" exp="atct/traceLength"/></context></harm>')
                info = d / "inv.json"
                subprocess.run([a.harm, *trace_args(fx, meta), "--conf", str(inv), "--max-threads", "1",
                                "--psilent", "--isilent", "--dump-assertion-info", str(info)], cwd=d,
                               capture_output=True, text=True)
                const = [x["text"] for x in json.loads(info.read_text())["assertions"]] if info.exists() else []
                print(f"  report: {len(const)} of {len(preds)} predicates constant on the trace"
                      + (f": {const}" if const else ""))
    print("ok" if ok else "FAIL")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
