#!/usr/bin/env python3
"""Generate the H25 evaluation fixture: HARM's `$signed(e)` and `$unsigned(e)` against SystemVerilog.

Writes, into tests/oracle/fixture_h25/:
  trace.csv  H19's trace (tests/oracle/fixture_h19/trace.csv), copied: C integer types, signed and unsigned logic of
             several widths, integer and time, with x/z bits in the 4-state variables
  cases.txt  one line per expression: ok|<category>|<expected value per row>|<expression>
  meta.txt   generator parameters and the Icarus Verilog version

Expected values: Icarus Verilog 12 (IEEE 1800-2017 20.5: `$signed`/`$unsigned` return their argument's bits with the
sign changed, the width unchanged; 11.8.1: an expression is signed only if all its operands are), mapped to HARM's
truth value as H19's fixture does (an `if`, and D-011 for a comparison at the top: false with an x or z operand bit).

The fixture is committed; regenerate only with approval:
  python3 tests/oracle/gen_h25_fixture.py
"""
import shutil
import subprocess
import tempfile
from pathlib import Path

ORACLE = Path(__file__).resolve().parent

# H19's variables: name, HARM CSV type, SystemVerilog type, kind, signed, width (the generators are not needed)
VARS = [
    ("ch", "char", "byte", "c", True, 8), ("sh", "short", "shortint", "c", True, 16),
    ("it", "int", "int", "c", True, 32), ("li", "long int", "longint", "c", True, 64),
    ("uch", "unsigned char", "byte unsigned", "c", False, 8), ("ush", "unsigned short", "shortint unsigned", "c", False, 16),
    ("ui", "unsigned int", "int unsigned", "c", False, 32), ("iu", "int unsigned", "int unsigned", "c", False, 32),
    ("uli", "unsigned long int", "longint unsigned", "c", False, 64),
    ("q", "logic [3:0]", "logic [3:0]", "l", False, 4), ("w", "logic [7:0]", "logic [7:0]", "l", False, 8),
    ("sq", "logic signed [3:0]", "logic signed [3:0]", "l", True, 4),
    ("sw", "logic signed [7:0]", "logic signed [7:0]", "l", True, 8),
    ("ig", "integer", "integer", "l", True, 32), ("tm", "time", "time", "l", False, 64),
    ("am", "logic [3:0]", "logic [3:0]", "l", False, 4),
]
INFO = {n: (k, sg, w) for n, _, _, k, sg, w in VARS}

src = (ORACLE / "fixture_h19" / "trace.csv").read_text().splitlines()
header = [h.rsplit(" ", 1)[1] for h in src[0].split(",")]
assert header == [n for n, *_ in VARS], header
rows = [r.split(",") for r in src[1:] if r]

cases = []
# the cast alone: its sign decides a comparison with 0 and a signed constant
for v in ["q", "w", "sq", "sw", "ig", "tm", "ch", "uch", "it", "ui"]:
    w = INFO[v][2]
    for f in ["$signed", "$unsigned"]:
        cases.append(("cast", f"{f}({v}) < 0"))
        cases.append(("cast", f"{f}({v}) > 1"))
        cases.append(("cast", f"{f}({v}) == {v}"))
        cases.append(("cast", f"{f}({v}) >>> 1 < 0"))
        cases.append(("cast", f"{f}({v}) + {v} < 0"))
    cases.append(("cast", f"$signed({v}) < -{w}'sd3"))
    cases.append(("cast", f"$signed({v}) > {w}'sd5"))
    cases.append(("cast", f"$signed({v}) == -{w}'sd1"))
    cases.append(("cast", f"$signed({v}) > {w}'d5"))          # an unsigned constant: the comparison is unsigned
# sign extension in a wider signed context, as harm-coi writes it (`$signed(x) + w'sd0`)
cases += [("extension", e) for e in [
    "($signed(w) + 13'sd0) < 0", "($signed(q) + 8'sd0) == -8'sd1", "($signed(w) + 13'sd0) + ($signed(q) + 13'sd0) < 0",
    "(($signed(w) + 13'sd0) + ($signed(q) + 13'sd0) & 13'd8191) > 13'd4000", "$signed(w) + $signed(q) < 0",
    "$signed(q) + sw < 0", "$signed(w) * $signed(q) < 0", "$signed(w) - 8'sd1 < 0", "-$signed(w) < 0"]]
# nested casts, selects, concatenations, ternaries, shifts by variable amounts. The ternary's condition is 2-valued:
# with an x condition HARM takes the else branch (the condition is a proposition, D-011) where SystemVerilog merges
# the branches; that is not H25's (found while writing S2)
cases += [("nested", e) for e in [
    "$signed($unsigned(sw)) < 0", "$unsigned($signed(w)) > 8'd127", "$signed(w[7:4]) < 0", "$signed(w[3:0]) == sq",
    "$signed({q, q}) < 0", "$signed(w) >>> am < 0", "$signed(w) >> am < 0", "$unsigned(sw) >>> am > 8'd60",
    "(uch > 8'd10 ? $signed(q) : sq) < 0", "$signed(w & 8'd240) < 0", "$signed(w) < $signed(q)", "$signed(w) < q",
    "$signed(tm) < 0", "$unsigned(ig) > 32'd100"]]
cases = list(dict.fromkeys(cases))

h19 = (ORACLE / "gen_h19_fixture.py").read_text()
ns = {"re": __import__("re")}
exec(h19[h19.index("# precedence classes"):h19.index("here = Path")], ns)  # top_comparison, svtext (D-011)
ns["C_LITERALS"] = {}


def sv_value(name, v):
    k, sg, w = INFO[name]
    if k == "c":
        return v
    return f"{w}'b{v}"


here = ORACLE / "fixture_h25"
here.mkdir(exist_ok=True)
shutil.copy(ORACLE / "fixture_h19" / "trace.csv", here / "trace.csv")
decl = "\n".join(f"  {sv} {n};" for n, _, sv, *_ in VARS)
body = []
for r in rows:
    body.append("    " + " ".join(f"{n} = {sv_value(n, v)};" for (n, *_), v in zip(VARS, r)))
    body.append('    $write("R");')
    body += [f'    if ({ns["svtext"](e)}) $write("1"); else $write("0");' for _, e in cases]
    body.append('    $display("");')
with tempfile.TemporaryDirectory() as d:
    sv = Path(d) / "t.sv"
    sv.write_text("module t;\n" + decl + "\n  initial begin\n" + "\n".join(body) + "\n  end\nendmodule\n")
    subprocess.run(["iverilog", "-g2012", "-o", f"{d}/t.vvp", str(sv)], check=True)
    out = subprocess.run(["vvp", "-n", f"{d}/t.vvp"], capture_output=True, text=True, check=True).stdout
lines = [l[1:] for l in out.splitlines() if l.startswith("R")]
assert len(lines) == len(rows)
expected = ["".join(lines[t][i] for t in range(len(rows))) for i in range(len(cases))]
(here / "cases.txt").write_text("".join(f"ok|{cat}|{v}|{e}\n" for (cat, e), v in zip(cases, expected)))
ver = subprocess.run(["iverilog", "-V"], capture_output=True, text=True).stdout.splitlines()[0]
(here / "meta.txt").write_text(f"rows={len(rows)} (H19's trace) cases={len(cases)}\n{ver}\n")
print(f"{len(cases)} cases")
