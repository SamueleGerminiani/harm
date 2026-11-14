// H45-mutant-eval: common_cells id_queue, 2-bit ids, 4 entries, 8-bit data, one compare port
module h45_id_queue (
  input  logic       clk_i, rst_ni,
  input  logic [1:0] inp_id_i,
  input  logic [7:0] inp_data_i,
  input  logic       inp_req_i,
  output logic       inp_gnt_o,
  input  logic [7:0] exists_data_i, exists_mask_i,
  input  logic       exists_req_i,
  output logic       exists_o, exists_gnt_o,
  input  logic [1:0] oup_id_i,
  input  logic       oup_pop_i, oup_req_i,
  output logic [7:0] oup_data_o,
  output logic       oup_data_valid_o, oup_gnt_o, full_o, empty_o
);
  id_queue #(.ID_WIDTH(2), .CAPACITY(4), .FULL_BW(1'b0), .NUM_CMP_PORTS(1), .data_t(logic [7:0])) i_q (
    .clk_i, .rst_ni, .inp_id_i, .inp_data_i, .inp_req_i, .inp_gnt_o, .exists_data_i, .exists_mask_i,
    .exists_req_i, .exists_o, .exists_gnt_o, .oup_id_i, .oup_pop_i, .oup_req_i, .oup_data_o, .oup_data_valid_o,
    .oup_gnt_o, .full_o, .empty_o);
endmodule
