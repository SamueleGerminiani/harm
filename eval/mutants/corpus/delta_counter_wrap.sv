// H45-mutant-eval: common_cells delta_counter, 6 bits, sticky overflow
// HL1 RQ3 amendment: the depth comes from `H45_WIDTH` (default 6, the base entry)
`ifndef H45_WIDTH
`define H45_WIDTH 6
`endif
module h45_delta_counter (
  input  logic       clk_i, rst_ni, clear_i, en_i, load_i, down_i,
  input  logic [`H45_WIDTH-1:0] delta_i, d_i,
  output logic [`H45_WIDTH-1:0] q_o,
  output logic       overflow_o
);
  delta_counter #(.WIDTH(`H45_WIDTH), .STICKY_OVERFLOW(1'b1)) i_cnt (
    .clk_i, .rst_ni, .clear_i, .en_i, .load_i, .down_i, .delta_i, .d_i, .q_o, .overflow_o);
endmodule
