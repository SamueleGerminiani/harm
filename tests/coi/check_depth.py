#!/usr/bin/env python3
"""H8, acceptance A2-A4 and the A6 report, for one configuration and one depth mode.

A2  plain templates: filter output (depth=<mode>) == rank output post-filtered with coiFrac == 1
    and, for exact, coiDepthFit == 1 (HARM's metric); for bounded, the D-020 rule computed here
    (sva_offsets.py) on the printed assertions (Spot LTL: the SVA text loses '->', finding F7)
A3  single-index decision trees: filter output == union of rank runs on per-(consequent, template)
    restricted configurations (restrict_config.py --depth, offsets and cones computed in Python)
A4  every template: every filter-mode antecedent leaf fits under the mode, with offsets parsed
    from the printed assertion (sva_offsets.py), not from HARM; for exact also coiDepthFit == 1
A6  report: assertions, search space and time for depth any / bounded / exact
Usage: check_depth.py <harm> <config.xml> <exact|bounded> <harm trace args...>
"""
import contextlib
import io
import json
import subprocess
import sys
import tempfile
import time
import xml.etree.ElementTree as ET
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from restrict_config import main as restrict, single_index_distance  # noqa: E402
from sva_offsets import violations  # noqa: E402

harm, config, mode, trace_args = sys.argv[1], Path(sys.argv[2]).resolve(), sys.argv[3], sys.argv[4:]
assert mode in ("exact", "bounded"), mode


def run(conf, d, tag):
    info = Path(d) / f"{tag}.json"
    t0 = time.time()
    r = subprocess.run([harm, *trace_args, "--conf", str(conf), "--max-threads", "1", "--psilent",
                        "--dump-assertion-info", str(info)], cwd=d, capture_output=True,
                       text=True)
    dt = time.time() - t0
    out = r.stdout + r.stderr
    if r.returncode == 0 and not info.exists() and "Could not mine any assertions" in out:
        return [], out, dt
    if r.returncode != 0 or not info.exists():
        sys.exit(f"HARM failed on {conf}:\n{out[-3000:]}")
    return json.loads(info.read_text())["assertions"], out, dt


def kind(t):
    exp = t.get("exp")
    if ".." not in exp:
        return "plain"
    return "single" if single_index_distance(exp, t.get("dtLimits")) is not None else "multi"


def variant(d, name, coi_mode, depth, kinds):
    tree = ET.parse(config)
    ctx = tree.getroot().find("context")
    coi = ctx.find("coi")
    coi.set("file", str((config.parent / coi.get("file")).resolve()))
    coi.set("mode", coi_mode)
    if depth is None:
        coi.attrib.pop("depth", None)
    else:
        coi.set("depth", depth)
    for t in ctx.findall("template"):
        if kind(t) not in kinds:
            ctx.remove(t)
    out = Path(d) / name
    tree.write(out)
    return out


texts = lambda records: {r["text"] for r in records}
one = lambda x: abs(x - 1.0) < 1e-9
coi = json.loads((config.parent / ET.parse(config).getroot().find("context/coi").get("file")).read_text())
ALL = ("plain", "single", "multi")
ok = True
with tempfile.TemporaryDirectory() as d:
    # A4: soundness on every template
    filt, out, _ = run(variant(d, "all.xml", "filter", mode, ALL), d, "all")
    bad = 0
    for r in filt:
        try:
            v = violations(coi, r["text"], mode)
        except ValueError as e:
            print(f"  A4: cannot parse: {e}")
            bad += 1
            continue
        for leaf in v:
            print(f"  A4: '{leaf}' does not fit ({mode}) in {r['text']}")
            bad += 1
        if not one(r["metrics"]["coiFrac"]) or (mode == "exact" and not one(r["metrics"]["coiDepthFit"])):
            print(f"  A4: coiFrac {r['metrics']['coiFrac']} coiDepthFit {r['metrics']['coiDepthFit']} "
                  f"in {r['text']}")
            bad += 1
    print(f"A4: {len(filt)} assertions, {bad} violations")
    ok &= bad == 0

    # A2: plain templates
    pf, _, _ = run(variant(d, "pf.xml", "filter", mode, ("plain",)), d, "pf")
    pr, _, _ = run(variant(d, "pr.xml", "rank", None, ("plain",)), d, "pr")
    if mode == "exact":
        want = {r["text"] for r in pr if one(r["metrics"]["coiFrac"]) and one(r["metrics"]["coiDepthFit"])}
    else:
        want = {r["text"] for r in pr if one(r["metrics"]["coiFrac"]) and not violations(coi, r["text"], mode)}
    print(f"A2: plain filter {len(texts(pf))}, plain rank post-filtered {len(want)} (of {len(pr)})")
    for t in sorted(texts(pf) ^ want):
        print(f"  differs: {t}")
    ok &= texts(pf) == want

    # A3: single-index decision trees
    sconf = variant(d, "single.xml", "filter", mode, ("single",))
    sf, _, _ = run(sconf, d, "sf")
    rdir = Path(d) / "restricted"
    rdir.mkdir()
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        restrict(sconf, rdir, depth=mode)
    union = set()
    confs = buf.getvalue().split()
    for i, conf in enumerate(confs):
        recs, _, _ = run(conf, d, f"r{i}")
        union |= texts(recs)
    print(f"A3: single-index filter {len(texts(sf))}, union of {len(confs)} restricted rank runs {len(union)}")
    for t in sorted(texts(sf) - union):
        print(f"  only in filter: {t}")
    for t in sorted(union - texts(sf)):
        print(f"  only in restricted rank: {t}")
    ok &= texts(sf) == union

    # A6: report (totals over the context, from the dump's coiFilter record)
    print("A6: depth    assertions  permutations  dt candidates  (candidate, index) pairs  time")
    for depth in ("any", "bounded", "exact"):
        conf = variant(d, f"rep_{depth}.xml", "filter", depth, ALL)
        recs, out, dt = run(conf, d, f"rep_{depth}")
        info = Path(d) / f"rep_{depth}.json"
        st = json.loads(info.read_text()).get("coiFilter", {}).get("default", {}) if info.exists() else {}
        pairs = (f"{st['dtPairsBefore']} -> {st['dtPairsAfter']}" if "dtPairsBefore" in st else "(not filtered)")
        print(f"    {depth:8} {len(recs):10}  {st.get('permutationsBefore')} -> {st.get('permutationsAfter'):<6} "
              f"{st.get('dtCandidatesBefore')} -> {st.get('dtCandidatesAfter'):<8} {pairs:24} {dt:.3f}s")

print("ok" if ok else "FAIL")
sys.exit(0 if ok else 1)
