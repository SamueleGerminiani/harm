// H45-mutant-eval testbench for h45_rr_arb_tree: random requests (sparse and dense phases), random downstream grant
module tb;
  `include "tb_common.svh"
  logic flush_i = 0, gnt_i = 0, req_o;
  logic [3:0] req_i = 0, gnt_o;
  logic [3:0][7:0] data_i = '0;
  logic [7:0] data_o;
  logic [1:0] idx_o;
  h45_rr_arb_tree dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      for (int i = 0; i < 4; i++) begin
        if (!(req_i[i] && !gnt_o[i])) begin  // a request stays until granted
          req_i[i] = chance(((c / 250) % 2) ? 3 : 1, 4);
          data_i[i] = $urandom;
        end
      end
      gnt_i = chance(3, 4);
      flush_i = chance(1, 500);
    end
    $finish;
  end
endmodule
