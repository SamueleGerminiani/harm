// H45-mutant-eval testbench for h45_spill_register (written for this evaluation). Directed tests: fill both stages
// with the sink stalled, then drain; streaming at full rate; ready toggling every cycle; a stall of each length 1..4.
// Then random valid/ready with data held while valid and not ready.
module tb;
  `include "tb_common.svh"
  logic valid_i = 0, ready_i = 0, ready_o, valid_o;
  logic [7:0] data_i = 0, data_o;
  h45_spill_register dut (.*);
  // one cycle: a new beat may start only when the previous one was taken (valid/ready protocol)
  task automatic step(bit want_valid, bit ready);
    if (!(valid_i && !ready_o)) begin valid_i = want_valid; data_i = $urandom; end
    ready_i = ready;
    @(negedge clk_i);
  endtask
  initial begin
    start();
    // fill both stages with the sink stalled, hold, drain
    valid_i = 0; ready_i = 0; do_reset();
    repeat (5) step(1, 0);
    repeat (3) step(0, 0);
    repeat (5) step(0, 1);
    // streaming at full rate
    valid_i = 0; ready_i = 0; do_reset();
    repeat (30) step(1, 1);
    // ready toggling every cycle
    valid_i = 0; ready_i = 0; do_reset();
    for (int i = 0; i < 30; i++) step(1, i % 2);
    // a stall of each length 1..4 in a stream
    valid_i = 0; ready_i = 0; do_reset();
    for (int n = 1; n <= 4; n++) begin
      repeat (4) step(1, 1);
      repeat (n) step(1, 0);
    end
    repeat (4) step(0, 1);
    valid_i = 0; ready_i = 0; do_reset();
    // random phase
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
