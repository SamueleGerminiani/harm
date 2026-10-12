// testbench for the H23 fixture 'keywords': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk = 1'b0;
  logic W;
  logic [1:0] G;
  logic substr;
  logic F, R, next, true, false, ok;
  keywords dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    int unsigned seed;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = `VCD;
    $dumpfile(vcd);
    $dumpvars(0, tb);
    if (!$value$plusargs("seed=%d", seed)) seed = 1;
    stim_seed(seed);
    W = '0; G = '0; substr = '0;
    repeat (300) begin
      @(negedge clk);
      W = 1'(stim_next()); G = 2'(stim_next()); substr = 1'(stim_next());
    end
    $finish;
  end
endmodule
