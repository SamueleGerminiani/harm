// H45-mutant-eval testbench for h45_plru_tree: one-hot uses (a hit), often the current PLRU entry (a refill)
module tb;
  `include "tb_common.svh"
  logic [7:0] used_i = 0, plru_o;
  h45_plru_tree dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      if (chance(1, 3)) used_i = 0;
      else if (chance(1, 2)) used_i = plru_o;
      else used_i = 8'(1) << ($urandom % 8);
    end
    $finish;
  end
endmodule
