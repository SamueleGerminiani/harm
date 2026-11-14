"""H45-mutant-eval: classical mutants of SystemVerilog sources, at source level, with pyslang (doc/plan/H45_PLAN.md).

A site is one fault:
- sa0 / sa1 / inv: one bit of a variable or net forced to 0, forced to 1, or inverted at every assignment to it in its
  module (procedural or continuous; the variable must be assigned whole, never through a select);
- op: one binary operator replaced by its pair (+/-, &/|, &&/||, ==/!=, </<=, >/>=);
- cond: an if condition or a ?: predicate negated;
- const: an integer literal k replaced by k+1 (k-1 at the top of its width).
Only code inside continuous assignments and always blocks is mutated (not declarations, parameters or selects).

Usage: python mutate.py --top TOP --files F... --list | --sample N --seed S --out DIR
"""

from __future__ import annotations

import argparse
import json
import random
import shutil
import sys
from dataclasses import asdict, dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "harm-coi" / "src"))
from pyslang import ast  # noqa: E402

from harm_coi.frontend import elaborate  # noqa: E402

SK, EK, STK = ast.SymbolKind, ast.ExpressionKind, ast.StatementKind
BO = ast.BinaryOperator

PAIRS = {BO.Add: "-", BO.Subtract: "+", BO.BinaryAnd: "|", BO.BinaryOr: "&", BO.LogicalAnd: "||",
         BO.LogicalOr: "&&", BO.Equality: "!=", BO.Inequality: "==", BO.LessThan: "<=", BO.LessThanEqual: "<",
         BO.GreaterThan: ">=", BO.GreaterThanEqual: ">"}
GROUP = {"sa0": "stuck", "sa1": "stuck", "inv": "inv", "op": "op", "cond": "condconst", "const": "condconst"}
PROPORTIONS = {"stuck": 0.5, "inv": 0.1, "op": 0.25, "condconst": 0.15}


@dataclass
class Site:
    id: str
    op: str
    module: str
    lines: list[int]
    detail: str
    edits: list[tuple[str, int, int, str]] = field(repr=False)  # (file, start, end, replacement)
    signal: str | None = None
    bit: int | None = None


class MacroCode(Exception):
    pass


class Collector:
    def __init__(self, comp):
        self.sm = comp.sourceManager
        self.text: dict[str, str] = {}
        self.sites: dict[str, Site] = {}
        # per (module, signal): whole assignments' right-hand sides, widths seen, a select seen, declared type text
        self.targets: dict[tuple[str, str], dict] = {}

    def src(self, rng) -> tuple[str, int, int]:
        """The range's file and offsets; MacroCode for text that comes from a macro expansion (not editable)."""
        if self.sm.isMacroLoc(rng.start) or self.sm.isMacroLoc(rng.end):
            raise MacroCode
        f = self.sm.getFullPath(rng.start.buffer)
        if f not in self.text:
            self.text[f] = Path(f).read_text()
        return f, rng.start.offset, rng.end.offset

    def line(self, f: str, off: int) -> int:
        return self.text[f].count("\n", 0, off) + 1

    def add(self, op, module, edits, detail, signal=None, bit=None):
        lines = sorted({self.line(f, a) for f, a, _, _ in edits})
        f0, a0 = edits[0][0], edits[0][1]
        sid = (f"{op}-{module}-{signal}-b{bit}" if signal is not None
               else f"{op}-{module}-L{self.line(f0, a0)}-C{a0 - self.text[f0].rfind(chr(10), 0, a0)}")
        if sid not in self.sites:  # the same source seen from another instance
            self.sites[sid] = Site(sid, op, module, lines, detail, edits, signal, bit)

    # ---- traversal
    def scope(self, body, module: str):
        for m in body:
            k = m.kind
            if k == SK.ContinuousAssign:
                self.code(m.assignment, module)
            elif k == SK.ProceduralBlock and m.procedureKind not in (ast.ProceduralBlockKind.Initial,
                                                                       ast.ProceduralBlockKind.Final):
                self.code(m.body, module)
            elif k == SK.Instance:
                self.scope(m.body, m.body.definition.name)
            elif k == SK.InstanceArray:
                for e in m.elements:
                    if e.kind == SK.Instance:
                        self.scope(e.body, e.body.definition.name)
            elif k == SK.GenerateBlock and not m.isUninstantiated:
                self.scope(m, module)
            elif k == SK.GenerateBlockArray:
                for e in m.entries:
                    if not e.isUninstantiated:
                        self.scope(e, module)

    def code(self, node, module: str):
        selectors: list[tuple[str, int, int]] = []

        def cb(e):
            try:
                act(e)
            except MacroCode:
                pass
            return True

        def act(e):
            k = getattr(e, "kind", None)
            if k in (EK.ElementSelect, EK.RangeSelect):
                for part in ((e.selector,) if k == EK.ElementSelect else (e.left, e.right)):
                    if part is not None and part.sourceRange is not None:
                        selectors.append(self.src(part.sourceRange))
            if k == EK.Assignment:
                self.assignment(e, module)
            elif k == EK.BinaryOp and e.op in PAIRS:
                syn = e.syntax
                while syn is not None and syn.kind.name == "ParenthesizedExpression":
                    syn = syn.expression
                tok = getattr(syn, "operatorToken", None)
                if tok is not None and not self.sm.isMacroLoc(tok.location):
                    f = self.sm.getFullPath(tok.location.buffer)
                    self.src(e.sourceRange)
                    a = tok.location.offset
                    old = tok.rawText
                    self.add("op", module, [(f, a, a + len(old), PAIRS[e.op])], f"{old} -> {PAIRS[e.op]}")
            elif k == EK.ConditionalOp:
                self.negate(e.conditions[0].expr, module)
            elif k == STK.Conditional:
                self.negate(e.conditions[0].expr, module)
            elif k == EK.IntegerLiteral:
                self.literal(e, module, selectors)

        node.visit(cb)

    def negate(self, cond, module):
        f, a, b = self.src(cond.sourceRange)
        old = self.text[f][a:b]
        self.add("cond", module, [(f, a, b, f"!({old})")], f"{old} -> !({old})")

    def literal(self, e, module, selectors):
        f, a, b = self.src(e.sourceRange)
        if any(sf == f and sa <= a and b <= sb for sf, sa, sb in selectors):
            return
        old = self.text[f][a:b]
        v = _literal_value(old)
        if v is None:
            return
        w = e.type.bitWidth
        new = v + 1 if v + 1 < (1 << w) else v - 1
        if "'" in old:
            size = old.split("'")[0]
            signed = "s" if old.split("'")[1][:1] in "sS" else ""
            text = f"{size}'{signed}d{new}"
        else:
            text = str(new)
        self.add("const", module, [(f, a, b, text)], f"{old} -> {text}")

    def assignment(self, e, module):
        lhs = e.left
        key = None
        if lhs.kind == EK.NamedValue:
            key = (module, lhs.symbol.name)
        else:  # a select or a concatenation: the variables inside are not stuck-at candidates
            def mark(x):
                if getattr(x, "kind", None) == EK.NamedValue:
                    self.targets.setdefault((module, x.symbol.name), _target())["partial"] = True
                return True
            lhs.visit(mark)
            return
        t = self.targets.setdefault(key, _target())
        sym = lhs.symbol
        if sym.kind == SK.Variable or sym.kind == SK.Net:
            t["widths"].add(lhs.type.bitWidth)
            t["enum"] = lhs.type.isEnum
            dt = sym.declaredType.typeSyntax
            if dt is not None and dt.sourceRange is not None:
                f, a, b = self.src(dt.sourceRange)
                t["type"] = self.text[f][a:b]
        else:
            t["partial"] = True
        try:
            f, a, b = self.src(e.right.sourceRange)
        except MacroCode:
            t["partial"] = True  # an assignment inside a macro: the bit cannot be forced at every assignment
            return
        t["rhs"].add((f, a, b))

    def stuck_at(self, inputs: set[tuple[str, str]]):
        for (module, name), t in sorted(self.targets.items()):
            if t["partial"] or len(t["widths"]) != 1 or (module, name) in inputs or not t["rhs"]:
                continue
            if t["enum"] and not t["type"]:
                continue
            w = next(iter(t["widths"]))
            full = (1 << w) - 1
            for bit in range(w):
                m = 1 << bit
                for op, expr in (("sa0", f"& {w}'h{full & ~m:x}"), ("sa1", f"| {w}'h{m:x}"), ("inv", f"^ {w}'h{m:x}")):
                    edits = []
                    for f, a, b in sorted(t["rhs"]):
                        inner = f"{w}'({self.text[f][a:b]}) {expr}"
                        edits.append((f, a, b, f"{t['type']}'({inner})" if t["enum"] else inner))
                    self.add(op, module, edits, f"{name}[{bit}] {op}", signal=name, bit=bit)


def _target():
    return {"rhs": set(), "widths": set(), "partial": False, "enum": False, "type": ""}


def _literal_value(text: str) -> int | None:
    t = text.replace("_", "")
    if "'" not in t:
        return int(t) if t.isdigit() else None
    base = t.split("'")[1].lstrip("sS")
    if not base:
        return None
    radix = {"d": 10, "h": 16, "b": 2, "o": 8}.get(base[0].lower())
    digits = base[1:]
    if radix is None or not digits or any(c in "xXzZ?" for c in digits):
        return None
    try:
        return int(digits, radix)
    except ValueError:
        return None


def sites(files: list[Path], top: str, defines=(), includes=()) -> list[Site]:
    comp, inst, _ = elaborate(top, [str(f) for f in files], defines, includes)
    c = Collector(comp)
    c.scope(inst.body, inst.body.definition.name)
    inputs = set()
    stack = [inst]
    while stack:  # every module's input ports: driven from outside
        i = stack.pop()
        for p in i.body.portList:
            if getattr(p, "direction", None) == ast.ArgumentDirection.In:
                inputs.add((i.body.definition.name, p.name))
        for m in i.body:
            if m.kind == SK.Instance:
                stack.append(m)
    c.stuck_at(inputs)
    return sorted(c.sites.values(), key=lambda s: s.id)


def sample(all_sites: list[Site], n: int, seed: int) -> list[Site]:
    """n sites, by group in PROPORTIONS (a group short of sites gives its share to the others), fixed seed."""
    if n >= len(all_sites):
        return sorted(all_sites, key=lambda s: s.id)
    by: dict[str, list[Site]] = {g: [] for g in PROPORTIONS}
    for s in sorted(all_sites, key=lambda s: s.id):
        by[GROUP[s.op]].append(s)
    quota = {g: round(n * p) for g, p in PROPORTIONS.items()}
    quota[max(quota, key=quota.get)] += n - sum(quota.values())
    while True:  # move the shares that a group cannot take
        spare = sum(max(0, quota[g] - len(by[g])) for g in quota)
        for g in quota:
            quota[g] = min(quota[g], len(by[g]))
        if not spare:
            break
        open_groups = [g for g in quota if quota[g] < len(by[g])]
        for i in range(spare):
            quota[open_groups[i % len(open_groups)]] += 1
    rng = random.Random(seed)
    out = []
    for g in PROPORTIONS:
        out += rng.sample(by[g], quota[g])
    return out


def apply(site: Site, files: list[Path], outdir: Path) -> list[Path]:
    """Copies of the files with the site's edits, in outdir (same file names); returns them in the files' order."""
    outdir.mkdir(parents=True, exist_ok=True)
    names = [Path(f).name for f in files]
    if len(set(names)) != len(names):
        raise ValueError("two source files with the same name")
    outs = []
    for f in files:
        f = Path(f).resolve()
        text = f.read_text()
        for ef, a, b, new in sorted((e for e in site.edits if Path(e[0]).resolve() == f), key=lambda e: -e[1]):
            text = text[:a] + new + text[b:]
        out = outdir / f.name
        out.write_text(text)
        outs.append(out)
    return outs


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--top", required=True)
    ap.add_argument("--files", nargs="+", required=True)
    ap.add_argument("-D", dest="defines", action="append", default=[])
    ap.add_argument("-I", dest="includes", action="append", default=[])
    ap.add_argument("--list", action="store_true", help="print every site as JSON lines")
    ap.add_argument("--sample", type=int)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--out", type=Path, help="with --sample: one folder per mutant, and mutants.json")
    a = ap.parse_args()
    files = [Path(f) for f in a.files]
    all_sites = sites(files, a.top, a.defines, a.includes)
    if a.list:
        for s in all_sites:
            print(json.dumps({k: v for k, v in asdict(s).items() if k != "edits"}))
        return
    chosen = sample(all_sites, a.sample or len(all_sites), a.seed)
    if a.out:
        if a.out.exists():
            shutil.rmtree(a.out)
        for s in chosen:
            apply(s, files, a.out / s.id)
        (a.out / "mutants.json").write_text(json.dumps(
            {"sites": len(all_sites), "seed": a.seed,
             "mutants": [{k: v for k, v in asdict(s).items() if k != "edits"} for s in chosen]}, indent=1))
    print(f"{len(all_sites)} sites, {len(chosen)} chosen")


if __name__ == "__main__":
    main()
