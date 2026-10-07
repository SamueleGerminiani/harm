// testbench for the H4 COI fixture 'structs': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk = 1'b0;
  logic [2:0] x;
  logic xv;
  logic [1:0] m;
  cfg_t c;
  structs dut (.*);
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
    x = '0; xv = '0; m = '0;
    repeat (200) begin
      @(negedge clk);
      x = 3'(stim_next()); xv = 1'(stim_next()); m = 2'(stim_next());
    end
    $finish;
  end
endmodule
