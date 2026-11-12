// H38 fixture: a top port and a top-level wire that are one net (H34's aliases); the port's name sorts after the
// wire's, as in AssertLLM2's pci_bridge32 (`wire pci_resi_pci_rstn_in = pci_rst_i;`)
module ports (
  input  logic clk, rst_i, d,
  output logic o
);
  wire  a_rst = rst_i;
  logic aa_q;
  always_ff @(posedge clk or posedge a_rst) if (a_rst) aa_q <= 1'b0; else aa_q <= d;
  assign o = aa_q;
endmodule
