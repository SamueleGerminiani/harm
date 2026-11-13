// H45-mutant-eval: common_cells credit_counter, 4 credits, full at reset
module h45_credit_counter (
  input  logic       clk_i, rst_ni, credit_give_i, credit_take_i, credit_init_i,
  output logic [2:0] credit_o,
  output logic       credit_left_o, credit_crit_o, credit_full_o
);
  credit_counter #(.NumCredits(4), .InitCreditEmpty(1'b0)) i_cc (
    .clk_i, .rst_ni, .credit_o, .credit_give_i, .credit_take_i, .credit_init_i, .credit_left_o, .credit_crit_o,
    .credit_full_o);
endmodule
