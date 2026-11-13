// H45-mutant-eval: shared testbench part (written for this evaluation). Clock clk_i, active-low reset rst_ni held
// for 3 cycles; +seed=, +cycles= (default 5000), +vcd=. Stimulus changes at falling edges.
logic clk_i = 1'b0, rst_ni = 1'b0;
int unsigned seed, cycles;
string vcd;
always #5 clk_i = ~clk_i;
task automatic start();
  if (!$value$plusargs("seed=%d", seed)) seed = 1;
  if (!$value$plusargs("cycles=%d", cycles)) cycles = 5000;
  if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
  $dumpfile(vcd);
  $dumpvars(0, tb);
  void'($urandom(seed));
  repeat (3) @(negedge clk_i);
  rst_ni = 1'b1;
endtask
// true with probability n/d
function automatic bit chance(int unsigned n, int unsigned d);
  return ($urandom % d) < n;
endfunction
