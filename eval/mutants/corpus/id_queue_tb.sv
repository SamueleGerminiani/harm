// H45-mutant-eval testbench for h45_id_queue (written for this evaluation). Directed tests: the queue filled with
// one entry per id, an insertion held while full, then granted after a pop; existence checks that hit (full and
// partial mask) and miss; a peek (no pop) and pops by id until empty; two entries with the same id, popped in order;
// an output request for an id that is not there. Then random inputs, existence checks and outputs by id, each
// request held until granted (or, for an absent id, given up), phases that fill and drain the queue.
module tb;
  `include "tb_common.svh"
  logic [1:0] inp_id_i = 0, oup_id_i = 0;
  logic [7:0] inp_data_i = 0, exists_data_i = 0, exists_mask_i = 0, oup_data_o;
  logic inp_req_i = 0, inp_gnt_o, exists_req_i = 0, exists_o, exists_gnt_o, oup_pop_i = 0, oup_req_i = 0;
  logic oup_data_valid_o, oup_gnt_o, full_o, empty_o;
  logic [7:0] stored [4];
  h45_id_queue dut (.*);
  task automatic quiet(); inp_req_i = 0; exists_req_i = 0; oup_req_i = 0; oup_pop_i = 0; endtask
  // a request held until granted, at most `limit` cycles
  task automatic insert(logic [1:0] id, logic [7:0] data, int unsigned limit = 40);
    inp_req_i = 1; inp_id_i = id; inp_data_i = data; #1;
    for (int unsigned k = 0; !inp_gnt_o && k < limit; k++) begin @(negedge clk_i); #1; end
    @(negedge clk_i); inp_req_i = 0;
  endtask
  task automatic exists(logic [7:0] data, logic [7:0] mask);
    exists_req_i = 1; exists_data_i = data; exists_mask_i = mask; #1;
    for (int unsigned k = 0; !exists_gnt_o && k < 40; k++) begin @(negedge clk_i); #1; end
    @(negedge clk_i); exists_req_i = 0;
  endtask
  task automatic output_id(logic [1:0] id, bit pop);
    oup_req_i = 1; oup_id_i = id; oup_pop_i = pop; #1;
    for (int unsigned k = 0; !oup_gnt_o && k < 20; k++) begin @(negedge clk_i); #1; end
    @(negedge clk_i); oup_req_i = 0; oup_pop_i = 0;
  endtask
  initial begin
    start();
    // fill with one entry per id; an insertion while full, granted after a pop
    quiet(); do_reset();
    for (int i = 0; i < 4; i++) begin stored[i] = $urandom; insert(2'(i), stored[i]); end
    idle(2);
    fork
      insert(2'd1, 8'($urandom));
      begin idle(5); output_id(2'd2, 1); end
    join
    // existence checks: hit (full mask), hit (partial mask), miss
    exists(stored[0], 8'hff);
    exists(stored[3] ^ 8'hf0, 8'h0f);
    exists(~stored[1], 8'hff);
    // a peek, then pops by id until empty
    output_id(2'd0, 0);
    for (int i = 0; i < 4; i++) output_id(2'(i), 1);
    output_id(2'd1, 1);
    idle(3);
    // two entries with the same id, popped in order; an absent id
    quiet(); do_reset();
    insert(2'd3, 8'($urandom));
    insert(2'd3, 8'($urandom));
    output_id(2'd1, 1);
    output_id(2'd3, 1);
    output_id(2'd3, 1);
    idle(3);
    quiet(); do_reset();
    // random phase
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      if (!(inp_req_i && !inp_gnt_o)) begin
        inp_req_i = chance(((c / 200) % 2) ? 3 : 1, 4);
        inp_id_i = $urandom;
        inp_data_i = chance(1, 2) ? 8'($urandom % 16) : 8'($urandom);  // few values half the time, so checks hit
      end
      if (!(exists_req_i && !exists_gnt_o)) begin
        exists_req_i = chance(1, 4);
        exists_data_i = chance(1, 2) ? 8'($urandom % 16) : 8'($urandom);
        exists_mask_i = chance(1, 2) ? 8'hff : 8'($urandom);
      end
      if (!(oup_req_i && !oup_gnt_o)) begin
        oup_req_i = chance(((c / 200) % 2) ? 1 : 3, 4);
        oup_id_i = $urandom;
        oup_pop_i = chance(3, 4);
      end
    end
    $finish;
  end
endmodule
