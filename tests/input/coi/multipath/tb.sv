// testbench for the H4 COI fixture 'multipath': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  logic clk = 1'b0;
  logic a;
  logic b;
  logic y;
  logic z;
  multipath dut (.*);
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
    void'($urandom(seed));
    a = '0; b = '0;
    repeat (200) begin
      @(negedge clk);
      a = 1'($urandom); b = 1'($urandom);
    end
    $finish;
  end
endmodule
