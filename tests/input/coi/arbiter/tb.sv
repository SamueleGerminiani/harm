// testbench for the H4 COI fixture 'arbiter': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  logic clk = 1'b0;
  logic rst;
  logic [1:0] req;
  logic [1:0] gnt;
  arbiter dut (.*);
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
    rst = '0; req = '0;
    rst = 1'b1;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    repeat (200) begin
      @(negedge clk);
      rst = ($urandom % 40) == 0; req = 2'($urandom);
    end
    $finish;
  end
endmodule
