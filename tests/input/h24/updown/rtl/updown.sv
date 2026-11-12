// D1 corner: an up/down counter modulo 12; ovf (unf) is high for the cycle after a wrap 11 -> 0 (0 -> 11);
// up and down together hold the count
module updown (
    input  logic       clk,
    input  logic       rst,
    input  logic       up,
    input  logic       down,
    output logic [3:0] cnt,
    output logic       ovf,
    output logic       unf
);
  always_ff @(posedge clk)
    if (rst) begin cnt <= 4'd0; ovf <= 1'b0; unf <= 1'b0; end
    else begin
      ovf <= 1'b0; unf <= 1'b0;
      if (up && !down) begin
        if (cnt == 4'd11) begin cnt <= 4'd0; ovf <= 1'b1; end
        else cnt <= cnt + 4'd1;
      end else if (down && !up) begin
        if (cnt == 4'd0) begin cnt <= 4'd11; unf <= 1'b1; end
        else cnt <= cnt - 4'd1;
      end
    end
endmodule
