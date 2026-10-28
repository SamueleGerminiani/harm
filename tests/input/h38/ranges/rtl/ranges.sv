// H38 fixture: one net declared with different ranges in two modules (H34's aliases), as AssertLLM2's pci_bridge32
// (`wire [19:19] conf_wb_am1_out` at the top, `input [31:31] addr_mask` in the decoder). The kept name is the
// top's, so a bit or range select written in the decoder's indices must be written in the top's.
module dec (
  input  logic        clk,
  input  logic [31:31] m,
  input  logic [7:4]  w,
  output logic        e,
  output logic [1:0]  f
);
  always_ff @(posedge clk) begin
    e <= m[31];
    f <= w[6:5];
  end
endmodule

module ranges (
  input  logic clk,
  input  logic [19:19] am,
  input  logic [3:0] aw,
  output logic e,
  output logic [1:0] f
);
  dec u (.clk(clk), .m(am), .w(aw), .e(e), .f(f));
endmodule
