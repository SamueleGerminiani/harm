// testbench for the H35 fixture 'two_counters': two unrelated clocks (10 ns and 7 ns, or +define+PB=6.5),
// seeded stimulus on each clock's falling edge
`timescale 1ns/100ps
`ifndef VCD
`define VCD "trace.vcd"
`endif
`ifndef PB
`define PB 3.5
`endif
module tb;
  `include "stim.svh"   // the stimulus generator (H11e, D-029)
  logic clk_a = 1'b0, clk_b = 1'b0;
  logic rst_a, en_a, rst_b, en_b;
  logic [3:0] cnt_a, cnt_b;
  logic wrap_a, wrap_b, neg_a;
  two_counters dut (.*);
  always #5 clk_a = ~clk_a;
  always #(`PB) clk_b = ~clk_b;
  initial begin
    string vcd;
    int unsigned seed;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = `VCD;
    $dumpfile(vcd);
    $dumpvars(0, tb);
    if (!$value$plusargs("seed=%d", seed)) seed = 1;
    stim_seed(seed);
    {rst_a, rst_b} = 2'b11;
    {en_a, en_b} = '0;
    repeat (2) @(negedge clk_a);
    {rst_a, rst_b} = 2'b00;
    #2000 $finish;
  end
  always @(negedge clk_a) if (!rst_a) en_a = 1'(stim_next());
  always @(negedge clk_b) if (!rst_b) en_b = 1'(stim_next());
endmodule
