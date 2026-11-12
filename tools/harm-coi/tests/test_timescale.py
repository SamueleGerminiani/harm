"""H28: harm-coi elaborates a design that mixes files with and without `timescale` (trivergence's F7-F2, AssertLLM2's
i2c_slave): slang's default `--timescale 1ns/1ps`, as trivergence and OpenFPV use."""

import pytest

from harm_coi import frontend

SUB = "module sub(input logic clk, a, output logic y); always_ff @(posedge clk) y <= a; endmodule\n"
TOP = "module top(input logic clk, a, output logic y); sub u(.clk(clk), .a(a), .y(y)); endmodule\n"


@pytest.mark.parametrize("scale", ["1ns/1ps", "1ps/1ps"])
def test_mixed_timescales_elaborate(tmp_path, scale):
    (tmp_path / "sub.sv").write_text(f"`timescale {scale}\n" + SUB)
    (tmp_path / "top.sv").write_text(TOP)
    comp, top, _ = frontend.elaborate("top", [str(tmp_path / "sub.sv"), str(tmp_path / "top.sv")])
    assert top.name == "top"
