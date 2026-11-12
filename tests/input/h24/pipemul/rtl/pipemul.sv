// D1 timing: a 3-stage pipelined 8x8 multiplier with a valid bit per stage (latency 3)
module pipemul (
    input  logic        clk,
    input  logic        rst,
    input  logic        in_valid,
    input  logic [7:0]  a,
    input  logic [7:0]  b,
    output logic        out_valid,
    output logic [15:0] p
);
  logic [7:0]  a1, b1;
  logic        v1, v2, v3;
  logic [15:0] m2, m3;
  always_ff @(posedge clk)
    if (rst) begin v1 <= 1'b0; v2 <= 1'b0; v3 <= 1'b0; end
    else begin v1 <= in_valid; v2 <= v1; v3 <= v2; end
  always_ff @(posedge clk) begin
    a1 <= a; b1 <= b;
    m2 <= a1 * b1;
    m3 <= m2;
  end
  assign out_valid = v3;
  assign p = m3;
endmodule
