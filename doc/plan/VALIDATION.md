# Validation log

One entry per completed milestone: commands, results, date, and anything checked by hand.

## H0: baseline and safety net (2026-10-05, macOS arm64, g++-13)

### Step 0: toolchain (D-010)
- Before: `build/harm --help` and `install/harm/bin/harm --help` aborted (`malloc: pointer being freed was not allocated`). Spot was linked to gcc-12 `libstdc++`, ANTLR and HARM to gcc-13 `libstdc++`, and Boost to `libc++`.
- `CC=gcc-13 CXX=g++-13 bash third_party/install_*.sh`. `otool -L` confirms Spot, Boost and ANTLR all link `/opt/homebrew/opt/gcc@13/lib/gcc/13/libstdc++.6.dylib`. `.harm_toolchain` records `g++-13 (Homebrew GCC 13.3.0) 13.3.0` for all three. CMake reports no toolchain warning.
- The old libraries were moved to the session scratchpad, not deleted; they can be discarded.
- **A5:** after a clean rebuild, the 35 pre-existing ctests pass, and `harm` actually runs. Note: on the old toolchain ctest had reported 35/35 passing while the example tests were aborting at load time (a re-run of `ex3` showed it), so those earlier results were not reliable.

### Step 1: set-mode baseline (commit `0a13dbd`)
- `tests/regression/update_baseline.sh build set` captures 17 cases from `examples/` with `--max-threads 1`.
- **Hand check against direct HARM runs (assertion tables printed to stdout):**
  - `ex3`: 1 assertion; matches.
  - `vendingMachine`: 2 assertions; matches.
  - `bl_master1k`: 4 assertions; matches. All four have score 1.00, so their order is decided by ties.
  - `csvCheck`: 0 assertions. This is a checking example and mines nothing, so its baseline is correctly empty. It only guards "still mines nothing".
- **Determinism before the fix:** 8 of 17 non-slow determinism tests failed: `fsm`, `paperRE`, `sub_platform1k`, `bl_master1h`, `bl_master1k`, `process`, `svaFunctions`, `bl_master1k_cut10`.

### Step 2: determinism fixes (D-001)
- **First round** (TLMiner collection, deduplication order, ranking tie-break): 17/17 non-slow tests pass. Two full runs including the slow cases gave 18/19: `sobel` failed, but only in `axc_faultCov.txt` (the `--find-min-subset` covering subset).
- **Investigation:** `sobel` varied even with `--max-threads 1`, so it was not a thread race. A temporary debug print (removed before commit) showed the faulty-trace list in a different order on each run: `main.cc` shuffled `--fd` VCD traces with `std::random_device`. The id-keyed fault-coverage maps were a second source.
- **Second round:**
  - sorted plus fixed-seed shuffle of `--fd` traces;
  - the fault loop follows the order of `selected`;
  - set-cover candidates sorted by assertion text, falling back to the id.

  The first attempt at the last item read `_originalAssertions` only. That broke `SetConvTest`, which fills `_aidToF` directly, and paal segfaulted on an empty problem. It was fixed with the fallback to the id, and the test passes.
- **Final results:**
  - `ctest -L determinism` (19 cases, including slow and the `--max-ass 10` cut cases): 19/19, twice after the second round of fixes, and once more after the set-cover fallback fix (19/19, 418 s).
  - `ctest -LE determinism`: 52/52 (unit, example and ordered-regression tests).

### Step 3: ordered baseline
- **Set comparison** against the step 1 baseline: identical for 16 of 17 cases.
  - `sobel`: `axc_ass.txt` has the identical set. `axc_faultCov.txt` has a different but equally minimal covering subset: 2 assertions, 38/38 faults covered in both.
  - The pre-fix subset was one random pick among equally minimal covers. The new subset had already appeared among the pre-fix random runs.
- **Ordered capture:** `tests/regression/update_baseline.sh build ordered`. Afterwards `ctest -L regression` passes 17/17.
- **Ordering rule checked by hand on `bl_master1k`:** four ties at 1.00 come out in ascending text order.

### Pending
- Linux run of `ctest -L regression` and `ctest -L determinism` on the Linux machine.

## H1: proposition and SVA language fixes (2026-10-05, macOS arm64, g++-13)

### Acceptance tests
They were written first and committed failing in `182b492`: 7 of 7 new tests failed before the implementation.

| Test | Result |
|---|---|
| A1 `PropositionLanguageTest` (literals, fill, concat/replication, ternary, `===`, print/parse round trip) | 9/9 pass |
| A2 `PropositionOracleTest` (iverilog oracle) | pass: 700 new-feature expressions × 32 rows, 0 parse errors, 0 mismatches; 300 existing-syntax expressions, 0 mismatches |
| A3 `.` alias and identifier boundaries (in `PropositionLanguageTest`) | pass |
| A4 `h1_invariant_needs_implication_for_dt` + invariants in A5 | pass |
| A5 `regression_h1_newops` | pass. The output matches the hand-derived expectation written before the implementation, byte for byte (7 assertions) |
| A6 `SvaOutputTest` (trivergence's M0 cases) | pass: 12/12 |
| A7 `h1_skip_invalid_props` | pass |
| A8 H0 regression | pass. Only `process` changed: re-captured, equal to the old output with the D-002 rewrites applied (checked as sets, 138 assertions). `edit` unchanged |

### Independent validation
- **Proposition semantics, iverilog oracle (A2).** iverilog 12.0 computes two columns:
  - the SV value;
  - HARM's documented model: comparisons are false with x/z operands (D-011).

  HARM matches the model everywhere. SV and the model differ on 337/700 new and 255/300 existing expressions (at least one row), which is the documented x/z gap. **Finding D-011, open.**
- **SVA printing, Verilator 5.034 replay** (`tests/oracle/verilator_replay.py`, ctest label `verilator`):

  | Case | Assertions | Checked as printed | Checked via `$past` encoding | Unsupported by Verilator | Lint errors | Failures | Controls fired |
  |---|---|---|---|---|---|---|---|
  | newops | 7 | 7 | 0 | 0 | 0 | 0 | all |
  | temporal2v | 653 | 64 | 194 | 395 (`until`, `s_eventually`) | 0 | 0 | all |
  | edit (example) | 3 | 0 | 3 | 0 | 0 | 0 | all |
  | ex3 (example) | 1 | 1 | 0 | 0 | 0 | 0 | all |

  - **What the replay does:** HARM's mined assertions are replayed on the same trace in Verilator. Each must never fail, and each negated control must fail at least once.
  - **The `$past` encoding:** Verilator 5.034 rejects any `##` in a property ("Unsupported: ## () cycle delay range expression"), so `b0 ##1 … |-> ##n q` is checked as the equivalent `cyc >= d && $past(b0, d) && … |-> q`. The encoding is written independently of HARM's printer.
  - **Sensitivity:** a hand mutation (`cnt >= 4'b110` → `4'b111`) was reported as failing at the expected cycle.

### Found and fixed during H1
- **F9:** variable substitution ignored identifier boundaries. Variables `x`, `a`, `b` corrupted literals such as `'b1x0` and `0xa`.
- **F10:** copying a bit selection swapped its bounds. Mined assertions with `r[7:4]` printed and evaluated `r[4:7]`. **This affects `main`.**
- **Grammar:** the semantic predicates dereferenced `LT(-1)`, which is null at the start of the input. They are now null-safe.
- **Edit rules and `--sva-assert`:** edit rules failed with `--sva-assert` on CSV traces, because the clock was not a trace variable. Edit rules now match the property without the `assert` wrapper.
- **Edit rules and D-002:** edit rules are matched against the pre-D-002 printing, so existing rules keep working.

### Determinism
`ctest -L determinism` after the last H1 change: 20/20 pass (416 s), including `h1_newops`, slow cases and the `--max-ass` cuts.

### Pending
- The Linux run of the regression, determinism and Verilator suites.

## H2: Z3 back end and proposition canonicalisation (2026-10-05, macOS arm64, g++-13)

### Build
- Z3 4.13.4 is built by `third_party/install_z3.sh` with g++-13. `otool -L` shows gcc-13 `libstdc++` only, and the `.harm_toolchain` record matches. CMake reports `Z3 4.13.4.0 found`.

### Acceptance tests
They were written first and committed failing in `e8237a9`, with the hand labels fixed from the evaluator's source code before any result existed.

| Test | Result |
|---|---|
| A2 hand-labelled pairs (56) | pass: every EQ proved, every NEQ not reported equivalent |
| A3 small variables (v1, v2, v3 = 6 bits; all 4^6 = 4,096 four-valued assignments; 960 pairs) | 765 equivalent by evaluation, **765 proved (none missed)**, **0 unsound**. All 195 "not equivalent" answers come with a counterexample that HARM's evaluator confirms |
| A3 wide variables (q4, r8, t13, u32; 20,000 random rows; 640 pairs) | **0 unsound.** 502 proved equivalent. 138 "not equivalent" answers, every counterexample confirmed by HARM's evaluator. These include 11 pairs that the random rows did not separate |
| A4 a timeout or unknown result is never "equivalent" | pass |
| A5 `h2_reduce_syntactic` / `h2_reduce_equiv` | pass. Both outputs match the hand-derived expectations (6 → 4 assertions; `!=` and `!==` kept apart) |
| A6 determinism with `--reduce equiv` | pass |
| All suites | `ctest -LE determinism`: 65/65 (including the Verilator replays). `ctest -L determinism`: 22/22 |

### Independent validation
- **HARM's evaluator as the oracle (A3), in both directions:**
  - no "equivalent" answer is refuted on any assignment;
  - every "not equivalent" answer has a counterexample that the evaluator confirms (333 in total);
  - for the 6-bit variables, every equivalent pair is proved, which shows the 4-valued encoding is exact there.
- **The USM-T cross-check** in the plan was **not run**. USM-T builds only on Linux. It is pending for the Linux machine, and it would only cover the bool/int subset, which A2 also covers.

### Semantics found while implementing (encoded exactly)
- HARM's `Logic` keeps hidden value bits above a value's width: the carry of `+`, the ones of `~`. Every operator masks or sign-extends at its own width.
- `~` turns z into x.
- A logic value used as a boolean tests only the value bits (x/z count as 0).
- Arithmetic with an x/z operand gives a 1-bit x.
- **Opaque atoms** (sound, incomplete): `/` and shifts (bad operands abort HARM); `$past`, `$stable`, `$rose`, `$fell`; strings; int types narrower than 64 bits; numeric conversions other than int→logic; consumers that depend on the run-time width of an arithmetic result.

### Pending
- The Linux run of all suites, and the USM-T cross-check.

## H4: COI contract and RTL fixture corpus (2026-10-05, macOS arm64, Verilator 5.034)

### Contract
- The schema `doc/schemas/coi.v1.json` (JSON Schema 2020-12) plus `tests/coi/check_coi.py`.
- **Change from the plan:** `depths` may be empty when `saturated` is true, for a source that reaches the target only through paths deeper than `max_depth`. Without this, such a source could not be listed and would look out of the cone.
- **A2:** 13 documents checked, 1 valid and 12 invalid. Each invalid one is rejected for its expected reason.

### Fixtures
`counter`, `arbiter`, `fsm`, `hier`, `structs`, `multipath`.
- The direct edges are written by hand from the RTL (`edges.txt`); the closure is mechanical (`closure.py`).
- **A1:** all 6 `expected_coi.json` are valid. Their names are exactly the signals HARM sees in the committed `trace.vcd` at the recorded `--vcd-ss` and `--vcd-r`, as reported by HARM itself through `--generate-config`.
- **A3:** fresh builds reproduce all 6 traces.

### Independent validation by simulation
- **HARM's sampling convention, measured first.** With inputs driven on the falling edge, HARM mines `G(a -> X q)` for `q <= a`, i.e. it sees the values in effect just before each rising edge. `perturb.py` samples the same way. A first version sampled just *after* the edge; every input-to-register depth then looked one cycle too short. The sampler was fixed and checked on that trace.
- **A4, non-influence:** 120 (source, excluded target) pairs checked across the 6 designs, **0 violations**. Only the parameters `N` and `W` can't be forced.
  - **Sensitivity:** in a copy of `multipath`, deleting the edge `z <- rb` (or the whole `z` entry) is caught: forcing `b` or `rb` changes `z`.
  - The script also checks visible signals that `coi.json` omits.
- **A5, depth evidence:** **102 of 105** claimed (source, target, depth) observed with one-cycle pulses (5 seeds × 4 pulse cycles × 2 values). The 3 not observed are structural paths whose effect can't, or rarely can, be excited, which a structural cone allows:
  - `fsm`, `finished <- go @1`: `go` only switches IDLE/RUN, and `finished` is 0 in both. The effect is impossible.
  - `counter`, `wrap <- cnt @3` and `wrap <- rst @3`: not excited by these pulses.

### Suites
- `ctest -L coi`: 25/25.
- `ctest -LE "determinism|coi"`: 65/65.
