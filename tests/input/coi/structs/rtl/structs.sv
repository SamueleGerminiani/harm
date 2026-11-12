// a packed struct register and an interface: field-level dependencies
typedef struct packed {
  logic [1:0] mode;
  logic [2:0] val;
} cfg_t;

interface bus_if;
  logic [2:0] data;
  logic       valid;
endinterface

module structs (
    input  logic       clk,
    input  logic [2:0] x,
    input  logic       xv,
    input  logic [1:0] m,
    output cfg_t       c
);
  bus_if bus ();
  always_ff @(posedge clk) begin
    bus.data  <= x;
    bus.valid <= xv;
  end
  always_ff @(posedge clk) begin
    c.mode <= m;
    if (bus.valid) c.val <= bus.data;
  end
endmodule
