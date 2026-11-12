// testbench for the H4 COI fixture 'fsm': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk = 1'b0;
  logic rst;
  logic go;
  logic stop;
  logic busy;
  logic finished;
  fsm dut (.*);
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
    rst = '0; go = '0; stop = '0;
    rst = 1'b1;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    repeat (200) begin
      @(negedge clk);
      rst = (stim_next() % 40) == 0; go = (stim_next() % 3) == 0; stop = (stim_next() % 3) == 0;
    end
    $finish;
  end
endmodule
