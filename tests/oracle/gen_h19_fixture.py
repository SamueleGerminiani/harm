#!/usr/bin/env python3
"""Generate the H19 evaluation fixture: HARM's evaluation and conversions against SystemVerilog.

Writes, into tests/oracle/fixture_h19/:
  trace.csv  random rows over every C integer type of the CSV format and its SystemVerilog
             counterpart, signed and unsigned logic of several widths, integer and time (4-state),
             with x/z in about 1 bit in 12 of the 4-state variables
  cases.txt  one line per expression: ok|<category>|<expected value per row>|<expression>
  meta.txt   generator parameters and the Icarus Verilog version

Expected values: Icarus Verilog 12 (SystemVerilog, IEEE 1800-2017 §11.4, §11.6, §11.8), mapped to
HARM's truth value by 'if (e)' (x and z are false, D-011; a '?:' would give x on an x condition). A
comparison at the top of an expression follows D-011: false when an operand has an x or z bit (where
SystemVerilog can still decide == and != from the known bits), as the H1 oracle's model does. Comparisons appear only at the top
of an expression, where SystemVerilog and D-011 agree on x. One exception, decided by the user
(H19, Q3 (a)): a C integer type has no x, so a division by zero gives 0; on those rows the expected
value is computed here (the expression evaluated with the quotient 0), not taken from Icarus.

The fixture is committed; regenerate only with approval:
  python3 tests/oracle/gen_h19_fixture.py
"""
import random
import re
import subprocess
import tempfile
from pathlib import Path

ROWS = 48
rng = random.Random(19)


def ints(lo, hi, zero=0.15):
    return lambda: 0 if rng.random() < zero else rng.randint(lo, hi)


def bits(w, signed, xz=1 / 12):
    def g():
        v = rng.randint(-(1 << (w - 1)), (1 << (w - 1)) - 1) if signed else rng.randint(0, (1 << w) - 1)
        if rng.random() < 0.12:
            v = 0
        b = list(format(v & ((1 << w) - 1), f"0{w}b"))
        for i in range(w):
            if rng.random() < xz:
                b[i] = rng.choice("xz")
        return "".join(b)
    return g


# name, HARM CSV type, SystemVerilog type, kind (c: 2-valued C integer, l: 4-state), signed, width, generator
VARS = [
    ("ch", "char", "byte", "c", True, 8, ints(-128, 127)),
    ("sh", "short", "shortint", "c", True, 16, ints(-300, 300)),
    ("it", "int", "int", "c", True, 32, ints(-40, 40)),
    ("li", "long int", "longint", "c", True, 64, ints(-50, 50)),
    ("uch", "unsigned char", "byte unsigned", "c", False, 8, ints(0, 255)),
    ("ush", "unsigned short", "shortint unsigned", "c", False, 16, ints(0, 400)),
    ("ui", "unsigned int", "int unsigned", "c", False, 32, ints(0, 40)),
    ("iu", "int unsigned", "int unsigned", "c", False, 32, ints(0, 40)),
    ("uli", "unsigned long int", "longint unsigned", "c", False, 64, ints(0, 60)),
    ("q", "logic [3:0]", "logic [3:0]", "l", False, 4, bits(4, False)),
    ("w", "logic [7:0]", "logic [7:0]", "l", False, 8, bits(8, False)),
    ("sq", "logic signed [3:0]", "logic signed [3:0]", "l", True, 4, bits(4, True)),
    ("sw", "logic signed [7:0]", "logic signed [7:0]", "l", True, 8, bits(8, True)),
    ("ig", "integer", "integer", "l", True, 32, bits(32, True, 1 / 40)),
    ("tm", "time", "time", "l", False, 64, bits(64, False, 1 / 80)),
    ("am", "logic [3:0]", "logic [3:0]", "l", False, 4, bits(4, False, 0)),  # a shift amount, 0..15
]
rows = [[gen() for *_, gen in VARS] for _ in range(ROWS)]
INFO = {n: (k, sg, w) for n, _, _, k, sg, w, _ in VARS}
cases = []

# signedness and conversions: every operator on pairs of types
OPERANDS = ["ch", "it", "li", "uch", "ui", "uli", "q", "w", "sq", "sw", "ig", "tm"]
for a in OPERANDS:
    for b in OPERANDS:
        for op in ["+", "-", "*"]:
            cases.append(("signedness", f"{a} {op} {b} < 0"))
        for op in ["&", "|", "^"]:  # bracketed: & | ^ bind looser than < (D-034)
            cases.append(("signedness", f"({a} {op} {b}) < 0"))
        cases.append(("signedness", f"{a} - {b} > 1"))
        for op in ["<", ">=", "==", "!="]:
            cases.append(("signedness", f"{a} {op} {b}"))
# shifts: variable amounts (0..15, and C integers that can be negative) and constant amounts
for v in ["ch", "it", "li", "uch", "ui", "q", "w", "sq", "sw", "ig", "tm"]:
    w = INFO[v][2]
    for amt in ["am", "it", "uch"]:
        for op in ["<<", ">>", "<<<", ">>>"]:
            cases.append(("shift", f"{v} {op} {amt} == 0"))
            cases.append(("shift", f"{v} {op} {amt} < 0"))
    for k in sorted({0, 1, w - 1, w, w + 1, w + 3}):
        for op in ["<<", ">>", ">>>"]:
            cases.append(("shift", f"{v} {op} {k} != {v}"))
            cases.append(("shift", f"{v} {op} {k} < 0"))
# division, divisors that can be 0
for a in ["it", "ui", "ch", "q", "sw", "ig"]:
    for b in ["it", "ui", "uch", "q", "sw", "ig"]:
        cases.append(("division", f"{a} / {b} == 0"))
        cases.append(("division", f"{a} / {b} < 0"))
# arithmetic with x/z, then a bitwise operator, as a condition
cases += [("xz", e) for e in [
    "(q + w) ^ 8'b1000_0000", "(q - 1) | 4'b0001", "(sq * 2) & 4'b1000", "(w + 1) ^ w",
    "(ig + 1) | 32'd1", "(tm - 1) ^ 64'd1", "~(q + 4'd0)", "(q + r_unused) == 0"]]
cases = [c for c in cases if "r_unused" not in c[1]]
# literals: values and the text they print
cases += [("literal", e) for e in [
    "q !== 4'b0x01", "q === 4'bz101", "q !== 4'bx", "sw == 8'sd5", "sw == -8'sd3", "sw < 8'sb1111_1111",
    "sq + 4'sd7 < 0", "it == 0x1F", "q == 0b101", "uli < 18446744073709551615ull", "w == 8'hF0",
    "ig < 32'sd0", "tm > 64'd5", "ig === 32'bx"]]
cases = list(dict.fromkeys(cases))


def sv_value(name, v):
    k, sg, w = INFO[name]
    if k == "c":
        return str(v) if v >= 0 else f"-{-v}"
    return f"{w}'b{v}"


def csv_value(name, v):
    return str(v)


# C-style literals are not SystemVerilog: HARM types them as unsigned, 4 bits per hex digit, 1 per
# binary digit, 64 bits with 'ull' (PropositionParserHandler::exitInt_constant)
C_LITERALS = {"0x1F": "8'h1F", "0b101": "3'b101", "18446744073709551615ull": "64'hFFFF_FFFF_FFFF_FFFF"}


# precedence classes, lowest first (IEEE 1800-2017 Table 11-2)
LEVELS = [{"||"}, {"&&"}, {"|"}, {"^"}, {"&"}, {"==", "!=", "===", "!=="}, {"<", "<=", ">", ">="}]


def top_comparison(e):
    """(L, R) when the operator at the top of e (bracket depth 0, lowest precedence, the last one
    of its level: operators are left-associative) is ==, !=, <, <=, > or >=; else None"""
    toks = [m for m in re.finditer(
        r"===|!==|==|!=|<<<|>>>|<<|>>|<=|>=|&&|\|\||[<>&|^(){}]", e)]
    depth, top = 0, {}
    for m in toks:
        t = m.group(0)
        if t in "({":
            depth += 1
        elif t in ")}":
            depth -= 1
        elif depth == 0:
            for lvl, ops in enumerate(LEVELS):
                if t in ops:
                    top[lvl] = m
    if not top:
        return None
    m = top[min(top)]
    if m.group(0) not in ("==", "!=", "<", "<=", ">", ">="):
        return None
    return e[:m.start()].strip(), e[m.end():].strip()


def svtext(e):
    for c, sv in C_LITERALS.items():
        e = e.replace(c, sv)
    # HARM's x/z rule (D-011): a comparison with an x or z bit in an operand is false (SystemVerilog
    # gives x, or a definite value when known bits already decide it, IEEE 1800-2017 11.4.5)
    lr = top_comparison(e)
    if lr is not None:
        # '(^(v)) === 1'bx': v has an x or z bit. Not $isunknown: Icarus 12 gets it wrong on some
        # 2-state sums ($isunknown(ch + ch) is 1 for a byte ch = -111; checked 2026-10-09)
        return f"((^({lr[0]})) !== 1'bx) && ((^({lr[1]})) !== 1'bx) && ({e})"
    return e


here = Path(__file__).resolve().parent / "fixture_h19"
here.mkdir(exist_ok=True)
(here / "trace.csv").write_text(",".join(f"{t} {n}" for n, t, *_ in VARS) + "\n" +
                                "\n".join(",".join(csv_value(n, v) for (n, *_), v in zip(VARS, r)) for r in rows) + "\n")

decl = "\n".join(f"  {sv} {n};" for n, _, sv, *_ in VARS)
body = []
for r in rows:
    body.append("    " + " ".join(f"{n} = {sv_value(n, v)};" for (n, *_), v in zip(VARS, r)))
    body.append('    $write("R");')
    # an if statement: an x or z condition is false (a ?: would merge both branches into x)
    body += [f'    if ({svtext(e)}) $write("1"); else $write("0");' for _, e in cases]
    body.append('    $display("");')
with tempfile.TemporaryDirectory() as d:
    sv = Path(d) / "t.sv"
    sv.write_text("module t;\n" + decl + "\n  initial begin\n" + "\n".join(body) + "\n  end\nendmodule\n")
    subprocess.run(["iverilog", "-g2012", "-o", f"{d}/t.vvp", str(sv)], check=True)
    out = subprocess.run(["vvp", "-n", f"{d}/t.vvp"], capture_output=True, text=True, check=True).stdout
lines = [l[1:] for l in out.splitlines() if l.startswith("R")]
assert len(lines) == ROWS


def c_division_by_zero(e, row):
    """Q3 (a): a C-integer division by zero gives 0; the expression's value with that quotient"""
    m = re.fullmatch(r"(\w+) / (\w+) (==|<) 0", e)
    if not m or INFO[m.group(2)][0] != "c" or INFO[m.group(1)][0] != "c":
        return None
    if row[[n for n, *_ in VARS].index(m.group(2))] != 0:
        return None
    return "1" if m.group(3) == "==" else "0"


expected = []
for i, (cat, e) in enumerate(cases):
    vals = []
    for t, r in enumerate(rows):
        hand = c_division_by_zero(e, r)
        vals.append(hand if hand is not None else lines[t][i])
    expected.append("".join(vals))
(here / "cases.txt").write_text("".join(f"ok|{cat}|{v}|{e}\n" for (cat, e), v in zip(cases, expected)))
ver = subprocess.run(["iverilog", "-V"], capture_output=True, text=True).stdout.splitlines()[0]
(here / "meta.txt").write_text(f"seed=19 rows={ROWS} cases={len(cases)}\n{ver}\n")
print(f"{len(cases)} cases")
