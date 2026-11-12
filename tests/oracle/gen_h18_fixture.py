#!/usr/bin/env python3
"""Generate the H18 operator fixture: HARM's operators against SystemVerilog (Icarus Verilog), 2-valued.

Writes, into tests/oracle/fixture_h18/:
  trace.csv  random 2-valued rows over bool, int, unsigned int, logic [3:0], logic [7:0],
             logic signed [3:0] and float variables (HARM CSV format)
  cases.txt  one line per expression: <expect>|<category>|<SV value per row>|<expression>
             expect: 'ok'  HARM must give the SystemVerilog value on every row (H18)
                     'H19:<ids>'  a known evaluation difference left to H19 (findings in
                     doc/plan/H18_PLAN.md), chosen by the rules in expect(); compared and reported,
                     not failed, so that H19 can shrink the list
  meta.txt   generator parameters and the Icarus Verilog version

Sources of truth (cross-checked in H18_PLAN.md): IEEE 1800-2017 Table 11-2 (precedence), 11.4.4,
11.4.7, 11.4.10, 11.8.1; Icarus agreed with the standard on every case of the H18 audit.
SystemVerilog's unary operand is a primary (A.8.3): '!!x' is given to Icarus as '!(!x)'; Icarus 12 has no
'inside', so those cases are given to it as == and || (11.4.13).

The fixture is committed; regenerate only with approval:
  python3 tests/oracle/gen_h18_fixture.py
"""
import random
import re
import subprocess
import tempfile
from pathlib import Path

ROWS = 40
rng = random.Random(7)
# name, HARM CSV type, SV type, signed, generator
VARS = [
    ("a", "bool", "bit", False, lambda: rng.randint(0, 1)),
    ("b", "bool", "bit", False, lambda: rng.randint(0, 1)),
    ("x", "int", "int", True, lambda: rng.randint(-9, 9)),
    ("y", "int", "int", True, lambda: rng.randint(-9, 9)),
    ("z", "int", "int", True, lambda: rng.choice([1, 2, 3, -2, 5])),          # never 0 (a divisor)
    ("u", "unsigned int", "int unsigned", False, lambda: rng.randint(0, 9)),
    ("n", "unsigned int", "int unsigned", False, lambda: rng.randint(1, 9)),  # never 0 (a divisor)
    ("q", "logic [3:0]", "logic [3:0]", False, lambda: rng.randint(0, 15)),
    ("r", "logic [3:0]", "logic [3:0]", False, lambda: rng.randint(0, 15)),
    ("w", "logic [7:0]", "logic [7:0]", False, lambda: rng.randint(0, 255)),
    ("s", "logic signed [3:0]", "logic signed [3:0]", True, lambda: rng.randint(-8, 7)),
    ("f", "float", "real", True, lambda: rng.choice([0.0, 0.5, 1.0, 2.5, -1.5, 3.0])),
    ("g", "float", "real", True, lambda: rng.choice([0.5, 1.0, 2.0, -2.0, 0.25])),  # never 0 (a divisor)
]
rows = [[gen() for *_, gen in VARS] for _ in range(ROWS)]
SIGNED = {n for n, _, _, sg, _ in VARS if sg}
UNSIGNED = {n for n, _, _, sg, _ in VARS if not sg}

BIN = ["*", "/", "+", "-", "<<", ">>", "&", "^", "|", "<", "<=", ">", ">=", "==", "!=", "&&", "||"]
REL = {"<", "<=", ">", ">="}
CMP = REL | {"==", "!="}
cases = []  # (category, expression)

# precedence: A op1 B op2 C on ints (divisors never 0; shift amounts unsigned)
for o1 in BIN:
    for o2 in BIN:
        B = "z" if o1 == "/" else ("u" if o1 in ("<<", ">>") else "y")
        C = "z" if o2 == "/" else ("u" if o2 in ("<<", ">>") else "y")
        cases.append(("precedence", f"x {o1} {B} {o2} {C}"))
# prefix operators before each binary operator, on int and on logic
for un in ["!", "~", "-", "+"]:
    for o in BIN:
        C = "z" if o == "/" else ("u" if o in ("<<", ">>") else "y")
        cases.append(("prefix", f"{un}x {o} {C}"))
        cases.append(("prefix", f"{un}q {o} {'n' if o == '/' else 'r'}"))
cases += [("prefix", e) for e in ["!!x", "~~x", "-(-x)", "!~x", "~!x", "!-x", "-!x", "!a", "!a && b", "!a == b",
                                  "!x && y", "!a ^ b", "!(a)", "!(x == y)", "-x == 0 - x", "+x == x", "!q[1]", "~q[1]"]]
# each operator on each pair of operand types
TYPED = {"bool": "a", "int": "x", "uint": "u", "logic4": "q", "logic8": "w", "slogic4": "s", "float": "f"}
for o in BIN:
    for t1, v1 in TYPED.items():
        for t2, v2 in TYPED.items():
            if o in ("&", "^", "|", "<<", ">>") and "float" in (t1, t2):
                continue  # illegal on real in SystemVerilog
            if o == "/":
                v2 = {"int": "z", "uint": "n", "float": "g"}.get(t2)
                if v2 is None:
                    continue
            cases.append(("types", f"{v1} {o} {v2}"))
# Booleans and numbers, chains, lexing, inside
cases += [("boolnum", e) for e in ["(x > 0) == y", "(x > 0) != y", "(!x) == y", "a == x", "a < y", "a + a == 2",
                                   "(x > 0) + 1 == 2", "(q == r) == u", "x < y < y", "x == y == y", "a == b",
                                   "(a) == b", "c_unused_placeholder"]]
cases = [c for c in cases if "c_unused" not in c[1]]
cases += [("lexing", e) for e in ["x-1 == 4", "x - 1 == 4", "x-y > 0", "5-3 == 2", "x+-1 == 0", "q-1 == 4'd3"]]
cases += [("inside", e) for e in ["q inside {1, 5}", "!(q inside {1, 5})", "!q inside {0, 1}", "q + 1 inside {2, 6}"]]
cases += [("width", e) for e in ["q + r == 5'd16", "q + r > 4'd15", "~q == 4'd0", "w + w > 8'd255", "-q == -1"]]
cases += [("ternary", e) for e in ["a ? x : y == 1", "a ? x > 0 : y > 0", "x > 0 ? q : r == 3"]]
cases = list(dict.fromkeys(cases))


def expect(e):
    """'ok' (since H19, D-035, every case must agree). Before H19: the H19 findings that explained a
    known difference, by these rules (kept to document the H18 fixture's history)."""
    return "ok"
    toks = re.findall(r"[A-Za-z_]\w*|\d+'[bdh]\w+|\d+|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/<>&^|!~()]", e)
    ids = []
    if "<<" in toks or ">>" in toks:
        ids.append("E1E2E4")  # shifts: amounts >= width or negative, >> on signed
    names = {t for t in toks if re.fullmatch(r"[a-z]", t)}
    signed = bool(names & (SIGNED - {"f", "g"})) or any(re.fullmatch(r"\d+", t) for t in toks) or "-" in toks
    unsigned = bool(names & UNSIGNED) or any("'" in t for t in toks) \
        or sum(t in CMP for t in toks) >= 2 or "!" in toks
    floats = bool(names & {"f", "g"})
    # a narrow signed operand (s) with an unsigned one: SystemVerilog zero-extends it (11.8.1, 11.8.2)
    if signed and unsigned and not floats and (REL & set(toks) or "/" in toks or "s" in names):
        ids.append("E3")  # signed with unsigned: SystemVerilog makes the operation unsigned (11.8.1)
    return "ok" if not ids else "H19:" + ",".join(ids)


# Icarus Verilog 12 does not implement 'inside': on 2-valued values, e inside {v1, v2} is
# (e == v1 || e == v2) (IEEE 1800-2017 11.4.13)
INSIDE_SV = {
    "q inside {1, 5}": "(q == 1 || q == 5)",
    "!(q inside {1, 5})": "!(q == 1 || q == 5)",
    "!q inside {0, 1}": "((!q) == 0 || (!q) == 1)",
    "q + 1 inside {2, 6}": "((q + 1) == 2 || (q + 1) == 6)",
}


def svtext(e):
    if e in INSIDE_SV:
        return INSIDE_SV[e]
    # a unary operand is a primary in SystemVerilog (A.8.3)
    e = re.sub(r"^([!~+-])([!~+-])x$", r"\1(\2x)", e)
    return e.replace("x+-1", "x+(-1)")


def fmt(t, v):
    m = re.search(r"\[(\d+):0\]", t)
    if t.startswith("logic"):
        w = int(m.group(1)) + 1
        return format(v & ((1 << w) - 1), f"0{w}b")
    return str(v)


here = Path(__file__).resolve().parent / "fixture_h18"
here.mkdir(exist_ok=True)
hdr = ",".join(f"{t} {n}" for n, t, *_ in VARS)
(here / "trace.csv").write_text(hdr + "\n" + "\n".join(",".join(fmt(t, v) for (_, t, *_), v in zip(VARS, r)) for r in rows) + "\n")

decl = "\n".join(f"  {sv} {n};" for n, _, sv, *_ in VARS)
body = []
for r in rows:
    body.append("    " + " ".join(f"{n} = {v};" for (n, *_), v in zip(VARS, r)))
    body.append('    $write("R");')
    body += [f'    $write("%0d", (({svtext(e)}) ? 1 : 0));' for _, e in cases]
    body.append('    $display("");')
with tempfile.TemporaryDirectory() as d:
    sv = Path(d) / "t.sv"
    sv.write_text("module t;\n" + decl + "\n  initial begin\n" + "\n".join(body) + "\n  end\nendmodule\n")
    subprocess.run(["iverilog", "-g2012", "-o", f"{d}/t.vvp", str(sv)], check=True)
    out = subprocess.run(["vvp", "-n", f"{d}/t.vvp"], capture_output=True, text=True, check=True).stdout
lines = [l[1:] for l in out.splitlines() if l.startswith("R")]
assert len(lines) == ROWS
(here / "cases.txt").write_text("".join(f"{expect(e)}|{cat}|{''.join(l[i] for l in lines)}|{e}\n"
                                        for i, (cat, e) in enumerate(cases)))
ver = subprocess.run(["iverilog", "-V"], capture_output=True, text=True).stdout.splitlines()[0]
(here / "meta.txt").write_text(f"seed=7 rows={ROWS} cases={len(cases)}\n{ver}\n")
print(f"{len(cases)} cases, {sum(1 for _, e in cases if expect(e) == 'ok')} must agree")
