# H38 plan: a 1-bit VCD variable with a nonzero index; a top port kept as its net's name

*Status: part of the miner portfolio's FX1 (`doc/plan/FX1_PLAN.md`, part C, approved by the user 2026-10-28). Owner: the portfolio's Mac session. Branch `ms/H38-vcd-bit-index` from `dev` @ `bd4bd62`. Effort: an hour.*

## Why
Verilator dumps `wire [1:1] i0` as `$var wire 1 P! i0 [1:1] $end`. HARM's VCD parser accepts a 1-bit variable only without an index or as `[0:0]`, and otherwise aborts ("!((new_signal->lindex == -1) || (new_signal->rindex == -1))"). On AssertLLM2's `pci_bridge` and `rtftextcontroller` this stops harm, harm-rel and the three satminer arms of the miner portfolio (its MC1b T10).

A second fault, found in FX1 part H: H34's kept name of a net (D-042) is its shallowest visible name, ties broken by string order alone. A top port and a top-level wire tie, so on `pci_bridge32` (`wire pci_resi_pci_rstn_in = pci_rst_i;`) the reset input `pci_rst_i` was merged into the wire, and `--reset pci_rst_i` stopped with "not a visible top input" (harm, harm-rel and satminer-rel in the portfolio, on the main clock alone too). `wb_rst_i`, `pci_rst_o` and `wb_rst_o` were renamed the same way.

A third fault, found in FX1's T9 (once the VCD reads): H34 merges the names of one net when their types are equivalent, which ignores the declared range. On `pci_bridge32`, `wire [19:19] conf_wb_am1_out` at the top is the decoder's `[31:31]` port, the class keeps the top's name, and the decoder's `m[31]` was written `conf_wb_am1_out[31]`; HARM stopped ("Index 31 is outside the declared range [19:19]", harm-rel on `pci_clk_i`).

## Change
A 1-bit variable `[k:k]` is read as a vector of range `[k:k]`: `i0` and `i0[k]` name it, any other index is an error (as for every declared range since H11c, D-028). `[0:0]` and unindexed 1-bit variables read as before. The grammar's action is changed in `VCDParser.ypp` and in the generated `VCDParser.cpp`.

The kept name (D-042 amended): the shallowest visible name, then a top input port, then a top output port, then string order. Classes with a port at the top keep the port's name; H34's fixtures change in three classes (`w = y` keeps `y`, `multipath` keeps `z`, `constructs` keeps `k`).

A bit or range select of a merged name is rebased to its kept name's declared range (bit `i` of `[31:31]` is bit 19 of `[19:19]`; `w[6:5]` of `[7:4]` is `aw[2:1]` of `[3:0]`), in predicates and in relations. A range select whose kept range ascends where the source descends is not translated (dropped, with its reason).

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/input/h38/bit_index.vcd` (by hand: `hi [1:1]`, `mid [5:5]`, `one [0:0]`): values by name and by the declared index; another index is an error | the change |
| T2 | `tests/input/h38/ports` (by hand): the input `rst_i` and the output `o` are kept over the wires `a_rst` and `aa_q`; `--reset rst_i` with `--hints` is accepted; H34's expectations updated for the three classes above | the second change |
| T2b | `tests/input/h38/ranges` (by hand): `am [19:19]` and `aw [3:0]` at the top, the submodule's `m [31:31]` and `w [7:4]`; the relations read `am[19]` and `aw[2:1]` | the third change |
| T3 | ctest and harm-coi's pytest on the Mac and on Linux | no other change |
