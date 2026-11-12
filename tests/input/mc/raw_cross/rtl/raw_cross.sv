// H35 fixture: a single-flop (unsynchronized) crossing and one through logic; no synchronizer
module raw_cross (
  input  logic       clk_a, clk_b, rst, req, en_b,
  output logic       seen_b, hit_b,
  output logic [3:0] cnt_b
);
  logic flag_a;
  always_ff @(posedge clk_a) if (rst) flag_a <= 1'b0; else flag_a <= req;
  always_ff @(posedge clk_b) seen_b <= flag_a;
  always_ff @(posedge clk_b) hit_b <= flag_a & en_b;
  always_ff @(posedge clk_b) if (rst) cnt_b <= '0; else if (seen_b) cnt_b <= cnt_b + 4'd1;
endmodule
