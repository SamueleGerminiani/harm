#!/usr/bin/env python3
"""H18 audit: HARM's proposition operators against Icarus Verilog (SystemVerilog), 2-valued values.
Usage: audit.py <harm> <outdir>"""
import json, random, subprocess, sys
from pathlib import Path

harm, out = str(Path(sys.argv[1]).resolve()), Path(sys.argv[2]).resolve(); out.mkdir(exist_ok=True)
rng = random.Random(7)
ROWS = 40
# name, HARM CSV type, SV type, value generator
VARS = [
    ("a", "bool", "bit", lambda: rng.randint(0, 1)),
    ("b", "bool", "bit", lambda: rng.randint(0, 1)),
    ("x", "int", "int", lambda: rng.randint(-9, 9)),
    ("y", "int", "int", lambda: rng.randint(-9, 9)),
    ("z", "int", "int", lambda: rng.choice([1, 2, 3, -2, 5])),          # never 0 (divisor)
    ("u", "unsigned int", "int unsigned", lambda: rng.randint(0, 9)),
    ("n", "unsigned int", "int unsigned", lambda: rng.randint(1, 9)),   # never 0
    ("q", "logic [3:0]", "logic [3:0]", lambda: rng.randint(0, 15)),
    ("r", "logic [3:0]", "logic [3:0]", lambda: rng.randint(0, 15)),
    ("w", "logic [7:0]", "logic [7:0]", lambda: rng.randint(0, 255)),
    ("s", "logic signed [3:0]", "logic signed [3:0]", lambda: rng.randint(-8, 7)),
    ("f", "float", "real", lambda: rng.choice([0.0, 0.5, 1.0, 2.5, -1.5, 3.0])),
    ("g", "float", "real", lambda: rng.choice([0.0, 1.0, 2.0, -2.0, 0.25])),
]
rows = [[gen() for _, _, _, gen in VARS] for _ in range(ROWS)]

BIN = ["*", "/", "+", "-", "<<", ">>", "&", "^", "|", "<", "<=", ">", ">=", "==", "!=", "&&", "||"]
SVPREC = {"*": 10, "/": 10, "+": 9, "-": 9, "<<": 8, ">>": 8, "<": 7, "<=": 7, ">": 7, ">=": 7,
          "==": 6, "!=": 6, "&": 5, "^": 4, "|": 3, "&&": 2, "||": 1}
cases = []  # (category, expression, bracketed SV reading or None)

# precedence: A op1 B op2 C on ints (divisors never 0)
for o1 in BIN:
    for o2 in BIN:
        A, B, C = "x", ("z" if o1 == "/" else "y"), ("z" if o2 == "/" else "u" if o2 in ("<<", ">>") else "y")
        if o1 in ("<<", ">>"):
            B = "u"
        if o2 == "/" and SVPREC[o1] < SVPREC[o2]:
            pass
        e = f"{A} {o1} {B} {o2} {C}"
        left = SVPREC[o1] >= SVPREC[o2]  # left-assoc at equal level
        br = f"({A} {o1} {B}) {o2} {C}" if left else f"{A} {o1} ({B} {o2} {C})"
        if o1 == "/" and not left:      # x / (y op z) may divide by 0: use n
            continue
        cases.append(("prec", e, br))
# prefix operators before each binary operator
for un in ["!", "~", "-"]:
    for o in BIN:
        C = "z" if o == "/" else ("u" if o in ("<<", ">>") else "y")
        cases.append(("prefix", f"{un}x {o} {C}", f"({un}x) {o} {C}"))
        cases.append(("prefix", f"{un}q {o} r" if o not in ("/",) else f"{un}q {o} n", None))
cases += [("prefix", e, None) for e in ["!!x", "~~x", "-(-x)", "!~x", "~!x", "!-x", "-!x", "!a", "!a && b", "!a == b", "!x && y"]]
# conversions: each operator on each pair of operand types
TYPED = {"bool": "a", "int": "x", "uint": "u", "logic4": "q", "logic8": "w", "slogic4": "s", "float": "f"}
for o in BIN:
    for t1, v1 in TYPED.items():
        for t2, v2 in TYPED.items():
            if o in ("&", "^", "|", "<<", ">>") and "float" in (t1, t2):
                continue  # illegal on real in SV
            if o == "/":
                v2 = {"int": "z", "uint": "n"}.get(t2, None) if t2 != "float" else "g"
                if v2 is None or t2 == "float":
                    continue
            cases.append((f"conv {t1} {o} {t2}", f"{v1} {o} {v2}", None))
# Boolean-versus-number comparisons, ternary, context width
cases += [("boolnum", e, None) for e in ["(x > 0) == y", "(x > 0) != y", "(!x) == y", "a == x", "a < y", "(x > 0) + 1 == 2", "a + a == 2", "(q == r) == u"]]
cases += [("width", e, None) for e in ["q + r == 5'd16", "q + r > 4'd15", "q << 1 == 5'd16", "~q == 0", "~q == 4'd0", "q - r < 0", "w + w > 8'd255", "-q == -1"]]
cases += [("ternary", e, None) for e in ["a ? x : y == 1", "a ? x > 0 : y > 0", "x > 0 ? q : r == 3"]]

# ---- HARM: one context per expression
def esc(s): return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
hdr = ",".join(f"{t} {n}" for n, t, _, _ in VARS)
import re as _re
def fmt(t, v):
    m = _re.search(r"\[(\d+):0\]", t)
    if t.startswith("logic"):
        w = int(m.group(1)) + 1
        return format(v & ((1 << w) - 1), f"0{w}b")
    return str(v)
(out / "trace.csv").write_text(hdr + "\n" + "\n".join(",".join(fmt(t, v) for (_, t, _, _), v in zip(VARS, r)) for r in rows) + "\n")
exprs = []
for cat, e, br in cases:
    exprs.append(e)
    if br: exprs.append(br)
exprs = list(dict.fromkeys(exprs))
from concurrent.futures import ThreadPoolExecutor
import tempfile
def run_one(i_e):
    i, e = i_e
    d = out / f"h{i}"
    d.mkdir(exist_ok=True)
    (d / "c.xml").write_text(f'<harm><context name="e"><prop exp="{esc(e)}" loc="a"/></context></harm>')
    r = subprocess.run([harm, "--csv", str(out / "trace.csv"), "--conf", str(d / "c.xml"),
                        "--dump-prop-table", str(d / "t.json")], capture_output=True, text=True, cwd=d)
    if r.returncode != 0 or not (d / "t.json").exists():
        msg = _re.sub(r"\x1b\[[0-9;]*m", "", r.stdout + r.stderr)
        m = _re.findall(r"Message: (.*)", msg)
        return e, (None, "ERROR: " + (m[-1] if m else msg[-200:]))
    ps = json.loads((d / "t.json").read_text())["contexts"][0]["propositions"]
    return e, ((ps[0]["values"], ps[0]["text"]) if ps else (None, "ERROR: no proposition"))
with ThreadPoolExecutor(8) as ex:
    H = dict(ex.map(run_one, enumerate(exprs)))

# ---- iverilog
# SystemVerilog's unary operand is a primary: '!!x' is written '!(!x)' (HARM accepts both)
def svtext(e):
    return _re.sub(r"^([!~-])([!~-])x$", r"\1(\2x)", e)
decl = "\n".join(f"  {sv} {n};" for n, _, sv, _ in VARS)
body = []
for r_ in rows:
    body.append("    " + " ".join(f"{n} = {v if not isinstance(v, int) or v >= 0 else '-' + str(-v)};" for (n, _, _, _), v in zip(VARS, r_)))
    body.append('    $write("R");')
    for e in exprs:
        body.append(f'    $write("%0d", (({svtext(e)}) ? 1 : 0));')
    body.append('    $display("");')
(out / "t.sv").write_text("module t;\n" + decl + "\n  initial begin\n" + "\n".join(body) + "\n  end\nendmodule\n")
c = subprocess.run(["iverilog", "-g2012", "-o", str(out / "t.vvp"), str(out / "t.sv")], capture_output=True, text=True)
ok_sv = c.returncode == 0
if not ok_sv:
    print("iverilog compile errors:\n" + c.stderr[:3000])
lines = [l[1:] for l in subprocess.run(["vvp", "-n", str(out / "t.vvp")], capture_output=True, text=True).stdout.splitlines() if l.startswith("R")]
SV = {e: "".join(l[i] for l in lines) for i, e in enumerate(exprs)} if ok_sv else {}

res = []
for cat, e, br in cases:
    hv, ht = H[e]
    sv = SV.get(e)
    entry = {"cat": cat, "exp": e, "harm_text": ht, "harm": hv, "sv": sv}
    if br:
        entry["br_harm"] = H[br][0]
    res.append(entry)
(out / "results.json").write_text(json.dumps(res, indent=1))
bad = [x for x in res if x["harm"] != x["sv"]]
print(f"{len(res)} cases, {len(bad)} differ (or HARM rejects)")
