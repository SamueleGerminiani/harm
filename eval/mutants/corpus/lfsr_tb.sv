// H45-mutant-eval testbench for h45_lfsr: random enable
module tb;
  `include "tb_common.svh"
  logic en_i = 0;
  logic [7:0] out_o;
  h45_lfsr dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      en_i = chance(3, 4);
    end
    $finish;
  end
endmodule
