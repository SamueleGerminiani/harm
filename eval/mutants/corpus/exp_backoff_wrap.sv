// H45-mutant-eval: common_cells exp_backoff, maximum exponent 6
module h45_exp_backoff (
  input  logic clk_i, rst_ni, set_i, clr_i,
  output logic is_zero_o
);
  exp_backoff #(.Seed(16'hffff), .MaxExp(6)) i_bo (.clk_i, .rst_ni, .set_i, .clr_i, .is_zero_o);
endmodule
