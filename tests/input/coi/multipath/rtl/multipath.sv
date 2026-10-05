// 'a' reaches y combinationally and through two registers; 'b' reaches only z
module multipath (
    input  logic clk,
    input  logic a,
    input  logic b,
    output logic y,
    output logic z
);
  logic r1, r2, rb;
  always_ff @(posedge clk) begin
    r1 <= a;
    r2 <= r1;
    rb <= b;
  end
  assign y = a ^ r2;
  assign z = rb;
endmodule
