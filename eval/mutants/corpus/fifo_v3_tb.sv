// H45-mutant-eval testbench for h45_fifo_v3 (written for this evaluation). Directed tests: fill to full and drain to
// empty; push and pop together at every fill level; flush when full, when empty and with a push; one-entry
// ping-pong. Then random push/pop that respect full/empty, phases that fill and drain the FIFO, rare flushes.
module tb;
  `include "tb_common.svh"
  logic flush_i = 0, push_i = 0, pop_i = 0, full_o, empty_o;
  logic [7:0] data_i = 0, data_o;
  logic [1:0] usage_o;
  h45_fifo_v3 dut (.*);
  task automatic quiet(); flush_i = 0; push_i = 0; pop_i = 0; endtask
  task automatic step(bit push, bit pop, bit flush = 0);
    push_i = push && !full_o; pop_i = pop && !empty_o; flush_i = flush; data_i = $urandom;
    @(negedge clk_i);
  endtask
  initial begin
    start();
    // fill to full, hold, drain to empty
    quiet(); do_reset();
    repeat (6) step(1, 0);
    quiet(); idle(3);
    repeat (6) step(0, 1);
    quiet(); idle(3);
    // push and pop together at each fill level 0..3
    for (int lvl = 0; lvl < 4; lvl++) begin
      quiet(); do_reset();
      repeat (lvl) step(1, 0);
      repeat (8) step(1, 1);
    end
    // flush when full, when empty, and together with a push
    quiet(); do_reset();
    repeat (4) step(1, 0);
    step(0, 0, 1);
    step(0, 0, 1);
    step(1, 0, 1);
    repeat (2) step(1, 0);
    // one-entry ping-pong
    quiet(); do_reset();
    repeat (12) begin step(1, 0); step(0, 1); end
    quiet(); do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      case ((c / 200) % 3)
        0: begin push_i = chance(1, 2); pop_i = chance(1, 2); end   // mixed
        1: begin push_i = chance(7, 8); pop_i = chance(1, 8); end   // fill
        2: begin push_i = chance(1, 8); pop_i = chance(7, 8); end   // drain
      endcase
      push_i &= !full_o;
      pop_i &= !empty_o;
      data_i = $urandom;
      flush_i = chance(1, 300);
    end
    $finish;
  end
endmodule
