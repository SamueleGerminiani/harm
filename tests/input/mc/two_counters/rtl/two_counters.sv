// H35 fixture: two independent clock domains, no crossing; clk_a also has a falling-edge register
module two_counters (
  input  logic       clk_a, rst_a, en_a,
  input  logic       clk_b, rst_b, en_b,
  output logic [3:0] cnt_a, cnt_b,
  output logic       wrap_a, wrap_b, neg_a
);
  always_ff @(posedge clk_a or posedge rst_a)
    if (rst_a) cnt_a <= '0; else if (en_a) cnt_a <= cnt_a + 4'd1;
  always_ff @(posedge clk_a) wrap_a <= en_a && cnt_a == 4'hf;
  always_ff @(negedge clk_a) neg_a <= cnt_a[0];
  always_ff @(posedge clk_b or posedge rst_b)
    if (rst_b) cnt_b <= '0; else if (en_b) cnt_b <= cnt_b + 4'd1;
  always_ff @(posedge clk_b) wrap_b <= en_b && cnt_b == 4'hf;
endmodule
