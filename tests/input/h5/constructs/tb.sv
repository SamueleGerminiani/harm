// testbench for the H5 validation design 'constructs': seeded random stimulus on the falling edge
`ifndef VCD
`define VCD "trace.vcd"
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk = 1'b0;
  logic rst, a, b, c, d, s, k;
  logic [1:0] sel;
  logic [3:0] v;
  logic y_case, y_full, y_cond, y_fn, y_tmp, y_bit, y_loop, q, o;
  logic [3:0] r, rp;
  constructs dut (.*);
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
    {rst, a, b, c, d, s, k, sel, v} = '0;
    repeat (200) begin
      @(negedge clk);
      rst = (stim_next() % 8) == 0;
      {a, b, c, d, s, k} = 6'(stim_next());
      sel = 2'(stim_next());
      v = 4'(stim_next());
    end
    $finish;
  end
endmodule
