// H34 fixture: nets that cross module ports, some of them one signal under several names (D-042)
module leaf (
    input  logic       clk,
    input  logic       rst,
    input  logic       a,
    input  logic [3:0] d,
    output logic       q,
    output logic [3:0] r
);
  always_ff @(posedge clk)
    if (rst) begin
      q <= 1'b0;
      r <= 4'd0;
    end else begin
      q <= a;
      if (a && d == 4'd3) r <= d;
    end
endmodule

module mid (
    input  logic       clk,
    input  logic       rst,
    input  logic       a,
    input  logic [3:0] d,
    output logic       q,
    output logic [3:0] r
);
  leaf u_leaf (.clk(clk), .rst(rst), .a(a), .d(d), .q(q), .r(r));
endmodule

module pad (inout wire io);
endmodule

module aliases (
    input  logic       clk,
    input  logic       rst,
    input  logic       x,
    input  logic       y,
    input  logic [3:0] d,
    input  logic [7:0] wide,
    output logic       q,
    output logic [3:0] r,
    output logic       w,
    inout  wire        io
);
  // one signal under several names: x, d, rst, q and r through the ports of u_mid and u_mid.u_leaf; w and y
  mid u_mid (.clk(clk), .rst(rst), .a(x), .d(d), .q(q), .r(r));
  assign w = y;
  // not one signal: an operator, a part-select, a constant, a width change, an inout
  leaf u_or (.clk(clk), .rst(rst | y), .a(x | y), .d(wide[3:0]), .q(), .r());
  leaf u_wide (.clk(clk), .rst(1'b0), .a(1'b0), .d(wide), .q(), .r());
  pad u_pad (.io(io));
endmodule
