// H45 fixture: an 8-bit counter with enable, load and a wrap flag
module counter (
    input  logic       clk,
    input  logic       rst_n,
    input  logic       en,
    input  logic       load,
    input  logic [7:0] din,
    output logic [7:0] q,
    output logic       wrap
);
  logic [7:0] q_next;
  assign q_next = load ? din : q + 8'd1;
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) q <= 8'd0;
    else if (en) q <= q_next;
  end
  assign wrap = en && !load && (q == 8'd255);
endmodule
