#!/usr/bin/env python3
"""H7, acceptance A1-A3 (and the A5 warning) for one fixture.

A1  filter output == union of rank runs on per-consequent restricted configurations
    (restrict_config.py, cones computed from coi.json, not by HARM)
A2  no filter-mode assertion has an antecedent proposition outside its consequent's cone, and
    every one has coiFrac == 1
A3  plain templates only: filter output == rank output post-filtered with coiFrac == 1
A5  the filter-mode warning is printed exactly once
Usage: check_filter.py <harm> <config.xml> <harm trace args...>
"""
import json
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from restrict_config import main as restrict, variables  # noqa: E402

harm, config, trace_args = sys.argv[1], Path(sys.argv[2]).resolve(), sys.argv[3:]
WARNING = "COI filter mode assumes the RTL is correct"


def run(conf, d, tag):
    info = Path(d) / f"{tag}.json"
    r = subprocess.run([harm, *trace_args, "--conf", str(conf), "--max-threads", "1", "--psilent",
                        "--dump-assertion-info", str(info)], cwd=d, capture_output=True, text=True)
    if r.returncode != 0 or not info.exists():
        sys.exit(f"HARM failed on {conf}:\n{(r.stdout + r.stderr)[-3000:]}")
    return json.loads(info.read_text())["assertions"], r.stdout + r.stderr


def variant(src, d, name, mode, plain_only):
    """a copy of the configuration with an absolute coi path, another mode, maybe no DT templates"""
    tree = ET.parse(src)
    ctx = tree.getroot().find("context")
    coi = ctx.find("coi")
    coi.set("file", str((Path(src).parent / coi.get("file")).resolve()))
    coi.set("mode", mode)
    if plain_only:
        for t in ctx.findall("template"):
            if t.get("dtLimits") is not None or ".." in t.get("exp"):
                ctx.remove(t)
    out = Path(d) / name
    tree.write(out)
    return out


def texts(records):
    return {r["text"] for r in records}


ok = True
with tempfile.TemporaryDirectory() as d:
    # filter mode
    filt, out = run(config, d, "filter")
    n_warn = out.count(WARNING)
    print(f"filter mode: {len(filt)} assertions; warning printed {n_warn} time(s)")
    for line in out.splitlines():
        if "COI filter:" in line:
            print("  " + line.split("Message: ")[-1].strip())
    if n_warn != 1:
        print("FAIL A5: the warning must be printed exactly once")
        ok = False

    # A1: per-consequent restricted configurations in rank mode
    rdir = Path(d) / "restricted"
    rdir.mkdir()
    import contextlib, io
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        restrict(config, rdir)
    union = set()
    for i, conf in enumerate(buf.getvalue().split()):
        recs, _ = run(conf, d, f"r{i}")
        union |= texts(recs)
    got = texts(filt)
    print(f"A1: filter {len(got)}, union of {len(buf.getvalue().split())} restricted rank runs {len(union)}")
    for t in sorted(got - union):
        print(f"  only in filter: {t}")
    for t in sorted(union - got):
        print(f"  only in restricted rank: {t}")
    ok &= got == union

    # A2: antecedents in the cone; coiFrac == 1
    coi = json.loads(Path((config.parent / ET.parse(config).getroot().find("context/coi")
                           .get("file"))).read_text())
    tg, unk = coi["targets"], set(coi.get("unknown", []))
    known = lambda v: v in tg and v not in unk
    bad = 0
    for r in filt:
        cvars = {v for l in r["leaves"] if not l["antecedent"] for v in l["variables"]}
        if any(not known(v) for v in cvars):
            continue
        cone = {s["sig"] for v in cvars for s in tg[v]["sources"]}
        for l in r["leaves"]:
            if l["antecedent"] and not all((not known(v)) or v in cone for v in l["variables"]):
                print(f"  A2: out-of-cone antecedent '{l['text']}' in {r['text']}")
                bad += 1
        if abs(r["metrics"]["coiFrac"] - 1.0) > 1e-9:
            print(f"  A2: coiFrac {r['metrics']['coiFrac']} in {r['text']}")
            bad += 1
    print(f"A2: {bad} violations")
    ok &= bad == 0

    # A3: plain templates, filter == rank post-filtered with coiFrac == 1
    pf, _ = run(variant(config, d, "plain_filter.xml", "filter", True), d, "pf")
    pr, _ = run(variant(config, d, "plain_rank.xml", "rank", True), d, "pr")
    want = {r["text"] for r in pr if abs(r["metrics"]["coiFrac"] - 1.0) < 1e-9}
    print(f"A3: plain filter {len(texts(pf))}, plain rank with coiFrac == 1 {len(want)} (of {len(pr)})")
    for t in sorted(texts(pf) ^ want):
        print(f"  differs: {t}")
    ok &= texts(pf) == want

print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
