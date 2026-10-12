#!/usr/bin/env python3
"""H22 B5: harm-coi's hints configuration mines on a fixture.

For --hints-use all and placement: harm-coi writes the configuration, HARM mines with it (exit 0), and every
mined assertion's consequent reads a comb, state or unknown signal (never only inputs, resets or constants); with
all, a `|=>` assertion's consequent reads a state signal and a `|->` one a comb or unknown signal.

  check_hints_mine.py FIXTURE_DIR --python PY --harm HARM --out DIR"""
import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("fixture")
    ap.add_argument("--python", required=True)
    ap.add_argument("--harm", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    f = Path(a.fixture)
    name = f.name
    meta = (f / ("meta.txt" if (f / "meta.txt").exists() else "edges.txt")).read_text()
    r = re.search(r"^vcd_recursion = (\d+)", meta, re.M).group(1)
    bad = []
    for use in ("all", "placement"):
        out = Path(a.out) / f"h22_{name}_{use}"
        out.mkdir(parents=True, exist_ok=True)
        env = {**os.environ, "PYTHONPATH": str(ROOT / "tools" / "harm-coi" / "src")}
        (out / "info.json").unlink(missing_ok=True)
        subprocess.run([a.python, "-m", "harm_coi", "--top", name, "--files", *map(str, sorted((f / "rtl").glob("*.sv"))),
                        "--vcd-scope", "tb::dut", "--vcd-recursion", r, "--vcd", str(f / "trace.vcd"),
                        "--hints", str(out / "hints.json"), "--hints-use", use, "--emit-config", str(out / "cfg.xml"),
                        "-o", str(out / "coi.json")], check=True, env=env)
        roles = {k: v["role"] for k, v in json.loads((out / "hints.json").read_text())["roles"].items()}
        h = subprocess.run([a.harm, "--vcd", str(f / "trace.vcd"), "--clk", "clk", "--vcd-ss", "tb::dut", "--vcd-r", r,
                            "--conf", str(out / "cfg.xml"), "--max-threads", "1", "--psilent", "--isilent",
                            "--dump-assertion-info", str(out / "info.json")], capture_output=True, text=True)
        if h.returncode != 0:
            # accepted only if the configuration of today (no --hints) fails the same way (hier: a parameter
            # named W, a HARM keyword; multipath: no RTL predicates at all)
            subprocess.run([a.python, "-m", "harm_coi", "--top", name, "--files",
                            *map(str, sorted((f / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut", "--vcd-recursion", r,
                            "--vcd", str(f / "trace.vcd"), "--emit-config", str(out / "default.xml"),
                            "-o", str(out / "coi.json")], check=True, env=env)
            d = subprocess.run([a.harm, "--vcd", str(f / "trace.vcd"), "--clk", "clk", "--vcd-ss", "tb::dut",
                                "--vcd-r", r, "--conf", str(out / "default.xml"), "--max-threads", "1", "--psilent",
                                "--isilent"], capture_output=True, text=True)
            msg = lambda p: re.findall(r"Message: (.*?)\x1b|Message: (.*)$", p.stdout + p.stderr, re.M)  # noqa: E731
            if d.returncode == 0 or msg(d) != msg(h):
                bad.append(f"{use}: HARM exit {h.returncode}, the default configuration does not fail the same way")
            else:
                print(f"{name} {use}: HARM fails as with the default configuration: {msg(h)[:1]}")
            continue
        n = 0
        info = out / "info.json"  # HARM writes no dump when mining yields nothing to qualify (as before H22)
        for x in json.loads(info.read_text())["assertions"] if info.exists() else []:
            n += 1
            cons = {v for leaf in x["leaves"] if not leaf["antecedent"] for v in leaf["variables"]}
            rs = {roles.get(re.sub(r"\[[0-9]+\]$", "", v), "unknown") for v in cons}
            if not rs & {"comb", "state", "unknown"}:
                bad.append(f"{use}: consequent of {x['text']!r} reads only {sorted(rs)}")
            elif use == "all" and "|=>" in x["text"] and "state" not in rs:
                bad.append(f"{use}: |=> assertion {x['text']!r} without a state consequent")
            elif use == "all" and "|->" in x["text"] and not rs & {"comb", "unknown"}:
                bad.append(f"{use}: |-> assertion {x['text']!r} without a comb consequent")
        print(f"{name} {use}: {n} assertions")
    for b in bad:
        print(b)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
