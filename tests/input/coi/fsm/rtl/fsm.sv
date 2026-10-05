// 3-state FSM with an enum state; outputs decoded from the state only
typedef enum logic [1:0] {
  IDLE = 2'd0,
  RUN  = 2'd1,
  DONE = 2'd2
} state_t;

module fsm (
    input  logic clk,
    input  logic rst,
    input  logic go,
    input  logic stop,
    output logic busy,
    output logic finished
);
  state_t state;
  always_ff @(posedge clk)
    if (rst) state <= IDLE;
    else
      case (state)
        IDLE: if (go) state <= RUN;
        RUN: if (stop) state <= DONE;
        DONE: state <= IDLE;
        default: state <= IDLE;
      endcase
  assign busy = (state == RUN);
  assign finished = (state == DONE);
endmodule
