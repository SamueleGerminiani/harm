#!/usr/bin/env python3
"""H9, acceptance A1-A4 for --dump-coi-report (D-022).

  expected   <harm> <config> <expected.json> <trace args...>
             A1/A2: HARM's report equals a hand-written one (texts, origins, numeric flag, the
             variables outside the cone, the unknown variables, coneUnknown)
  crosscheck <harm> <config> <trace args...>
             A3: HARM's report equals the pairs computed here from the configuration and coi.json
  noeffect   <harm> <config> <trace args...>
             A4: mining output is identical with and without --dump-coi-report

The rule computed here (D-022, D-017): consequents are the propositions whose loc has c or ac;
antecedents are the propositions and numerics with any other loc; a proposition is not paired with
itself. If a consequent variable is unknown (not a target, or listed as unknown), the cone is
unknown and every antecedent is 'unknown'. Otherwise an antecedent is out of the cone if one of its
known variables is not a source of any consequent variable ('outside'); else 'unknown' if it has
an unknown variable; else in the cone (not reported).
"""
import json
import re
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from restrict_config import variables  # noqa: E402


def run(harm, config, trace_args, d, report=True):
    out = Path(d) / "report.json"
    dump = Path(d) / "dump"
    dump.mkdir(exist_ok=True)
    args = [harm, *trace_args, "--conf", str(config), "--max-threads", "1", "--psilent",
            "--dump-to", str(dump) + "/"]
    if report:
        args += ["--dump-coi-report", str(out)]
    r = subprocess.run(args, cwd=d, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"HARM failed:\n{(r.stdout + r.stderr)[-3000:]}")
    mined = "".join(f.read_text() for f in sorted(dump.iterdir()))
    return (json.loads(out.read_text()) if report else None), mined, r.stdout + r.stderr


def normalise(report):
    """the comparable content of a report: {context: {"coi": bool, "consequents": {...}}}"""
    if report.get("version") != "1":
        sys.exit(f"unexpected report version {report.get('version')}")
    out = {}
    for ctx in report["contexts"]:
        cons = {}
        for c in ctx.get("consequents", []):
            cons[c["text"]] = {
                "origin": c["origin"], "coneUnknown": c["coneUnknown"],
                "outOfCone": {a["text"]: {"origin": a["origin"], "numeric": a["numeric"],
                                          "outside": sorted(a["outside"])} for a in c["outOfCone"]},
                "unknown": {a["text"]: {"origin": a["origin"],
                                        "unknownVariables": sorted(a["unknownVariables"])}
                            for a in c["unknown"]}}
        out[ctx["name"]] = {"coi": ctx["coi"] is not None, "consequents": cons}
    return out


def harm_text(exp):
    """the configuration text as HARM prints it: decimal sized literals become binary"""
    return re.sub(r"(\d+)'d(\d+)", lambda m: f"{m.group(1)}'b{int(m.group(2)):b}", exp)


def compute(config):
    """the report computed from the configuration and coi.json (A3)"""
    config = Path(config).resolve()
    out = {}
    for ctx in ET.parse(config).getroot().findall("context"):
        coi_tag = ctx.find("coi")
        if coi_tag is None:
            out[ctx.get("name")] = {"coi": False, "consequents": {}}
            continue
        coi = json.loads((config.parent / coi_tag.get("file")).read_text())
        targets, unknown = coi["targets"], set(coi.get("unknown", []))
        known = lambda v: v in targets and v not in unknown
        items = []  # (text, locs, origin, numeric)
        for tag, numeric in (("prop", False), ("numeric", True)):
            for p in ctx.findall(tag):
                locs = {l.strip() for l in p.get("loc", "").split(",")}
                items.append((harm_text(p.get("exp")), locs, p.get("origin"), numeric))
        cons = {}
        for ct, clocs, corigin, cnum in items:
            if cnum or not clocs & {"c", "ac"}:
                continue
            cvars = variables(ct)
            cone_unknown = any(not known(v) for v in cvars)
            cone = set() if cone_unknown else {s["sig"] for v in cvars for s in targets[v]["sources"]}
            entry = {"origin": corigin, "coneUnknown": cone_unknown, "outOfCone": {}, "unknown": {}}
            for at, alocs, aorigin, anum in items:
                if (at == ct and not anum) or not alocs - {"c"}:
                    continue
                avars = variables(at)
                unk = sorted(v for v in avars if not known(v))
                outside = [] if cone_unknown else sorted(v for v in avars if known(v) and v not in cone)
                if outside:
                    entry["outOfCone"][at] = {"origin": aorigin, "numeric": anum, "outside": outside}
                elif cone_unknown or unk:
                    entry["unknown"][at] = {"origin": aorigin, "unknownVariables": unk}
            cons[ct] = entry
        out[ctx.get("name")] = {"coi": True, "consequents": cons}
    return out


def diff(got, want, path=""):
    if isinstance(got, dict) and isinstance(want, dict):
        for k in sorted(set(got) | set(want)):
            if k not in got:
                print(f"  missing: {path}/{k}")
            elif k not in want:
                print(f"  extra:   {path}/{k} = {json.dumps(got[k])[:200]}")
            else:
                diff(got[k], want[k], f"{path}/{k}")
    elif got != want:
        print(f"  differs: {path}: got {json.dumps(got)} want {json.dumps(want)}")


def main():
    mode, harm, config = sys.argv[1], sys.argv[2], Path(sys.argv[3]).resolve()
    with tempfile.TemporaryDirectory() as d:
        if mode == "expected":
            want = json.loads(Path(sys.argv[4]).read_text())["contexts"]
            report, _, _ = run(harm, config, sys.argv[5:], d)
            got = normalise(report)
        elif mode == "crosscheck":
            report, _, _ = run(harm, config, sys.argv[4:], d)
            got, want = normalise(report), compute(config)
        elif mode == "noeffect":
            report, with_report, out = run(harm, config, sys.argv[4:], d)
            d2 = Path(d) / "without"
            d2.mkdir()
            _, without, _ = run(harm, config, sys.argv[4:], d2, report=False)
            same = with_report == without
            print(f"mining output identical with and without the report: {same}")
            nocoi = [c["name"] for c in report["contexts"] if c["coi"] is None]
            if nocoi:
                print(f"contexts without <coi>: {nocoi}; note printed: {'no <coi>' in out}")
            sys.exit(0 if same and (not nocoi or "no <coi>" in out) else 1)
        else:
            sys.exit(__doc__)
    n = sum(len(c["outOfCone"]) for ctx in got.values() for c in ctx["consequents"].values())
    print(f"{mode}: {n} out-of-cone pairs reported")
    if got != want:
        diff(got, want)
        print("FAIL")
        sys.exit(1)
    print("ok")


if __name__ == "__main__":
    main()
