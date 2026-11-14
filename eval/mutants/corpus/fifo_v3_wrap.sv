// H45-mutant-eval: common_cells fifo_v3 with fixed parameters (8-bit data, depth 4)
// HL1 RQ3 amendment: the depth comes from `H45_DEPTH` (default 4, the base entry)
`ifndef H45_DEPTH
`define H45_DEPTH 4
`endif
module h45_fifo_v3 (
  input  logic       clk_i, rst_ni, flush_i, push_i, pop_i,
  input  logic [7:0] data_i,
  output logic       full_o, empty_o,
  output logic [$clog2(`H45_DEPTH)-1:0] usage_o,
  output logic [7:0] data_o
);
  fifo_v3 #(.FALL_THROUGH(1'b0), .DATA_WIDTH(8), .DEPTH(`H45_DEPTH)) i_fifo (
    .clk_i, .rst_ni, .flush_i, .testmode_i(1'b0), .full_o, .empty_o, .usage_o, .data_i, .push_i, .data_o, .pop_i);
endmodule
