// H23 fixture: signals and a parameter named after HARM keywords (X, W, G, F, R, next, true, false,
// substr) next to an ordinary one (ok); conditions over them so that harm-coi finds predicates
module keywords #(
    parameter int X = 1  // a parameter named X, dumped by Verilator as a constant signal
) (
    input  logic       clk,
    input  logic       W,
    input  logic [1:0] G,
    input  logic       substr,
    output logic       F,
    output logic       R,
    output logic       next,
    output logic       true,
    output logic       false,
    output logic       ok
);
  always_comb
    if (W && substr) F = 1'b1;
    else F = 1'b0;
  always_comb
    case (G)
      2'b11:   R = 1'b1;
      default: R = 1'b0;
    endcase
  always_ff @(posedge clk)
    if (W) next <= 1'b1;
    else next <= 1'b0;
  always_comb
    if (G[0] || W) true = 1'b1;
    else true = 1'b0;
  assign false = !true;
  always_ff @(posedge clk)
    if (next) ok <= 1'b1;
    else ok <= 1'b0;
  // registers whose conditions read F, R and true, so that harm-coi makes them propositions
  logic seen_f, seen_r, seen_t;
  always_ff @(posedge clk)
    if (F) seen_f <= 1'b1;
    else seen_f <= 1'b0;
  always_ff @(posedge clk)
    if (R) seen_r <= 1'b1;
    else seen_r <= 1'b0;
  always_ff @(posedge clk)
    if (true) seen_t <= 1'b1;
    else seen_t <= 1'b0;
endmodule
