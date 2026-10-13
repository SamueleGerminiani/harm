"""H25 test S1 (D-039): signed RTL comparisons, negative constants and sign extensions. A trace carries no signedness
(HARM reads every VCD vector as unsigned), so harm-coi writes a signed operand as `$signed(x)` (HARM's
`$signed`/`$unsigned`, H25) and a signed constant as `w'sdN` / `-w'sdN`. Each expected line is written by hand from the
RTL in the test (SystemVerilog, IEEE 1800-2017 11.8.1: an expression is signed only if all its operands are)."""
import textwrap

from harm_coi import cli

from test_relations import emit

SAT = """
    module m(input logic clk, rst, en, input logic signed [7:0] x, output logic signed [11:0] acc, output logic big,
             output logic signed [12:0] h, output logic [12:0] u);
      logic signed [12:0] sum;
      assign sum = acc + x;
      assign big = sum > 13'sd2047;
      assign h = sum >>> 2;
      assign u = $unsigned(sum) >> 1;
      always_ff @(posedge clk)
        if (rst) acc <= -12'sd3;
        else if (en) begin
          if (sum > 13'sd2047) acc <= 12'sd2047;
          else if (sum < -13'sd2047) acc <= -12'sd2047;
          else if (sum > 13'd5) acc <= 12'sd5;
          else if (sum < -5000) acc <= 12'sd0;
          else acc <= sum[11:0];
        end
    endmodule
"""


def test_signed_comparisons(tmp_path):
    props, _, _ = emit(tmp_path, SAT, "--reset", "rst")
    assert "$signed(sum) > 13'sd2047" in props          # was sum > 13'd2047 (true for every negative sum)
    assert "$signed(sum) < -13'sd2047" in props         # was dropped: a negative constant
    assert "sum > 13'd2047" not in props
    assert "sum > 13'd5" in props                       # 13'd5 is unsigned: the comparison is unsigned, as written
    assert not any("5000" in p for p in props)          # always true for a 13-bit signed sum: dropped, as before


def test_negative_reset_value(tmp_path):
    props, _, _ = emit(tmp_path, SAT, "--reset", "rst")
    assert "$signed(acc) == -12'sd3" in props           # was dropped


def test_sign_extension_relation(tmp_path):
    props, _, _ = emit(tmp_path, SAT, "--reset", "rst")
    # acc (12 bits) and x (8 bits) are sign-extended to the 13 bits of the signed sum; each extension is a function's
    # argument, self-determined, so the relation's unsigned mask does not turn it into a zero extension (11.8.2)
    assert props["sum == (($unsigned($signed(acc) + 13'sd0) + $unsigned($signed(x) + 13'sd0)) & 13'd8191)"] == ["c", "5"]


def test_signed_comparison_and_arithmetic_shift_relations(tmp_path):
    props, _, _ = emit(tmp_path, SAT, "--reset", "rst")
    assert props["big == ($signed(sum) > 13'sd2047)"] == ["c", "5"]
    assert props["h == $unsigned($signed(sum) >>> 2)"] == ["c", "5"]  # self-determined: arithmetic in any context
    assert props["u == (sum >> 1)"] == ["c", "5"]       # $unsigned: a logical shift, as before


def test_unsigned_design_unchanged(tmp_path):
    props, _, _ = emit(tmp_path, """
        module m(input logic clk, rst, input logic [7:0] a, b, output logic [8:0] s, output logic gt);
          assign s = a + b;
          assign gt = a > 8'd100;
          logic [8:0] s2;
          always_ff @(posedge clk) if (rst) s2 <= 9'd0; else s2 <= s;
        endmodule
    """, "--reset", "rst")
    assert not any("$signed" in p or "'sd" in p for p in props)


def test_no_signed_without_relations(tmp_path):
    # predicates are written signed with or without relations (the meaning of the RTL's condition)
    props, _, _ = emit(tmp_path, SAT, "--reset", "rst", relations=False)
    assert "$signed(sum) > 13'sd2047" in props and "$signed(sum) < -13'sd2047" in props
    assert not any(p.startswith("sum ==") for p in props)


def test_no_hints_predicates_signed(tmp_path):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(SAT))
    assert cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut", "--vcd-recursion", "0",
                     "--clock", "clk", "--emit-config", str(tmp_path / "c.xml"), "-o", str(tmp_path / "coi.json")]) == 0
    xml = (tmp_path / "c.xml").read_text()
    assert "$signed(sum) &gt; 13'sd2047" in xml
