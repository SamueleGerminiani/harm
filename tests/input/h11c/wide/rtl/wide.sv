// H11c, F-L5: predicates on signals wider than HARM's 511-bit limit must not reach HARM.
module wide(input logic clk, input logic rst, input logic [7:0] in8, output logic hit, output logic [7:0] cnt);
  logic [1599:0] state;   // like sha3's 1600-bit permutation state
  always_ff @(posedge clk)
    if (rst) state <= '0;
    else state <= {state[1591:0], in8};
  always_ff @(posedge clk)
    if (rst) cnt <= 8'd0;
    else if (in8 == 8'd3) cnt <= cnt + 8'd1;
  assign hit = (state == '0);
endmodule
