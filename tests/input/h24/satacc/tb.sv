// D1 testbench for 'satacc': climbing, falling and small steps at the bounds, then random
module tb;
  `include "stim.svh"
  logic clk = 1'b0;
  logic rst;
  logic en, clr;
  logic signed [7:0] x;
  logic signed [11:0] acc;
  logic sat;
  satacc dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
    $dumpfile(vcd);
    $dumpvars(0, tb);
    stim_seed(1);
    rst = 1'b1;
    en = 1'b0; clr = 1'b0; x = 8'sd0;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    for (int i = 0; i < 500; i++) begin
      @(negedge clk);
      rst = (stim_next() % 97) == 0;
      // phases of 50 cycles: climb to +2047, step by -1..1 at the bound, fall to -2047, step there, random
      en = (stim_next() % 8) != 0;
      clr = (stim_next() % 300) == 0;
      case ((i / 50) % 5)
        0: x = 8'sd100 + 8'(stim_next() % 27);
        1, 3: x = 8'(int'(stim_next() % 3) - 1);
        2: x = -8'sd100 - 8'(stim_next() % 28);
        default: x = 8'(stim_next());
      endcase
    end
    $finish;
  end
endmodule
