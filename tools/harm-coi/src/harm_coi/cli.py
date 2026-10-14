"""Command line of harm-coi: SystemVerilog RTL in, coi.json (coi.v1) out."""
import argparse
import json
import sys
from importlib.metadata import PackageNotFoundError, version
from pathlib import Path

from . import __version__, cone, frontend, hints, predicates, relations, vcd


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
    ap.add_argument("--hints", metavar="FILE.json",
                    help="write HARM's hints from the RTL (hints v1, H22): roles, placement, templates per timing "
                         "class; --emit-config then uses them (implies --predicates)")
    ap.add_argument("--hints-use", choices=["all", "placement"], default="all",
                    help="what --emit-config takes from --hints (default all; placement: the placement only)")
    ap.add_argument("--reset", action="append", default=[], metavar="NAME",
                    help="a reset input, as HARM names it (--hints; asynchronous controls are found anyway); "
                         "!NAME for an active-low reset")
    ap.add_argument("--relations", action=argparse.BooleanOptionalAction, default=None,
                    help="H24 (D-038): also propositions from assignments (x == $past(e) / x == e, $stable(x)), both "
                         "polarities of 1-bit flags, assigned-only signals, and the fixed templates for the end of "
                         "reset and for unconditional relations; the default with --hints and --emit-config, "
                         "--no-relations restores the output before H24 (--relations needs --hints and --emit-config)")
    ap.add_argument("-v", "--verbose", action="store_true",
                    help="print why each signal is unknown and why each predicate was dropped")
    return ap


def main(argv=None):
    a = parser().parse_args(argv)
    if a.relations and not (a.hints and a.emit_config):
        print("harm-coi: --relations needs --hints and --emit-config", file=sys.stderr)
        return 2
    if a.relations is None:   # the default since H24's sign-off (the user, 2026-10-13)
        a.relations = bool(a.hints and a.emit_config)
    resets = [(r[1:], True) if r.startswith("!") else (r, False) for r in a.reset]
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
        preds, dropped, extra = [], [], {}
        if a.predicates or a.emit_config or a.hints:
            preds, dropped = predicates.harvest(design, comp, vis, extra)
    except (frontend.FrontendError, ValueError, OSError) as e:
        print(f"harm-coi: {e}", file=sys.stderr)
        return 1
    meta = {"design": a.top, "top": a.top, "vcd_scope": a.vcd_scope, "vcd_recursion": a.vcd_recursion,
            "clock": cone.name(clk), "max_depth": a.max_depth,
            "generator": {"name": "harm-coi", "version": generator_version()}}
    doc = {"version": "1", "meta": meta, "targets": targets, "unknown": sorted(unknown), "predicates": preds}
    h = None
    if a.hints:
        try:
            h = hints.build(doc, design, vis, extra, [n for n, _ in resets])
        except ValueError as e:
            print(f"harm-coi: {e}", file=sys.stderr)
            return 1
        Path(a.hints).write_text(json.dumps(h, indent=2) + "\n")
    Path(a.output).write_text(json.dumps(doc, indent=2) + "\n")
    if a.edges:
        lines = [f"{k} = {meta[k]}" for k in ("design", "top", "vcd_scope", "vcd_recursion", "clock", "max_depth")]
        lines += [f"target {n}" for n in sorted(names - unknown) if not direct.get(n)]
        lines += [f"{t} <- {s} @{d}" for t in sorted(direct) if t not in unknown for s, d in sorted(direct[t])]
        lines += [f"unknown {n}" for n in sorted(unknown)]
        Path(a.edges).write_text("\n".join(lines) + "\n")
    ext = None
    if a.relations:
        rel = relations.Relations(design, comp, vis)
        rels = rel.run()
        dropped += rel.dropped
        ext = relations.extras(rels, h, preds, extra, relations.widths(design, vis), resets, rel.holds(),
                               rel.constant_props)
    if a.emit_config:
        predicates.emit_config(a.emit_config, preds, a.output, h, a.hints_use, ext)
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
