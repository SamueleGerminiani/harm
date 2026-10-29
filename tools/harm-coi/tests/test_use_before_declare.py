"""H39 (the miner portfolio's HX1 part F): harm-coi elaborates a design that uses a signal before declaring it, as
Verilator and trivergence's simulator accept (AssertLLM2's sdspi: "identifier 'pre_rsp_state' used before its
declaration")."""

from harm_coi import frontend

SRC = """module top(input logic clk, a, output logic y);
  always_ff @(posedge clk) if (late) y <= a;
  logic late;
  assign late = a;
endmodule
"""


def test_use_before_declare_elaborates(tmp_path):
    (tmp_path / "top.v").write_text(SRC)
    comp, top, _ = frontend.elaborate("top", [str(tmp_path / "top.v")])
    assert top.name == "top"
