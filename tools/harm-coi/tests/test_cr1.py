"""CR1 (miner-portfolio's correctness review): C9-1, an element select of a packed multi-dimensional array is not a
1-bit select (HARM reads the VCD's flattened vector, SystemVerilog the element); C9-2, a relation keeps the RTL's
context width: every widening operator's left operand and every shifted part of a concatenation are widened in the
text, so the width survives `$past` (whose argument is self-determined) and HARM's operand-width arithmetic."""

import json
import re
import textwrap

from harm_coi import cli


def config(tmp_path, sv, relations=False):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(sv))
    rc = cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut", "--vcd-recursion", "0", "--clock",
                   "clk", "-o", str(tmp_path / "coi.json"), "--emit-config", str(tmp_path / "e.xml"), "--hints",
                   str(tmp_path / "h.json"), "--relations" if relations else "--no-relations"])
    assert rc == 0
    return (tmp_path / "e.xml").read_text()


def relation(xml, target):
    """the emitted relation propositions of `target` (XML entities decoded)"""
    exps = [m.replace("&amp;", "&").replace("&lt;", "<").replace("&gt;", ">") for m in re.findall(r'exp="([^"]*)"', xml)]
    return [e for e in exps if e.startswith(f"{target} == ")]


def test_packed_array_element_is_not_a_bit(tmp_path):
    xml = config(tmp_path, """
        module m(input logic clk, input logic [3:0][7:0] w, output logic y);
          always_ff @(posedge clk) if (w[2]) y <= 1'b1; else y <= 1'b0;
        endmodule
    """)
    assert 'exp="w[2]"' not in xml and 'exp="!w[2]"' not in xml


def test_a_real_bit_select_still_is(tmp_path):
    xml = config(tmp_path, """
        module m(input logic clk, input logic [7:0] v, output logic y);
          always_ff @(posedge clk) if (v[2]) y <= 1'b1; else y <= 1'b0;
        endmodule
    """)
    assert 'exp="v[2]"' in xml


def test_relation_keeps_context_width(tmp_path):
    xml = config(tmp_path, """
        module m(input logic clk, input logic [3:0] a, b, output logic [4:0] sum, output logic [7:0] cat, subw);
          always_ff @(posedge clk) begin sum <= a + b; cat <= {a, b}; subw <= a - b; end
        endmodule
    """, relations=True)
    (s,), (c,), (d,) = relation(xml, "sum"), relation(xml, "cat"), relation(xml, "subw")
    assert "5'd0" in s, s
    assert "8'd0" in c, c
    assert "8'd0" in d, d
