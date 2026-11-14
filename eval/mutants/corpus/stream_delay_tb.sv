// H45-mutant-eval testbench for h45_stream_delay (written for this evaluation). Directed tests: one beat with the sink
// ready; beats with a sink stall of 3 and 10 cycles once valid_o rises; back to back; a long idle gap. Then random
// beats with idle gaps (up to 60 cycles one time in four, else up to 3) and sink stalls of 0-7 cycles. valid_i is held
// until the beat is taken (valid/ready protocol).
module tb;
  `include "tb_common.svh"
  logic valid_i = 0, ready_i = 0, ready_o, valid_o;
  logic [7:0] payload_i = 0, payload_o;
  h45_stream_delay dut (.*);
  task automatic beat(int unsigned stall);  // one transfer; the sink stalls `stall` cycles once valid_o rises
    valid_i = 1; payload_i = $urandom; ready_i = 0;
    while (!valid_o) @(negedge clk_i);
    repeat (stall) @(negedge clk_i);
    ready_i = 1; @(negedge clk_i);
    valid_i = 0; ready_i = 0;
  endtask
  initial begin
    start();
    do_reset();
    beat(0); idle(5); beat(3); beat(0); idle(40); beat(10);
    valid_i = 0; ready_i = 0; do_reset();
    // random phase: about `cycles` cycles (a beat takes about 26 cycles plus its stall)
    for (int unsigned c = 0; c < cycles; ) begin
      int unsigned gap = chance(1, 4) ? $urandom % 60 : $urandom % 4;
      idle(gap);
      beat(chance(1, 2) ? 0 : $urandom % 8);
      c += gap + 30;
    end
    $finish;
  end
endmodule
