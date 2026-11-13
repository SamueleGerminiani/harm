// H45-mutant-eval testbench for h45_exp_backoff: failures (set) and successes (clr) while the counter is zero
module tb;
  `include "tb_common.svh"
  logic set_i = 0, clr_i = 0, is_zero_o;
  h45_exp_backoff dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      set_i = is_zero_o && chance(((c / 400) % 2) ? 3 : 1, 4);
      clr_i = is_zero_o && !set_i && chance(1, 4);
    end
    $finish;
  end
endmodule
