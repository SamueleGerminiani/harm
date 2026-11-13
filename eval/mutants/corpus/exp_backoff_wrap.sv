// H45-mutant-eval: common_cells exp_backoff, maximum exponent 6
// HL1 RQ3 amendment: the depth comes from `H45_MAXEXP` (default 6, the base entry)
`ifndef H45_MAXEXP
`define H45_MAXEXP 6
`endif
module h45_exp_backoff (
  input  logic clk_i, rst_ni, set_i, clr_i,
  output logic is_zero_o
);
  exp_backoff #(.Seed(16'hffff), .MaxExp(`H45_MAXEXP)) i_bo (.clk_i, .rst_ni, .set_i, .clr_i, .is_zero_o);
endmodule
