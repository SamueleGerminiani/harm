// D1 testbench for 'pipemul': random operands, valid two cycles in three
module tb;
  `include "stim.svh"
  logic clk = 1'b0;
  logic rst;
  logic in_valid;
  logic [7:0] a, b;
  logic out_valid;
  logic [15:0] p;
  pipemul dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
    $dumpfile(vcd);
    $dumpvars(0, tb);
    stim_seed(1);
    rst = 1'b1;
    in_valid = 1'b0; a = 8'd0; b = 8'd0;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    for (int i = 0; i < 400; i++) begin
      @(negedge clk);
      rst = (stim_next() % 97) == 0;
      in_valid = (stim_next() % 3) != 0;
      a = 8'(stim_next());
      b = 8'(stim_next());
    end
    $finish;
  end
endmodule
