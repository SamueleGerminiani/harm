#!/usr/bin/env python3
"""Generate the iverilog oracle fixture for HARM's proposition semantics (H1, acceptance test A2).

Writes, into tests/oracle/fixture/:
  trace.csv  a random 4-valued trace over a fixed pool of logic variables (HARM CSV format)
  cases.txt  one line per expression: <category>|<SV per row>|<HARM model per row>|<expression>
             SV: the SystemVerilog value of the expression at each row (0, 1, x or z).
             HARM model: the SV value of the same expression with every relational/equality
             comparison made false when an operand contains x/z, which is HARM's documented
             semantics (H1 does not change it, see DECISIONS.md). The proposition must hold
             exactly where the HARM model is 1; where SV and the model differ is reported.
  meta.txt   generator parameters and the iverilog version

Categories:
  new       uses at least one H1 feature (based/fill literals, concatenation, replication, ?:, ===, !==)
  existing  pre-H1 syntax only; characterises current semantics (differences are reviewed, not hidden)

The fixture is committed; regenerate only with approval (it is a golden fixture):
  python3 tests/oracle/gen_iverilog_fixture.py [--seed N] [--rows N] [--new N] [--existing N]
"""
import argparse
import random
import subprocess
import tempfile
from pathlib import Path

# Variable names avoid letters that occur in literals (hex digits, x, z, base letters), so the
# oracle does not depend on substitution boundaries; boundaries are tested separately (A3).
VARS = [("p1", 1), ("q4", 4), ("r8", 8), ("t13", 13), ("u32", 32), ("v70", 70), ("w8", 8)]
BIN = "01xz"


class Gen:
    def __init__(self, rng: random.Random):
        self.r = rng

    # ---- literals -------------------------------------------------------------------------------
    def bits(self, w, xz=0.15):
        return "".join(self.r.choice("xz") if self.r.random() < xz else self.r.choice("01") for _ in range(w))

    def based(self, w):
        """A sized based literal of width w (new syntax except plain 'b, which is existing)."""
        base = self.r.choice("bhdo")
        if base == "b":
            return f"{w}'b{self.bits(w)}"
        if base == "h":
            n = (w + 3) // 4
            digits = "".join(self.r.choice("0123456789abcdefABCDEF" + ("xz" if self.r.random() < 0.3 else "")) for _ in range(n))
            return f"{w}'h{digits}"
        if base == "o":
            n = (w + 2) // 3
            digits = "".join(self.r.choice("01234567" + ("xz" if self.r.random() < 0.3 else "")) for _ in range(n))
            return f"{w}'o{digits}"
        if self.r.random() < 0.05:
            return f"{w}'d{self.r.choice('xz')}"
        return f"{w}'d{self.r.randrange(0, 2 ** min(w, 62))}"

    # ---- numeric expressions; returns (text, width, uses_new) ------------------------------------
    def num(self, depth, allow_new):
        choices = ["var", "var", "lit"]
        if depth > 0:
            choices += ["bit", "bit", "not"]
            if allow_new:
                choices += ["concat", "concat", "repl", "tern", "tern"]
        k = self.r.choice(choices)
        if k == "var":
            n, w = self.r.choice(VARS)
            return n, w, False
        if k == "lit":
            w = self.r.choice([1, 3, 4, 8, 13, 32])
            if allow_new and self.r.random() < 0.7:
                lit = self.based(w)
                return lit, w, not lit.split("'")[1].startswith("b")
            return f"{w}'b{self.bits(w)}", w, False
        if k == "not":
            t, w, n = self.num(depth - 1, allow_new)
            return f"(~{t})", w, n
        if k == "bit":
            # same-width operands, so context-determined sizing cannot differ between HARM and SV
            a, wa, na = self.num(depth - 1, allow_new)
            b, wb, nb = self.num_of_width(wa, depth - 1, allow_new)
            return f"({a} {self.r.choice('&|^')} {b})", wa, na or nb
        if k == "concat":
            parts = [self.num(depth - 1, allow_new) for _ in range(self.r.randint(2, 3))]
            if sum(p[1] for p in parts) > 200:
                return self.num(0, allow_new)
            return "{" + ", ".join(p[0] for p in parts) + "}", sum(p[1] for p in parts), True
        if k == "repl":
            t, w, _ = self.num(depth - 1, allow_new)
            n = self.r.randint(1, 4)
            if n * w > 200:
                n = 1
            return f"{{{n}{{{t}}}}}", n * w, True
        if k == "tern":
            # a case-equality condition is 2-valued in both SV and HARM, so the ternary tests the
            # selection itself (SV merges both branches when the condition is x)
            ca, wc, _ = self.num(depth - 1, allow_new)
            cb, _, _ = self.num_of_width(wc, depth - 1, allow_new)
            c = f"{ca} {self.r.choice(['===', '!=='])} {cb}"
            a, wa, _ = self.num(depth - 1, allow_new)
            b, _, _ = self.num_of_width(wa, depth - 1, allow_new)
            return f"({c} ? {a} : {b})", wa, True
        raise AssertionError(k)

    def num_of_width(self, w, depth, allow_new):
        """An expression of exactly width w."""
        same = [n for n, vw in VARS if vw == w]
        if same and self.r.random() < 0.5:
            return self.r.choice(same), w, False
        if allow_new and self.r.random() < 0.5:
            lit = self.based(w)
            return lit, w, not lit.split("'")[1].startswith("b")
        return f"{w}'b{self.bits(w)}", w, False

    # ---- boolean expressions; returns (text, uses_new) -------------------------------------------
    def boolean(self, depth, allow_new):
        """Returns (SV text, HARM-model text, uses_new)."""
        choices = ["cmp", "cmp", "cmp"]
        if depth > 0:
            choices += ["and", "or", "not"]
        k = self.r.choice(choices)
        if k == "cmp":
            a, wa, na = self.num(depth, allow_new)
            if allow_new and self.r.random() < 0.15:
                b, nb = self.r.choice(["'0", "'1", "'x", "'z"]), True
            else:
                b, _, nb = self.num_of_width(wa, depth, allow_new)
            ops = ["==", "!=", "<", "<=", ">", ">="] + (["===", "!=="] * 2 if allow_new else [])
            op = self.r.choice(ops)
            text = f"{a} {op} {b}"
            if op in ("===", "!=="):
                model = f"({text})"
            else:
                # HARM: a comparison with an x/z operand is false
                model = f"((^({a}) !== 1'bx) && (^({b}) !== 1'bx) && (({a}) {op} ({b})))"
            return text, model, na or nb or op in ("===", "!==")
        if k == "not":
            t, m, n = self.boolean(depth - 1, allow_new)
            return f"!({t})", f"!({m})", n
        a, ma, na = self.boolean(depth - 1, allow_new)
        b, mb, nb = self.boolean(depth - 1, allow_new)
        op = "&&" if k == "and" else "||"
        return f"({a}) {op} ({b})", f"({ma}) {op} ({mb})", na or nb


def run_iverilog(cases, rows):
    decls = "\n".join(f"  reg [{w - 1}:0] {n};" if w > 1 else f"  reg {n};" for n, w in VARS)
    body = []
    for row in rows:
        for (n, w), v in zip(VARS, row):
            body.append(f"    {n} = {w}'b{v};")
        body.append("    #1;")
        for i, (_, expr) in enumerate(cases):
            body.append(f'    $display("C{i} %b", ({expr}));')
    src = f"module tb;\n{decls}\n  initial begin\n" + "\n".join(body) + "\n  end\nendmodule\n"
    with tempfile.TemporaryDirectory() as d:
        (Path(d) / "tb.sv").write_text(src)
        subprocess.run(["iverilog", "-g2012", "-o", f"{d}/tb", f"{d}/tb.sv"], check=True, capture_output=True)  # warnings: literal truncation, as in SV
        out = subprocess.run(["vvp", "-n", f"{d}/tb"], check=True, capture_output=True, text=True).stdout
    values = [[] for _ in cases]
    for line in out.splitlines():
        if line.startswith("C"):
            idx, val = line[1:].split()
            values[int(idx)].append(val)
    for v in values:
        assert len(v) == len(rows), "iverilog output incomplete"
    return ["".join(v) for v in values]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--rows", type=int, default=32)
    ap.add_argument("--new", type=int, default=700)
    ap.add_argument("--existing", type=int, default=300)
    args = ap.parse_args()
    rng = random.Random(args.seed)
    g = Gen(rng)

    rows = [[g.bits(w, xz=rng.choice([0.0, 0.0, 0.1, 0.3])) for _, w in VARS] for _ in range(args.rows)]
    cases, seen = [], set()
    while sum(c[0] == "new" for c in cases) < args.new:
        e, m, uses_new = g.boolean(3, True)
        if uses_new and e not in seen:
            seen.add(e)
            cases.append(("new", e, m))
    while sum(c[0] == "existing" for c in cases) < args.existing:
        e, m, uses_new = g.boolean(3, False)
        assert not uses_new
        if e not in seen:
            seen.add(e)
            cases.append(("existing", e, m))

    sv = run_iverilog([(c, e) for c, e, _ in cases], rows)
    model = run_iverilog([(c, m) for c, _, m in cases], rows)
    out = Path(__file__).resolve().parent / "fixture"
    out.mkdir(exist_ok=True)
    header = ", ".join(f"logic [{w - 1}:0] {n}" if w > 1 else f"logic {n}" for n, w in VARS)
    (out / "trace.csv").write_text(header + "\n" + "\n".join(",".join(r) for r in rows) + "\n")
    (out / "cases.txt").write_text(
        "".join(f"{c}|{v}|{m}|{e}\n" for (c, e, _), v, m in zip(cases, sv, model)))
    ver = subprocess.run(["iverilog", "-V"], capture_output=True, text=True).stdout.splitlines()[0]
    (out / "meta.txt").write_text(
        f"seed={args.seed} rows={args.rows} new={args.new} existing={args.existing}\n{ver}\n")
    print(f"wrote {len(cases)} cases x {len(rows)} rows to {out}")


if __name__ == "__main__":
    main()
