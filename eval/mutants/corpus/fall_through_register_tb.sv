// H45-mutant-eval testbench for h45_fall_through_register: valid/ready with data held, rare clears
module tb;
  `include "tb_common.svh"
  logic clr_i = 0, valid_i = 0, ready_i = 0, ready_o, valid_o;
  logic [7:0] data_i = 0, data_o;
  h45_fall_through_register dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      if (!(valid_i && !ready_o)) begin
        valid_i = chance(((c / 250) % 2) ? 7 : 2, 8);
        data_i = $urandom;
      end
      ready_i = chance(((c / 300) % 2) ? 1 : 3, 4);
      clr_i = chance(1, 300);
    end
    $finish;
  end
endmodule
