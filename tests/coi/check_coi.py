#!/usr/bin/env python3
"""Validate a coi.json file (H4, acceptance tests A1/A2).

Checks:
  1. the JSON Schema doc/schemas/coi.v1.json;
  2. what the schema cannot express: depths sorted, unique and <= max_depth; the clock is never a
     source; a source/target name appears at most once per target;
  3. with --vcd and --harm: the names are exactly the signals HARM sees in the trace with
     --vcd-ss <meta.vcd_scope> --vcd-r <meta.vcd_recursion> (asked to HARM itself, through
     --generate-config); every visible signal except the clock is a target or listed in "unknown".

Usage: check_coi.py <coi.json> [--vcd <trace.vcd> --harm <harm binary>]
Exit status 0 if valid; otherwise 1, with one line per problem on stdout.
"""
import argparse
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

import jsonschema

SCHEMA = Path(__file__).resolve().parents[2] / "doc" / "schemas" / "coi.v1.json"


def harm_signals(harm, vcd, coi):
    """the signal names HARM sees in the trace, under the scope and recursion of coi.json"""
    m = coi["meta"]
    with tempfile.TemporaryDirectory() as d:
        conf = Path(d) / "gen.xml"
        cmd = [str(Path(harm).resolve()), "--vcd", str(Path(vcd).resolve()), "--clk", m["clock"], "--conf", str(conf), "--generate-config",
               "--psilent", "--isilent", "--wsilent", "--max-threads", "1"]
        if m["vcd_scope"]:
            cmd += ["--vcd-ss", m["vcd_scope"]]
        if m["vcd_recursion"] > 0:
            cmd += [f"--vcd-r={m['vcd_recursion']}"]
        r = subprocess.run(cmd, cwd=d, capture_output=True, text=True)
        if r.returncode != 0 or not conf.exists():
            errors = [l for l in (r.stdout + r.stderr).splitlines() if "ERROR" in l or "Message" in l]
            return None, "HARM --generate-config failed: " + " ".join(errors[-2:])
        # HARM's generated XML is not strictly well-formed (e.g. clustering="...><..."): read the
        # exp attribute of each <prop>/<numeric> line
        names = set()
        for line in conf.read_text().splitlines():
            m2 = re.match(r'\s*<(?:prop|numeric)\b.*?\bexp="([^"]*)"', line)
            if m2:
                names.add(m2.group(1))
    return names, None


def check(coi, problems, vcd=None, harm=None):
    try:
        jsonschema.validate(coi, json.loads(SCHEMA.read_text()))
    except jsonschema.ValidationError as e:
        problems.append(f"schema: {e.message} (at {'/'.join(map(str, e.absolute_path))})")
        return
    m = coi["meta"]
    for target, cone in coi["targets"].items():
        seen = set()
        for s in cone["sources"]:
            if s["sig"] in seen:
                problems.append(f"{target}: source '{s['sig']}' listed twice")
            seen.add(s["sig"])
            d = s["depths"]
            if not d and not s.get("saturated", False):
                problems.append(f"{target} <- {s['sig']}: empty depths without saturated")
            if d != sorted(set(d)):
                problems.append(f"{target} <- {s['sig']}: depths not sorted and unique: {d}")
            if any(x > m["max_depth"] for x in d):
                problems.append(f"{target} <- {s['sig']}: depth above max_depth {m['max_depth']}: {d}")
            if s["sig"] == m["clock"]:
                problems.append(f"{target}: the clock '{m['clock']}' cannot be a source")
    if vcd is None:
        return
    names, err = harm_signals(harm, vcd, coi)
    if err:
        problems.append(err)
        return
    used = set(coi["targets"]) | set(coi.get("unknown", []))
    used |= {s["sig"] for c in coi["targets"].values() for s in c["sources"]}
    for n in sorted(used - names):
        problems.append(f"'{n}' is not a signal HARM sees in the trace")
    for n in sorted(names - set(coi["targets"]) - set(coi.get("unknown", [])) - {m["clock"]}):
        problems.append(f"visible signal '{n}' is neither a target nor unknown")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("coi")
    ap.add_argument("--vcd")
    ap.add_argument("--harm")
    a = ap.parse_args()
    problems = []
    try:
        coi = json.loads(Path(a.coi).read_text())
    except json.JSONDecodeError as e:
        print(f"not JSON: {e}")
        sys.exit(1)
    check(coi, problems, a.vcd, a.harm)
    for p in problems:
        print(p)
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
