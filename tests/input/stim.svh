// H11e (finding F-L7, D-029): the stimulus generator of the fixture testbenches.
// A simulator's $urandom sequence changes between versions (Verilator 5.031 -> 5.052), so the
// committed traces could not be reproduced. This xorshift32 generator (Marsaglia, 2003) is plain
// SystemVerilog: the same seed gives the same sequence on every simulator and version.
// Included inside the testbench module: `include "stim.svh"
int unsigned stim_state = 32'd1;

function automatic void stim_seed(int unsigned s);
  stim_state = (s == 0) ? 32'd1 : s; // xorshift must not start from 0
endfunction

function automatic int unsigned stim_next();
  stim_state ^= stim_state << 13;
  stim_state ^= stim_state >> 17;
  stim_state ^= stim_state << 5;
  return stim_state;
endfunction
