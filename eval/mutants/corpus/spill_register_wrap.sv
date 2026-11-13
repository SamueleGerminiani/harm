// H45-mutant-eval: common_cells spill_register with 8-bit data
module h45_spill_register (
  input  logic       clk_i, rst_ni, valid_i, ready_i,
  input  logic [7:0] data_i,
  output logic       ready_o, valid_o,
  output logic [7:0] data_o
);
  spill_register #(.T(logic [7:0]), .Bypass(1'b0)) i_spill (
    .clk_i, .rst_ni, .valid_i, .ready_o, .data_i, .valid_o, .ready_i, .data_o);
endmodule
