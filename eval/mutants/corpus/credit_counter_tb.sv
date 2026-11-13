// H45-mutant-eval testbench for h45_credit_counter (written for this evaluation). Directed tests: every credit taken
// (left, critical, none left), then all given back (full); give and take in the same cycle; init in the middle.
// Then random takes while credits are left and gives while not full, rare inits.
module tb;
  `include "tb_common.svh"
  logic credit_give_i = 0, credit_take_i = 0, credit_init_i = 0;
  logic [2:0] credit_o;
  logic credit_left_o, credit_crit_o, credit_full_o;
  h45_credit_counter dut (.*);
  task automatic quiet(); credit_give_i = 0; credit_take_i = 0; credit_init_i = 0; endtask
  initial begin
    start();
    quiet(); do_reset();
    while (credit_left_o) begin credit_take_i = 1; @(negedge clk_i); end
    credit_take_i = 0; idle(3);
    while (!credit_full_o) begin credit_give_i = 1; @(negedge clk_i); end
    credit_give_i = 0; idle(3);
    quiet(); do_reset();
    repeat (2) begin credit_take_i = 1; @(negedge clk_i); end
    credit_take_i = 1; credit_give_i = 1; repeat (4) @(negedge clk_i);
    quiet(); credit_init_i = 1; @(negedge clk_i);
    quiet(); idle(3);
    do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      credit_take_i = credit_left_o && chance(((c / 200) % 2) ? 3 : 1, 4);
      credit_give_i = !credit_full_o && chance(((c / 200) % 2) ? 1 : 3, 4);
      credit_init_i = chance(1, 500);
    end
    $finish;
  end
endmodule
