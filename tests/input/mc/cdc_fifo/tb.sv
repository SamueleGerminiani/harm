// testbench for the H35 fixture 'cdc_fifo': write clock 10 ns, read clock 7 ns (or +define+PB=6.5),
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
  logic wclk = 1'b0, rclk = 1'b0;
  logic wrst_n, winc, rrst_n, rinc;
  logic [7:0] wdata, rdata;
  logic wfull, rempty;
  cdc_fifo dut (.*);
  always #5 wclk = ~wclk;
  always #(`PB) rclk = ~rclk;
  initial begin
    string vcd;
    int unsigned seed;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = `VCD;
    $dumpfile(vcd);
    $dumpvars(0, tb);
    if (!$value$plusargs("seed=%d", seed)) seed = 1;
    stim_seed(seed);
    {wrst_n, rrst_n} = 2'b00;
    {winc, rinc, wdata} = '0;
    repeat (2) @(negedge wclk);
    {wrst_n, rrst_n} = 2'b11;
    #3000 $finish;
  end
  always @(negedge wclk) if (wrst_n) begin winc = 1'(stim_next()); wdata = 8'(stim_next()); end
  always @(negedge rclk) if (rrst_n) rinc = 1'(stim_next());
endmodule
