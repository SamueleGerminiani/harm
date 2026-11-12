module probe (
    input  logic       clk, a, b, s, k,
    input  logic [1:0] sel,
    input  logic [3:0] v,
    output logic       y1, y2, y3, y4, y5,
    output logic [3:0] r
);
  function automatic logic f(input logic p, input logic q); return p ^ q; endfunction
  logic t;
  always_comb begin
    case (sel)
      2'd0: y1 = a;
      2'd1: y1 = b;
      default: y1 = 1'b0;
    endcase
  end
  assign y2 = s ? a : b;
  assign y3 = f(a, k);
  always_comb begin
    t = a & b;          // blocking temporary: y4 sees a, b, not t
    y4 = t | k;
  end
  assign y5 = v[sel];   // bit select: index is a source
  always_ff @(posedge clk) r[0] <= a;   // partial write: other bits hold
endmodule
