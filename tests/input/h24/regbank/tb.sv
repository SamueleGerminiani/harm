// D1 testbench for 'regbank': random reads, rare writes, resets now and then
module tb;
  `include "stim.svh"
  logic clk = 1'b0;
  logic rst;
  logic we;
  logic [1:0] addr;
  logic [7:0] wdata;
  logic [7:0] rdata;
  logic enable;
  logic [3:0] mode;
  regbank dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
    $dumpfile(vcd);
    $dumpvars(0, tb);
    stim_seed(1);
    rst = 1'b1;
    we = 1'b0; addr = 2'd0; wdata = 8'd0;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    for (int i = 0; i < 400; i++) begin
      @(negedge clk);
      rst = (stim_next() % 97) == 0;
      we = (stim_next() % 6) == 0;  // rare writes: the reset values are read for a while
      addr = 2'(stim_next());
      wdata = 8'(stim_next());
    end
    $finish;
  end
endmodule
