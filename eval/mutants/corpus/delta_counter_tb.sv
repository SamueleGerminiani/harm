// H45-mutant-eval testbench for h45_delta_counter (written for this evaluation). Directed tests: counting up by the
// largest delta through overflow; counting down through zero; a load of the maximum then an increment; clear while
// counting; load and enable together; delta 0. Then random counting up and down (small deltas mostly, any delta
// sometimes), rare loads and clears.
module tb;
  `include "tb_common.svh"
  logic clear_i = 0, en_i = 0, load_i = 0, down_i = 0, overflow_o;
  logic [`H45_WIDTH-1:0] delta_i = 0, d_i = 0, q_o;
  h45_delta_counter dut (.*);
  task automatic quiet(); clear_i = 0; en_i = 0; load_i = 0; down_i = 0; delta_i = 0; d_i = 0; endtask
  task automatic count(bit down, logic [`H45_WIDTH-1:0] delta, int unsigned n);
    en_i = 1; down_i = down; delta_i = delta;
    repeat (n) @(negedge clk_i);
    en_i = 0;
  endtask
  initial begin
    start();
    // up by the largest delta, through overflow (sticky)
    quiet(); do_reset();
    count(0, {`H45_WIDTH{1'b1}}, 4);
    idle(3);
    // down through zero
    quiet(); do_reset();
    count(1, `H45_WIDTH'(5), 4);
    idle(2);
    // load the maximum, then +1
    quiet(); do_reset();
    load_i = 1; d_i = {`H45_WIDTH{1'b1}}; @(negedge clk_i); load_i = 0;
    count(0, `H45_WIDTH'(1), 2);
    // clear while counting
    quiet(); do_reset();
    en_i = 1; delta_i = `H45_WIDTH'(3);
    repeat (5) @(negedge clk_i);
    clear_i = 1; @(negedge clk_i); clear_i = 0;
    repeat (3) @(negedge clk_i);
    // load and enable together; delta 0
    quiet(); do_reset();
    en_i = 1; load_i = 1; d_i = $urandom; delta_i = $urandom; @(negedge clk_i); load_i = 0;
    delta_i = 0; repeat (4) @(negedge clk_i);
    quiet(); do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      en_i = chance(3, 4);
      down_i = ((c / 150) % 2) ? chance(7, 8) : chance(1, 8);
      delta_i = chance(3, 4) ? `H45_WIDTH'($urandom % 5) : `H45_WIDTH'($urandom);
      load_i = chance(1, 64);
      d_i = $urandom;
      clear_i = chance(1, 200);
    end
    $finish;
  end
endmodule
