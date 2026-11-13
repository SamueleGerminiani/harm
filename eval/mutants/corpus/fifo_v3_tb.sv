// H45-mutant-eval testbench for h45_fifo_v3 (written for this evaluation): random push/pop that respect full/empty,
// phases that fill and drain the FIFO, rare flushes
module tb;
  `include "tb_common.svh"
  logic flush_i = 0, push_i = 0, pop_i = 0, full_o, empty_o;
  logic [7:0] data_i = 0, data_o;
  logic [1:0] usage_o;
  h45_fifo_v3 dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      case ((c / 200) % 3)
        0: begin push_i = chance(1, 2); pop_i = chance(1, 2); end   // mixed
        1: begin push_i = chance(7, 8); pop_i = chance(1, 8); end   // fill
        2: begin push_i = chance(1, 8); pop_i = chance(7, 8); end   // drain
      endcase
      push_i &= !full_o;
      pop_i &= !empty_o;
      data_i = $urandom;
      flush_i = chance(1, 300);
    end
    $finish;
  end
endmodule
