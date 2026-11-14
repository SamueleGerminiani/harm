// H45-mutant-eval testbench for h45_lossy_valid_to_stream (written for this evaluation). Directed tests: four beats
// with the sink stalled (two pending, then the last entry overwritten), a long stall, then a drain; a stream of ten
// beats with the sink ready. Then random beats (sparse and dense phases) with the sink stalled 40 of every 200
// cycles and ready 2 of 3 cycles otherwise. valid_i is a plain valid (no ready: the module drops what it cannot keep).
module tb;
  `include "tb_common.svh"
  logic valid_i = 0, ready_i = 0, valid_o, busy_o;
  logic [7:0] data_i = 0, data_o;
  h45_lossy_valid_to_stream dut (.*);
  initial begin
    start();
    do_reset();
    ready_i = 0; repeat (4) begin valid_i = 1; data_i = $urandom; @(negedge clk_i); end
    valid_i = 0; idle(30); ready_i = 1; idle(5);
    valid_i = 1; repeat (10) begin data_i = $urandom; @(negedge clk_i); end
    valid_i = 0; ready_i = 0; do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      valid_i = chance(1, ((c / 400) % 2) ? 3 : 12);
      data_i = $urandom;
      if ((c % 200) < 40) ready_i = 0; else ready_i = chance(2, 3);
    end
    $finish;
  end
endmodule
