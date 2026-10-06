#!/usr/bin/env python3
"""H7, acceptance A1: per-consequent restricted configurations (H7_PLAN F3, D-017).

For a HARM configuration with <coi mode="filter">, writes one configuration per consequent
proposition c, in rank mode, whose only consequent is c and whose antecedent and decision-tree
propositions are those in c's cone, computed here from coi.json (not by HARM):
  a proposition is in the cone if every one of its variables is a source of some variable of c;
  a variable that coi.json does not know (not a target, or listed as unknown) counts as in the
  cone; if a variable of c is unknown, every proposition is kept; propositions without variables
  are kept.
A consequent with no proposition in its cone gets no configuration (filter mode must mine
nothing for it).
With --depth exact|bounded (H8, acceptance A3), one configuration per (consequent, decision-tree
template), only for templates whose operator has a single index (..&&.., or 1D): the tree's
domain is the propositions that also fit, under D-020, the one distance between that index and
the consequent, computed here from the template text (single_index_distance). Plain templates are
dropped (A2 covers them).
Usage: restrict_config.py <config.xml> <out-dir> [--depth exact|bounded]   (prints the files)
"""
import json
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

KEYWORDS = {"true", "false"}


def variables(expr):
    """the variables of a proposition: identifiers with '::' scopes, without bit selects or
    sized literals (4'd9)"""
    expr = re.sub(r"\d+'[sS]?[bBoOdDhH][0-9a-fA-FxXzZ_]+", " ", expr)
    expr = re.sub(r"\[[^\]]*\]", lambda m: m.group(0) if "::" in expr[m.end():m.end() + 2] else " ", expr)
    names = re.findall(r"[A-Za-z_][\w]*(?:\[\d+\])?(?:::[A-Za-z_][\w]*(?:\[\d+\])?)*", expr)
    return sorted({n for n in names if n not in KEYWORDS})


def single_index_distance(exp, dt_limits):
    """cycles from the only index of a decision-tree operator to the consequent placeholder, for
    G({<op>} |-> | |=> [X ...] P0); None if the template is not of that shape"""
    m = re.fullmatch(r"G\(\{\s*\.\.(&&|##\d+|#\d+&)\.\.\s*\}\s*(\|->|\|=>)\s*((?:X\s*)*)P\d+\s*\)",
                     exp.replace(" ", ""))
    if not m:
        return None
    if m.group(1) != "&&" and not re.search(r"(^|,)1D(,|$)", dt_limits or ""):
        return None  # several indices
    return (m.group(2) == "|=>") + m.group(3).count("X")


def main(config, out_dir, depth=None):
    config, out_dir = Path(config).resolve(), Path(out_dir)
    tree = ET.parse(config)
    ctx = tree.getroot().find("context")
    coi_tag = ctx.find("coi")
    coi_file = (config.parent / coi_tag.get("file")).resolve()
    coi = json.loads(coi_file.read_text())
    targets = coi["targets"]
    unknown = set(coi.get("unknown", []))

    def known(v):
        return v in targets and v not in unknown

    def sources(v):
        return {s["sig"] for s in targets[v]["sources"]}

    props = [(p.get("exp"), {l.strip() for l in p.get("loc").split(",")}) for p in ctx.findall("prop")]
    written = []
    if depth is not None:
        from sva_offsets import fits
        for k, (c, locs) in enumerate(props):
            if "c" not in locs:
                continue
            for j, t in enumerate(ctx.findall("template")):
                d = single_index_distance(t.get("exp"), t.get("dtLimits"))
                if d is None:
                    continue
                root = ET.Element("harm")
                new = ET.SubElement(root, "context", {"name": "default"})
                cand = [p for p, plocs in props
                        if "dt" in plocs and fits(coi, variables(p), [(variables(c), d)], depth)]
                if not cand:
                    continue  # no candidate fits: filter mode must mine nothing here
                for p, plocs in props:
                    loc = (["c"] if p == c else []) + (["dt"] if p in cand else [])
                    if loc:
                        ET.SubElement(new, "prop", {"exp": p, "loc": ", ".join(loc)})
                ET.SubElement(new, "coi", {"file": str(coi_file), "mode": "rank"})
                new.append(t)
                for srt in ctx.findall("sort"):
                    new.append(srt)
                out = out_dir / f"consequent{k}_template{j}.xml"
                ET.ElementTree(root).write(out)
                written.append(out)
        for w in written:
            print(w)
        return
    for k, (c, locs) in enumerate(props):
        if "c" not in locs:
            continue
        cvars = variables(c)
        if all(known(v) for v in cvars):
            cone = set().union(*[sources(v) for v in cvars]) if cvars else set()
            keep = lambda p: all((not known(v)) or v in cone for v in variables(p))
        else:
            keep = lambda p: True  # the cone of an unknown consequent signal is unknown
        root = ET.Element("harm")
        new = ET.SubElement(root, "context", {"name": "default"})
        for p, plocs in props:
            alocs = sorted(plocs - {"c"}) if keep(p) else []
            if p == c:
                alocs = sorted(alocs + ["c"])  # the consequent, and an antecedent if in its own cone
            if alocs:
                ET.SubElement(new, "prop", {"exp": p, "loc": ", ".join(alocs)})
        if not any(set(e.get("loc").split(", ")) - {"c"} for e in new.findall("prop")):
            continue  # no antecedent in the cone: filter mode must mine nothing for c
        ET.SubElement(new, "coi", {"file": str(coi_file), "mode": "rank"})
        for t in ctx.findall("template") + ctx.findall("sort"):
            new.append(t)
        out = out_dir / f"consequent{k}.xml"
        ET.ElementTree(root).write(out)
        written.append(out)
    for w in written:
        print(w)


if __name__ == "__main__":
    args = sys.argv[1:]
    depth = None
    if "--depth" in args:
        i = args.index("--depth")
        depth = args[i + 1]
        del args[i:i + 2]
    if len(args) != 2:
        sys.exit(__doc__)
    main(*args, depth=depth)
