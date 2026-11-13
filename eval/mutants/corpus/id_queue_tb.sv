// H45-mutant-eval testbench for h45_id_queue: inputs, existence checks and outputs by id, each request held until
// granted; phases that fill and drain the queue
module tb;
  `include "tb_common.svh"
  logic [1:0] inp_id_i = 0, oup_id_i = 0;
  logic [7:0] inp_data_i = 0, exists_data_i = 0, exists_mask_i = 0, oup_data_o;
  logic inp_req_i = 0, inp_gnt_o, exists_req_i = 0, exists_o, exists_gnt_o, oup_pop_i = 0, oup_req_i = 0;
  logic oup_data_valid_o, oup_gnt_o, full_o, empty_o;
  h45_id_queue dut (.*);
  initial begin
    start();
    for (int unsigned c = 0; c < cycles; c++) begin
      @(negedge clk_i);
      if (!(inp_req_i && !inp_gnt_o)) begin
        inp_req_i = chance(((c / 200) % 2) ? 3 : 1, 4);
        inp_id_i = $urandom;
        inp_data_i = $urandom % 16;  // few values, so that existence checks hit
      end
      if (!(exists_req_i && !exists_gnt_o)) begin
        exists_req_i = chance(1, 4);
        exists_data_i = $urandom % 16;
        exists_mask_i = chance(1, 2) ? 8'hff : 8'h0f;
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
