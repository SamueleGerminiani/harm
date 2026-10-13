"""H24 (D-038): propositions from assignments, `--relations`.

- A relation per assignment to a whole visible signal x, outside a clocked process's reset branch (the first if whose
  branch assigns only constants, as the reset values of D-023): `x <= e` in a clocked process gives
  `x == ($past(e, 1) & M)`, a continuous or combinational `x = e` gives `x == (e & M)`. `e` is written in HARM's
  syntax with SystemVerilog's widths kept (a product or left shift with one operand widened, as HARM computes them at
  the operands' width): a subexpression that may carry bits above its width (`+ - *`, unary `-`,
  `~`, an RTL `<<`, and `& | ^ ?:` over such) is masked to its width where a context needs the exact value
  (comparison and logical operands, `>>`, a concatenation's part, a condition); the relation is masked to x's width
  when e may carry such bits or is wider. A concatenation is written with shifts and `|` (constant zero parts left
  out). Signed comparisons, sign extensions, arithmetic right shifts, `/ % **`, replications, reductions and unknown
  constructs are not translated (dropped); other signed arithmetic is the same bits as unsigned once masked.
  At most MAX_PER_TARGET relations per target (source order) and MAX_OPS operators per relation.
- Unconditional (no if or case above the assignment but the reset branch) or conditional; registered or not.
- Numerics (Q6): a register whose assignment reads it gets its delta `x - $past(x, 1)` (the values of wide signals
  were dropped: most of ima's mining time for little).
- Conditional relations and `$stable` go to their own single-cycle decision trees (domains 6, 7).
"""
from dataclasses import dataclass, field

from pyslang import ast

from .frontend import EK, SK, TK
from .predicates import COMPARISONS, HARM_MAX_LOGIC_BITS, Harvester, escaped

BO, UO = ast.BinaryOperator, ast.UnaryOperator
MAX_PER_TARGET = 8
MAX_OPS = 16
DIRTY_BIN = {BO.Add: "+", BO.Subtract: "-", BO.Multiply: "*", BO.LogicalShiftLeft: "<<",
             BO.ArithmeticShiftLeft: "<<"}  # fmt: skip
WIDEN = {BO.Multiply, BO.LogicalShiftLeft, BO.ArithmeticShiftLeft}
BITWISE = {BO.BinaryAnd: "&", BO.BinaryOr: "|", BO.BinaryXor: "^"}
LOGICAL = {BO.LogicalAnd: "&&", BO.LogicalOr: "||"}
SHR = {BO.LogicalShiftRight: ">>"}


class NotTranslatable(Exception):
    pass


@dataclass
class Val:
    text: str            # HARM syntax; compound values are parenthesised
    width: int           # SystemVerilog width
    dirty: bool          # may carry bits above `width` in HARM's arithmetic
    compound: bool
    ops: int
    signals: set = field(default_factory=set)
    hw: int = 0          # the width HARM computes it at, when narrower than `width` (a widening conversion)


@dataclass
class Relation:
    target: str          # HARM name
    width: int
    expr: str
    registered: bool
    conditional: bool
    reads_target: bool
    where: str


class Relations:
    def __init__(self, design, comp, vis):
        self.h = Harvester(design.extractor, comp, vis)
        self.x = design.extractor
        self.vis = vis
        self.found: list[Relation] = []
        self.dropped: list = []
        self.assigned: list = []   # (target, registered, conditional) of every assignment to a whole signal

    # ------------------------------------------------------------------ expressions
    def mask(self, w):
        return f"{w}'d{(1 << w) - 1}"

    def clean(self, v: Val) -> Val:
        """v with no bit above its width"""
        if not v.dirty:
            return v
        return Val(f"({v.text} & {self.mask(v.width)})", v.width, False, True, v.ops + 1, v.signals)

    def render(self, e) -> Val:
        k = e.kind
        if k == EK.Conversion:
            inner = e.operand
            if e.type.isSigned and inner.type.isSigned and inner.type.bitWidth < e.type.bitWidth:
                raise NotTranslatable("sign extension")  # an unsigned context zero-extends: that is translated
            v = self.render(inner)
            if e.type.bitWidth < v.width:      # truncation
                v = Val(f"({v.text} & {self.mask(e.type.bitWidth)})", e.type.bitWidth, False, True, v.ops + 1,
                        v.signals)  # fmt: skip
            hw = (v.hw or v.width) if e.type.bitWidth > v.width else 0
            return Val(v.text, e.type.bitWidth, v.dirty, v.compound, v.ops, v.signals, hw)
        c = self.h.constant(e)
        if c is not None and k == EK.IntegerLiteral and e.isDeclaredUnsized and c >= 0:
            return Val(str(c), e.type.bitWidth, False, False, 0)  # an unsized literal (a shift amount)
        if c is not None:
            w = max(1, e.type.bitWidth)
            return Val(f"{w}'d{c % (1 << w)}", w, False, False, 0)
        if k in (EK.NamedValue, EK.HierarchicalValue, EK.ElementSelect, EK.MemberAccess):
            op = self.h.operand(e)
            if op is None:
                raise NotTranslatable("operand")
            if op[0] == "sig":
                if op[2] > HARM_MAX_LOGIC_BITS:
                    raise NotTranslatable(f"wider than HARM's {HARM_MAX_LOGIC_BITS}-bit limit")
                n = self.h.name(op[1])
                return Val(escaped(n), op[2], False, False, 0, {n})
            if self.h.out.widths.get(op[1], 0) > HARM_MAX_LOGIC_BITS:
                raise NotTranslatable(f"wider than HARM's {HARM_MAX_LOGIC_BITS}-bit limit")
            n = self.h.name(op[1])
            return Val(f"{escaped(n)}[{op[2]}]", 1, False, False, 0, {n})
        if k == EK.RangeSelect:
            op = self.h.operand(e.value)
            hi, lo = self.h.constant(e.left), self.h.constant(e.right)
            if op is None or op[0] != "sig" or hi is None or lo is None or hi < lo:
                raise NotTranslatable("range select")
            if op[2] > HARM_MAX_LOGIC_BITS:
                raise NotTranslatable(f"wider than HARM's {HARM_MAX_LOGIC_BITS}-bit limit")
            n = self.h.name(op[1])
            return Val(f"{escaped(n)}[{hi}:{lo}]", hi - lo + 1, False, False, 0, {n})
        if k == EK.Concatenation:
            parts = [self.clean(self.render(o)) for o in e.operands]
            total = sum(p.width for p in parts)
            terms, shift = [], total
            for p in parts:
                shift -= p.width
                if p.text.endswith("'d0") and not p.compound:
                    continue                    # a constant zero part
                terms.append(p if shift == 0 else Val(f"({p.text} << {shift})", p.width + shift, False, True,
                                                      p.ops + 1, p.signals))  # fmt: skip
            if not terms:
                return Val(f"{total}'d0", total, False, False, 0)
            if len(terms) == 1:
                t = terms[0]
                return Val(t.text, total, False, t.compound, t.ops, t.signals)
            return Val("(" + " | ".join(t.text for t in terms) + ")", total, False, True,
                       sum(t.ops for t in terms) + len(terms) - 1, set().union(*(t.signals for t in terms)))  # fmt: skip
        if k == EK.UnaryOp:
            v = self.render(e.operand)
            w = e.type.bitWidth
            if e.op == UO.LogicalNot:
                v = self.clean(v)
                return Val(f"!{v.text}", 1, False, True, v.ops + 1, v.signals)
            if e.op == UO.BitwiseNot:
                return Val(f"~{v.text}", w, True, True, v.ops + 1, v.signals)
            if e.op == UO.Minus:
                return Val(f"-{v.text}", w, True, True, v.ops + 1, v.signals)
            if e.op == UO.Plus:
                return v
            raise NotTranslatable(f"unary {e.op}")
        if k == EK.BinaryOp:
            # two's complement + - * & | ^ give the same bits signed or not (masked to the width); a comparison of two
            # signed operands does not, nor an arithmetic right shift (not translated)
            if e.op in COMPARISONS and e.left.type.isSigned and e.right.type.isSigned:
                raise NotTranslatable("signed comparison")
            a, b = self.render(e.left), self.render(e.right)
            w = e.type.bitWidth
            sig = a.signals | b.signals
            ops = a.ops + b.ops + 1
            if e.op in DIRTY_BIN:
                if e.op in WIDEN and (a.hw or a.width) < w:
                    # HARM computes * and << at the operands' width, SystemVerilog at the context's: widen one
                    a = Val(f"({a.text} + {w}'d0)", w, a.dirty, True, a.ops + 1, a.signals)
                return Val(f"({a.text} {DIRTY_BIN[e.op]} {b.text})", w, True, True, ops, sig)
            if e.op in BITWISE:
                return Val(f"({a.text} {BITWISE[e.op]} {b.text})", w, a.dirty or b.dirty, True, ops, sig)
            if e.op in SHR or e.op in COMPARISONS or e.op in LOGICAL:
                a, b = self.clean(a), self.clean(b)
                sym = SHR.get(e.op) or COMPARISONS.get(e.op) or LOGICAL[e.op]
                return Val(f"({a.text} {sym} {b.text})", w, False, True, a.ops + b.ops + 1, sig)
            raise NotTranslatable(f"operator {e.op}")
        if k == EK.ConditionalOp:
            if len(e.conditions) != 1 or e.conditions[0].pattern is not None:
                raise NotTranslatable("condition")
            c = self.clean(self.render(e.conditions[0].expr))
            a, b = self.render(e.left), self.render(e.right)
            return Val(f"({c.text} ? {a.text} : {b.text})", e.type.bitWidth, a.dirty or b.dirty, True,
                       a.ops + b.ops + c.ops + 1, a.signals | b.signals | c.signals)  # fmt: skip
        raise NotTranslatable(f"{k}")

    # ------------------------------------------------------------------ assignments
    def assignment(self, a, registered, conditional):
        where = self.h.src(a)
        op = self.h.operand(a.left)
        if op is None or op[0] != "sig":
            self.dropped.append(("relation: not a whole signal", where))
            return
        try:
            target = self.h.name(op[1])
        except KeyError:
            self.dropped.append(("relation: target not visible", where))
            return
        w = op[2]
        if w > HARM_MAX_LOGIC_BITS:
            self.dropped.append((f"relation: target wider than HARM's {HARM_MAX_LOGIC_BITS}-bit limit", where))
            return
        self.assigned.append((target, registered, conditional))
        try:
            v = self.render(a.right)
        except NotTranslatable as ex:
            self.dropped.append((f"relation: {ex}", where))
            return
        except KeyError as ex:
            self.dropped.append((f"relation: signal {ex} not visible", where))
            return
        if not v.signals:
            return                              # a constant: a reset value or a constant comparison already
        if v.ops > MAX_OPS:
            self.dropped.append((f"relation: more than {MAX_OPS} operators", where))
            return
        masked = v.dirty or v.width > w
        if registered:
            strip = v.compound and v.text.startswith("(") and _balanced(v.text[1:-1]) and a.right.kind != EK.ConditionalOp
            core = v.text[1:-1] if strip else v.text  # HARM reads $past((c ? a : b), 1), not $past(c ? a : b, 1)
            past = f"$past({core}, 1)"
            expr = f"{escaped(target)} == ({past} & {self.mask(w)})" if masked else f"{escaped(target)} == {past}"
        else:
            expr = f"{escaped(target)} == ({v.text} & {self.mask(w)})" if masked else f"{escaped(target)} == {v.text}"
        self.found.append(Relation(target, w, expr, registered, conditional, target in v.signals, where))

    def stmt(self, s, registered, conditional, top=False):
        k = s.kind
        if k == TK.Block:
            self.stmt(s.body, registered, conditional, top)
        elif k == TK.List:
            for x in s.list:
                self.stmt(x, registered, conditional, top)
        elif k == TK.Timed:
            self.stmt(s.stmt, registered, conditional, top)
        elif k == TK.ExpressionStatement and s.expr.kind == EK.Assignment:
            self.assignment(s.expr, registered, conditional)
        elif k == TK.Conditional:
            if top and registered and self.is_reset_if(s):
                if s.ifFalse is not None:
                    self.stmt(s.ifFalse, registered, conditional, False)
                return
            self.stmt(s.ifTrue, registered, True)
            if s.ifFalse is not None:
                self.stmt(s.ifFalse, registered, True)
        elif k == TK.Case:
            for it in s.items:
                self.stmt(it.stmt, registered, True)
            if s.defaultCase is not None:
                self.stmt(s.defaultCase, registered, True)

    def is_reset_if(self, s):
        consts = []

        def cb(n):
            if isinstance(n, ast.Expression) and n.kind == EK.Assignment:
                consts.append(self.h.constant(n.right) is not None)
                return ast.VisitAction.Skip
            return ast.VisitAction.Advance
        s.ifTrue.visit(cb)
        return bool(consts) and all(consts)

    def scope(self, body):
        for m in body:
            k = m.kind
            if k == SK.ContinuousAssign:
                self.assignment(m.assignment, False, False)
            elif k == SK.ProceduralBlock:
                PK = ast.ProceduralBlockKind
                if m.procedureKind in (PK.Initial, PK.Final):
                    continue
                b = m.body
                registered = m.procedureKind == PK.AlwaysFF or (b.kind == TK.Timed and m.procedureKind == PK.Always
                                                               and b.timing.kind != ast.TimingControlKind.ImplicitEvent)  # fmt: skip
                self.stmt(b.stmt if b.kind == TK.Timed else b, registered, False, top=True)
            elif k == SK.Instance:
                self.scope(m.body)
            elif k == SK.GenerateBlock and not m.isUninstantiated:
                self.scope(m)

    def holds(self):
        """registers assigned only under a condition: they keep their value otherwise ($stable)"""
        cond = {t for t, r, c in self.assigned if r and c}
        always = {t for t, r, c in self.assigned if r and not c}
        return sorted(cond - always)

    def run(self):
        self.scope(self.x.top.body)
        per, out = {}, []
        for r in self.found:
            n = per.get(r.target, 0)
            if n >= MAX_PER_TARGET:
                self.dropped.append((f"relation: more than {MAX_PER_TARGET} for {r.target}", r.where))
                continue
            if any(o.expr == r.expr for o in out):
                continue
            per[r.target] = n + 1
            out.append(r)
        return out


def _balanced(t):
    d = 0
    for ch in t:
        d += ch == "("
        d -= ch == ")"
        if d < 0:
            return False
    return d == 0


def widths(design, vis):
    """HARM name -> width of every visible module-level signal"""
    return {vis[path]: typ.bitWidth for path, typ, _ in design.extractor.sig.values() if path in vis}


# ------------------------------------------------------------------ the configuration's additions
CLASS = {"comb": "1", "unknown": "1", "state": "2"}
# contiguous clustering: one `==` proposition per value (K-means merged the deltas of `updown` into none); no
# ranges (an open range breaks OpenFPV's model build, portfolio F-P9)
DELTA = "C,10Max,=="
DT_FIXED = "5D,3W,15A,-0.1E,U"      # unused (no placeholder in the antecedent), as harm-coi's other templates
DT_RELATION = "1D,2W,2A,-0.1E,U"   # one cycle, at most two propositions


def extras(rels, hints, preds, extra, wid, resets, holds=()):
    """What --relations adds to --emit-config: {"props": [(expr, loc)], "loc_add": {expr: [domains]},
    "numerics": [(clustering, exp, loc)], "templates": [template], "domains": {domain}} (the class domains used,
    so that their templates are written)."""
    roles = {k: v["role"] for k, v in hints["roles"].items()}
    place = {p["expr"]: p["loc"] for p in hints["propositions"]}
    reset = resets[0] if resets else None
    out = {"props": [], "loc_add": {}, "numerics": [], "templates": [], "domains": set(), "drop": set()}
    have = set(place)
    # with a reset, a predicate that mixes it with other signals (`rst || clr`) only gives assertions that are vacuous
    # under disable iff, and the redundancy reduction then removes the useful `clr |=> …`: its parts are kept
    if resets:
        rnames = {n for n, _ in resets}
        out["drop"] = {p["expr"] for p in preds
                       if extra[p["expr"]]["signals"] & rnames and extra[p["expr"]]["signals"] - rnames}

    def add(expr, loc, origin="rtl"):
        if expr not in have:
            have.add(expr)
            out["props"].append((expr, loc, origin))
            out["domains"] |= {d for d in loc if d in ("1", "2")}

    # reset values: also consequents of G({$fell(R)}|-> P0(3)); 1-bit ones in both polarities
    rv = [p["expr"] for p in preds if "reset value" in extra[p["expr"]]["kinds"] and "c" in place[p["expr"]]]
    for e in rv:
        if reset:
            out["loc_add"][e] = ["3"]
        bare = e[1:] if e.startswith("!") else e
        if " " not in bare and "==" not in e:
            comp = bare if e.startswith("!") else "!" + e
            add(comp, place[e] + (["3"] if reset else []))
    # relations: unconditional ones to the fixed templates (with a reset), the others to their own single-cycle trees:
    # the condition guarding an assignment is one cycle's (2026-10-13: deeper trees made ima's mining 4x slower)
    for r in rels:
        if reset and not r.conditional:
            loc = ["c", "4" if r.registered else "5"]
        else:
            loc = ["c", "7" if r.registered else "6"]
        add(r.expr, loc, "rtl-relation")
    for t in holds:
        add(f"$stable({escaped(t)})", ["c", "7"], "rtl-relation")
    # assigned-only signals: 1-bit ones both ways, wide ones as numeric values; register deltas
    read = {s for e in extra.values() for s in e["signals"]}
    for name, w in sorted(wid.items()):
        cls = CLASS.get(roles.get(name, ""))
        if cls is None or name in read:
            continue
        if w == 1:  # a wide one gets no value numeric: they cost most of ima's mining time (2026-10-13)
            add(escaped(name), ["a", "c", "dt", cls])
            add("!" + escaped(name), ["a", "c", "dt", cls])
    for t in sorted({r.target for r in rels if r.registered and r.reads_target}):
        out["numerics"].append((DELTA, f"{escaped(t)} - $past({escaped(t)}, 1)", ["c", "2"]))
        out["domains"].add("2")
    if reset:
        name, low = reset
        inactive, end = (name, f"$rose({name})") if low else (f"!{name}", f"$fell({name})")
        used = {d for _, loc, _ in out["props"] for d in loc} | {d for v in out["loc_add"].values() for d in v}
        if "3" in used:
            out["templates"].append((DT_FIXED, f"G({{{end}}}|-> P0(3))"))
        if "4" in used:
            out["templates"].append((DT_FIXED, f"G({{{inactive}}}|=> P0(4))"))
        if "5" in used:
            out["templates"].append((DT_FIXED, f"G({{{inactive}}}|-> P0(5))"))
    used = {d for _, loc, _ in out["props"] for d in loc}
    if "6" in used:
        out["templates"].append((DT_RELATION, "G({..#1&..}|-> P0(6))"))
    if "7" in used:
        out["templates"].append((DT_RELATION, "G({..#1&..}|=> P0(7))"))
    return out
