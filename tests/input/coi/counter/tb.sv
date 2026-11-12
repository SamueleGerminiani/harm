// testbench for the H4 COI fixture 'counter': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk = 1'b0;
  logic rst;
  logic en;
  logic [3:0] cnt;
  logic wrap;
  counter dut (.*);
  always #5 clk = ~clk;
`ifdef PERTURB
  `include "perturb.svh"
`endif
  initial begin
    string vcd;
    int unsigned seed;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = `VCD;
    $dumpfile(vcd);
    $dumpvars(0, tb);
    if (!$value$plusargs("seed=%d", seed)) seed = 1;
    stim_seed(seed);
    rst = '0; en = '0;
    rst = 1'b1;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    repeat (200) begin
      @(negedge clk);
      rst = (stim_next() % 40) == 0; en = (stim_next() % 4) != 0;
    end
    $finish;
  end
endmodule
