// H45-mutant-eval: common_cells lossy_valid_to_stream with 8-bit data (two entries, 1-bit read and write pointers)
module h45_lossy_valid_to_stream (
  input  logic       clk_i, rst_ni, valid_i, ready_i,
  input  logic [7:0] data_i,
  output logic       valid_o, busy_o,
  output logic [7:0] data_o
);
  lossy_valid_to_stream #(.DATA_WIDTH(8)) i_lv (.clk_i, .rst_ni, .valid_i, .data_i, .valid_o, .ready_i, .data_o, .busy_o);
endmodule
