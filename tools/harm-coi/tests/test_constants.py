"""H26 test C1 (D-040): constants assigned outside a reset branch. A constant `c` assigned to a whole signal `x` under a
condition gives the consequent `x == c` (H25's form for a negative constant of a signed target), placed as a relation:
registered in the single-cycle `|=>` tree (domain 7), combinational in the `|->` tree (domain 6). A constant signal
(`assign k = 4'd3`) gives nothing; a proposition harm-coi already writes gains the placement; a target with more than 8
distinct constants (a lookup table) gets none. Each expected line is written by hand from the RTL in the test."""
import re

from test_relations import emit

RTL = """
    module m(input logic clk, rst, en, sel, input logic signed [12:0] sum, input logic [3:0] i,
             output logic signed [11:0] acc, output logic [3:0] mode, tab, k, output logic [7:0] y);
      assign k = 4'd3;
      always_comb
        if (sel) y = 8'd5;
        else y = 8'd9;
      always_ff @(posedge clk)
        if (rst) begin acc <= 12'sd0; mode <= 4'd0; end
        else if (en) begin
          if (sum > 13'sd2047) acc <= 12'sd2047;
          else if (sum < -13'sd2047) acc <= -12'sd2047;
          else acc <= sum[11:0];
          if (sum == 13'sd0) mode <= 4'd0;
          else mode <= 4'd2;
        end
      always_ff @(posedge clk)
        case (i)
          4'd0: tab <= 4'd1;  4'd1: tab <= 4'd2;  4'd2: tab <= 4'd3;  4'd3: tab <= 4'd4;  4'd4: tab <= 4'd5;
          4'd5: tab <= 4'd6;  4'd6: tab <= 4'd7;  4'd7: tab <= 4'd8;  default: tab <= 4'd9;
        endcase
    endmodule
"""


def test_registered_constants(tmp_path):
    props, _, _ = emit(tmp_path, RTL, "--reset", "rst")
    assert props["acc == 12'd2047"] == ["c", "7"]
    assert props["$signed(acc) == -12'sd2047"] == ["c", "7"]  # H25's form: a negative constant of a signed target
    assert props["mode == 4'd2"] == ["c", "7"]


def test_combinational_constants(tmp_path):
    props, _, _ = emit(tmp_path, RTL, "--reset", "rst")
    assert props["y == 8'd5"] == ["c", "6"] and props["y == 8'd9"] == ["c", "6"]


def test_constant_signal_gives_nothing(tmp_path):
    props, _, _ = emit(tmp_path, RTL, "--reset", "rst")
    assert not any(p.startswith("k ==") for p in props)


def test_existing_proposition_gains_the_placement(tmp_path):
    props, _, _ = emit(tmp_path, RTL, "--reset", "rst")
    assert "7" in props["mode == 4'd0"] and "3" in props["mode == 4'd0"]  # the reset value, also a consequent of 7
    xml = (tmp_path / "cfg.xml").read_text()
    assert len(re.findall(r'<prop exp="mode == 4\'d0"', xml)) == 1


def test_lookup_table_capped(tmp_path, capsys):
    props, _, _ = emit(tmp_path, RTL, "--reset", "rst", "-v")
    assert not any(p.startswith("tab ==") for p in props)
    assert "more than 8 distinct constants" in capsys.readouterr().err


def test_no_relations_no_constants(tmp_path):
    props, _, _ = emit(tmp_path, RTL, "--reset", "rst", relations=False)
    assert "acc == 12'd2047" not in props and "y == 8'd5" not in props and "mode == 4'd2" not in props
