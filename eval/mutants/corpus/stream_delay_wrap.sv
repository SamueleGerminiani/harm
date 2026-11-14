// H45-mutant-eval: common_cells stream_delay with an 8-bit payload and a fixed delay of 24 cycles (its Idle, Valid
// and Ready states and its down counter)
module h45_stream_delay (
  input  logic       clk_i, rst_ni, valid_i, ready_i,
  input  logic [7:0] payload_i,
  output logic       ready_o, valid_o,
  output logic [7:0] payload_o
);
  stream_delay #(.StallRandom(1'b0), .FixedDelay(24), .payload_t(logic [7:0])) i_sd (
    .clk_i, .rst_ni, .payload_i, .ready_o, .valid_i, .payload_o, .ready_i, .valid_o);
endmodule
