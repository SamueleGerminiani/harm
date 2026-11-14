// H45 fixture: a request/grant FSM with an enum state and a busy counter
module fsm (
    input  logic clk,
    input  logic rst_n,
    input  logic req,
    input  logic done,
    output logic gnt,
    output logic busy
);
  typedef enum logic [1:0] {IDLE, GRANT, WAIT} state_e;
  state_e state, state_n;
  logic [2:0] cnt;
  always_comb begin
    state_n = state;
    case (state)
      IDLE:  if (req) state_n = GRANT;
      GRANT: state_n = WAIT;
      WAIT:  if (done || cnt == 3'd7) state_n = IDLE;
      default: state_n = IDLE;
    endcase
  end
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state <= IDLE;
      cnt <= 3'd0;
    end else begin
      state <= state_n;
      cnt <= (state == WAIT) ? cnt + 3'd1 : 3'd0;
    end
  end
  assign gnt = (state == GRANT);
  assign busy = (state != IDLE);
endmodule
