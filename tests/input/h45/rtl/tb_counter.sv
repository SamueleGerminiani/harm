// H45 fixture testbench: random stimulus from +seed, +cycles cycles, VCD to +vcd
module tb;
  logic clk = 0, rst_n = 0, en, load;
  logic [7:0] din, q;
  logic wrap;
  counter dut (.*);
  int unsigned seed, cycles;
  string vcd;
  always #5 clk = ~clk;
  initial begin
    if (!$value$plusargs("seed=%d", seed)) seed = 1;
    if (!$value$plusargs("cycles=%d", cycles)) cycles = 400;
    if (!$value$plusargs("vcd=%s", vcd)) vcd = "trace.vcd";
    $dumpfile(vcd);
    $dumpvars(0, tb);
    void'($urandom(seed));
    en = 0; load = 0; din = 0;
    repeat (2) @(negedge clk);
    rst_n = 1;
    repeat (cycles) begin
      @(negedge clk);
      en = ($urandom % 4) != 0;
      load = ($urandom % 16) == 0;
      din = $urandom;
    end
    $finish;
  end
endmodule
