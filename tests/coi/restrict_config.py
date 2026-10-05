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
Usage: restrict_config.py <config.xml> <out-dir>   (prints the written files)
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


def main(config, out_dir):
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
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    main(*sys.argv[1:])
