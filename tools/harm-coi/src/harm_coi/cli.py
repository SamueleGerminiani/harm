"""Command line of harm-coi: SystemVerilog RTL in, coi.json (coi.v1) out."""
import argparse
import json
import sys
from importlib.metadata import PackageNotFoundError, version
from pathlib import Path

from . import __version__, cone, frontend, predicates, vcd


def generator_version():
    try:
        fe = version("pyslang")
    except PackageNotFoundError:
        fe = "?"
    return f"{__version__} (pyslang {fe})"


def parser():
    ap = argparse.ArgumentParser(prog="harm-coi", description=__doc__)
    ap.add_argument("--top", required=True, help="top module (the design under the VCD scope)")
    ap.add_argument("--files", nargs="+", required=True, help="SystemVerilog sources")
    ap.add_argument("--define", action="append", default=[], metavar="NAME[=VALUE]")
    ap.add_argument("--include", action="append", default=[], metavar="DIR")
    ap.add_argument("--vcd-scope", required=True, help="scope of the top instance in the trace, e.g. tb::dut")
    ap.add_argument("--vcd-recursion", type=int, required=True, help="as HARM's --vcd-r")
    ap.add_argument("--vcd", help="the trace: its signal names are the visible ones")
    ap.add_argument("--clock", help="the sampling clock, as HARM names it (default: inferred)")
    ap.add_argument("--max-depth", type=int, default=3)
    ap.add_argument("--edges", help="also write the direct edges, in edges.txt format")
    ap.add_argument("-o", "--output", required=True)
    ap.add_argument("--predicates", action="store_true",
                    help="also harvest RTL predicates into coi.json (H10, D-023)")
    ap.add_argument("--emit-config", metavar="FILE.xml",
                    help="write a starter HARM configuration with the predicates (implies --predicates)")
    ap.add_argument("-v", "--verbose", action="store_true",
                    help="print why each signal is unknown and why each predicate was dropped")
    return ap


def main(argv=None):
    a = parser().parse_args(argv)
    if not 0 <= a.max_depth <= 64:
        print("harm-coi: --max-depth must be in 0..64", file=sys.stderr)
        return 2
    try:
        comp, top, am = frontend.elaborate(a.top, a.files, a.define, a.include)
        design = frontend.extract(top, am)
        clk, clock_nodes = cone.resolve_clocks(design, a.clock)
        vcd_names = vcd.visible_names(a.vcd, a.vcd_scope, a.vcd_recursion) if a.vcd else None
        vis, orphans = cone.visible_names(design, a.vcd_recursion, vcd_names, clk)
        vis = {x: n for x, n in vis.items() if x != clk}   # the clock is neither target nor source
        direct, unknown = cone.direct_edges(design, vis, clock_nodes, a.max_depth)
        unknown |= orphans
        names = set(vis.values())
        targets, unknown = cone.closure(names, direct, unknown, a.max_depth)
        preds, dropped = [], []
        if a.predicates or a.emit_config:
            preds, dropped = predicates.harvest(design, comp, vis)
    except (frontend.FrontendError, ValueError, OSError) as e:
        print(f"harm-coi: {e}", file=sys.stderr)
        return 1
    meta = {"design": a.top, "top": a.top, "vcd_scope": a.vcd_scope, "vcd_recursion": a.vcd_recursion,
            "clock": cone.name(clk), "max_depth": a.max_depth,
            "generator": {"name": "harm-coi", "version": generator_version()}}
    doc = {"version": "1", "meta": meta, "targets": targets, "unknown": sorted(unknown), "predicates": preds}
    Path(a.output).write_text(json.dumps(doc, indent=2) + "\n")
    if a.edges:
        lines = [f"{k} = {meta[k]}" for k in ("design", "top", "vcd_scope", "vcd_recursion", "clock", "max_depth")]
        lines += [f"target {n}" for n in sorted(names - unknown) if not direct.get(n)]
        lines += [f"{t} <- {s} @{d}" for t in sorted(direct) if t not in unknown for s, d in sorted(direct[t])]
        lines += [f"unknown {n}" for n in sorted(unknown)]
        Path(a.edges).write_text("\n".join(lines) + "\n")
    if a.emit_config:
        predicates.emit_config(a.emit_config, preds, a.output)
    if a.verbose:
        for why, where in dropped:
            print(f"harm-coi: predicate dropped at {where}: {why}", file=sys.stderr)
        for atom, why in sorted(design.unknown.items()):
            print(f"harm-coi: unknown {cone.name(atom)}: {why}", file=sys.stderr)
        for n in sorted(orphans):
            print(f"harm-coi: unknown {n}: in the trace, not produced by the RTL", file=sys.stderr)
    return 0


def entry():
    sys.exit(main())
