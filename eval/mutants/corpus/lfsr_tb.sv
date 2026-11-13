// H45-mutant-eval testbench for h45_lfsr (written for this evaluation). Directed tests: enable held high for a long
// run; enable low (the state holds); a reset in the middle of a run. Then random enable.
module tb;
  `include "tb_common.svh"
  logic en_i = 0;
  logic [7:0] out_o;
  h45_lfsr dut (.*);
  initial begin
    start();
    en_i = 0; do_reset();
    en_i = 1; idle(300);
    en_i = 0; idle(20);
    en_i = 1; idle(40);
    en_i = 0; do_reset();   // reset in the middle of a run
    en_i = 1; idle(40);
    en_i = 0; do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      en_i = chance(3, 4);
    end
    $finish;
  end
endmodule
