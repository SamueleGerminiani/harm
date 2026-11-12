// D1 data: a saturating accumulator: acc += x (signed) when en, saturating at +2047 and -2047 (sat is set in
// a cycle that saturates); clr clears
module satacc (
    input  logic               clk,
    input  logic               rst,
    input  logic               en,
    input  logic               clr,
    input  logic signed [7:0]  x,
    output logic signed [11:0] acc,
    output logic               sat
);
  logic signed [12:0] sum;
  assign sum = acc + x;  // 13 bits: cannot overflow
  always_ff @(posedge clk)
    if (rst || clr) begin acc <= 12'sd0; sat <= 1'b0; end
    else if (en) begin
      if (sum > 13'sd2047) begin acc <= 12'sd2047; sat <= 1'b1; end
      else if (sum < -13'sd2047) begin acc <= -12'sd2047; sat <= 1'b1; end
      else begin acc <= sum[11:0]; sat <= 1'b0; end
    end
endmodule
