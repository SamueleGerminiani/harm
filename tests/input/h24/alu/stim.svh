// D1's stimulus generator: xorshift32, seeded with stim_seed (0 is taken as 1); the same sequence everywhere
int unsigned stim_state = 32'd1;
function automatic void stim_seed(int unsigned s);
  stim_state = (s == 0) ? 32'd1 : s;
endfunction
function automatic int unsigned stim_next();
  stim_state = stim_state ^ (stim_state << 13);
  stim_state = stim_state ^ (stim_state >> 17);
  stim_state = stim_state ^ (stim_state << 5);
  return stim_state;
endfunction
