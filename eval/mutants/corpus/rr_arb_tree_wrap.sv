// H45-mutant-eval: common_cells rr_arb_tree, 4 inputs of 8-bit data, fair round robin
module h45_rr_arb_tree (
  input  logic            clk_i, rst_ni, flush_i, gnt_i,
  input  logic [3:0]      req_i,
  input  logic [3:0][7:0] data_i,
  output logic [3:0]      gnt_o,
  output logic            req_o,
  output logic [7:0]      data_o,
  output logic [1:0]      idx_o
);
  rr_arb_tree #(.NumIn(4), .DataWidth(8), .ExtPrio(1'b0), .AxiVldRdy(1'b0), .LockIn(1'b0), .FairArb(1'b1)) i_arb (
    .clk_i, .rst_ni, .flush_i, .rr_i(2'd0), .req_i, .gnt_o, .data_i, .req_o, .gnt_i, .data_o, .idx_o);
endmodule
