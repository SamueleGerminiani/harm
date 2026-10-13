"""RTL predicate harvesting (H10, D-023): conditions, case labels, enum (FSM) values, comparisons
with constants and reset values, translated into HARM propositions with HARM's signal names.

A predicate is kept only if every signal it reads is visible (HARM's names, as in the cones); the
others are dropped and counted. Constants are written as sized decimal literals with the width of
the signal they are compared with, the signal on the left; a 1-bit comparison is written as the
signal or its negation. Elaboration-time conditions (generate if) are never seen: they are not
statements of a process.
"""
from collections import defaultdict
from dataclasses import dataclass, field

import pyslang
from pyslang import ast

from .frontend import SK, EK, TK, STRUCTS

BO = ast.BinaryOperator
COMPARISONS = {BO.Equality: "==", BO.Inequality: "!=", BO.CaseEquality: "==", BO.CaseInequality: "!=",
               BO.LessThan: "<", BO.LessThanEqual: "<=", BO.GreaterThan: ">", BO.GreaterThanEqual: ">="}
MIRROR = {"==": "==", "!=": "!=", "<": ">", "<=": ">=", ">": "<", ">=": "<="}
# HARM keeps at most this many bits of a logic signal (it truncates wider ones when reading the
# trace, minerUtils.cc toVarDeclaration), so a predicate on a wider signal is dropped (H11c, F-L5)
HARM_MAX_LOGIC_BITS = 511


# ---- predicate trees: ("sig", atom) | ("bit", atom, i) | ("cmp", op, operand, value, width[, signed])
# signed (H25, D-039): the RTL compares the signal as signed and the value is the signed constant
#                      | ("not", p) | ("and", [p...]) | ("or", [p...])
@dataclass
class Harvest:
    preds: dict = field(default_factory=lambda: defaultdict(
        lambda: {"targets": set(), "src": set(), "signals": set(), "kinds": set()}))
    dropped: list = field(default_factory=list)   # (reason, src)
    widths: dict = field(default_factory=dict)    # atom -> width of the signal it reads


class Harvester:
    def __init__(self, extractor, comp, vis):
        self.x = extractor
        self.sm = comp.sourceManager
        self.ctx = ast.EvalContext(extractor.top)
        self.vis = vis                             # atom -> visible HARM name
        self.out = Harvest()

    # ------------------------------------------------------------------ constants
    def constant(self, e):
        """the integer value of a constant expression, or None"""
        refs = []

        def cb(n):
            if isinstance(n, ast.Expression) and n.kind in (EK.NamedValue, EK.HierarchicalValue):
                if n.symbol.kind not in (SK.Parameter, SK.EnumValue):
                    refs.append(n)
            return ast.VisitAction.Advance

        e.visit(cb)
        if refs:
            return None
        cv = e.constant
        if cv is None:
            try:
                cv = e.eval(self.ctx)
            except Exception:
                return None
        v = getattr(cv, "value", None) if cv is not None else None
        if not isinstance(v, pyslang.SVInt) or v.hasUnknown:
            return None
        return int(v.toString(pyslang.LiteralBase.Decimal, False))

    # ------------------------------------------------------------------ operands
    def operand(self, e):
        """('sig', atom, width) or ('bit', atom, i) for a signal or a constant bit select of one"""
        while e.kind == EK.Conversion:
            e = e.operand
        r = self.x.resolve(e)
        if r is not None and r[0] == "sig" and r[2].canonicalType.kind not in STRUCTS:
            self.out.widths[r[1]] = r[2].bitWidth
            return ("sig", r[1], r[2].bitWidth)
        if e.kind == EK.ElementSelect:
            r = self.x.resolve(e.value)
            i = self.constant(e.selector)
            if r is not None and r[0] == "sig" and i is not None:
                self.out.widths[r[1]] = r[2].bitWidth
                return ("bit", r[1], i)
        return None

    def pred(self, e):
        """the predicate tree of a Boolean expression, or None if it cannot be translated"""
        while e.kind == EK.Conversion:
            e = e.operand
        if e.kind == EK.BinaryOp and e.op in COMPARISONS:
            op = COMPARISONS[e.op]
            # H25: a comparison is signed when both its operands are (IEEE 1800-2017 11.8.1)
            signed = e.left.type.isSigned and e.right.type.isSigned
            for a, b, o in ((e.left, e.right, op), (e.right, e.left, MIRROR[op])):
                opnd = self.operand(a)
                v = self.constant(b)
                if opnd is not None and v is not None:
                    w = opnd[2] if opnd[0] == "sig" else 1
                    return self.cmp(o, opnd, v % (1 << w) if v >= 0 else v % (1 << w), w, v, signed)
            return None
        if e.kind == EK.BinaryOp and e.op in (BO.LogicalAnd, BO.LogicalOr):
            l, r = self.pred(e.left), self.pred(e.right)
            if l is None or r is None:
                return None
            kind = "and" if e.op == BO.LogicalAnd else "or"
            items = []
            for p in (l, r):
                items += p[1] if p[0] == kind else [p]
            return (kind, items)
        if e.kind == EK.UnaryOp and e.op in (ast.UnaryOperator.LogicalNot, ast.UnaryOperator.BitwiseNot):
            p = self.pred(e.operand)
            if p is None or (e.op == ast.UnaryOperator.BitwiseNot and p[0] not in ("sig", "bit", "not")):
                return None
            return p[1] if p[0] == "not" else ("not", p)
        opnd = self.operand(e)
        if opnd is not None and (opnd[0] == "bit" or opnd[2] == 1):
            return opnd if opnd[0] == "bit" else ("sig", opnd[1])
        return None

    def cmp(self, op, opnd, v, w, raw, signed=False):
        if signed and w > 1 and opnd[0] == "sig" and (raw < 0 or op not in ("==", "!=")):
            # H25 (D-039): an ordering, or a negative constant, read as signed: $signed(x) < -w'sdN
            if not -(1 << (w - 1)) <= raw < (1 << (w - 1)):
                return None                 # the constant does not fit the signed signal: always true/false
            return ("cmp", op, ("sig", opnd[1]), raw, w, True)
        if raw < 0 or raw >= (1 << w):
            return None                     # the constant does not fit the signal: always true/false
        atom = opnd if opnd[0] == "bit" else ("sig", opnd[1])
        if w == 1 and op in ("==", "!="):
            positive = (v == 1) == (op == "==")
            return atom if positive else ("not", atom)
        return ("cmp", op, atom, v, w)

    def width(self, p):
        """the widest signal or constant a predicate tree reads"""
        if p[0] in ("sig", "bit"):
            return self.out.widths.get(p[1], 1)
        if p[0] == "cmp":
            return max(p[4], self.width(p[2]))
        if p[0] == "not":
            return self.width(p[1])
        return max(self.width(i) for i in p[1])

    # ------------------------------------------------------------------ rendering
    def name(self, atom):
        n = self.vis.get(atom)
        if n is None:
            raise KeyError(atom)
        return n

    def render(self, p, top=True):
        k = p[0]
        if k == "sig":
            return escaped(self.name(p[1]))
        if k == "bit":
            return f"{escaped(self.name(p[1]))}[{p[2]}]"
        if k == "cmp" and len(p) > 5 and p[5]:
            return f"$signed({self.render(p[2], False)}) {p[1]} {signed_literal(p[3], p[4])}"
        if k == "cmp":
            return f"{self.render(p[2], False)} {p[1]} {p[4]}'d{p[3]}"
        if k == "not":
            inner = self.render(p[1], False)
            return "!" + inner if p[1][0] in ("sig", "bit") else f"!({inner})"
        sep = " && " if k == "and" else " || "
        parts = [self.render(i, False) for i in p[1]]
        parts = [f"({t})" if i[0] in ("and", "or") and i[0] != k else t for t, i in zip(parts, p[1])]
        return sep.join(parts)

    def atoms(self, p):
        if p[0] in ("sig", "bit", "cmp"):
            return [p]
        if p[0] == "not":
            return self.atoms(p[1])
        return [a for i in p[1] for a in self.atoms(i)]

    # ------------------------------------------------------------------ recording
    def src(self, e):
        loc = e.sourceRange.start
        import os
        return f"{os.path.basename(self.sm.getFileName(loc))}:{self.sm.getLineNumber(loc)}"

    def add(self, p, targets, where, kind):
        """record p (a tree, or None if not translatable) with the target atoms"""
        if p is None:
            self.out.dropped.append((f"{kind}: not translatable", where))
            return
        if self.width(p) > HARM_MAX_LOGIC_BITS:
            self.out.dropped.append((f"{kind}: wider than HARM's {HARM_MAX_LOGIC_BITS}-bit limit", where))
            return
        try:
            text = self.render(p)
        except KeyError as k:
            self.out.dropped.append((f"{kind}: signal {k} not visible", where))
            return
        entry = self.out.preds[text]
        entry["src"].add(where)
        entry["signals"] |= {self.name((a[2] if a[0] == "cmp" else a)[1]) for a in self.atoms(p)}  # H22: what it reads
        entry["kinds"].add(kind)
        entry["targets"] |= {self.vis[t] for t in targets if t in self.vis}

    def condition(self, e, targets, kind="condition"):
        p = self.pred(e)
        where = self.src(e)
        self.add(p, targets, where, kind)
        if p is not None and p[0] in ("and", "or", "not"):
            for a in self.atoms(p):
                self.add(a, targets, where, kind)

    def comparisons(self, e, targets):
        """comparisons with a constant side, and the conditions of ?:, inside an expression"""
        def cb(n):
            if not isinstance(n, ast.Expression):
                return ast.VisitAction.Advance
            if n.kind == EK.BinaryOp and n.op in COMPARISONS:
                p = self.pred(n)
                if p is not None:
                    self.add(p, targets, self.src(n), "comparison")
            elif n.kind == EK.ConditionalOp:
                for c in n.conditions:
                    self.condition(c.expr, targets)
            return ast.VisitAction.Advance
        e.visit(cb)

    # ------------------------------------------------------------------ structure
    def written(self, lhs):
        outs, _ = self.x.lvalues(lhs, None)
        return {a for a, _, local in outs if not local}

    def assigned_in(self, stmt):
        out = set()

        def cb(n):
            if isinstance(n, ast.Expression) and n.kind == EK.Assignment:
                out.update(self.written(n.left))
            return ast.VisitAction.Advance
        stmt.visit(cb)
        return out

    def run(self):
        for path, typ, sym in self.x.sig.values():
            t = typ.canonicalType
            if t.kind == SK.EnumType:
                for ev in t:
                    if ev.kind == SK.EnumValue:
                        v = ev.value.value
                        if isinstance(v, pyslang.SVInt) and not v.hasUnknown:
                            n = int(v.toString(pyslang.LiteralBase.Decimal, False))
                            self.add(self.cmp("==", ("sig", path, t.bitWidth), n, t.bitWidth, n),
                                     {path}, self.src_sym(ev), "enum value")
        self.scope(self.x.top.body)
        return self.out

    def src_sym(self, sym):
        import os
        return f"{os.path.basename(self.sm.getFileName(sym.location))}:{self.sm.getLineNumber(sym.location)}"

    def scope(self, body):
        for m in body:
            k = m.kind
            if k == SK.ContinuousAssign:
                a = m.assignment
                self.comparisons(a.right, self.written(a.left))
            elif k == SK.Net and m.initializer is not None:
                self.comparisons(m.initializer, set(self.x.leaves(self.x.path_of(m), m.type)))
            elif k == SK.ProceduralBlock:
                self.procedure(m)
            elif k == SK.Instance:
                self.scope(m.body)
            elif k == SK.InstanceArray:
                for e in m.elements:
                    if e.kind == SK.Instance:
                        self.scope(e.body)
            elif k == SK.GenerateBlock and not m.isUninstantiated:
                self.scope(m)
            elif k == SK.GenerateBlockArray:
                for e in m.entries:
                    if not e.isUninstantiated:
                        self.scope(e)

    def procedure(self, pb):
        PK = ast.ProceduralBlockKind
        if pb.procedureKind in (PK.Initial, PK.Final):
            return
        body = pb.body
        stmt = body.stmt if body.kind == TK.Timed else body
        self.stmt(stmt)
        if pb.procedureKind == PK.AlwaysFF or (body.kind == TK.Timed and pb.procedureKind == PK.Always):
            self.reset_values(stmt)

    def reset_values(self, stmt):
        """the first if of a clocked process whose branch assigns only constants (D-023)"""
        first = self.first_if(stmt)
        if first is None:
            return
        assigns = []

        def cb(n):
            if isinstance(n, ast.Expression) and n.kind == EK.Assignment:
                assigns.append(n)
                return ast.VisitAction.Skip
            return ast.VisitAction.Advance
        first.ifTrue.visit(cb)
        if not assigns:
            return
        values = []
        for a in assigns:
            opnd = self.operand(a.left)
            v = self.constant(a.right)
            if opnd is None or v is None:
                return                       # not only constants: not a reset branch
            values.append((a, opnd, v))
        for a, opnd, v in values:
            w = opnd[2] if opnd[0] == "sig" else 1
            self.add(self.cmp("==", opnd, v, w, v, a.left.type.isSigned), {opnd[1]}, self.src(a), "reset value")

    def first_if(self, s):
        if s.kind == TK.Conditional:
            return s
        if s.kind == TK.Block:
            return self.first_if(s.body)
        if s.kind == TK.List:
            for x in s.list:
                f = self.first_if(x)
                if f is not None:
                    return f
        return None

    def stmt(self, s):
        k = s.kind
        if k == TK.Block:
            self.stmt(s.body)
        elif k == TK.List:
            for x in s.list:
                self.stmt(x)
        elif k == TK.ExpressionStatement and s.expr.kind == EK.Assignment:
            self.comparisons(s.expr.right, self.written(s.expr.left))
        elif k == TK.Conditional:
            targets = self.assigned_in(s.ifTrue) | (self.assigned_in(s.ifFalse) if s.ifFalse else set())
            for c in s.conditions:
                self.condition(c.expr, targets)
            self.stmt(s.ifTrue)
            if s.ifFalse is not None:
                self.stmt(s.ifFalse)
        elif k == TK.Case:
            for it in s.items:
                targets = self.assigned_in(it.stmt)
                for label in it.expressions:
                    v = self.constant(label)
                    opnd = self.operand(s.expr)
                    if opnd is not None and v is not None:
                        w = opnd[2] if opnd[0] == "sig" else 1
                        self.add(self.cmp("==", opnd, v, w, v), targets, self.src(label), "case label")
                    else:
                        self.out.dropped.append(("case label: not translatable", self.src(label)))
                self.stmt(it.stmt)
            if s.defaultCase is not None:
                self.stmt(s.defaultCase)
        elif k in (TK.ForLoop, TK.WhileLoop, TK.DoWhileLoop, TK.RepeatLoop, TK.ForeachLoop, TK.ForeverLoop):
            if k == TK.ForLoop and s.stopExpr is not None:
                self.condition(s.stopExpr, self.assigned_in(s.body), "loop condition")
            self.stmt(s.body)
        elif k == TK.Timed:
            self.stmt(s.stmt)


# H23 (D-037): HARM's keywords, as in HARM's src/utils/include/harmKeywords.hh (tests/test_keywords.py compares
# the two); a signal named after one is written as a SystemVerilog escaped identifier
KEYWORDS = frozenset({"inside", "true", "false", "substr", "and", "or", "not", "eventually", "s_eventually",
                      "nexttime", "next", "X", "until", "W", "always", "G", "first_match", "F", "R", "intersect"})


def signed_literal(v, w):
    """H25: a signed constant of width w as HARM and SystemVerilog read it: w'sdN, -w'sdN, or the most negative value
    in binary (w'sdN would not fit)"""
    if v >= 0:
        return f"{w}'sd{v}"
    if -v < (1 << (w - 1)):
        return f"-{w}'sd{-v}"
    return f"{w}'sb1{'0' * (w - 1)}"


def escaped(name):
    """a HARM name as a formula writes it: '\\W ' for a keyword, unchanged otherwise"""
    return f"\\{name} " if name in KEYWORDS else name


def harvest(design, comp, vis, extra=None):
    """(sorted predicate records for coi.json, dropped list); `extra`, if given, gets each predicate's signals and
    harvesting kinds (H22), which coi.json does not carry"""
    h = Harvester(design.extractor, comp, vis).run()
    if extra is not None:
        extra.update({t: {"signals": e["signals"], "kinds": e["kinds"]} for t, e in h.preds.items()})
    records = []
    for text in sorted(h.preds):
        e = h.preds[text]
        records.append({"expr": text, "origin": "rtl", "src": ", ".join(sorted(e["src"])),
                        "targets": sorted(e["targets"])})
    return records, h.dropped


def emit_config(path, records, coi_path, hints=None, use="all", extras=None):
    """a starter HARM configuration (D-023): one context, the predicates with origin "rtl", the
    cone in rank mode, and --generate-config's templates and sorts. With `hints` (H22): each predicate's
    placement; with use="all" also a template per timing class that has a consequent (one class, one domain)"""
    import os
    from xml.sax.saxutils import quoteattr
    rel = os.path.relpath(coi_path, os.path.dirname(os.path.abspath(path)) or ".")
    lines = ["<harm>", "    <!-- written by harm-coi --emit-config (H10): RTL predicates with origin=\"rtl\" -->",
             '    <context name="default">']
    place = {p["expr"]: p for p in hints["propositions"]} if hints else {}
    for r in records:
        if extras and r["expr"] in extras["drop"]:
            continue
        loc = "a, c, dt"
        if hints:
            p = place[r["expr"]]
            loc = ", ".join(p["loc"] if use == "all" else ["a", "c", "dt"] if p["consequent"] else ["a", "dt"])
        if extras and r["expr"] in extras["loc_add"]:
            loc = ", ".join([loc] + extras["loc_add"][r["expr"]])
        lines.append(f'        <prop exp={quoteattr(r["expr"])} loc="{loc}" origin="rtl"/>')
    if extras:   # H24, --relations (D-038)
        for e, loc, origin in extras["props"]:
            lines.append(f'        <prop exp={quoteattr(e)} loc="{", ".join(loc)}" origin="{origin}"/>')
        for c, e, loc in extras["numerics"]:
            lines.append(f'        <numeric clustering={quoteattr(c)} exp={quoteattr(e)} loc="{", ".join(loc)}" origin="rtl"/>')
    lines.append(f"        <coi file={quoteattr(rel)} mode=\"rank\"/>")
    if hints and use == "all":
        used = {c for p in hints["propositions"] for c in p["consequent"]}
        if extras:
            used |= {c for c, d in hints["classes"].items() if str(d["domain"]) in extras["domains"]}
        for c, d in hints["classes"].items():
            if c in used:
                lines.append(f'        <template dtLimits="{d["dtLimits"]}" exp={quoteattr(d["template"])}/>')
    else:
        lines.append('        <template dtLimits="5D,3W,15A,-0.1E,U" exp="G({..#1&amp;..}|-&gt; P0)"/>')
    for dt, t in (extras or {}).get("templates", []):
        lines.append(f'        <template dtLimits="{dt}" exp={quoteattr(t)}/>')
    lines += [
              '        <sort name="causality" exp="1-afct/traceLength"/>',
              '        <sort name="frequency" exp="atct/traceLength"/>',
              "    </context>", "</harm>", ""]
    with open(path, "w") as f:
        f.write("\n".join(lines))
