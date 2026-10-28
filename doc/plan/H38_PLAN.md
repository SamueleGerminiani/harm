# H38 plan: a 1-bit VCD variable with a nonzero index

*Status: part of the miner portfolio's FX1 (`doc/plan/FX1_PLAN.md`, part C, approved by the user 2026-10-28). Owner: the portfolio's Mac session. Branch `ms/H38-vcd-bit-index` from `dev` @ `bd4bd62`. Effort: an hour.*

## Why
Verilator dumps `wire [1:1] i0` as `$var wire 1 P! i0 [1:1] $end`. HARM's VCD parser accepts a 1-bit variable only without an index or as `[0:0]`, and otherwise aborts ("!((new_signal->lindex == -1) || (new_signal->rindex == -1))"). On AssertLLM2's `pci_bridge` and `rtftextcontroller` this stops harm, harm-rel and the three satminer arms of the miner portfolio (its MC1b T10).

## Change
A 1-bit variable `[k:k]` is read as a vector of range `[k:k]`: `i0` and `i0[k]` name it, any other index is an error (as for every declared range since H11c, D-028). `[0:0]` and unindexed 1-bit variables read as before. The grammar's action is changed in `VCDParser.ypp` and in the generated `VCDParser.cpp`.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/input/h38/bit_index.vcd` (by hand: `hi [1:1]`, `mid [5:5]`, `one [0:0]`): values by name and by the declared index; another index is an error | the change |
| T2 | ctest and harm-coi's pytest on the Mac and on Linux | no other change |
