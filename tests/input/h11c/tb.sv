// H11c / D-028: SystemVerilog vector indexing, checked against Verilator.
// Each cycle the testbench drives random values and prints the selects that
// tests/vectorIndexTests.cc evaluates with HARM on the dumped trace (gen.sh).
module tb;
  logic clk = 0;
  logic [1:10] asc;     // ascending
  logic [10:3] off;     // descending, LSB index 3
  logic [7:0]  d;       // the usual form
  logic [0:0]  one;     // one bit, explicit range
  int unsigned cyc = 0;
  always #5 clk = ~clk;
  initial begin
    $dumpfile("ranges.vcd");
    $dumpvars(0, tb);
  end
  always @(negedge clk) begin
    asc <= 10'($urandom);
    off <= 8'($urandom);
    d   <= 8'($urandom);
    one <= 1'($urandom);
  end
  always @(posedge clk) begin
    // one line per cycle: the values HARM must compute, MSB first
    $display("CYC %0d asc[1]=%b asc[2]=%b asc[10]=%b asc[3:6]=%b asc[1:10]=%b off[3]=%b off[4]=%b off[10]=%b off[6:3]=%b off[10:7]=%b d[0]=%b d[7]=%b d[5:2]=%b one[0]=%b",
             cyc, asc[1], asc[2], asc[10], asc[3:6], asc[1:10], off[3], off[4], off[10], off[6:3], off[10:7], d[0], d[7], d[5:2], one[0]);
    cyc <= cyc + 1;
    if (cyc == 40) $finish;
  end
endmodule
