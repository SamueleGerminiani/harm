# H11e plan: fixtures and oracles independent of the Verilator version (findings F-L6, F-L7, F-L8)

*Status: approved 2026-10-07 by the user (F-L7 option (a); fix F-L6 and F-L8); in progress. Branch: `ms/H11e-fixtures`, from `ms/H11d-tools` @ `57ccff9`: the findings show only with H11d's Verilator 5.052, so H11e is merged after H11d. Effort: 1 d.*

The findings are in H11d's VALIDATION entry. All are test machinery; HARM is not changed.

## F-L6: the replay oracle's control assertions
- `tests/oracle/verilator_replay.py:203` negates the consequent with `!(…)`, which is invalid SystemVerilog when the consequent is a property (`##3 v2`, `s_eventually …`, `… until …`).
- **Fix:** `not (…)`, the property negation of IEEE 1800, valid for Boolean consequents too.
- **Tests:** `verilator_replay_{newops,temporal2v,edit,ex3}` with Verilator 5.052. They failed before. The script's own check that every control fails somewhere must still hold.

## F-L8: `perturb.py influence` and the trace's signal set
- `influence` compares the reference and the perturbed traces on every signal of the reference. A signal that one Verilator dumps and another does not (`unnamedblk1::i`, the loop variable of an unnamed block) raises a `KeyError`.
- **Fix:** both traces are built in the same run with the same Verilator, so the comparison is over the signals present in both. A signal present in only one is reported, not compared.
- **Test:** `h5_influence_constructs` with Verilator 5.052 (failed before).

## F-L7 (option a): stimulus from a generator in the testbench
- **The problem:** the 7 fixture testbenches (`tests/input/coi/{counter,arbiter,fsm,hier,structs,multipath}/tb.sv`, `tests/input/h5/constructs/tb.sv`) draw their stimulus from seeded `$urandom`. Verilator 5.052's generator differs from 5.031's, so the committed traces cannot be reproduced.
- **Fix:**
  - A shared `tests/input/stim.svh` with a xorshift32 generator (`stim_seed`, `stim_next`), written in SystemVerilog, so its sequence depends on no simulator.
  - The testbenches use it instead of `$urandom`, and their `build.sh` adds `-I` for it.
  - The traces are regenerated once with `build.sh`. `tests/input/h11c` is not changed: its `gen.sh` writes the trace and the expected values together, and nothing reproduces them.
- **Ripple, the price of option (a):** the traces change, so everything computed from them is re-checked.
  - The H4–H10 regressions mostly check properties of HARM's output (soundness, filter invariants), which must still hold.
  - Expectations stored as values (e.g. `tests/input/h6/multipath_rank_expected.txt`) are regenerated. Each change is listed in VALIDATION with the reason "new trace (F-L7)", and checked to be a value change, not a broken property.
  - If a fixture no longer exercises what it was written for (a corner case the old stimulus reached, the new one does not), the testbench's seed or stimulus is adjusted and the reason is recorded. Expectations are not edited to hide it.
  - **The evaluation tables:**
    - `eval/results/linux-fixtures` is re-run on Linux.
    - `eval/results/macos-fixtures` must be re-run on the Mac (pending, the user). Until then the two cannot be compared with `--check`.
    - The examples (`eval/results/*-examples`) do not use these traces.
  - A DECISIONS entry (D-029) records the change of the fixtures' stimulus.

## Tests
| # | Test | Kind |
|---|---|---|
| A1 | The 7 `*_reproduce_*` tests pass with Verilator 5.052: the regenerated traces are reproduced exactly | regression |
| A2 | `stim.svh` is independent of the simulator: the same testbench gives the same input values under Verilator and Icarus. The inputs' values are compared, cycle by cycle, for one fixture | regression (python) |
| A3 | F-L6: the 4 `verilator_replay_*` tests pass with 5.052, and every control still fails | regression |
| A4 | F-L8: `h5_influence_constructs` passes with 5.052 | regression |
| A5 | Full Linux `ctest`, 218 tests, with the `third_party` tools; the H0 baselines byte-identical (they do not use these traces) | ctest |
| A6 | The Linux evaluation of the fixtures re-run; `--check` against the Mac is pending until the Mac re-run | eval |
