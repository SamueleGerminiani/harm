#!/usr/bin/env python3
"""Independent oracle for HARM's end-of-trace semantics (H1c, D-016).

Parses the SVA text HARM prints, with IEEE 1800-2017 operator precedence (Table 16-3), and
evaluates it on finite traces with the truncated-path semantics on which IEEE 1800 Annex F is
based (Eisner, Fisman, Havlicek, Lustig, McIsaac, Van Campenhout, "Reasoning with temporal logic
on truncated paths", CAV 2003):
  - weak view (--trace-end harm): the trace is extended with the letter TOP (every boolean holds);
    negation switches to the strong view (extension with BOT, every boolean fails);
  - neutral view (--trace-end sva): no extension; nexttime is weak (holds at the last cycle),
    s_nexttime, s_eventually and s_until are strong, until and always are weak, and a sequence
    used as a property is weak (holds if the trace ends before it can be refuted).
`always (P)` holds if P holds at every cycle of the trace. Written from the standard, not from
HARM's code.

Usage:
  sva_finite_semantics.py check <dump>             compare with EndOfTraceTest's dump (A2)
  sva_finite_semantics.py filter <harm-output> <csv>...   assertions of a HARM output (SVA, one
      'always (...)' per line, '###' file headers kept) that hold on all the CSV traces in the
      neutral view (A3: the expected output of --trace-end sva)
Exit status 0 on success.
"""
import re
import sys
from pathlib import Path

# ------------------------------------------------------------------ parsing (Pratt)
TOKEN = re.compile(r"\s*(##\d+|\|->|\|=>|&&|\|\||1'b[01]|[A-Za-z_][\w.:]*|[()!])")
KEYWORDS = {"always", "s_eventually", "not", "nexttime", "s_nexttime", "until", "s_until",
            "and", "or"}
# binding powers (higher binds tighter), IEEE 1800-2017 Table 16-3
INFIX = {"||": (20, "left"), "&&": (22, "left"), "##": (18, "left"),
         "and": (10, "left"), "or": (8, "left"), "until": (6, "right"), "s_until": (6, "right"),
         "|->": (4, "right"), "|=>": (4, "right")}
PREFIX = {"!": 24, "not": 12, "nexttime": 12, "s_nexttime": 12, "always": 2, "s_eventually": 2}


def tokenize(text):
    toks, pos = [], 0
    while pos < len(text):
        if text[pos:].strip() == "":
            break
        m = TOKEN.match(text, pos)
        if not m:
            raise ValueError(f"cannot tokenize at {text[pos:]!r}")
        toks.append(m.group(1))
        pos = m.end()
    return toks


class Parser:
    def __init__(self, text):
        self.toks, self.i = tokenize(text), 0

    def peek(self):
        return self.toks[self.i] if self.i < len(self.toks) else None

    def next(self):
        t = self.peek()
        self.i += 1
        return t

    def expr(self, min_bp=0):
        t = self.next()
        if t is None:
            raise ValueError("unexpected end")
        if t == "(":
            left = self.expr(0)
            if self.next() != ")":
                raise ValueError("missing )")
        elif t.startswith("##"):  # a sequence starting with a delay: ##n s
            left = ("delay", int(t[2:]), self.expr(INFIX["##"][0] + 1))
        elif t in PREFIX:
            left = (t, self.expr(PREFIX[t]))
        elif t in ("1'b1", "true"):
            left = ("const", True)
        elif t in ("1'b0", "false"):
            left = ("const", False)
        elif t in KEYWORDS or t in INFIX or t == ")":
            raise ValueError(f"unexpected {t!r}")
        else:
            left = ("var", t)
        while True:
            t = self.peek()
            if t is None or t == ")":
                return left
            if t.startswith("##"):
                op, n = "##", int(t[2:])
            elif t in INFIX:
                op, n = t, None
            else:
                raise ValueError(f"unexpected {t!r}")
            bp, assoc = INFIX[op]
            if bp < min_bp or (bp == min_bp and assoc == "left"):
                return left
            self.next()
            right = self.expr(bp if assoc == "right" else bp + 1)
            left = ("concat", n, left, right) if op == "##" else (op, left, right)


def parse_assertion(text):
    p = Parser(text)
    tree = p.expr(0)
    if p.peek() is not None:
        raise ValueError(f"trailing tokens in {text!r}")
    if tree[0] != "always":
        raise ValueError(f"not an 'always' assertion: {text!r}")
    return tree[1]


# ------------------------------------------------------------------ sequences
def is_boolean(node):
    k = node[0]
    return k in ("var", "const") or (k in ("!", "&&", "||") and all(
        is_boolean(c) for c in node[1:]))


def sequence(node):
    """a fixed-length sequence as [(offset, boolean)] and its length - 1, or None"""
    k = node[0]
    if is_boolean(node):
        return [(0, node)], 0
    if k == "delay":
        s = sequence(node[2])
        return ([(o + node[1], b) for o, b in s[0]], s[1] + node[1]) if s else None
    if k == "concat":
        l, r = sequence(node[2]), sequence(node[3])
        if not l or not r:
            return None
        shift = l[1] + node[1]
        return l[0] + [(o + shift, b) for o, b in r[0]], r[1] + shift
    return None


# ------------------------------------------------------------------ evaluation
class Trace:
    def __init__(self, rows):  # rows: list of {name: bool}
        self.rows, self.n = rows, len(rows)

    def boolean(self, node, i, tail):
        """a boolean at cycle i; beyond the end, TOP (all true) or BOT (all false)"""
        if i >= self.n:
            assert tail in ("top", "bot"), "the neutral view never reads beyond the end"
            return tail == "top"
        k = node[0]
        if k == "var":
            return self.rows[i][node[1]]
        if k == "const":
            return node[1]
        if k == "!":
            return not self.boolean(node[1], i, tail)
        if k == "&&":
            return self.boolean(node[1], i, tail) and self.boolean(node[2], i, tail)
        if k == "||":
            return self.boolean(node[1], i, tail) or self.boolean(node[2], i, tail)
        raise ValueError(f"not a boolean: {node}")

    def holds(self, node, i, tail):
        """node at cycle i (0 <= i <= n); tail: 'top' (weak view), 'bot' (strong), None (neutral)"""
        n, k = self.n, node[0]
        if tail is not None:
            i = min(i, n)  # beyond the end every cycle is the same letter
        seq = sequence(node)
        if seq is not None:  # a sequence used as a property: weak
            if tail is None:
                return all(self.boolean(b, i + o, tail) for o, b in seq[0] if i + o < n)
            return all(self.boolean(b, i + o, tail) for o, b in seq[0])
        if k == "not":
            dual = {"top": "bot", "bot": "top", None: None}[tail]
            return not self.holds(node[1], i, dual)
        if k == "and":
            return self.holds(node[1], i, tail) and self.holds(node[2], i, tail)
        if k == "or":
            return self.holds(node[1], i, tail) or self.holds(node[2], i, tail)
        if k in ("nexttime", "s_nexttime"):
            if tail is None and i + 1 >= n:
                return k == "nexttime"
            return self.holds(node[1], i + 1, tail)
        last = n if tail is not None else n - 1  # the cycles to consider
        if k == "s_eventually":
            return any(self.holds(node[1], j, tail) for j in range(i, last + 1))
        if k == "always":
            return all(self.holds(node[1], j, tail) for j in range(i, last + 1))
        if k in ("until", "s_until"):
            for j in range(i, last + 1):
                if self.holds(node[2], j, tail):
                    return True
                if not self.holds(node[1], j, tail):
                    return False
            return k == "until"  # the left side held to the end
        if k in ("|->", "|=>"):
            ant = sequence(node[1])
            if ant is None:
                raise ValueError(f"unsupported antecedent {node[1]}")
            con = node[2] if k == "|->" else ("nexttime", node[2])
            end = i + ant[1]
            if tail is None and end >= n:
                return True  # no match inside the trace
            if not all(self.boolean(b, i + o, tail) for o, b in ant[0]):
                return True
            return self.holds(con, end, tail)
        raise ValueError(f"unsupported operator {k}")

    def assertion_holds(self, prop, mode):
        tail = "top" if mode == "harm" else None
        return all(self.holds(prop, i, tail) for i in range(self.n))


# ------------------------------------------------------------------ commands
def all_traces(max_len=4, atoms="abc"):
    for L in range(1, max_len + 1):
        for code in range(1 << (len(atoms) * L)):
            yield Trace([{a: bool((code >> (t * len(atoms) + k)) & 1)
                          for k, a in enumerate(atoms)} for t in range(L)])


def check(dump):
    traces = list(all_traces())
    bad = 0
    lines = [l for l in Path(dump).read_text().splitlines() if l.strip()]
    for line in lines:
        formula, sva, harm, sv = [x.strip() for x in line.split("|||")]
        try:
            prop = parse_assertion(sva)
        except ValueError as e:
            print(f"PARSE {formula} | {sva}: {e}")
            bad += 1
            continue
        for mode, got in (("harm", harm), ("sva", sv)):
            want = "".join("1" if t.assertion_holds(prop, mode) else "0" for t in traces)
            if want != got:
                j = next(x for x in range(len(want)) if want[x] != got[x])
                rows = ";".join("".join(str(int(r[a])) for a in "abc") for r in traces[j].rows)
                print(f"DIFF [{mode}] {formula} | {sva} | trace {rows}: "
                      f"oracle {want[j]}, HARM {got[j]} ({sum(a != b for a, b in zip(want, got))} traces)")
                bad += 1
    print(f"{len(lines)} assertions x {len(traces)} traces x 2 modes: {bad} disagreements")
    return bad == 0


def read_csv(path):
    lines = [l.strip() for l in Path(path).read_text().splitlines() if l.strip()]
    names = [h.strip().split()[-1] for h in lines[0].split(",")]
    return Trace([{n: v.strip() == "1" for n, v in zip(names, l.split(","))} for l in lines[1:]])


def filter_output(output, csvs):
    traces = [read_csv(c) for c in csvs]
    for line in Path(output).read_text().splitlines():
        if line.startswith("always"):
            prop = parse_assertion(line)
            if all(t.assertion_holds(prop, "sva") for t in traces):
                print(line)
        else:
            print(line)
    return True


if __name__ == "__main__":
    if len(sys.argv) >= 3 and sys.argv[1] == "check":
        sys.exit(0 if check(sys.argv[2]) else 1)
    if len(sys.argv) >= 4 and sys.argv[1] == "filter":
        sys.exit(0 if filter_output(sys.argv[2], sys.argv[3:]) else 1)
    sys.exit(__doc__)
