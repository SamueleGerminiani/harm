// H45-mutant-eval testbench for h45_spill_register: valid/ready with data held while valid and not ready
module tb;
  `include "tb_common.svh"
  logic valid_i = 0, ready_i = 0, ready_o, valid_o;
  logic [7:0] data_i = 0, data_o;
  h45_spill_register dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      if (!(valid_i && !ready_o)) begin  // the previous beat was taken (or none): a new one may start
        valid_i = chance(((c / 250) % 2) ? 7 : 1, 8);
        data_i = $urandom;
      end
      ready_i = chance(((c / 300) % 2) ? 1 : 3, 4);
    end
    $finish;
  end
endmodule
