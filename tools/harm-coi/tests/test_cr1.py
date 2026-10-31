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


def run(tmp_path, sv, extra=(), vcd=None):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(sv))
    args = ["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut", "--vcd-recursion", "0", "--clock", "clk",
            "-o", str(tmp_path / "coi.json"), *extra]
    rc = cli.main(args)
    return rc, (json.loads((tmp_path / "coi.json").read_text()) if rc == 0 else None)


# C9-3 .. C9-7 (the reviewer's tests, unchanged)
def test_deep_source_is_saturated(tmp_path):
    rc, doc = run(tmp_path, """
        module m(input logic clk, a, output logic r1, r2, r3, r4, r5, r6);
          always_ff @(posedge clk) begin r1 <= a; r2 <= r1; r3 <= r2; r4 <= r3; r5 <= r4; r6 <= r5; end
        endmodule
    """)
    assert rc == 0
    assert {"sig": "a", "depths": [], "saturated": True} in doc["targets"]["r6"]["sources"]


def test_invisible_pipeline_keeps_its_input(tmp_path):
    rc, doc = run(tmp_path, """
        module p(input logic clk, a, output logic o);
          logic r1, r2, r3, r4;
          always_ff @(posedge clk) begin r1 <= a; r2 <= r1; r3 <= r2; r4 <= r3; o <= r4; end
        endmodule
        module m(input logic clk, a, output logic o);
          p u(.clk(clk), .a(a), .o(o));
        endmodule
    """)
    assert rc == 0
    assert [s["sig"] for s in doc["targets"]["o"]["sources"]] == ["a"]


def test_truncating_cast_and_signed_constant(tmp_path):
    xml = config(tmp_path, """
        module m(input logic clk, input logic [7:0] x, input logic signed [3:0] s, output logic y, z);
          assign y = (4'(x) == 4'd3);
          assign z = (s == 15);
        endmodule
    """)
    assert "x == 8'd3" not in xml
    assert "s == 4'd15" not in xml


def test_always_ff_iff_is_unknown(tmp_path):
    rc, doc = run(tmp_path, """
        module m(input logic clk, en, d, output logic q);
          always_ff @(posedge clk iff en) q <= d;
        endmodule
    """)
    assert rc == 0 and "q" in doc["unknown"]


def test_top_inout_is_unknown(tmp_path):
    rc, doc = run(tmp_path, """
        module m(input logic clk, inout wire b, input logic oe, d, output logic q);
          assign b = oe ? d : 1'bz;
          always_ff @(posedge clk) q <= b;
        endmodule
    """)
    assert rc == 0 and "b" in doc["unknown"]


def test_relations_in_generate_for(tmp_path):
    xml = config(tmp_path, """
        module m(input logic clk, input logic [3:0] a);
          for (genvar k = 0; k < 2; k++) begin : g
            logic [3:0] r;
            always_ff @(posedge clk) r <= a;
          end
        endmodule
    """, relations=True)
    assert "g[0]::r == $past(a, 1)" in xml
