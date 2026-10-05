// a parameterised stage instantiated N times by a generate loop
module stage #(
    parameter int W = 2
) (
    input  logic         clk,
    input  logic [W-1:0] d,
    output logic [W-1:0] q
);
  always_ff @(posedge clk) q <= d;
endmodule

module hier #(
    parameter int N = 3,
    parameter int W = 2
) (
    input  logic         clk,
    input  logic [W-1:0] din,
    output logic [W-1:0] dout
);
  for (genvar i = 0; i < N; i++) begin : g
    logic [W-1:0] w;
    if (i == 0) begin : first
      stage #(.W(W)) st (.clk(clk), .d(din), .q(w));
    end else begin : next
      stage #(.W(W)) st (.clk(clk), .d(g[i-1].w), .q(w));
    end
  end
  assign dout = g[N-1].w;
endmodule
