#!/usr/bin/env python3
"""H5a spike: direct COI edges from the pyslang elaborated AST, written in edges.txt format.

Usage: spike_pyslang.py <fixture-dir>   (reads <dir>/edges.txt header for top/scope/recursion/...)
Throwaway code: it covers the constructs of the H4 fixtures, not the full language.
"""
import glob
import sys
from collections import defaultdict
from pathlib import Path

from pyslang import ast, syntax

SK, EK, TK = ast.SymbolKind, ast.ExpressionKind, ast.StatementKind
CONSTANTS = (SK.Parameter, SK.EnumValue)


def header(fixture):
    meta = {}
    for line in (Path(fixture) / "edges.txt").read_text().splitlines():
        line = line.split("#")[0].strip()
        if "=" in line and "<-" not in line:
            k, v = [x.strip() for x in line.split("=", 1)]
            meta[k] = v
    return meta


class Extractor:
    def __init__(self, top_inst):
        self.top = top_inst
        self.edges = defaultdict(set)        # target path -> {(source path, delay)}
        self.signals = set()                 # every leaf path seen as a value
        self.params = set()
        self.clocks = set()
        self.unknown = set()

    # ---- names: a path is a tuple of components below the top instance ----
    def sym_path(self, sym):
        hp = sym.hierarchicalPath            # e.g. "hier.g[1].w"
        parts = split_hier(hp)
        assert parts[0] == self.top.name, hp
        return tuple(parts[1:])

    def leaves(self, path, typ):
        """Expand a packed struct into its fields (field-level precision)."""
        t = typ.canonicalType
        if t.kind == SK.PackedStructType:
            out = []
            for f in t:
                if f.kind == SK.Field:
                    out += self.leaves(path + (f.name,), f.type)
            return out
        return [path]

    def base(self, expr):
        """(path, type) named by expr if it is a value, possibly member-accessed; else None."""
        if expr.kind in (EK.NamedValue, EK.HierarchicalValue):
            if expr.symbol.kind in CONSTANTS:
                return None
            return self.sym_path(expr.symbol), expr.symbol.type
        if expr.kind == EK.MemberAccess:
            b = self.base(expr.value)
            if b is None:
                return None
            return b[0] + (expr.member.name,), expr.member.type
        return None

    def value_paths(self, expr):
        """Leaf paths named by expr, or None if expr is not a (member-accessed) value."""
        if expr.kind in (EK.NamedValue, EK.HierarchicalValue) and expr.symbol.kind in CONSTANTS:
            return []          # parameters and enum values are constants: no dependency
        b = self.base(expr)
        return None if b is None else self.leaves(*b)

    def reads(self, expr, env=None):
        out = set()

        def cb(e):
            if not isinstance(e, ast.Expression):
                return ast.VisitAction.Advance
            if e.kind == EK.Call:
                sub = e.subroutine
                if not isinstance(sub, ast.SubroutineSymbol) and e.isSystemCall():
                    return ast.VisitAction.Advance
                if isinstance(sub, ast.SubroutineSymbol):
                    # a user function: its result depends on its arguments (pure-function assumption)
                    return ast.VisitAction.Advance
            p = self.value_paths(e)
            if p is not None:
                for x in p:
                    if env is not None and x in env:
                        out.update(env[x])
                    else:
                        out.add(x)
                return ast.VisitAction.Skip
            return ast.VisitAction.Advance

        expr.visit(cb)
        return out

    def lvalues(self, expr):
        p = self.value_paths(expr)
        if p is not None:
            return p
        if expr.kind in (EK.ElementSelect, EK.RangeSelect):
            return self.lvalues(expr.value)       # bit/part select: whole signal (signal-level)
        if expr.kind == EK.Concatenation:
            return [x for op in expr.operands for x in self.lvalues(op)]
        self.unknown.add(str(expr.syntax))
        return []

    def lvalue_index_reads(self, expr):
        if expr.kind == EK.ElementSelect:
            return self.reads(expr.selector) | self.lvalue_index_reads(expr.value)
        if expr.kind == EK.RangeSelect:
            return self.reads(expr.left) | self.reads(expr.right) | self.lvalue_index_reads(expr.value)
        return set()

    # ---- structure ----
    def walk_scope(self, body):
        for m in body:
            k = m.kind
            if k == SK.Parameter:
                # a genvar loop creates an implicit localparam per block: simulators do not dump it
                if m.syntax is not None and m.syntax.kind == syntax.SyntaxKind.Declarator:
                    self.params.add(self.sym_path(m))
            elif k in (SK.Net, SK.Variable):
                for leaf in self.leaves(self.sym_path(m), m.type):
                    self.signals.add(leaf)
            elif k == SK.ContinuousAssign:
                a = m.assignment
                src = self.reads(a.right) | self.lvalue_index_reads(a.left)
                for t in self.lvalues(a.left):
                    self.edges[t] |= {(s, 0) for s in src}
            elif k == SK.ProceduralBlock:
                self.procedure(m)
            elif k == SK.Instance:
                self.instance(m)
            elif k in (SK.GenerateBlock,):
                if not m.isUninstantiated:
                    self.walk_scope(m)
            elif k == SK.GenerateBlockArray:
                for e in m.entries:
                    if not e.isUninstantiated:
                        self.walk_scope(e)
            elif k in (SK.Port, SK.TypeAlias, SK.Genvar, SK.TransparentMember, SK.Modport,
                       SK.InterfacePort, SK.EmptyMember):
                pass
            else:
                self.unknown.add(f"{k} {getattr(m, 'name', '')}")

    def instance(self, inst):
        self.walk_scope(inst.body)
        for pc in inst.portConnections:
            port = pc.port
            if port.kind != SK.Port or pc.expression is None:
                continue
            inner = self.leaves(self.sym_path(port.internalSymbol), port.internalSymbol.type)
            ext = pc.expression
            if port.direction == ast.ArgumentDirection.In:
                src = self.reads(ext)
                for t in inner:
                    self.edges[t] |= {(s, 0) for s in src}
            elif port.direction == ast.ArgumentDirection.Out:
                if ext.kind == EK.Assignment:   # output connections are wrapped in an assignment
                    ext = ext.left
                for t in self.lvalues(ext):
                    self.edges[t] |= {(s, 0) for s in inner}
            else:
                self.unknown.add(f"inout port {port.name}")

    def procedure(self, pb):
        body = pb.body
        kind = pb.procedureKind
        if kind == ast.ProceduralBlockKind.AlwaysFF or (kind == ast.ProceduralBlockKind.Always
                                                        and body.kind == TK.Timed):
            assert body.kind == TK.Timed
            tc = body.timing
            self.note_clock(tc)
            assigned = defaultdict(set)
            full = self.stmt(body.stmt, frozenset(), assigned, None, delay=1)
            # a register not assigned on every path holds its value: it depends on itself
            for t in assigned:
                if t not in full:
                    assigned[t].add(t)
            for t, srcs in assigned.items():
                self.edges[t] |= {(s, 1) for s in srcs}
        elif kind in (ast.ProceduralBlockKind.AlwaysComb, ast.ProceduralBlockKind.Always):
            assigned = defaultdict(set)
            env = {}
            full = self.stmt(body, frozenset(), assigned, env, delay=0)
            for t, srcs in assigned.items():
                if t not in full:
                    self.unknown.add(f"latch {'::'.join(t)}")
                self.edges[t] |= {(s, 0) for s in srcs}
        elif kind == ast.ProceduralBlockKind.Initial:
            pass
        else:
            self.unknown.add(f"procedure {kind}")

    def note_clock(self, tc):
        if tc.kind == ast.TimingControlKind.SignalEvent:
            for p in self.value_paths(tc.expr) or []:
                self.clocks.add(p)
        elif tc.kind == ast.TimingControlKind.EventList:
            # posedge clk or posedge rst: the first is the clock, the others async controls
            evs = list(tc.events)
            self.note_clock(evs[0])

    def stmt(self, s, ctrl, assigned, env, delay):
        """Walk a statement; returns the set of targets assigned on every path."""
        k = s.kind
        if k == TK.Block:
            return self.stmt(s.body, ctrl, assigned, env, delay)
        if k == TK.List:
            full = set()
            for x in s.list:
                full |= self.stmt(x, ctrl, assigned, env, delay)
            return full
        if k == TK.Empty:
            return set()
        if k == TK.ExpressionStatement:
            e = s.expr
            if e.kind != EK.Assignment:
                if e.kind == EK.Call:
                    return set()  # system task ($display): no data effect
                self.unknown.add(str(s.syntax))
                return set()
            src = self.reads(e.right, env) | self.lvalue_index_reads(e.left) | set(ctrl)
            ts = self.lvalues(e.left)
            partial = e.left.kind in (EK.ElementSelect, EK.RangeSelect)
            for t in ts:
                if partial:      # a partial write keeps the other bits
                    src = src | ({t} if env is None else env.get(t, {t}))
                assigned[t] |= src
                if env is not None and not e.isNonBlocking:
                    env[t] = set(src)   # blocking temporary: later reads see its sources
            return set() if partial else set(ts)
        if k == TK.Conditional:
            c = set()
            for cond in s.conditions:
                c |= self.reads(cond.expr, env)
            c2 = ctrl | c
            e1 = dict(env) if env is not None else None
            f1 = self.stmt(s.ifTrue, c2, assigned, e1, delay)
            if s.ifFalse is not None:
                e2 = dict(env) if env is not None else None
                f2 = self.stmt(s.ifFalse, c2, assigned, e2, delay)
                merge_env(env, e1, e2)
                return f1 & f2
            merge_env(env, e1, None)
            return set()
        if k == TK.Case:
            c = set(self.reads(s.expr, env))
            for it in s.items:
                for x in it.expressions:
                    c |= self.reads(x, env)
            c2 = ctrl | c
            fulls, envs = [], []
            branches = [it.stmt for it in s.items] + ([s.defaultCase] if s.defaultCase else [])
            for b in branches:
                e = dict(env) if env is not None else None
                fulls.append(self.stmt(b, c2, assigned, e, delay))
                envs.append(e)
            if env is not None:
                for e in envs:
                    merge_env(env, e, None)
            if s.defaultCase is None:
                return set()
            return set.intersection(*fulls) if fulls else set()
        if k == TK.Timed:
            self.unknown.add("nested timing control")
            return self.stmt(s.stmt, ctrl, assigned, env, delay)
        self.unknown.add(f"statement {k}")
        return set()


def merge_env(env, a, b):
    if env is None:
        return
    for e in (a, b):
        if e is None:
            continue
        for k, v in e.items():
            env[k] = env.get(k, set()) | v


def common_prefix(paths):
    p = paths[0]
    for q in paths[1:]:
        n = 0
        while n < min(len(p), len(q)) and p[n] == q[n]:
            n += 1
        p = p[:n]
    return p


def split_hier(hp):
    """Split 'a.g[1].b' on dots outside brackets."""
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


def collapse(edges, visible, max_depth):
    """Direct edges between visible signals: walk back through invisible ones, summing delays."""
    out = defaultdict(set)
    limit = max_depth + 4
    for t in visible:
        stack = [(s, d) for s, d in edges.get(t, ())]
        seen = set()
        while stack:
            s, d = stack.pop()
            if (s, d) in seen or d > limit:
                continue
            seen.add((s, d))
            if s in visible:
                out[t].add((s, d))
            else:
                stack += [(s2, d + d2) for s2, d2 in edges.get(s, ())]
    return out


def main():
    fixture = sys.argv[1]
    meta = header(fixture)
    rec = int(meta["vcd_recursion"])
    c = ast.Compilation()
    for f in sorted(glob.glob(f"{fixture}/rtl/*.sv")):
        c.addSyntaxTree(syntax.SyntaxTree.fromFile(f))
    diags = [d for d in c.getAllDiagnostics() if d.isError()]
    if diags:
        sys.exit(f"elaboration errors: {len(diags)}")
    top = [t for t in c.getRoot().topInstances if t.name == meta["top"]][0]
    x = Extractor(top)
    x.walk_scope(top.body)
    # a signal that only reaches a clock input through wires/ports is a clock too
    changed = True
    while changed:
        changed = False
        for t in list(x.clocks):
            for src, d in x.edges.get(t, ()):
                if d == 0 and src not in x.clocks:
                    x.clocks.add(src)
                    changed = True
    # visible = at most `rec` sub-scopes below the top (a struct counts as a scope with --trace-structs)
    visible = {p for p in x.signals | x.params if len(p) - 1 <= rec} - x.clocks
    direct = collapse(x.edges, visible, int(meta["max_depth"]))
    name = lambda p: "::".join(p)
    for k in ("design", "top", "vcd_scope", "vcd_recursion", "clock", "max_depth"):
        print(f"{k} = {meta[k]}")
    for t in sorted(visible, key=name):
        if not direct.get(t):
            print(f"target {name(t)}")
    for t in sorted(direct, key=name):
        for s, d in sorted(direct[t], key=lambda e: (name(e[0]), e[1])):
            if s in x.clocks:
                continue
            print(f"{name(t)} <- {name(s)} @{d}")
    for u in sorted(x.unknown):
        print(f"# unknown: {u}", file=sys.stderr)


if __name__ == "__main__":
    main()
