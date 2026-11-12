# H28 plan: harm-coi's default timescale

*Status: approved by the user 2026-10-15 ("Fix both, release v1.0.1", on trivergence's finding F7-F2, raised through the miner portfolio). Branch `ms/H28-timescale` from `dev` @ `6f736fa`. Effort: about an hour.*

## Why
trivergence's F7 tools tests (its finding F7-F2) ran harm-coi on AssertLLM2's `i2c_slave`. Some of its files declare a `timescale` (`include/timescale.v`, `serialInterface.v`) and the others do not. slang refuses that mix: "design element does not have a time scale defined but others in the design do" (3 errors), so every arm that uses harm-coi fails on the design. trivergence (`triad_core.rtl_files.slang_args`) and OpenFPV run slang with `--timescale 1ns/1ps`, the default for a file without one, as simulators do. harm-coi passes none. Reproduced on the Mac.

## Change
`frontend.elaborate` passes slang `--timescale 1ns/1ps`. A file's own `timescale` still governs that file. Nothing else changes: harm-coi uses no time values.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | A design of two files, one with `` `timescale 1ns/1ps `` and one without: `frontend.elaborate` succeeds | the default (it raised before) |
| T2 | The same with an explicit `` `timescale 1ps/1ps `` in one file and none in the other: it still elaborates | a file's own timescale is kept |
| T3 | harm-coi's whole test suite, and HARM's fast tests | no other change |
