// H45-mutant-eval testbench for h45_exp_backoff (written for this evaluation). Directed tests: failures in a row
// (set each time the wait is over) until the back-off saturates; a success (clr) after a long back-off, then one
// failure; set and clr in the same cycle. Then random failures and successes while the counter is zero.
module tb;
  `include "tb_common.svh"
  logic set_i = 0, clr_i = 0, is_zero_o;
  h45_exp_backoff dut (.*);
  task automatic fail_when_zero();  // wait for the back-off to end, then one failure
    while (!is_zero_o) @(negedge clk_i);
    set_i = 1; @(negedge clk_i); set_i = 0;
  endtask
  initial begin
    start();
    set_i = 0; clr_i = 0; do_reset();
    repeat (10) fail_when_zero();
    while (!is_zero_o) @(negedge clk_i);
    clr_i = 1; @(negedge clk_i); clr_i = 0;
    fail_when_zero();
    set_i = 0; clr_i = 0; do_reset();
    set_i = 1; clr_i = 1; @(negedge clk_i);
    set_i = 0; clr_i = 0; idle(8);
    do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      set_i = is_zero_o && chance(((c / 400) % 2) ? 3 : 1, 4);
      clr_i = is_zero_o && !set_i && chance(1, 4);
    end
    $finish;
  end
endmodule
