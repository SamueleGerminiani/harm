#!/usr/bin/env python3
"""H11 evaluation (D-026): run HARM's configurations C0-C7 on the designs of a manifest and write
a results table (CSV and Markdown).

  C0  vanilla: the design's own configuration, or HARM's --generate-config one
  C1  C0 + --reduce implies
  C2  C1 + --atom-premises
  C3  C0 + <coi mode="rank">, sorted first by coiDepthFit            (needs RTL: harm-coi)
  C4  C0 + <coi mode="filter">                                       (needs RTL)
  C5  C0 + <coi mode="filter" depth="exact">                         (needs RTL)
  C6  harm-coi --emit-config: the RTL predicates                     (needs RTL)
  C7  C6 + filter depth="exact" + --reduce implies --atom-premises   (needs RTL)

Measures per run: assertions out, wall time, assertions dropped by the reduction, the COI filter's
search space (permutations, decision-tree pairs), mean coiFrac and coiDepthFit of the output, and
fault coverage when the design has faulty traces (--fd). These are measurements, not thresholds.

Manifest (JSON list), one entry per design; paths relative to the repository root:
  {"name", "trace": {"vcd" | "csv" | "csv_dir": path, "clk", "scope", "recursion"},
   "config": path (optional: else --generate-config), "args": [extra HARM args] (optional),
   "faults": dir (optional), "rtl": {"files": [...], "top"} (optional: enables C3-C7)}

Usage: run_eval.py <manifest.json> <out-dir> [--harm build/harm] [--python <py with harm-coi>]
                   [--configs C0,C1,...] [--check <previous results.csv>]
With --check, the counts (not the times) must equal those of a previous run (acceptance A1).
"""
import argparse
import csv
import json
import os
import re
import subprocess
import sys
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COUNT_COLUMNS = ["assertions", "dropped", "permutations", "dt_pairs", "coi_frac", "coi_depth_fit",
                 "coverage"]


def trace_args(t):
    a = []
    for k, flag in (("vcd", "--vcd"), ("csv", "--csv"), ("csv_dir", "--csv-dir"), ("vcd_dir", "--vcd-dir")):
        if k in t:
            a += [flag, str(ROOT / t[k])]
    if "clk" in t:
        a += ["--clk", t["clk"]]
    if "scope" in t:
        a += ["--vcd-ss", t["scope"]]
    if "recursion" in t:
        a += ["--vcd-r", str(t["recursion"])]
    return a


def insert_before_context_end(xml, text):
    i = xml.rindex("</context>")
    return xml[:i] + text + "\n    " + xml[i:]


def insert_after_context_start(xml, text):
    m = re.search(r"<context[^>]*>", xml)
    return xml[:m.end()] + "\n        " + text + xml[m.end():]


def run_harm(harm, args, d, timeout):
    info = Path(d) / "info.json"
    if info.exists():
        info.unlink()
    cmd = [harm, *args, "--max-threads", "8", "--psilent", "--dump-assertion-info", str(info)]
    t0 = time.time()
    try:
        r = subprocess.run(cmd, cwd=d, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return {"wall_s": timeout, "ok": False, "assertions": "", "error": f"timeout ({timeout} s)"}
    wall = time.time() - t0
    out = re.sub(r"\x1b\[[0-9;]*m", "", r.stdout + r.stderr)
    row = {"wall_s": round(wall, 2), "ok": r.returncode == 0}
    recs = json.loads(info.read_text())["assertions"] if info.exists() else []
    row["assertions"] = len(recs)
    m = re.findall(r"Implication: dropped (\d+) of (\d+)", out)
    row["dropped"] = sum(int(x) for x, _ in m) if m else ""
    if info.exists():
        cf = json.loads(info.read_text()).get("coiFilter", {})
        if cf:
            st = next(iter(cf.values()))
            row["permutations"] = f"{st['permutationsBefore']}->{st['permutationsAfter']}"
            if "dtPairsBefore" in st:
                row["dt_pairs"] = f"{st['dtPairsBefore']}->{st['dtPairsAfter']}"
    fr = [a["metrics"]["coiFrac"] for a in recs if "coiFrac" in a["metrics"]]
    df = [a["metrics"]["coiDepthFit"] for a in recs if "coiDepthFit" in a["metrics"]]
    if fr:
        row["coi_frac"] = round(sum(fr) / len(fr), 3)
        row["coi_depth_fit"] = round(sum(df) / len(df), 3)
    cov = re.findall(r"Coverage: ([0-9.]+)%", out)
    if cov:
        row["coverage"] = cov[-1]
    if not row["ok"]:
        row["error"] = out.strip().splitlines()[-1][:120] if out.strip() else f"exit {r.returncode}"
    return row


def configs_for(design, harm, py, d):
    """{name: (config xml text, extra args)}"""
    t = design.get("trace", {})
    base_args = trace_args(t) + design.get("args", [])
    if design.get("config"):
        xml = (ROOT / design["config"]).read_text()
    else:
        gen = Path(d) / "generated.xml"
        subprocess.run([harm, *trace_args(t), "--conf", str(gen), "--generate-config", "--psilent", "--isilent"],
                       cwd=d, capture_output=True)
        xml = gen.read_text()
    cfg = {"C0": (xml, []), "C1": (xml, ["--reduce", "implies"]),
           "C2": (xml, ["--reduce", "implies", "--atom-premises"])}
    rtl = design.get("rtl")
    if rtl and py:
        coi = Path(d) / "coi.json"
        emitted = Path(d) / "emitted.xml"
        vcd = t.get("vcd")
        r = subprocess.run([py, "-m", "harm_coi", "--top", rtl["top"],
                            "--files", *[str(ROOT / f) for f in rtl["files"]],
                            "--vcd-scope", t["scope"], "--vcd-recursion", str(t.get("recursion", 0)),
                            *(["--vcd", str(ROOT / vcd)] if vcd else []),
                            "--emit-config", str(emitted), "-o", str(coi)],
                           env={**os.environ, "PYTHONPATH": str(ROOT / "tools" / "harm-coi" / "src")},
                           capture_output=True, text=True)
        if r.returncode == 0:
            c = f'<coi file="{coi}" mode="rank"/>'
            cfg["C3"] = (insert_after_context_start(insert_before_context_end(xml, c),
                                                    '<sort name="structure" exp="coiDepthFit"/>'), [])
            cfg["C4"] = (insert_before_context_end(xml, f'<coi file="{coi}" mode="filter"/>'), [])
            cfg["C5"] = (insert_before_context_end(xml, f'<coi file="{coi}" mode="filter" depth="exact"/>'), [])
            em = emitted.read_text().replace('file="coi.json"', f'file="{coi}"')
            if "<prop " in em:
                cfg["C6"] = (em, [])
                cfg["C7"] = (em.replace('mode="rank"', 'mode="filter" depth="exact"'),
                             ["--reduce", "implies", "--atom-premises"])
        else:
            print(f"  harm-coi failed on {design['name']}: {r.stderr.strip()[-200:]}", file=sys.stderr)
    return base_args, cfg


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("manifest")
    ap.add_argument("out")
    ap.add_argument("--harm", default=str(ROOT / "build" / "harm"))
    ap.add_argument("--python", help="a Python with harm-coi's dependencies (pyslang)")
    ap.add_argument("--configs", default="C0,C1,C2,C3,C4,C5,C6,C7")
    ap.add_argument("--check", help="a previous results.csv: the counts must be equal")
    ap.add_argument("--timeout", type=int, default=1800, help="seconds per HARM run (default 1800)")
    a = ap.parse_args()
    wanted = a.configs.split(",")
    designs = json.loads(Path(a.manifest).read_text())
    version = subprocess.run([a.harm, "--version"], capture_output=True, text=True).stdout.strip()
    rows = []
    for design in designs:
        with tempfile.TemporaryDirectory() as d:
            base_args, cfg = configs_for(design, a.harm, a.python, d)
            for name in wanted:
                if name not in cfg:
                    continue
                xml, extra = cfg[name]
                conf = Path(d) / f"{name}.xml"
                conf.write_text(xml)
                args = base_args + ["--conf", str(conf)] + extra
                if design.get("faults"):
                    args += ["--fd", str(ROOT / design["faults"])]
                row = {"design": design["name"], "config": name, **run_harm(a.harm, args, d, a.timeout)}
                rows.append(row)
                print(f"{row['design']:16} {name}  {row['assertions']!s:>6} assertions  {row['wall_s']:7}s"
                      + ("" if row["ok"] else f"  FAILED: {row.get('error', '')}"), flush=True)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    cols = ["design", "config", "assertions", "wall_s", "dropped", "permutations", "dt_pairs",
            "coi_frac", "coi_depth_fit", "coverage", "ok", "error"]
    with open(out / "results.csv", "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=cols, extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow({c: r.get(c, "") for c in cols})
    with open(out / "results.md", "w") as f:
        f.write(f"# HARM evaluation ({version})\n\nManifest: `{a.manifest}`. Configurations: see `eval/run_eval.py`.\n\n")
        f.write("| " + " | ".join(cols[:-2]) + " |\n|" + "---|" * (len(cols) - 2) + "\n")
        for r in rows:
            f.write("| " + " | ".join(str(r.get(c, "")) for c in cols[:-2]) + " |\n")
    print(f"written {out / 'results.csv'} and results.md ({len(rows)} runs)")
    # a timeout is a measurement (reported); a HARM error is a failure
    failed = [r for r in rows if not r["ok"] and not str(r.get("error", "")).startswith("timeout")]
    ok = not failed
    if a.check:
        prev = {(r["design"], r["config"]): r for r in csv.DictReader(open(a.check))}
        for r in rows:
            p = prev.get((r["design"], r["config"]))
            if p is None:
                continue
            for c in COUNT_COLUMNS:
                if str(r.get(c, "")) != p.get(c, ""):
                    print(f"  differs from the previous run: {r['design']} {r['config']} {c}: "
                          f"{p.get(c)} -> {r.get(c, '')}")
                    ok = False
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
