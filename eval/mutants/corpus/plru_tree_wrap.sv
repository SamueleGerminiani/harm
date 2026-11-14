// H45-mutant-eval: common_cells plru_tree, 8 entries
module h45_plru_tree (
  input  logic       clk_i, rst_ni,
  input  logic [7:0] used_i,
  output logic [7:0] plru_o
);
  plru_tree #(.ENTRIES(8)) i_plru (.clk_i, .rst_ni, .used_i, .plru_o);
endmodule
