// mod-10 counter with enable: register feedback, combinational wrap
module counter (
    input  logic       clk,
    input  logic       rst,
    input  logic       en,
    output logic [3:0] cnt,
    output logic       wrap
);
  assign wrap = en && (cnt == 4'd9);
  always_ff @(posedge clk)
    if (rst) cnt <= 4'd0;
    else if (en) cnt <= (cnt == 4'd9) ? 4'd0 : cnt + 4'd1;
endmodule
