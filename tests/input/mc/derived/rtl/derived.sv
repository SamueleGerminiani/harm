// H35 fixture: a divide-by-2 clock and a gated clock, both derived from clk
module derived (
  input  logic       clk, rst, en,
  output logic [3:0] fast, slow, gated
);
  logic clk_div2;
  logic gclk;
  assign gclk = clk & en;
  always_ff @(posedge clk) if (rst) clk_div2 <= 1'b0; else clk_div2 <= ~clk_div2;
  always_ff @(posedge clk) if (rst) fast <= '0; else fast <= fast + 4'd1;
  always_ff @(posedge clk_div2) if (rst) slow <= '0; else slow <= slow + 4'd1;
  always_ff @(posedge gclk) if (rst) gated <= '0; else gated <= gated + 4'd1;
endmodule
