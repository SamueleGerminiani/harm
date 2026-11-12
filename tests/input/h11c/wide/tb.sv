module tb;
  logic clk = 0, rst = 1;
  logic [7:0] in8 = 0;
  logic hit;
  logic [7:0] cnt;
  wide dut(.clk(clk), .rst(rst), .in8(in8), .hit(hit), .cnt(cnt));
  always #5 clk = ~clk;
  int unsigned cyc = 0;
  initial begin $dumpfile("trace.vcd"); $dumpvars(0, dut); end
  always @(negedge clk) begin
    cyc++;
    rst <= (cyc < 3);
    in8 <= 8'($urandom % 5);
    if (cyc > 60) $finish;
  end
endmodule
