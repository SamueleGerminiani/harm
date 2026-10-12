// D1 testbench for 'alu': random operations and operands; equal operands one cycle in eight
module tb;
  `include "stim.svh"
  logic clk = 1'b0;
  logic rst;
  logic [2:0] op;
  logic [7:0] a, b;
  logic [7:0] y;
  logic zero, carry, neg;
  alu dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
    $dumpfile(vcd);
    $dumpvars(0, tb);
    stim_seed(1);
    rst = 1'b1;
    op = 3'd0; a = 8'd0; b = 8'd0;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    for (int i = 0; i < 400; i++) begin
      @(negedge clk);
      rst = (stim_next() % 97) == 0;
      op = 3'(stim_next());
      a = 8'(stim_next());
      b = (stim_next() % 8 == 0) ? a : 8'(stim_next());  // a == b now and then: sub and xor give 0
    end
    $finish;
  end
endmodule
