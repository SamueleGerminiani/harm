// testbench for the H34 fixture 'aliases': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk = 1'b0;
  logic rst, x, y;
  logic [3:0] d;
  logic [7:0] wide;
  logic q, w;
  logic [3:0] r;
  wire io;
  aliases dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    int unsigned seed;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = `VCD;
    $dumpfile(vcd);
    $dumpvars(0, tb);
    if (!$value$plusargs("seed=%d", seed)) seed = 1;
    stim_seed(seed);
    rst = 1'b1;
    {x, y, d, wide} = '0;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    repeat (200) begin
      @(negedge clk);
      {x, y} = 2'(stim_next());
      d = 4'(stim_next());
      wide = 8'(stim_next());
    end
    $finish;
  end
endmodule
