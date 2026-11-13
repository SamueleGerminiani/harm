// H45-mutant-eval testbench for h45_delta_counter: counting up and down by small deltas, rare loads and clears
module tb;
  `include "tb_common.svh"
  logic clear_i = 0, en_i = 0, load_i = 0, down_i = 0, overflow_o;
  logic [5:0] delta_i = 0, d_i = 0, q_o;
  h45_delta_counter dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      en_i = chance(3, 4);
      down_i = ((c / 150) % 2) ? chance(7, 8) : chance(1, 8);
      delta_i = $urandom % 5;
      load_i = chance(1, 64);
      d_i = $urandom;
      clear_i = chance(1, 200);
    end
    $finish;
  end
endmodule
