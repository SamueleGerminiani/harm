// H35 fixture: an asynchronous FIFO (4 entries), gray-coded pointers crossing through 2-flop synchronizers;
// the data crosses unsynchronized (safe by the full/empty protocol)
module sync2 (input logic clk, rst_n, input logic [2:0] d, output logic [2:0] q);
  logic [2:0] q1;
  always_ff @(posedge clk or negedge rst_n)
    if (!rst_n) begin q1 <= '0; q <= '0; end
    else begin q1 <= d; q <= q1; end
endmodule

module cdc_fifo (
  input  logic       wclk, wrst_n, winc,
  input  logic [7:0] wdata,
  output logic       wfull,
  input  logic       rclk, rrst_n, rinc,
  output logic [7:0] rdata,
  output logic       rempty
);
  logic [7:0] mem0, mem1, mem2, mem3;
  logic [2:0] wbin, wptr, rbin, rptr, wq2_rptr, rq2_wptr;
  logic [2:0] wbin_next, rbin_next;
  assign wbin_next = wbin + 3'(winc && !wfull);
  assign rbin_next = rbin + 3'(rinc && !rempty);
  always_ff @(posedge wclk or negedge wrst_n)
    if (!wrst_n) begin wbin <= '0; wptr <= '0; wfull <= 1'b0; end
    else begin
      wbin <= wbin_next;
      wptr <= (wbin_next >> 1) ^ wbin_next;
      wfull <= ((wbin_next >> 1) ^ wbin_next) == {~wq2_rptr[2:1], wq2_rptr[0]};
    end
  always_ff @(posedge wclk)
    if (winc && !wfull)
      case (wbin[1:0])
        2'd0: mem0 <= wdata;
        2'd1: mem1 <= wdata;
        2'd2: mem2 <= wdata;
        default: mem3 <= wdata;
      endcase
  always_ff @(posedge rclk or negedge rrst_n)
    if (!rrst_n) begin rbin <= '0; rptr <= '0; rempty <= 1'b1; rdata <= '0; end
    else begin
      rbin <= rbin_next;
      rptr <= (rbin_next >> 1) ^ rbin_next;
      rempty <= ((rbin_next >> 1) ^ rbin_next) == rq2_wptr;
      if (rinc && !rempty)
        case (rbin[1:0])
          2'd0: rdata <= mem0;
          2'd1: rdata <= mem1;
          2'd2: rdata <= mem2;
          default: rdata <= mem3;
        endcase
    end
  sync2 u_w2r (.clk(rclk), .rst_n(rrst_n), .d(wptr), .q(rq2_wptr));
  sync2 u_r2w (.clk(wclk), .rst_n(wrst_n), .d(rptr), .q(wq2_rptr));
endmodule
