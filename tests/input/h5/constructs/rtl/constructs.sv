// H5 validation: the A4 constructs in one design, for the yosys cross-check (tests/coi/xcheck_yosys.py)
interface bif;
  logic [2:0] data;
  logic       valid;
  modport slv(input data, valid);
endinterface

module sub (
    input  logic clk,
    bif.slv      b,
    output logic o
);
  always_ff @(posedge clk) o <= b.valid & b.data[0];
endmodule

module constructs (
    input  logic       clk, rst, a, b, c, d, s, k,
    input  logic [1:0] sel,
    input  logic [3:0] v,
    output logic       y_case, y_full, y_cond, y_fn, y_tmp, y_bit, y_loop, q, o,
    output logic [3:0] r, rp
);
  logic g, t;
  bif bus ();

  function automatic logic f(input logic p);
    logic l;
    l = p ^ g;
    return l;
  endfunction

  always_comb
    case (sel)
      2'd0: y_case = a;
      2'd1: y_case = b;
      default: y_case = 1'b0;
    endcase
  always_comb
    case (sel)
      2'd0: y_full = a; 2'd1: y_full = b; 2'd2: y_full = c; 2'd3: y_full = d;
    endcase
  assign y_cond = s ? a : b;
  assign g = k;
  assign y_fn = f(a);
  always_comb begin
    t = a & b;
    y_tmp = t | k;
  end
  assign y_bit = v[sel];
  always_comb begin
    y_loop = 1'b0;
    for (int i = 0; i < 4; i++) y_loop = y_loop | v[i];
  end
  always_ff @(posedge clk)
    if (a) begin
      if (b) r <= {3'b0, c};
      else   r <= {3'b0, d};
    end
  always_ff @(posedge clk) rp[0] <= a;
  always_ff @(posedge clk or posedge rst)
    if (rst) q <= 1'b0; else q <= d;
  assign bus.data = v[2:0];
  assign bus.valid = a;
  sub u (.clk(clk), .b(bus.slv), .o(o));
endmodule
