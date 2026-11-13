// H45-mutant-eval: shared testbench part (written for this evaluation). Clock clk_i, active-low reset rst_ni held
// for 3 cycles; +seed=, +cycles= (default 5000: the random phase), +vcd=. Stimulus changes at falling edges.
// H45 amendment: each testbench runs its directed tests first (each one from reset, data from the seed), then the
// constrained-random phase of +cycles cycles.
logic clk_i = 1'b0, rst_ni = 1'b0;
int unsigned seed, cycles;
string vcd;
always #5 clk_i = ~clk_i;
// H45 amendment (T12): a watchdog. A mutant can stall a directed test (e.g. a wait for a flag it never raises); the run
// then stops after +cycles plus +watchdog= cycles (default 10000, traces.WATCHDOG_MARGIN), far above every directed
// phase (base golden runs end within +cycles plus 500), so its trace is scored like any other. HL1 RQ3 amendment:
// the margin is a plusarg, for the depth variants' longer directed phases.
function automatic int unsigned watchdog_margin();  // a function, so the trace has no new variable
  int unsigned w;
  if (!$value$plusargs("watchdog=%d", w)) w = 10000;
  return w;
endfunction
initial begin : watchdog
  int unsigned n;
  if (!$value$plusargs("cycles=%d", n)) n = 5000;
  repeat (n + watchdog_margin()) @(negedge clk_i);
  $display("H45 watchdog: stopped after %0d cycles", n + watchdog_margin());
  $finish;
end
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
// a directed test starts from reset (the caller sets the inputs to their idle values first)
task automatic do_reset();
  rst_ni = 1'b0;
  repeat (3) @(negedge clk_i);
  rst_ni = 1'b1;
  @(negedge clk_i);
endtask
task automatic idle(int unsigned n);
  repeat (n) @(negedge clk_i);
endtask
// true with probability n/d
function automatic bit chance(int unsigned n, int unsigned d);
  return ($urandom % d) < n;
endfunction
