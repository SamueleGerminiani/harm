// H45-mutant-eval testbench for h45_plru_tree (written for this evaluation). Directed tests: every entry used once
// in order and in reverse; refills of the current PLRU entry for a full round; one entry used repeatedly; no use.
// Then random one-hot uses (a hit), often the current PLRU entry (a refill).
module tb;
  `include "tb_common.svh"
  logic [7:0] used_i = 0, plru_o;
  h45_plru_tree dut (.*);
  initial begin
    start();
    used_i = 0; do_reset();
    for (int i = 0; i < 8; i++) begin used_i = 8'(1) << i; @(negedge clk_i); end
    for (int i = 7; i >= 0; i--) begin used_i = 8'(1) << i; @(negedge clk_i); end
    used_i = 0; do_reset();
    repeat (16) begin used_i = plru_o; @(negedge clk_i); end
    used_i = 0; do_reset();
    used_i = 8'(1) << ($urandom % 8); idle(6);
    used_i = 0; idle(4);
    do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      if (chance(1, 3)) used_i = 0;
      else if (chance(1, 2)) used_i = plru_o;
      else used_i = 8'(1) << ($urandom % 8);
    end
    $finish;
  end
endmodule
