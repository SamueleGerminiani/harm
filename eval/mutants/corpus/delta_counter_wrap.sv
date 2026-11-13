// H45-mutant-eval: common_cells delta_counter, 6 bits, sticky overflow
module h45_delta_counter (
  input  logic       clk_i, rst_ni, clear_i, en_i, load_i, down_i,
  input  logic [5:0] delta_i, d_i,
  output logic [5:0] q_o,
  output logic       overflow_o
);
  delta_counter #(.WIDTH(6), .STICKY_OVERFLOW(1'b1)) i_cnt (
    .clk_i, .rst_ni, .clear_i, .en_i, .load_i, .down_i, .delta_i, .d_i, .q_o, .overflow_o);
endmodule
