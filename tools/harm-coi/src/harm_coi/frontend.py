"""RTL front end (D-006: pyslang): elaborate the design and extract direct dependencies.

The result is a graph over *atoms*: the leaf signals of the elaborated design, named by their path
below the top instance (a tuple of components, e.g. ('g[1]', 'w') or ('c', 'mode')). Packed structs
are split into their fields. An edge `target <- source @delay` means that the value of target,
sampled as HARM samples (just before a rising edge of the clock), depends on the value of source
`delay` samples earlier:
  - continuous assignments, port connections and combinational processes: delay 0;
  - a register on the sampling clock: delay 1 from everything its process reads, including the
    conditions that control the assignment (control dependencies), and from itself when some path
    does not assign it (it holds its value);
  - an asynchronous control of a register (`posedge rst` in the event list): delay 0 and 1.
Anything the extractor cannot model goes to `unknown`, never silently dropped.
"""
import shlex
from collections import defaultdict
from dataclasses import dataclass, field

from pyslang import ast, driver, analysis, syntax

SK, EK, TK = ast.SymbolKind, ast.ExpressionKind, ast.StatementKind
CONSTANTS = (SK.Parameter, SK.EnumValue, SK.Specparam, SK.TypeParameter)
STRUCTS = (SK.PackedStructType, SK.UnpackedStructType)
INC_DEC = (ast.UnaryOperator.Preincrement, ast.UnaryOperator.Predecrement,
           ast.UnaryOperator.Postincrement, ast.UnaryOperator.Postdecrement)
LOOPS = (TK.ForLoop, TK.RepeatLoop, TK.ForeachLoop, TK.WhileLoop, TK.DoWhileLoop, TK.ForeverLoop)
IGNORED_STATEMENTS = (TK.ImmediateAssertion, TK.ConcurrentAssertion, TK.Continue, TK.Break,
                      TK.Empty, TK.Return)
MAX_LOOP_PASSES = 64


class FrontendError(Exception):
    pass


@dataclass(frozen=True)
class Now:
    """A source read at the target's own sample: a signal blocking-assigned earlier in the same
    process is read with its new value (delay 0), not its value at the previous sample."""
    atom: tuple


def edge_of(src, register_delay):
    return (src.atom, 0) if isinstance(src, Now) else (src, register_delay)


@dataclass
class Process:
    """A clocked process: its clock atom, edge, and the targets it assigns."""
    clock: tuple
    edge: str                     # 'pos', 'neg' or 'both'
    targets: set = field(default_factory=set)


@dataclass
class Design:
    edges: dict                   # atom -> {(atom, delay)}
    signals: set                  # every leaf signal atom
    params: set                   # parameters a simulator dumps (declared, not genvar copies)
    unknown: dict                 # atom -> reason
    processes: list               # clocked processes (their delays are fixed later, per clock)
    clock_uses: set          # atoms used as clocks of processes (before propagation)
    top_inputs: set               # atoms of the top's input ports


def elaborate(top, files, defines=(), includes=()):
    """Parse and elaborate with slang's own command line handling. Raises FrontendError."""
    d = driver.Driver()
    d.addStandardArgs()
    args = ["harm-coi", "--top", top]
    args += [f"-D{x}" for x in defines] + [f"-I{x}" for x in includes] + list(files)
    if not d.parseCommandLine(shlex.join(args), driver.CommandLineOptions()) or not d.processOptions():
        raise FrontendError("invalid front-end options")
    if not d.parseAllSources():
        raise FrontendError("cannot parse the sources")
    comp = d.createCompilation()
    errors = [x for x in comp.getAllDiagnostics() if x.isError()]
    if errors:
        d.reportCompilation(comp, False)
        d.reportDiagnostics(False)
        raise FrontendError(f"{len(errors)} elaboration error(s)")
    tops = [t for t in comp.getRoot().topInstances if t.name == top]
    if not tops:
        raise FrontendError(f"top module '{top}' not found")
    am = analysis.AnalysisManager()
    am.analyze(comp)
    return comp, tops[0], am


def split_hier(hp):
    """'a.g[1].b' -> ['a', 'g[1]', 'b'] (dots inside brackets are kept)."""
    parts, cur, depth = [], "", 0
    for ch in hp:
        if ch == "[":
            depth += 1
        elif ch == "]":
            depth -= 1
        if ch == "." and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    return parts


def sym_key(sym):
    loc = sym.location
    return (sym.hierarchicalPath, loc.offset, loc.buffer.id)


class Ctx:
    """State of one process walk."""

    def __init__(self, clocked, once=frozenset()):
        self.clocked = clocked
        self.once = once                    # signal atoms assigned exactly once, outside loops
        self.env = {}                       # atom or local key -> sources of its current value
        self.assigned = defaultdict(set)    # signal atom -> sources over all assignments
        self.unknown = None                 # reason, if the process cannot be modelled

    def fail(self, reason):
        if self.unknown is None:
            self.unknown = reason


class Extractor:
    def __init__(self, top, am):
        self.top = top
        self.am = am
        self.edges = defaultdict(set)
        self.sig = {}                       # sym_key -> (path, type, symbol) of module-level signals
        self.signals = set()
        self.params = set()
        self.unknown = {}
        self.processes = []
        self.clock_uses = set()
        self.driven = set()
        self.sub_cache = {}
        self.top_inputs = set()

    # ------------------------------------------------------------------ names
    def path_of(self, sym):
        parts = split_hier(sym.hierarchicalPath)
        if parts[0] != self.top.name:
            raise FrontendError(f"signal outside the top instance: {sym.hierarchicalPath}")
        return tuple(parts[1:])

    def leaves(self, path, typ):
        t = typ.canonicalType
        if t.kind in STRUCTS:
            out = []
            for f in t:
                if f.kind == SK.Field:
                    out += self.leaves(path + (f.name,), f.type)
            return out
        return [path]

    def add_unknown(self, atom, reason):
        self.unknown.setdefault(atom, reason)

    # ------------------------------------------------------------------ references
    def resolve(self, expr):
        """('sig', path, type) | ('local', key) | ('const',) | ('expr', e) | None"""
        k = expr.kind
        if k in (EK.NamedValue, EK.HierarchicalValue):
            s = expr.symbol
            if s.kind in CONSTANTS:
                return ("const",)
            if s.kind == SK.ModportPort:
                if s.internalSymbol is not None:
                    s = s.internalSymbol
                elif s.explicitConnection is not None:
                    return ("expr", s.explicitConnection)
                else:
                    return None
            key = sym_key(s)
            if key in self.sig:
                path, typ, _ = self.sig[key]
                return ("sig", path, typ)
            if s.kind in (SK.Variable, SK.Net, SK.FormalArgument, SK.Iterator, SK.Field):
                return ("local", key)
            return None
        if k == EK.MemberAccess:
            r = self.resolve(expr.value)
            if r is None:
                return None
            if r[0] == "sig":
                if r[2].canonicalType.kind in STRUCTS:
                    return ("sig", r[1] + (expr.member.name,), expr.member.type)
                return None
            return r                        # a member of a local or constant: the whole of it
        return None

    def sub_info(self, sub):
        """(signal atoms a user subroutine reads outside its arguments, whether it writes signals)"""
        key = sym_key(sub)
        if key in self.sub_cache:
            return self.sub_cache[key] or (set(), True)   # None: recursion in progress
        self.sub_cache[key] = None
        reads, writes = set(), False

        def cb(e):
            nonlocal writes
            if isinstance(e, ast.Expression):
                if e.kind == EK.Call and not e.isSystemCall:
                    r2, w2 = self.sub_info(e.subroutine)
                    reads.update(r2)
                    writes = writes or w2
                elif e.kind == EK.Assignment:
                    r = self.resolve(e.left)
                    if r is None or r[0] == "sig":
                        writes = True
                else:
                    r = self.resolve(e)
                    if r is not None and r[0] == "sig":
                        reads.update(self.leaves(r[1], r[2]))
                        return ast.VisitAction.Skip
            return ast.VisitAction.Advance

        sub.visit(cb)
        self.sub_cache[key] = (reads, writes)
        return reads, writes

    def reads(self, expr, ctx=None):
        """Signal atoms the value of expr depends on (temporaries replaced by their sources)."""
        out = set()

        def cb(e):
            if not isinstance(e, ast.Expression):
                return ast.VisitAction.Advance
            if e.kind == EK.Call:
                if not e.isSystemCall:
                    r, w = self.sub_info(e.subroutine)
                    out.update(r)
                    if w and ctx is not None:
                        ctx.fail(f"call of {e.subroutineName} writes signals")
                return ast.VisitAction.Advance
            if e.kind == EK.Assignment and ctx is not None:
                self.assign(e, frozenset(), ctx)      # an assignment inside an expression
                out.update(self.reads(e.left, ctx))
                return ast.VisitAction.Skip
            r = self.resolve(e)
            if r is None:
                return ast.VisitAction.Advance
            if r[0] == "const":
                return ast.VisitAction.Skip
            if r[0] == "expr":
                out.update(self.reads(r[1], ctx))
                return ast.VisitAction.Skip
            if r[0] == "local":
                if ctx is not None and r[1] in ctx.env:
                    out.update(ctx.env[r[1]])
                elif ctx is not None:
                    ctx.fail("a local variable is read before it is written (it keeps state)")
                return ast.VisitAction.Skip
            for leaf in self.leaves(r[1], r[2]):
                if ctx is not None and leaf in ctx.env:
                    # a visible signal assigned earlier in this process: its new value is both
                    # the signal itself (forcing it changes the reader) and a function of the
                    # sources assigned to it
                    out.update(ctx.env[leaf])
                    if leaf in ctx.once:        # else the value read may not be the final one
                        out.add(Now(leaf))
                else:
                    out.add(leaf)
            return ast.VisitAction.Skip

        expr.visit(cb)
        return out

    def lvalues(self, expr, ctx):
        """[(atom or local key, partial, is_local)] written by expr, plus the reads of its indices."""
        r = self.resolve(expr)
        if r is not None:
            if r[0] == "sig":
                return [(x, False, False) for x in self.leaves(r[1], r[2])], set()
            if r[0] == "local":
                return [(r[1], False, True)], set()
            if r[0] == "expr":
                return self.lvalues(r[1], ctx)
            return [], set()
        k = expr.kind
        if k == EK.ElementSelect:
            inner, idx = self.lvalues(expr.value, ctx)
            return [(a, True, l) for a, _, l in inner], idx | self.reads(expr.selector, ctx)
        if k == EK.RangeSelect:
            inner, idx = self.lvalues(expr.value, ctx)
            return ([(a, True, l) for a, _, l in inner],
                    idx | self.reads(expr.left, ctx) | self.reads(expr.right, ctx))
        if k == EK.MemberAccess:                 # e.g. arr[i].f: part of the array
            inner, idx = self.lvalues(expr.value, ctx)
            return [(a, True, l) for a, _, l in inner], idx
        if k == EK.Concatenation:
            outs, idx = [], set()
            for op in expr.operands:
                o, i = self.lvalues(op, ctx)
                outs += o
                idx |= i
            return outs, idx
        if k == EK.Conversion:
            return self.lvalues(expr.operand, ctx)
        if ctx is not None:
            ctx.fail(f"unsupported assignment target: {expr.syntax}")
        return [], set()

    # ------------------------------------------------------------------ structure
    def run(self):
        self.declare(self.top.body)
        for m in self.top.body:
            if m.kind == SK.Port and m.direction == ast.ArgumentDirection.In and m.internalSymbol:
                s = m.internalSymbol
                self.top_inputs.update(self.leaves(self.path_of(s), s.type))
        self.walk(self.top.body)
        self.check_drivers()

    def declare(self, scope):
        """Record the module-level signals of every scope below the top (first pass)."""
        for m in scope:
            k = m.kind
            if k in (SK.Net, SK.Variable):
                path = self.path_of(m)
                self.sig[sym_key(m)] = (path, m.type, m)
                self.signals.update(self.leaves(path, m.type))
            elif k == SK.Parameter:
                # a genvar loop creates an implicit parameter per block, which simulators do not dump
                if m.syntax is not None and m.syntax.kind == syntax.SyntaxKind.Declarator:
                    self.params.add(self.path_of(m))
            elif k == SK.Instance:
                self.declare(m.body)
            elif k == SK.InstanceArray:
                for e in m.elements:
                    self.declare_instance_like(e)
            elif k == SK.GenerateBlock:
                if not m.isUninstantiated:
                    self.declare(m)
            elif k == SK.GenerateBlockArray:
                for e in m.entries:
                    if not e.isUninstantiated:
                        self.declare(e)

    def declare_instance_like(self, e):
        if e.kind == SK.Instance:
            self.declare(e.body)
        elif e.kind == SK.InstanceArray:
            for x in e.elements:
                self.declare_instance_like(x)

    def walk(self, scope):
        for m in scope:
            k = m.kind
            if k == SK.Net:
                if m.initializer is not None:        # wire w = expr;
                    ctx = Ctx(clocked=False)
                    self.drive(self.leaves(self.path_of(m), m.type), self.reads(m.initializer, ctx), ctx)
            elif k == SK.ContinuousAssign:
                self.continuous(m.assignment)
            elif k == SK.ProceduralBlock:
                self.procedure(m)
            elif k == SK.Instance:
                self.instance(m)
            elif k == SK.InstanceArray:
                for e in m.elements:
                    self.instance_like(e)
            elif k == SK.GenerateBlock:
                if not m.isUninstantiated:
                    self.walk(m)
            elif k == SK.GenerateBlockArray:
                for e in m.entries:
                    if not e.isUninstantiated:
                        self.walk(e)
            elif k == SK.PrimitiveInstance:
                for e in m.portConnections:
                    for leaf in self.written_by(e):
                        self.add_unknown(leaf, "driven by a gate primitive")
            # declarations, ports, types, subroutines, modports, assertions: nothing to do

    def instance_like(self, e):
        if e.kind == SK.Instance:
            self.instance(e)
        elif e.kind == SK.InstanceArray:
            for x in e.elements:
                self.instance_like(x)

    def written_by(self, expr):
        if expr is None:
            return []
        if expr.kind == EK.Assignment:
            expr = expr.left
        outs, _ = self.lvalues(expr, None)
        return [a for a, _, l in outs if not l]

    def drive(self, targets, srcs, ctx):
        """Zero-delay edges (assigns, ports, net initialisers); unknown if ctx failed."""
        for t in targets:
            self.driven.add(t)
            if ctx.unknown:
                self.add_unknown(t, ctx.unknown)
            else:
                self.edges[t] |= {edge_of(s, 0) for s in srcs}

    def continuous(self, a):
        ctx = Ctx(clocked=False)
        outs, idx = self.lvalues(a.left, ctx)
        src = self.reads(a.right, ctx) | idx
        self.drive([atom for atom, _, is_local in outs if not is_local], src, ctx)

    def instance(self, inst):
        self.walk(inst.body)
        for pc in inst.portConnections:
            port = pc.port
            if port.kind != SK.Port:
                continue                    # interface ports: members are resolved through modports
            ext = pc.expression
            if ext is None or port.internalSymbol is None:
                continue
            isym = port.internalSymbol
            inner = self.leaves(self.path_of(isym), isym.type)
            d = port.direction
            ctx = Ctx(clocked=False)
            if d == ast.ArgumentDirection.In:
                self.drive(inner, self.reads(ext, ctx), ctx)
            elif d == ast.ArgumentDirection.Out:
                self.drive(self.written_by(ext), inner, ctx)
            else:
                for t in inner + self.written_by(ext):
                    self.add_unknown(t, f"{d.name} port {port.name}")

    # ------------------------------------------------------------------ processes
    def procedure(self, pb):
        kind, body = pb.procedureKind, pb.body
        PK = ast.ProceduralBlockKind
        if kind in (PK.Initial, PK.Final):
            return
        timing = body.timing if body.kind == TK.Timed else None
        events = self.edge_events(timing) if timing is not None else None
        if kind == PK.AlwaysFF or (kind == PK.Always and events):
            self.clocked(pb, body, events)
        elif kind == PK.AlwaysComb or (kind == PK.Always and timing is not None and events == []):
            self.combinational(body.stmt if timing is not None else body)
        elif kind == PK.AlwaysLatch:
            self.give_up(body, "latch (always_latch)")
        else:
            self.give_up(body, f"unsupported process ({kind.name})")

    def edge_events(self, tc):
        """[(expr, edge)] for an edge-sensitive event control; [] for @(*) or a level list;
        None for anything else."""
        TCK = ast.TimingControlKind
        if tc.kind == TCK.ImplicitEvent:
            return []
        if tc.kind == TCK.SignalEvent:
            if tc.iffCondition is not None:
                return None
            e = tc.edge
            if e == ast.EdgeKind.None_:
                return []
            return [(tc.expr, {ast.EdgeKind.PosEdge: "pos", ast.EdgeKind.NegEdge: "neg"}.get(e, "both"))]
        if tc.kind == TCK.EventList:
            out = []
            for ev in tc.events:
                x = self.edge_events(ev)
                if x is None:
                    return None
                out += x
            if out and len(out) != len(list(tc.events)):
                return None                 # a mix of edges and levels
            return out
        return None

    def give_up(self, stmt, reason):
        ctx = Ctx(clocked=False)
        self.stmt(stmt, frozenset(), ctx)
        for t in ctx.assigned:
            self.add_unknown(t, reason)
            self.driven.add(t)

    def assigned_once(self, stmt):
        """Signal atoms with exactly one assignment in stmt, not inside a loop."""
        counts, in_loops = defaultdict(int), set()

        def targets(e):
            if e.kind == EK.Assignment:
                outs, _ = self.lvalues(e.left, None)
            elif e.kind == EK.UnaryOp and e.op in INC_DEC:
                outs, _ = self.lvalues(e.operand, None)
            else:
                return []
            return [a for a, _, is_local in outs if not is_local]

        def count(node):
            if isinstance(node, ast.Expression):
                for a in targets(node):
                    counts[a] += 1
            return ast.VisitAction.Advance

        def loops(node):
            if isinstance(node, ast.Statement) and node.kind in LOOPS:
                def inner(n):
                    if isinstance(n, ast.Expression):
                        in_loops.update(targets(n))
                    return ast.VisitAction.Advance
                node.visit(inner)
            return ast.VisitAction.Advance

        stmt.visit(count)
        stmt.visit(loops)
        return frozenset(a for a, c in counts.items() if c == 1) - in_loops

    def clocked(self, pb, body, events):
        ctx = Ctx(clocked=True, once=self.assigned_once(body.stmt))
        full = self.stmt(body.stmt, frozenset(), ctx)
        # the clock is the event signal that the body does not read; the others are async controls
        body_reads = self.reads_anywhere(body.stmt)
        ev = []
        for expr, edge in events:
            r = self.resolve(expr)
            if r is None or r[0] != "sig":
                ctx.fail("an event that is not a signal")
                continue
            ev.append((self.leaves(r[1], r[2]), edge))
        clocks = [(l, e) for l, e in ev if not set(l) & body_reads]
        if len(clocks) != 1 or len(clocks[0][0]) != 1:
            ctx.fail("cannot tell the clock from the asynchronous controls")
        for t in ctx.assigned:
            self.driven.add(t)
        if ctx.unknown:
            for t in ctx.assigned:
                self.add_unknown(t, ctx.unknown)
            return
        clock, edge = clocks[0][0][0], clocks[0][1]
        asyncs = {a for l, _ in ev if l is not clocks[0][0] for a in l}
        p = Process(clock=clock, edge=edge, targets=set(ctx.assigned))
        self.processes.append(p)
        self.clock_uses.add(clock)
        for t, srcs in ctx.assigned.items():
            if t not in full:
                srcs = srcs | {t}               # not assigned on every path: holds its value
            p_edges = {edge_of(s, "reg") for s in srcs} | {(a, 0) for a in asyncs}
            self.edges[t] |= p_edges

    def reads_anywhere(self, stmt):
        out = set()

        def cb(e):
            if isinstance(e, ast.Expression):
                r = self.resolve(e)
                if r is not None and r[0] == "sig":
                    out.update(self.leaves(r[1], r[2]))
                    return ast.VisitAction.Skip
            return ast.VisitAction.Advance

        stmt.visit(cb)
        return out

    def combinational(self, stmt):
        ctx = Ctx(clocked=False, once=self.assigned_once(stmt))
        full = self.stmt(stmt, frozenset(), ctx)
        for t in ctx.assigned:
            self.driven.add(t)
            if ctx.unknown:
                self.add_unknown(t, ctx.unknown)
            elif t not in full:
                self.add_unknown(t, "latch: not assigned on every path of a combinational process")
            else:
                self.edges[t] |= {edge_of(s, 0) for s in ctx.assigned[t]}

    # ------------------------------------------------------------------ statements
    def assign(self, e, ctrl, ctx):
        outs, idx = self.lvalues(e.left, ctx)
        src = self.reads(e.right, ctx) | idx | set(ctrl)
        if e.isCompound:
            src |= self.reads(e.left, ctx)
        full = set()
        for atom, partial, is_local in outs:
            s = src
            if partial:
                s = s | ctx.env.get(atom, set() if is_local else {atom})
            if is_local:
                ctx.env[atom] = s
                continue
            ctx.assigned[atom] |= s
            if not e.isNonBlocking:
                ctx.env[atom] = s
            if not partial:
                full.add(atom)
        return full

    def expr_stmt(self, e, ctrl, ctx):
        if e.kind == EK.Assignment:
            return self.assign(e, ctrl, ctx)
        if e.kind == EK.UnaryOp and e.op in INC_DEC:
            outs, idx = self.lvalues(e.operand, ctx)
            for atom, _, is_local in outs:
                s = ctx.env.get(atom, set() if is_local else {atom}) | idx | set(ctrl)
                if is_local:
                    ctx.env[atom] = s
                else:
                    ctx.assigned[atom] |= s
                    ctx.env[atom] = s
            return set()
        if e.kind == EK.Call:
            if e.isSystemCall:
                return set()                    # $display, $error...: no effect on signals
            if e.subroutine.subroutineKind == ast.SubroutineKind.Task:
                ctx.fail(f"task call {e.subroutineName}")
            else:
                self.reads(e, ctx)              # a void function: fails if it writes signals
            return set()
        self.reads(e, ctx)
        return set()

    def branch(self, stmts, ctrl, ctx, exhaustive):
        """Run alternative branches on copies of the environment and merge them."""
        before = dict(ctx.env)
        envs, fulls = [], []
        for s in stmts:
            ctx.env = dict(before)
            fulls.append(self.stmt(s, ctrl, ctx) if s is not None else set())
            envs.append(ctx.env)
        if not exhaustive:
            envs.append(before)
            fulls.append(set())
        merged = {}
        for k in set().union(*envs):
            vals = set()
            for e in envs:
                vals |= e.get(k, before.get(k, {k} if isinstance(k, tuple) and k in self.signals else set()))
            merged[k] = vals
        ctx.env = merged
        return set.intersection(*fulls) if fulls else set()

    def stmt(self, s, ctrl, ctx):
        """Walk a statement; returns the signal atoms it assigns on every path."""
        k = s.kind
        if k == TK.Block:
            return self.stmt(s.body, ctrl, ctx)
        if k == TK.List:
            full = set()
            for x in s.list:
                full |= self.stmt(x, ctrl, ctx)
            return full
        if k == TK.ExpressionStatement:
            return self.expr_stmt(s.expr, ctrl, ctx)
        if k == TK.VariableDeclaration:
            v = s.symbol
            init = v.initializer
            ctx.env[sym_key(v)] = self.reads(init, ctx) | set(ctrl) if init is not None else set()
            return set()
        if k == TK.Conditional:
            c = set()
            for cond in s.conditions:
                if cond.pattern is not None:
                    ctx.fail("pattern-matching if")
                c |= self.reads(cond.expr, ctx)
            exhaustive = s.ifFalse is not None
            return self.branch([s.ifTrue, s.ifFalse] if exhaustive else [s.ifTrue],
                               ctrl | c, ctx, exhaustive)
        if k == TK.Case:
            c = self.reads(s.expr, ctx)
            for it in s.items:
                for x in it.expressions:
                    c |= self.reads(x, ctx)
            stmts = [it.stmt for it in s.items]
            exhaustive = s.defaultCase is not None or self.case_complete(s)
            if s.defaultCase is not None:
                stmts.append(s.defaultCase)
            return self.branch(stmts, ctrl | c, ctx, exhaustive)
        if k in LOOPS:
            self.loop(s, ctrl, ctx)
            return set()
        if k in IGNORED_STATEMENTS:
            return set()
        if k == TK.Timed:
            ctx.fail("a timing control inside a process")
            self.stmt(s.stmt, ctrl, ctx)
            return set()
        ctx.fail(f"unsupported statement ({k.name})")
        return set()

    def case_complete(self, s):
        """Constant items that cover every value of a small selector. unique/priority are not
        trusted: if the uncovered value occurs anyway, the outputs hold their value."""
        if s.condition != ast.CaseStatementCondition.Normal:
            return False
        w = s.expr.type.bitWidth
        if w > 12:
            return False
        values = set()
        for it in s.items:
            for x in it.expressions:
                cv = x.eval(ast.EvalContext(self.top)) if hasattr(ast, "EvalContext") else None
                v = getattr(cv, "value", None) if cv is not None else None
                try:
                    values.add(int(v))
                except (TypeError, ValueError):
                    return False
        return len(values) == 2 ** w

    def loop(self, s, ctrl, ctx):
        k = s.kind
        if k == TK.ForLoop:
            for v in s.loopVars:
                ctx.env[sym_key(v)] = self.reads(v.initializer, ctx) if v.initializer is not None else set()
            for e in s.initializers:
                self.expr_stmt(e, ctrl, ctx)
        if k == TK.ForeachLoop:
            for d in s.loopDims:
                if d.loopVar is not None:
                    ctx.env[sym_key(d.loopVar)] = set()
        for _ in range(MAX_LOOP_PASSES):
            before = {x: set(v) for x, v in ctx.env.items()}
            assigned_before = {x: set(v) for x, v in ctx.assigned.items()}
            c = set()
            if k == TK.ForLoop and s.stopExpr is not None:
                c = self.reads(s.stopExpr, ctx)
            elif k in (TK.WhileLoop, TK.DoWhileLoop):
                c = self.reads(s.cond, ctx)
            elif k == TK.RepeatLoop:
                c = self.reads(s.count, ctx)
            self.branch([s.body], ctrl | c, ctx, exhaustive=False)
            if k == TK.ForLoop:
                for e in s.steps:
                    self.expr_stmt(e, ctrl | c, ctx)
            if ctx.env == before and dict(ctx.assigned) == assigned_before:
                return
        ctx.fail("loop analysis did not converge")

    # ------------------------------------------------------------------ safety net
    def check_drivers(self):
        """A signal that slang sees driven, but the extraction never assigned, is unknown."""
        for path, typ, sym in self.sig.values():
            leaves = self.leaves(path, typ)
            if any(l in self.driven or l in self.unknown or l in self.top_inputs for l in leaves):
                continue
            if len(self.am.getDrivers(sym)) > 0:
                for l in leaves:
                    self.add_unknown(l, "driven by a construct harm-coi does not model")


def extract(top, am):
    x = Extractor(top, am)
    x.run()
    return Design(edges=x.edges, signals=x.signals, params=x.params, unknown=x.unknown,
                  processes=x.processes, clock_uses=x.clock_uses, top_inputs=x.top_inputs)
