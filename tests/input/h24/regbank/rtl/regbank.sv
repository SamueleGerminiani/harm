// D1 reset: four 8-bit configuration registers with distinct reset values (01, 0a, ff, 00), a write port and a
// registered read; enable is cfg0[0], mode is cfg1[3:0]
module regbank (
    input  logic       clk,
    input  logic       rst,
    input  logic       we,
    input  logic [1:0] addr,
    input  logic [7:0] wdata,
    output logic [7:0] rdata,
    output logic       enable,
    output logic [3:0] mode
);
  logic [7:0] cfg0, cfg1, cfg2, cfg3;
  always_ff @(posedge clk)
    if (rst) begin
      cfg0 <= 8'h01; cfg1 <= 8'h0a; cfg2 <= 8'hff; cfg3 <= 8'h00;
    end else if (we) begin
      case (addr)
        2'd0: cfg0 <= wdata;
        2'd1: cfg1 <= wdata;
        2'd2: cfg2 <= wdata;
        2'd3: cfg3 <= wdata;
      endcase
    end
  always_ff @(posedge clk)
    if (rst) rdata <= 8'h00;
    else case (addr)
      2'd0: rdata <= cfg0;
      2'd1: rdata <= cfg1;
      2'd2: rdata <= cfg2;
      2'd3: rdata <= cfg3;
    endcase
  assign enable = cfg0[0];
  assign mode = cfg1[3:0];
endmodule
