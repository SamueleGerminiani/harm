// D1 data: a registered 8-bit ALU with zero, carry and negative flags (of the registered result)
module alu (
    input  logic       clk,
    input  logic       rst,
    input  logic [2:0] op,
    input  logic [7:0] a,
    input  logic [7:0] b,
    output logic [7:0] y,
    output logic       zero,
    output logic       carry,
    output logic       neg
);
  logic [8:0] r;
  always_comb begin
    case (op)
      3'd0: r = {1'b0, a} + {1'b0, b};
      3'd1: r = {1'b0, a} - {1'b0, b};
      3'd2: r = {1'b0, a & b};
      3'd3: r = {1'b0, a | b};
      3'd4: r = {1'b0, a ^ b};
      3'd5: r = {a, 1'b0};             // shift left, the top bit to carry
      3'd6: r = {a[0], 1'b0, a[7:1]};  // shift right, the bottom bit to carry
      default: r = {1'b0, b};
    endcase
  end
  always_ff @(posedge clk)
    if (rst) begin y <= 8'd0; carry <= 1'b0; end
    else begin y <= r[7:0]; carry <= r[8]; end
  assign zero = (y == 8'd0);
  assign neg = y[7];
endmodule
