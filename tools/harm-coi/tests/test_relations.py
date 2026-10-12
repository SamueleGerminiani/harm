"""H24 tests R1–R3 and Q6 (D-038): `--relations`. Each expected line of the emitted configuration is written by hand
from the RTL in the test:
  - a non-blocking `x <= e` (outside the reset branch) gives `x == ($past(e, 1) & M)`, a continuous or combinational
    `x = e` gives `x == (e & M)`; `M` is x's mask as a sized decimal; `e` with no arithmetic (`+ - *`, unary `-`,
    `~`, an RTL `<<`) and no wider than x is not masked; a concatenation is written with shifts and `|` (exact,
    leading zero constants dropped);
  - unconditional relations go to the fixed templates `G({!R}|=> P0(4))` / `G({!R}|-> P0(5))`, conditional ones to
    their class (`c, 2` registered, `c, 1` combinational);
  - a 1-bit reset-value predicate gets its other polarity; an assigned-only 1-bit target gets `x` and `!x`;
  - with `--reset R` the reset values are also in domain 3, with `G({$fell(R)}|-> P0(3))` (`$rose` for `!R`);
  - a register whose assignment reads it gets `<numeric exp="x - $past(x, 1)" …>`, a wide target with no
    predicate `<numeric exp="x" …>`.
"""
import re
import textwrap

import pytest

from harm_coi import cli

PROP = re.compile(r'<prop exp="([^"]*)" loc="([^"]*)"')
NUM = re.compile(r'<numeric clustering="([^"]*)" exp="([^"]*)" loc="([^"]*)"')
TPL = re.compile(r'<template [^>]*exp="([^"]*)"')
UNESC = {"&amp;": "&", "&lt;": "<", "&gt;": ">", "&quot;": '"'}


def un(s):
    for k, v in UNESC.items():
        s = s.replace(k, v)
    return s


def emit(tmp_path, sv, *extra, relations=True):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(sv))
    args = ["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut", "--vcd-recursion", "0", "--clock", "clk",
            "--emit-config", str(tmp_path / "cfg.xml"), "--hints", str(tmp_path / "hints.json"),
            "-o", str(tmp_path / "coi.json"), *extra]
    if relations:
        args.append("--relations")
    assert cli.main(args) == 0
    xml = (tmp_path / "cfg.xml").read_text()
    props = {un(e): [x.strip() for x in loc.split(",")] for e, loc in PROP.findall(xml)}
    nums = {un(e): (un(c), [x.strip() for x in loc.split(",")]) for c, e, loc in NUM.findall(xml)}
    return props, nums, [un(t) for t in TPL.findall(xml)]


REG = """
    module m(input logic clk, rst, en, input logic [7:0] a, b, output logic [7:0] y, z);
      always_ff @(posedge clk)
        if (rst) y <= 8'd0;
        else y <= a - b;
      always_ff @(posedge clk)
        if (rst) z <= 8'd0;
        else if (en) z <= a + b;
    endmodule
"""


def test_registered_relations(tmp_path):
    props, _, tpls = emit(tmp_path, REG, "--reset", "rst")
    assert props["y == ($past(a - b, 1) & 8'd255)"] == ["c", "4"]  # unconditional: the fixed template
    assert props["z == ($past(a + b, 1) & 8'd255)"] == ["c", "2"]  # under `en`: the decision tree finds it
    assert "G({!rst}|=> P0(4))" in tpls
    assert not any("8'd0" in e and "$past" in e for e in props)  # the reset branch gives no relation


def test_combinational_relations_case_arms_and_concatenation(tmp_path):
    props, _, tpls = emit(tmp_path, """
        module m(input logic clk, rst, input logic [1:0] op, input logic [7:0] a, b,
                 output logic [8:0] r, output logic [15:0] c, output logic z);
          always_comb
            case (op)
              2'd0: r = {1'b0, a} + {1'b0, b};
              2'd1: r = {a, 1'b0};
              default: r = {1'b0, b};
            endcase
          assign c = {a, b};
          assign z = (a == b);
        endmodule
    """, "--reset", "rst")
    assert props["r == ((a + b) & 9'd511)"] == ["c", "1"]
    assert props["r == (a << 1)"] == ["c", "1"]  # a concatenation is exact: no mask when it fits
    assert props["r == b"] == ["c", "1"]
    assert props["c == ((a << 8) | b)"] == ["c", "5"]
    assert props["z == (a == b)"] == ["c", "5"]
    assert "G({!rst}|-> P0(5))" in tpls


def test_untranslatable_and_caps(tmp_path):
    arms = "\n".join(f"              4'd{i}: r = a + 8'd{i};" for i in range(10))
    props, _, _ = emit(tmp_path, f"""
        module m(input logic clk, input logic [3:0] s, input logic [7:0] a, output logic [7:0] r, q);
          always_comb
            case (s)
{arms}
              default: r = a;
            endcase
          assign q = a % 8'd3;
        endmodule
    """)
    rel = [e for e in props if e.startswith("r == ")]
    assert len(rel) == 8  # at most 8 relations per target, in source order
    assert "r == ((a + 8'd0) & 8'd255)" in props and "r == ((a + 8'd9) & 8'd255)" not in props
    assert not any(e.startswith("q == ") for e in props)  # % is not in HARM's grammar


def test_both_polarities_and_assigned_only(tmp_path):
    props, _, _ = emit(tmp_path, """
        module m(input logic clk, rst, input logic [3:0] cnt, input logic t, output logic ovf, walk);
          always_ff @(posedge clk)
            if (rst) ovf <= 1'b0;
            else ovf <= (cnt == 4'd11);
          assign walk = t && cnt[0];
        endmodule
    """, "--reset", "rst")
    assert "!ovf" in props and "ovf" in props and props["ovf"] == props["!ovf"]
    assert "walk" in props and "!walk" in props


def test_reset_end(tmp_path):
    props, _, tpls = emit(tmp_path, """
        module m(input logic clk, rst, we, input logic [7:0] d, output logic [7:0] q);
          always_ff @(posedge clk)
            if (rst) q <= 8'd10;
            else if (we) q <= d;
        endmodule
    """, "--reset", "rst")
    assert "3" in props["q == 8'd10"]
    assert "G({$fell(rst)}|-> P0(3))" in tpls


def test_active_low_reset(tmp_path):
    props, _, tpls = emit(tmp_path, """
        module m(input logic clk, rst_n, input logic [7:0] d, output logic [7:0] q);
          always_ff @(posedge clk)
            if (!rst_n) q <= 8'd10;
            else q <= d;
        endmodule
    """, "--reset", "!rst_n")
    assert "G({$rose(rst_n)}|-> P0(3))" in tpls and "G({rst_n}|=> P0(4))" in tpls
    assert props["q == $past(d, 1)"] == ["c", "4"]


def test_numerics(tmp_path):
    _, nums, _ = emit(tmp_path, """
        module m(input logic clk, rst, up, input logic [7:0] a, b, output logic [3:0] cnt, output logic [15:0] p);
          always_ff @(posedge clk)
            if (rst) cnt <= 4'd0;
            else if (up) cnt <= cnt + 4'd1;
          assign p = a * b;
        endmodule
    """, "--reset", "rst")
    assert nums["cnt - $past(cnt, 1)"] == ("C,10Max,==", ["c", "2"])  # contiguous: one proposition per value
    assert nums["p"] == ("C,10Max,==", ["c", "1"])  # no open ranges (OpenFPV, F-P9)


def test_off_by_default(tmp_path):
    props, nums, tpls = emit(tmp_path, REG, "--reset", "rst", relations=False)
    assert not any("$past" in e for e in props) and not nums
    assert not any("$fell" in t or "{!rst}" in t for t in tpls)


def test_relations_need_hints(tmp_path):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(REG))
    rc = cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut", "--vcd-recursion", "0",
                   "--clock", "clk", "--emit-config", str(tmp_path / "c.xml"), "-o", str(tmp_path / "coi.json"),
                   "--relations"])
    assert rc == 2


def test_registered_conditional_expression_keeps_parentheses(tmp_path):
    # HARM cannot parse $past(c ? a : b, 1) (D1's lfsr, 2026-10-12): the conditional stays parenthesised
    props, _, _ = emit(tmp_path, """
        module m(input logic clk, rst, load, input logic [7:0] seed, output logic [7:0] q);
          always_ff @(posedge clk)
            if (rst) q <= 8'd1;
            else if (load) q <= (seed == 8'd0) ? 8'd1 : seed;
        endmodule
    """, "--reset", "rst")
    assert props["q == $past(((seed == 8'd0) ? 8'd1 : seed), 1)"] == ["c", "2"]
