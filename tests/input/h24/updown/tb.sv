// D1 testbench for 'updown': phases mostly up, mostly down and random: both wraps and up with down
module tb;
  `include "stim.svh"
  logic clk = 1'b0;
  logic rst;
  logic up, down;
  logic [3:0] cnt;
  logic ovf, unf;
  updown dut (.*);
  always #5 clk = ~clk;
  initial begin
    string vcd;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
    $dumpfile(vcd);
    $dumpvars(0, tb);
    stim_seed(1);
    rst = 1'b1;
    up = 1'b0; down = 1'b0;
    repeat (2) @(negedge clk);
    rst = 1'b0;
    for (int i = 0; i < 400; i++) begin
      @(negedge clk);
      rst = (stim_next() % 97) == 0;
      // phases of 40 cycles: mostly up, mostly down, random
      case ((i / 40) % 3)
        0: begin up = (stim_next() % 5) != 0; down = (stim_next() % 5) == 0; end
        1: begin up = (stim_next() % 5) == 0; down = (stim_next() % 5) != 0; end
        default: begin up = stim_next() % 2 == 0; down = stim_next() % 2 == 0; end
      endcase
    end
    $finish;
  end
endmodule
