// H45-mutant-eval: common_cells fall_through_register with 8-bit data
module h45_fall_through_register (
  input  logic       clk_i, rst_ni, clr_i, valid_i, ready_i,
  input  logic [7:0] data_i,
  output logic       ready_o, valid_o,
  output logic [7:0] data_o
);
  fall_through_register #(.T(logic [7:0])) i_ftr (
    .clk_i, .rst_ni, .clr_i, .testmode_i(1'b0), .valid_i, .ready_o, .data_i, .valid_o, .ready_i, .data_o);
endmodule
