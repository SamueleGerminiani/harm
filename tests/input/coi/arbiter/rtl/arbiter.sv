// 2-requester round-robin arbiter: grant from requests (combinational) and a priority register
module arbiter (
    input  logic       clk,
    input  logic       rst,
    input  logic [1:0] req,
    output logic [1:0] gnt
);
  logic prio;  // 1: requester 1 wins a conflict
  always_comb
    if (req == 2'b11) gnt = prio ? 2'b10 : 2'b01;
    else gnt = req;
  always_ff @(posedge clk)
    if (rst) prio <= 1'b0;
    else if (gnt[0]) prio <= 1'b1;
    else if (gnt[1]) prio <= 1'b0;
endmodule
