// H45-mutant-eval testbench for h45_fall_through_register (written for this evaluation). Directed tests: a beat
// passing through in the same cycle; the register filled with the sink stalled, then drained; streaming; clear when
// full, when empty and together with a new beat. Then random valid/ready with data held, rare clears.
module tb;
  `include "tb_common.svh"
  logic clr_i = 0, valid_i = 0, ready_i = 0, ready_o, valid_o;
  logic [7:0] data_i = 0, data_o;
  h45_fall_through_register dut (.*);
  task automatic step(bit want_valid, bit ready, bit clr = 0);
    if (!(valid_i && !ready_o)) begin valid_i = want_valid; data_i = $urandom; end
    ready_i = ready; clr_i = clr;
    @(negedge clk_i);
  endtask
  task automatic quiet(); valid_i = 0; ready_i = 0; clr_i = 0; endtask
  initial begin
    start();
    // pass-through and stall
    quiet(); do_reset();
    repeat (3) begin step(1, 1); step(0, 1); end
    repeat (4) step(1, 0);
    repeat (2) step(0, 0);
    repeat (4) step(0, 1);
    // streaming
    quiet(); do_reset();
    repeat (24) step(1, 1);
    // clear when full, when empty, with a new beat
    quiet(); do_reset();
    repeat (2) step(1, 0);
    step(1, 0, 1);
    step(0, 0, 1);
    step(1, 1, 1);
    repeat (4) step(1, 1);
    quiet(); do_reset();
    // random phase
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
