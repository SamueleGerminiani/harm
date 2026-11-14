// H45-mutant-eval: common_cells credit_counter, 4 credits, full at reset
// HL1 RQ3 amendment: the depth comes from `H45_NUMCREDITS` (default 4, the base entry)
`ifndef H45_NUMCREDITS
`define H45_NUMCREDITS 4
`endif
module h45_credit_counter (
  input  logic       clk_i, rst_ni, credit_give_i, credit_take_i, credit_init_i,
  output logic [$clog2(`H45_NUMCREDITS):0] credit_o,
  output logic       credit_left_o, credit_crit_o, credit_full_o
);
  credit_counter #(.NumCredits(`H45_NUMCREDITS), .InitCreditEmpty(1'b0)) i_cc (
    .clk_i, .rst_ni, .credit_o, .credit_give_i, .credit_take_i, .credit_init_i, .credit_left_o, .credit_crit_o,
    .credit_full_o);
endmodule
