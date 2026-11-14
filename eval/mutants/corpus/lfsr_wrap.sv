// H45-mutant-eval: common_cells lfsr, 16-bit state, 8-bit output, no cipher layers
module h45_lfsr (
  input  logic       clk_i, rst_ni, en_i,
  output logic [7:0] out_o
);
  lfsr #(.LfsrWidth(16), .OutWidth(8), .RstVal(16'hACE1), .CipherLayers(0), .CipherReg(1'b0)) i_lfsr (
    .clk_i, .rst_ni, .en_i, .out_o);
endmodule
