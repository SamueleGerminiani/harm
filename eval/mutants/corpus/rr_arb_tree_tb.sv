// H45-mutant-eval testbench for h45_rr_arb_tree (written for this evaluation). Directed tests: all four inputs
// requesting with the output always granted (the round-robin rotation); each input alone; all requesting with the
// output stalled, then released; a flush during a stall; two inputs alternating. Then random requests held until
// granted (sparse and dense phases), random downstream grant, rare flushes.
module tb;
  `include "tb_common.svh"
  logic flush_i = 0, gnt_i = 0, req_o;
  logic [3:0] req_i = 0, gnt_o;
  logic [3:0][7:0] data_i = '0;
  logic [7:0] data_o;
  logic [1:0] idx_o;
  h45_rr_arb_tree dut (.*);
  // one cycle: input i keeps its request until granted, then requests again when want[i]
  task automatic step(logic [3:0] want, bit gnt, bit flush = 0);
    for (int i = 0; i < 4; i++)
      if (!(req_i[i] && !gnt_o[i])) begin req_i[i] = want[i]; data_i[i] = $urandom; end
    gnt_i = gnt; flush_i = flush;
    @(negedge clk_i);
  endtask
  task automatic quiet(); req_i = 0; gnt_i = 0; flush_i = 0; endtask
  initial begin
    start();
    // all requesting, always granted: the rotation
    quiet(); do_reset();
    repeat (24) step(4'b1111, 1);
    // each input alone
    for (int i = 0; i < 4; i++) begin
      quiet(); do_reset();
      repeat (6) step(4'(1) << i, 1);
    end
    // stalled output, then released
    quiet(); do_reset();
    repeat (8) step(4'b1111, 0);
    repeat (12) step(4'b1111, 1);
    // a flush during a stall
    quiet(); do_reset();
    repeat (4) step(4'b1011, 0);
    step(4'b1011, 0, 1);
    repeat (8) step(4'b1011, 1);
    // two inputs alternating
    quiet(); do_reset();
    for (int k = 0; k < 16; k++) step(k % 2 ? 4'b0101 : 4'b1010, 1);
    quiet(); do_reset();
    // random phase
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
