// H45-mutant-eval: common_cells fifo_v3 with fixed parameters (8-bit data, depth 4)
module h45_fifo_v3 (
  input  logic       clk_i, rst_ni, flush_i, push_i, pop_i,
  input  logic [7:0] data_i,
  output logic       full_o, empty_o,
  output logic [1:0] usage_o,
  output logic [7:0] data_o
);
  fifo_v3 #(.FALL_THROUGH(1'b0), .DATA_WIDTH(8), .DEPTH(4)) i_fifo (
    .clk_i, .rst_ni, .flush_i, .testmode_i(1'b0), .full_o, .empty_o, .usage_o, .data_i, .push_i, .data_o, .pop_i);
endmodule
