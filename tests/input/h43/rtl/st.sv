// H43-struct-fields: packed struct fields, traced as one vector per struct (Verilator's default) or field by field
module st(input logic clk, input logic rst, input logic [3:0] a, input logic [2:0] c,
          output logic y, output logic [3:0] q, output logic z, output logic v);
  typedef struct packed { logic [3:0] hi; logic [3:0] lo; } pair_t;
  typedef struct packed { logic f; struct packed { logic g; logic [2:0] b; } in; } nest_t;
  pair_t s;
  nest_t u;
  always_ff @(posedge clk) begin
    if (rst) begin s <= '0; u <= '0; end
    else begin
      s.hi <= a;
      s.lo <= ~a;
      u.in.b <= c;
    end
    y <= (s.hi == 4'd3);
    q <= s.hi;
    z <= u.in.b[1];
    v <= (u.in.b == 3'd5);
  end
endmodule
