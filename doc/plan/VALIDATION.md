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
- **HARM's sampling convention** (confirmed by measurement: HARM mines `G(a -> X q)` for `q <= a`). HARM takes the values in effect just before each rising edge. The reason: simulators dump VCD values from the end of the time step, after nonblocking assignments, while SVA concurrent assertions sample their values in the Preponed region, i.e. before the edge's updates. Sampling before the edge makes HARM see what an assertion would see in simulation. `perturb.py` samples the same way. A first version sampled just *after* the edge; every input-to-register depth then looked one cycle too short. The sampler was fixed and checked on that trace.
- **A4, non-influence:** 120 (source, excluded target) pairs checked across the 6 designs, **0 violations**. Only the parameters `N` and `W` can't be forced.
  - **Sensitivity:** in a copy of `multipath`, deleting the edge `z <- rb` (or the whole `z` entry) is caught: forcing `b` or `rb` changes `z`.
  - The script also checks visible signals that `coi.json` omits.
- **A5, depth evidence:** **102 of 105** claimed (source, target, depth) observed with one-cycle pulses (5 seeds × 4 pulse cycles × 2 values). The 3 not observed are structural paths whose effect can't, or rarely can, be excited, which a structural cone allows:
  - `fsm`, `finished <- go @1`: `go` only switches IDLE/RUN, and `finished` is 0 in both. The effect is impossible.
  - `counter`, `wrap <- cnt @3` and `wrap <- rst @3`: not excited by these pulses.

### Suites
- `ctest -L coi`: 25/25.
- `ctest -LE "determinism|coi"`: 65/65.

## H6: COI rank mode (2026-10-05, macOS arm64, g++-13)

### Acceptance tests
They were written first and committed failing in `c8abf51`.

| Test | Result |
|---|---|
| A1 leaf offsets, 16 formula shapes | pass |
| A2 COI metrics, 19 assertions on `multipath` + 5 on `counter` (saturated depths) + the trace-name check | pass. All expected values computed by hand from D-014, on cones validated by simulation in H4 |
| A3 configuration errors (no `<coi>`, `mode="filter"`, missing file, `version` ≠ 1) | pass |
| A4 end to end on `multipath` with `<sort exp="coiDepthFit"/>` | pass. HARM mines exactly the 7 hand-derived assertions, with the hand-computed `coiFrac`/`coiDepthFit`/`coiUnknown` in `--dump-assertion-info`. **One correction after implementation:** the hand-written ordered baseline had two equal-score lines in the wrong order (`XXr2` sorts before `Xr1`, since `X` < `r` in ASCII: the D-001 tie-break). Values and set unchanged |
| A5 no change without `<coi>` | pass: all H0–H4 regression and determinism tests unchanged |

### Suites
- `ctest -L determinism`: 23/23, including `h6_multipath_rank`.
- `ctest -L coi`: 25/25 (H4, unchanged).
- `ctest -LE "determinism|coi|verilator"`: 68/68 in 6 of 8 parallel runs (`-j6`); see below.

### Open finding: intermittent crash under parallel load (not yet explained)
- **What happens:** in 2 of 8 parallel runs (`ctest -j6`) after H6 was built, one test binary crashed with a segmentation fault. Once it was `PropositionOracleTest` (H1), once `Z3EquivalenceTest` (H2).
- **What has been ruled out:**
  - **Not reproducible in isolation:** 0 crashes in about 40 isolated runs, 25 of them under lldb, and 0 in 12 runs under lldb with the rest of the suite in parallel.
  - **No heap errors under Guard Malloc** (`libgmalloc`): page-guarded allocations, scribbled frees. Clean for `PropositionOracleTest`, `PropositionLanguageTest` and `Z3EquivalenceTest` (without the wide random test, for time).
  - **Not memory exhaustion:** peak resident memory is 112 MB and 181 MB on a 34 GB machine.
- **Not yet determined:** whether it predates H6. The binaries that crashed don't use H6 code, and earlier milestones ran parallel suites about 8 times without a crash, which is not enough to conclude either way.
- **Next step:** an AddressSanitizer and UndefinedBehaviorSanitizer build on the Linux machine. Homebrew g++-13 has no ASan on macOS. Until then, it's recorded here and in the H6 report, not hidden.

## H3: semantic redundancy reduction (2026-10-05, macOS arm64, g++-13)

### Acceptance tests
They were written first and committed failing in `60be5aa`.

| Test | Result |
|---|---|
| A1 hand-labelled pairs (`pairs.txt`, 37) | pass. **One pair changed after the first run:** `G(a -> b U c)` doesn't parse, because HARM's temporal grammar has no strong until. It was replaced by `G(a -> F b)` vs `G(a -> b)`, same label `SKIPPED` (not safety). Its label and the 36 others are unchanged |
| A2 bounded oracle, 310 generated pairs, every boolean trace of 3 atoms up to length 6, judged by **HARM's own evaluator** | pass: 239 implications claimed, 10 skipped (liveness), **0 unsound**. The first implementation (Spot over infinite words only, as D-004 was approved) had **1 unsound claim**: `G({b ##2 !a} \|-> X (b && !b))` ⇒ `G({b ##2 !a} \|-> (b && !b))`, refuted on a 3-cycle trace. That led to the D-004 amendment (see DECISIONS, H3_PLAN F5) |
| A2, second set: 200 pairs in mined shapes (`gen_mined_pairs.py`: SERE `&&`/`&` antecedents, `##1`/`##2` sequences, `\|=>`, `W`, `R`) | pass: 152 claimed, 1 skipped, **0 unsound**; 75 pairs contain SERE conjunction nodes. **Added after implementation:** A3 showed that mined antecedents (`{a && b}`) are SERE conjunctions, which the first set never produced and the first model rejected. The test is answer-agnostic (it checks claims against HARM's evaluator), but its thresholds were set after a first run: "> 100 pairs with SERE conjunctions" was lowered to "> 50", because `{a && b}` often parses as one boolean leaf |
| A3 `--reduce implies` on `reduce.csv`/`reduce.xml`: hand-derived output and `--dump-implications` | pass: the three conjunction variants are dropped, with exactly the hand-derived kept assertions |
| A4 determinism of A3 | pass |
| A5 without `--reduce implies`, baselines byte-identical | pass: all regression and determinism tests unchanged |

### Not part of the acceptance tests, also checked
- **`--keep weaker` and `--keep ranked` on A3:** checked by hand.
  - `weaker` keeps the three conjunctions and drops `G(a -> c)` and `G(d -> c)`.
  - `ranked` keeps the two frequency-0.5 assertions.
- **Error paths:** `--keep` or `--dump-implications` without `--reduce implies` is an error.
- **Synthetic ground truth** (`s6 = X(s0 || s1)`, `s7 = s2 && s3 || s4`, 8 signals, 400 cycles, 6 templates): 116 mined assertions, of which 112 are dropped. The 4 kept are exactly the planted relations:
  - `G(s0 -> X s6)`;
  - `G(s1 -> X s6)`;
  - `G(s4 -> s7)`;
  - `G({s2 && s3} -> s7)`.

  12 sampled records of the dump were checked by hand.

### Performance (acceptance item 5)

| Case | Assertions | Pairs checked | Reduction time | Total, `implies` / `syntactic` |
|---|---|---|---|---|
| `bl_master1k` (no `--min-frank`) | 31 | 332 | 0.04 s | 14.96 s / 15.05 s (×1.0; mining dominates) |
| `camellia` | 3 | 0 | 0 s | 0.11 s / 0.10 s |
| synthetic (above) | 116 | 5,439 | 0.06 s | 0.23 s / 0.16 s (×1.4, including Z3 canonicalisation) |

- **`camellia` found two problems:**
  - **The example's `camellia.xml` is not valid XML** (raw `&`), so rapidxml mangles the templates, and its propositions lack the `camallia_u::` scope that `--vcd-r 1` gives. This happens before any H3 code runs; the measurement used a fixed copy. Not fixed in the repository (out of scope); to be raised separately.
  - **A real H3 performance bug.** Its assertions span 25 cycles (`X[23]`). Spot's infinite-word automaton for `G(a -> X^k b)` needs about 2^k states, and the first finite-trace model tracked all pending instances of both assertions, which is exponential as well. `--reduce implies` ran for over 10 minutes before being stopped. The fixes:
    - assertions spanning more than `maxImplicationDepth` = 10 cycles are never reduced;
    - the finite-trace search follows one chosen instance of the dropped assertion, not all of them;
    - the search gives up after 20,000 states, which means "not proved", so both assertions are kept.

    All three only remove claims. A1 and both A2 sets were rerun after these changes and are unchanged: 239 and 152 claims, 0 unsound.

### Suites
- `ctest -j6 -LE slow`: 100/100, both before and after the performance fixes (2 runs; no intermittent crash this time).
- Regression test for the `camellia` bug: `ImplicationTest.deepAssertionsAreSkippedQuickly`. A 24-cycle pair is `SKIPPED` in 0.14 s, and a 10-cycle pair is still decided.

### Still pending
- Cross-check with USM-T's `semantic_equivalence`: needs Linux.

## H1c: end-of-trace semantics, `--trace-end sva` (2026-10-05, macOS arm64, g++-13)

### Acceptance tests
They were written first and committed failing in `e11f05c`. The SVA printer fix that A2 needed is in `2427893`.

| Test | Result |
|---|---|
| A1 hand-derived verdicts: 33 cases × 2 modes (`F`, `X`, `!X`, `W`, `!(W)`, nesting, `\|=>`, sequences) | pass. Before the implementation, every `harm`-mode verdict already matched, and exactly the 11 expected `sva` cases failed |
| A2 **independent oracle** (`tests/oracle/sva_finite_semantics.py`): written from IEEE 1800 Annex F / the truncated-path semantics, it parses HARM's printed SVA with the standard's precedence. 297 generated assertions × 4,680 traces (3 atoms, lengths 1–4) × 2 modes | pass, **0 disagreements** in both modes. 3 of the 300 generated formulas cannot be evaluated by HARM at all (see the open finding below) |
| A3 `process` with `--trace-end sva`: expected output = the baseline filtered by the oracle (not by HARM), 138 → 76 assertions | pass, identical. Two of the 62 drops were checked by hand on the CSV traces: `case9` ends with `Assess_Loan_Risk`, so `not nexttime …` and `s_eventually Assess_Eligibility` fail there |
| A4 H3 oracles with `--trace-end sva`, both sets | pass, 0 unsound (239 and 152 claims) |
| A4, added after its first run: 150 strong/weak twin pairs (`!X p` vs `X !p`, `!(p W q)` vs its weak form) in both modes, plus 4 hand labels | pass, 0 unsound in both modes (96 claims in `sva` mode). **Why added:** in the original sets, the only strong operator was `F`, which D-004 skips, so the claims were identical in both modes and didn't test the new model. **One hand label corrected after the run:** `!(b W c)` is a strong until, not syntactic safety, so D-004 skips it in both modes (I had labelled it `A_IMPLIES_B` in `sva` mode). The `!X` labels were right: equivalent in `harm` mode, `A_IMPLIES_B` in `sva` mode |
| A5 without the option: all baselines byte-identical | pass |

### Findings while writing the tests
- **F-a. SVA printer precedence bug, fixed.** HARM printed SVA with its own LTL precedence. So `(b W c) && X X F b` came out as `b until c and nexttime nexttime s_eventually b`, which SystemVerilog parses as `b until (c and …)`.
  - The fix adds brackets only, and only in SVA output. Every existing baseline is unchanged.
  - Regression test: `EndOfTraceTest.svaPrecedence`, 6 cases.
  - H1's Verilator replay could not see it, because its templates never combine `and`/`or` with `until` or `s_eventually`.
  - **One existing unit expectation was wrong and is corrected.** `svaParserPrinterTests.parse_print7`, written in H1 for D-002, expected `G(b_0 -> Fb_1 W b_2)` to print as `b_0 |-> s_eventually b_1 until b_2`. In SystemVerilog that means `s_eventually (b_1 until b_2)`, so it encoded the bug. It now expects `(s_eventually b_1) until b_2`.
- **F-b.** Spot 2.9.7's `from_ltlf` reads `X` as **weak** (`X b` becomes `X(!alive | b)`). My earlier note, which assumed strong, was wrong. A first implementation built on it failed A1 on every `nexttime` case and was corrected.
- **Open finding (predates H1c, not fixed):** HARM cannot evaluate some formulas that its grammar accepts.
  - Spot gives a non-deterministic automaton for `F X X (a W c)`.
  - Spot gives transition-based acceptance for some `W` nested in `W` (e.g. `(F a W b) W a`), and `buildAutomatonFromSpot` throws on it (`state_is_accepting()`).

  None of HARM's shipped templates have these shapes. To be raised as a separate issue.

### Not available here
- A commercial simulator check (Questa/VCS) of `s_eventually` and `not nexttime` at the end of a simulation. Verilator 5.034 rejects `s_eventually` as unsupported, and Icarus has no concurrent assertions. A2 relies on the standard's semantics instead.

### Suites
- `ctest -j6 -LE slow`: 104 tests. 103 passed on the first run; the one failure was `parse_print7` (above), and it passes after the correction.

### Performance
`--trace-end sva` costs one linear pass over the instances still pending at the end of each trace. `process`: 0.09 s in both modes. `bl_master1k`: 14.84 s vs 14.90 s.

## H7: COI filter mode (2026-10-05, macOS arm64, g++-13)

### Acceptance tests
They were written first and committed failing in `2838651`, after the permutation fix `9678656` (see the findings below).

| Test | Result |
|---|---|
| A1 per-consequent oracle (H7_PLAN F3) on 5 fixtures: the union of rank runs on configurations restricted by `tests/coi/restrict_config.py` (cones read from `coi.json` in Python) equals filter output | pass, exactly: counter 11 = 11, arbiter 45 = 45, fsm 46 = 46, multipath 28 = 28, structs 19 = 19 |
| A2 no out-of-cone antecedent; `coiFrac` = 1 | pass, 0 violations |
| A3 plain templates: filter = rank post-filtered with `coiFrac == 1` | pass on all 5, e.g. multipath 12 of 87 |
| A4 `CoiInfo::inCone`, 12 hand cases | pass |
| A5 determinism (`h7_multipath_filter`); the warning printed exactly once; baselines unchanged | pass |

### Mutation test of the oracle (not in the plan, done to check that A1–A3 can fail)
| Planted bug | Caught by |
|---|---|
| M1: decision-tree candidates not pruned | 4 of 5 fixtures, by A1 and A2 (`structs` doesn't separate it) |
| M2: "any variable in the cone" instead of "every variable" | **at first, no fixture.** All configuration propositions had one variable, so the two rules agreed. After adding two multi-variable propositions per configuration: 4 of 5, by A1 and A2. A3 cannot catch it, because both of its sides use HARM's rule; A1's independent rule does |

The multi-variable propositions were added to the test inputs after the first run, for this reason. Each configuration's comment says so.

### Search-space reduction (A6)
| Fixture | Permutations | Decision-tree candidates (summed over consequents) | Assertions, filter / rank | Mining time, filter / rank |
|---|---|---|---|---|
| counter | 259 → 84 | 98 → 40 | 11 / 61 | 0.007 s / 0.022 s |
| arbiter | 368 → 192 | 128 → 64 | 45 / 74 | 0.017 s / 0.031 s |
| fsm | 504 → 138 | 162 → 60 | 46 / 126 | 0.015 s / 0.043 s |
| multipath | 504 → 50 | 162 → 24 | 28 / 129 | 0.005 s / 0.041 s |
| structs | 504 → 53 | 162 → 20 | 19 / 82 | 0.005 s / 0.039 s |

The fixtures are small, so the times only show the trend. There is no `coi.json` for larger designs until H5.

### Findings
- **F-a (bug that predates H7, fixed in `9678656`): HARM hung when a template had more placeholders of one kind than propositions in the domain**, e.g. `G(P0 && P1 -> X P2)` with one antecedent proposition.
  - `computeBinomialCoefficient(n, k)` with `k > n` recursed in exponential time, and then an empty permutation list crashed `genPermutations`.
  - Now such a template has no permutations. Regression case: `h7_small_domain`, with its output derived by hand.
- **F-b (predates H7, not fixed):** HARM cannot load the `hier` fixture's trace, because it contains a signal named `W`, which is reserved (weak until). So `hier` is not in H7's tests. H4 and H6 only ever checked it in Python. To be raised with the other grammar issues.
- **Test change (H6):** `h6_error_coi_filter` expected "not supported before H7". It became `h6_error_coi_mode` (an unknown mode is rejected).

### Suites
- `ctest -j6 -LE slow`: 113/113 on the final code.

## H5: `harm-coi` generator (2026-10-06, macOS arm64, Python 3.12, pyslang 12.0.0)

### H5a spike and D-006
Results in `H5_PLAN.md`, section "H5a results"; code in `doc/plan/h5a_spike/`.
- **pyslang:** the throwaway extractor reproduced all 6 fixtures exactly.
- **yosys + yosys-slang:**
  - yosys-slang is now "sv-elab", and Homebrew's yosys 0.51 is too old for it;
  - with the OSS CAD Suite's yosys 0.69 it works, but it loses struct fields and parameters.
- **D-006 = pyslang**, decided by the user.

### Acceptance tests
Written first and committed failing in `e43c091`, against a stub that raised `NotImplementedError`. Implemented in `c3f11eb`.

| Test | Result |
|---|---|
| A1 `coi.json` = hand-written `expected_coi.json` (order-insensitive, `meta.generator` aside), and `check_coi.py` accepts it against the trace with HARM | pass, 6/6 exact (`hier` included: `check_coi.py` reads its names from the VCD) |
| A2 direct edges (`--edges`) = hand-written `edges.txt` | pass, 6/6 exact |
| A3 `perturb.py influence` on the generator's output | pass, 6/6 fixtures (for these it equals the H4 check, since the output is identical) and the new `constructs` design: 606 pairs |
| A4 constructs, hand-written edges (pytest) | pass, 22/22. 16 were committed failing with the other tests: the planned constructs plus async reset, `for` loop, struct/trace naming and error cases. One of their expectations was changed (F2). 6 were added during implementation: `case` completeness, falling-edge register, another clock, interface through a modport port (F3), several clocks, process-local temporary |
| A5 Linux | **pending**, like the other Linux checks |

### Independent validation
- **yosys cross-check** (`tests/coi/xcheck_yosys.py`, yosys 0.69 from OSS CAD Suite):
  - bit-level reachability after `proc; flatten; techmap`, aliases resolved;
  - **0 unsound on all 7 designs**. One over-approximation is reported: `constructs` `rp <- rp`, the hold of a partially written register (`rp[0] <= a` keeps bits that are in fact never driven).
  - **Its own mutation test:** removing one true edge from harm-coi's output was caught in 3 of 4 cases. The miss, counter `wrap <- en @0`, keeps the signal-level reachability through `cnt`, and only depths can show it (A1/A2).
- **Simulation on the new design `tests/input/h5/constructs/`** (testbench, trace; the A4 constructs in one design):
  - `perturb.py reproduce` and `influence` pass;
  - `perturb.py depths` (report only): 50 of 53 claimed (source, target, depth) observed. Not observed: `rp <- a @2`, `rp <- a @3`, both through the over-approximate hold above, and `r <- c @3`.

### Mutation test of the oracles (bugs planted in harm-coi, each oracle run on its own)
| Planted bug | A4 | A1/A2 (6 fixtures) | A3 simulation (7) | yosys (7) |
|---|---|---|---|---|
| M1: no control dependencies | caught | counter, arbiter, fsm, structs | counter, arbiter, fsm, structs, constructs | counter, arbiter, fsm, structs, constructs |
| M2: a register not assigned on every path does not hold | caught | arbiter, structs | — | — |
| M3: no `y <- t @0` for a once-assigned visible signal | caught | — | constructs | constructs |
| M4: register delay 0 instead of 1 | caught | all 6 | — | — |
| M5: output port connections ignored | caught | hier | hier, constructs (\*) | — (\*\*) |
| M6: asynchronous reset without depth 0 | caught | — | — | — |

- **What only one family can see:**
  - the simulation and yosys checks cannot see self-dependencies (M2) or depths (M4, M6): they are signal-level checks of non-influence;
  - A1/A2 cannot see constructs that are not in the fixtures (M3).
  - A4 caught all six.
- \* run before the oracle change in F4c, which counted unknown signals as having an empty cone.
- \*\* **The safety net worked:** with M5, slang still reports drivers for the signals the walk missed. They became `unknown`, so harm-coi claimed nothing wrong, and yosys had nothing to refute.

### Findings
- **F1 (spike):** the front-end comparison is in `H5_PLAN.md`. Practical consequences:
  - pyslang needs Python ≥ 3.11 (macOS' system Python 3.9 has no wheel);
  - Homebrew's yosys 0.51 cannot run the cross-check; it is skipped with a message.
- **F2, test change after the first implementation: A4 "blocking temporary".**
  - **The case:** `logic t; always_comb begin t = a & b; y = t | k; end`, where `t` is a module-level signal.
  - **First expectation:** `y <- a, b, k`, "not t".
  - **Found by:** the yosys cross-check on `constructs` (`y_tmp` reaches `t`). The simulation oracle agrees: forcing `t` changes `y`.
  - **Why the old expectation was wrong:** filter mode would have pruned the genuine assertion `G(t -> y)`.
  - **Expectation now:** `y <- a, b, k, t`, with `t` at depth 0. A new test keeps the old expectation for a process-local `t`, which is substituted.
  - **What changes:** only harm-coi's direct edges. The cones are the same, because the closure through `t` gives `a` and `b` at depth 0 anyway. HARM is not changed.
- **F3, test change: A4 "interface through modport port"**, added during implementation. It gained `target u::clk` after the decision that a visible alias of the clock is a target with no sources (D-019). `check_coi.py` requires every visible name to be a target or unknown.
- **F4, oracle changes in `tests/coi/perturb.py`** (H4's simulation check):
  - (a) `--coi <file>`, so that it can check generator output. The default is unchanged.
  - (b) a pair whose two names share a VCD identifier (one net in the simulator) is not checked, and the clock's net is never forced. Both are printed. **On the H4 fixtures this drops 2 pairs** (`hier` dout/g[2]::w, `multipath` z/rb), which passed before.
  - (c) unknown signals are still forced as sources, but are not checked as targets: `unknown` makes no claim. This has no effect on the H4 fixtures, which have no unknowns.
- **F5, conservative choices recorded in D-019:**
  - a `unique`/`priority` `case` is not trusted to be complete;
  - registers on another clock, latches, `inout`, tasks and the like are `unknown`;
  - a target that reaches an unknown is unknown.
- **F6:** `check_coi.py` needs `jsonschema`, so the harm-coi test extras include it.

### Suites
- `ctest -j6` (all labels, slow included), on the final code: **162/162**, 31 min.
  - The regression baselines are unchanged; H5 does not touch HARM's C++.
  - The suite includes the 23 H5 tests: `h5_unit`, `h5_generator_*` ×7, `h5_influence_*` ×7, `h5_xcheck_yosys_*` ×7 and `h5_reproduce_constructs`.
- **The yosys cross-check ran with OSS CAD Suite's yosys** (`-DHARM_COI_YOSYS=…`). Without a yosys that has `read_slang`, those 7 tests are skipped with a message.
- **Linux: pending** (A5).

## H8: depth-aware COI filter (2026-10-06, macOS arm64, g++-13)

### Acceptance tests
Written first and committed failing in `7b52d80`, against stubs. Implemented in `a23ec43`; tests strengthened after the mutation test in `22f7edf` (see "Test changes").

| Test | Result |
|---|---|
| A1 `CoiDepthTest`: D-007 table (12 template shapes), `insertionIndex`, D-020 `fits` (13 hand cases × 3 modes on `multipath`, 7 checks on `counter`), `->` offsets (F6) | pass. The expectations were written before the implementation; none changed |
| A2 plain templates: filter (`exact`/`bounded`) = rank post-filtered by the Python D-020 rule on the printed text; for `exact`, HARM's `coiDepthFit == 1` selects the same set | pass, 6 designs × 2 modes |
| A3 single-index decision trees: filter = union of per-(consequent, template) restricted rank runs | pass, 6 × 2 (e.g. multipath `exact` 9 = 9 from 8 runs) |
| A4 soundness on every template, multi-index trees included, offsets parsed from the text | pass, 0 violations on 6 × 2 |
| A5 errors (`depth` with rank mode, unknown value); `determinism_h8_multipath_exact`; H7 tests and all baselines unchanged | pass |
| A6 report | below |

### A6: search space and output (filter mode)
| Design | Assertions: `any` / `bounded` / `exact` | Permutations, `exact` (`any`) | (candidate, index) pairs, `exact` |
|---|---|---|---|
| counter | 24 / 21 / 13 | 721 → 214 (225) | 332 → 277 |
| arbiter | 76 / 72 / 51 | 1032 → 513 (536) | 544 → 401 |
| fsm | 83 / 75 / 58 | 1422 → 353 (375) | 495 → 385 |
| multipath | 55 / 41 / 37 | 1422 → 63 (129) | 120 → 59 |
| structs | 34 / 30 / 25 | 1422 → 85 (140) | 118 → 65 |
| constructs (H5) | 16 / 12 / 11 | 3156 → 96 (182) | 191 → 111 |

- **Output:** `exact` removes 26–46% of filter mode's output, `bounded` 5–25%.
- **Mining times** are about 0.12 s everywhere: the fixtures are too small to show a difference.
- **No `bl_master`:** it has no RTL (F5 of the plan).
- **Why `bounded` changes less on `counter`, `arbiter` and `fsm`:** their cones are saturated (register feedback), so what `bounded` prunes there is mostly items after the consequent (`d < 0`, `->` templates).

### D-007, checked by hand
On mined `counter` assertions, one or more per operator and implication, the distance of each tree item was counted by hand from the printed formula and compared with the table. All agree; the cases are listed in D-007.

### Mutation test of the oracles (bugs planted in HARM, after `22f7edf`)
| Planted bug | Caught by |
|---|---|
| M1: distance off by one in `fits` | A1, H6's `CoiMetricsTest` and `h6_assertion_info`, all 12 H8 checks |
| M2: `\|=>` treated as `\|->` in `leafOffsets` | A1, `CoiMetricsTest`, 7 H8 checks |
| M3: `->` anchored at the end of the antecedent (F6 reverted) | A1, 11 H8 checks |
| M4: `bounded` and `exact` swapped | A1, `CoiMetricsTest`, 11 H8 checks |
| M5: saturation dropped from `exact` | A1, `CoiMetricsTest`, `h8_depth_fsm_exact` |
| M6: the tree's index ignored (every index checked as index 0) | 11 H8 checks (not A1: it does not run the tree) |

- **The first run, before `22f7edf`, showed gaps:**
  - M2 and M5 were caught only by the gtests;
  - no fixture had a plain `|=>` template or a distance beyond `max_depth`;
  - A2 `exact` compared with HARM's own `coiDepthFit`, which shares the mutated code.
- **The fix:** two templates in every configuration, and A2 against the Python rule as well. M2 is then caught by 7 fixture checks and M5 by one.

### Findings
- **F6 (fixed): `leafOffsets` anchored the consequent of `->` at the end of a multi-cycle antecedent.**
  - **Effect before the fix:** `coiDepthFit` (H6) was wrong for those templates. HARM evaluates them from the start: mining `G({a ##1 b} -> X c)` finds `c` one cycle after `a`.
  - **The fix** changes rank-mode `coiDepthFit` only for `->` with a multi-cycle antecedent. No baseline or H6 test has such a template, and none changed. H3's depth cutoff uses the same offsets; H3's tests are unchanged.
- **F7 (fixed in H1d, D-021): `--sva` printed `G({s} -> X c)` as `s |=> c`.**
  - The printed SVA anchors `c` at the end of `s`, which is not what HARM mined. A start-anchored translation is `(s) implies nexttime c`.
  - It affects only `->` templates with multi-cycle antecedents. No example or trivergence template uses them, but the trivergence hand-off mentions it.
- **F8 (fixed in H1d, D-021): HARM's Spot-LTL printer wrote `X(en && wrap)` as `Xen && wrap`,** which Spot reads as `(X en) && wrap` (`ltlfilt -p` gives `(wrap) & (X(en))`). The bug is in HARM's printer, not in Spot.
  - It affects only the Spot-LTL text: the default output and the dump.
  - The SVA output is correct (`|=> en && wrap`), and so is H3's reducer, which writes every Boolean connective in parentheses (`skeleton`).
- **Spot's own check of F6 and F7** (`third_party/spot/bin/ltlfilt --equivalent-to`, added after review questions):

  | Formula | Compared with | Spot |
  |---|---|---|
  | `G({a;b} -> X c)` | `G(a && X b -> X c)` | equivalent: `->` starts the consequent with the antecedent (F6) |
  | `G({a;b} []=> c)` (`\|=>`) | `G(a && X b -> X X c)` | equivalent: `\|=>` starts it after the end |
  | `G({a;b} -> X c)` | `G({a;b} []=> c)` | **not equivalent** (F7) |
  | `G({a} -> X c)` | `G({a} []=> c)` | equivalent: F7 needs an antecedent longer than one cycle |
- **F7 on a trace:** `a` at `t`; `b` and `c1` at `t+1`; `c2` at `t+2`.
  - HARM mines `G({a ##1 b} -> X c1)` and `G({a ##1 b} |-> X c2)`.
  - `--sva` prints them as `a ##1 b |=> c1` and `a ##1 b |=> c2`. `c1` and `c2` are never true together, so these cannot both hold; in SVA the first is false.
  - Verilator's replay (H1) reports both as unsupported (multi-cycle sequences), so it could not catch this.
- **Test changes after the first implementation run:**
  - **A4 parses the Spot-LTL text instead of the SVA** (F7). With SVA it flagged `r1 ##1 !a |=> y`, which HARM had mined as `{r1 ##1 !a} -> X y`, a correct `exact` result.
  - **The A4 parser fixes:**
    - a leading `X` applies to the rest of the operand (F8);
    - `:` (fusion) no longer matches inside `bus::valid`. Before the fix, scoped names were split into unknown "signals", so `structs` and `constructs` were checked too leniently. The strengthened A2 exposed it.
  - **After the mutation test:** the two templates and the A2 change described above.
  - No expected value of A1 changed. A2/A3 compare HARM runs, so they have no hand-written expected values.

### Suites
- `ctest -j6` (all labels): **178/178**, 31 min. Baselines byte-identical.
- **After merging `dev` (H1d) into the H8 branch:** `ctest -j6` gives **180/180**. H8's depth checks pass with H1d's Spot printing (`X(...)`), which the A4 parser reads with the same rule.
- **Linux: pending.**

## H1d: printing fixes F7 and F8 (2026-10-06, macOS arm64, g++-13)
Requested by the user after H8's findings. Tests written first and committed failing in `447807d`.

| Test | Result |
|---|---|
| A1 `PrintingTest`, hand-written texts | pass: 8 F7 cases, 3 F8 cases, 9 unchanged cases. Before the fix, all 11 F7/F8 cases failed with the old texts and all unchanged ones passed |
| A2 `h1d_spot_equivalence` (Spot `ltlfilt`) | pass: 6 F7 meanings equivalent to HARM's formulas; 3 F8 texts parse as intended. Every control fails as it should: the old SVA meanings are not equivalent, and the old Spot texts parse differently |
| A3 baselines | 1 changed, `sub_platform1k` (see below); all others byte-identical |

- **The baseline change:**
  - 46 of 91 assertions change, from `|-> X<a && b>` to `|-> X(<a && b>)`.
  - Rewriting the old baseline that way gives the new one exactly: same assertions, same order. So nothing else changed.
  - Recaptured with `HARM_REGRESSION_CAPTURE=ordered`, as part of the requested fix.
- **Edit rules:** they match against the legacy SVA printing (D-002). The F7 change does not apply to it, and F8 only touches Spot text, so existing `<edit>` rules are unaffected. `EditTest` and the `edit` example pass.
- **Also found:** before the fix, a property antecedent printed invalid SVA: `G(a && X b -> X c)` gave `a and nexttime b |=> c`, and `|=>` needs a sequence on its left. It is now `(a and nexttime b) implies nexttime c`.
- **Suites:** `ctest -j6`: **164/164**, 31 min. Linux: pending.

## H9: out-of-cone report (2026-10-06, macOS arm64, g++-13)
Tests written first and committed failing in `e574590` (all 12 failed: the option did not exist). Implemented in `ddddff6`.

| Test | Result |
|---|---|
| A1 hand-written reports, `multipath` (9 propositions, 2 origins) and `structs` (scoped names, a numeric with origin) | pass: 60 and 70 out-of-cone pairs, equal on texts, origins, `numeric`, `outside`, `coneUnknown` |
| A2 unknown signals, `constructs` with a `coi.json` lacking the target `t` (and `unnamedblk1::i` listed unknown) | pass: 6 out-of-cone pairs; the unknown entries and the three `coneUnknown` consequents as written by hand; `t && a` against `k` is out (its known `a` settles it) |
| A3 cross-check with the rule recomputed in Python, on H7's 5 configurations and H8's `constructs` | pass: 24–117 pairs per configuration |
| A4 mining output with and without the option (`multipath` rank, H7 `multipath` filter); a context without `<coi>` | pass: identical outputs; `"coi": null` and the note printed |

- **Hand values vs. the Python rule:** before any implementation, the hand-written expected reports were compared with `check_coi_report.py`'s own computation. They agreed on all three designs.
- **Mutation test** (bugs planted in HARM's report):

  | Planted bug | Caught by |
  |---|---|
  | "any variable in the cone" instead of "every variable" | 6 tests (A1 ×2, A3 ×4) |
  | unknown variables counted as out | A2 (`h9_expected_constructs`) |
  | a proposition paired with itself | 9 tests |
  | origins dropped | A1 ×2 |

  A3's configurations have no origins and no unknown propositions, so only A1/A2 catch those two bugs.
- **Test change:** `structs.xml` declared its numeric with `loc="dt"`, which HARM expands into propositions at load. It was corrected to `loc="[dt]"` (a numeric candidate, as intended) before the first implementation run. The expected report did not change.
- **Suites:** `ctest -j6` gives **192/192**, 31 min. Baselines byte-identical. Linux: pending.

## H10: RTL predicate harvesting (2026-10-06, macOS arm64, Python 3.12, pyslang 12.0.0)
Tests written first and committed failing in `60f3f10` (15 of 15 failed: `--predicates` did not exist). Implemented in `7c54f99`.

| Test | Result |
|---|---|
| A1 hand-labelled predicates (`expr` → `targets`), 6 H4 fixtures + `constructs` | pass, all equal on the first full run: counter 4, arbiter 6, fsm 6, structs 1, constructs 9, multipath 0, hier 0 (its `generate if` is not harvested) |
| A2 HARM loads the emitted configuration on each fixture's trace and mines, without `--skip-invalid-props` | pass on the 5 fixtures with predicates; `multipath` and `hier` have nothing to load |
| A3 translation unit tests (pytest) | pass, 13: enum, parameter, constant on the left, `'0`, `!=`/`<`, 1-bit comparisons, bit select, async reset value, compound condition and atoms, case labels, struct field and interface, invisible signal dropped, elaboration-time `if` and loop variable, the reset rule on a non-reset condition |
| A4 `coi.json` with predicates passes `check_coi.py` | pass on all 7 |

- **Z3 duplicates** (`CoiPredicateTest`, HARM's H2 canonicaliser on the labelled predicates): every label parses as a HARM proposition, with 0 duplicates (counter 4/4 classes, arbiter 6/6, fsm 6/6, structs 1/1, constructs 9/9).
- **Trace sanity** (report): no harvested predicate is constant on its fixture's trace (0 of 26). A planted constant, `cnt == 4'd15` on `counter`, is flagged, so the check works.
- **Mutation test** (bugs planted in `predicates.py`):

  | Planted bug | Caught by |
  |---|---|
  | enum value off by one | A1 `fsm`, A3 |
  | an invisible signal kept (named by its path) | A3 only: no fixture has a condition on an invisible signal |
  | literal width + 1 | A1 counter, arbiter, fsm, constructs; A3 |
  | reset-value rule removed | A1 counter, arbiter, constructs; A3 |

  A2 catches none of these, as expected: wrong values still parse.
- **Test adjustments before the first implementation run:**
  - two A3 tests switched to non-constant assignments, and one test added for the reset rule's side effect;
  - A2 skips HARM when nothing is harvested.
- **Suites:** `ctest -j6` gives **207/207**, 32 min. Baselines byte-identical. Linux: pending.

## H1b: x/z semantics, documented (D-011 option a, 2026-10-06)
- **The user's decision:** document the difference with SystemVerilog instead of adding an SV-semantics option. In HARM a proposition is true or false and complementary to its negation, which SV's three-valued evaluation would break. The plan for the option (D-024) is withdrawn.
- **`h1b_x_semantics`** (regression): 23 propositions on a 2-row trace with x values (`tests/input/h1b`).
  - HARM's value of each is pinned; pass.
  - The documented SystemVerilog value of each was checked with iverilog 12.0 (`!(!(e))` on the same values): 23/23 agree. HARM differs from SV on 9 of them, in both directions, as the README table says.
- **Sources for the SV values:** IEEE 1800-2017 §11.4.4, §11.4.5, §11.4.7, §16.6 (the user's copy), and §12.4 for values used as conditions ("tested for being zero"); iverilog agrees (`if`/`assert` on `4'b01x0` pass, on `4'b00x0` fail).
- **Correction:** D-011 and TRIVERGENCE_IMPACT had called x/z "the likely root cause" of trivergence M0 #33. M0 attributes #33 to inout sampling (#24); the text now says "may explain".
- **No change to HARM's code;** the default and every baseline are unchanged.

## H3b: atom-implication premises (2026-10-06, macOS arm64, g++-13)
Tests written first and committed failing in `e87b42b` (API stubs). Implemented in `6217c07`, sped up in `e9e311f`.

| Test | Result |
|---|---|
| A1 H3's 49 hand-labelled pairs (37 evaluated) with `--atom-premises`: only `G(cnt > 9 -> b)` / `G(cnt > 8 -> b)` changes, to `B_IMPLIES_A` | pass |
| A2 20 new hand-labelled pairs (`tests/input/h3b/pairs.txt`): ranges, FSM exclusions, `X`/`\|=>`/`##2`/decision-tree shapes, x/z-sensitive pairs, pairs facts do not help | pass, 20/20; 14 of them are labelled differently without premises (the other 6: one H2 equivalence and five `NONE`) |
| A2 oracle: every claim checked on 2,000 random traces per pair, in which `cnt` and `st` take x/z bits, with HARM's evaluator | pass, 0 unsound |
| A3 facts between atoms (Z3), hand-labelled: ranges, bit selects, `!=` vs `!(==)` under x/z, exclusion, signed, a factoring query with a 1 ms timeout (no fact) | pass, 13 |
| A4 without the option: H3's tests, dumps and all baselines unchanged; `--atom-premises` without `--reduce implies` is an error | pass |
| A5 the cap: with no queries allowed, every claim is H3's own; at the command line `--atom-premises-max 0` keeps all 3 and prints the message | pass |

- **Validation by enumeration** (`factsMatchEnumerationWithHarmsEvaluator`): the facts over `cnt`/`st` were re-checked with HARM's evaluator on all 4-valued values (4,096 rows). All 10 agree with Z3.
- **Mutation test** (bugs planted in HARM):

  | Planted bug | Caught by |
  |---|---|
  | M1 facts proved without x/z (2-valued encoding) | A3 |
  | M2 premises given to Spot but not to the finite-trace model | A2, the CLI test |
  | M3 `p → q` stored as `q → p` | A2 (6 unsound claims caught by the trace oracle), the CLI test |
  | M4 the cap ignored | A5 (gtest and CLI) |
- **F2 (from M1): why the x/z-sensitive pairs of A2 pass even with 2-valued facts.**
  - The facts relate atoms: in `!(cnt == 1)`, the atom is `cnt == 1` and the `!` is structure.
  - Only `p → q` and `p → ¬q` are asked. With a comparison `p`, which is false on x, those are vacuous on x cycles, so a 2-valued proof usually carries over.
  - The direction a 2-valued encoding would add wrongly, `¬p → q` (covering), is never asked; it is almost never valid for 4-valued signals.
  - A3 is the test that checks the encoding itself.
- **Effect and cost** (`--reduce implies` with / without `--atom-premises`, 8 threads):

  | Case | Dropped by the reduction | Final output | Reduction time |
  |---|---|---|---|
  | `sub_platform1k` (camellia design, numeric ranges) | 4 → **215** of 497 | 89 → **69** | 0.94 s → 5.3 s (first version: 33.8 s) |
  | `bl_master1k` without `--min-frank` | 0 → 0 of 31 | 31 → 31 | 0.04 s → 0.12 s |

  - The final `sub_platform1k` output loses exactly the 20 assertions the measurement's lower bound predicted.
  - Checked by hand: `G({state ∈ [0,4] ##1 true} |-> X RSTn)` is dropped for `G({!(state ∈ [5,12]) ##1 true} |-> X RSTn)`.
  - `camellia`'s own example is still the invalid XML noted in H3, so `sub_platform1k`, the same design, stands in for it.
- **Test corrections after the first run:**
  - A2's count of pairs that need premises: 14, not "at least 15" (miscounted when written);
  - A3: `i` is a 64-bit int (the Z3 encoding is exact only at 64 bits; with 32 bits the "no" case is "unknown", soundly);
  - A3: the timeout query `w64 * v64 == N ⇒ w64 != 1` was false (`w64 = 1`), so Z3 answered "no" at once; it was replaced by a true implication that needs factoring.
- **Suites:** `ctest -j6`: **211/211**, 31 min. Baselines byte-identical. Linux: pending.

## H11: evaluation, documentation, `--version`, Docker (2026-10-06, macOS arm64, g++-13; Linux 2026-10-07, Ubuntu 22.04, g++ 11.4.0, after H11b)
Tests written first and committed failing in `917e103` (`h11_version`, `h11_readme_commands`). `--version` implemented in `7c36fa3`.

| Test | Result |
|---|---|
| A1 `eval/run_eval.py` reproduces its own table: the fixtures re-run on HEAD (40 runs: all but C2, whose two runs take 20 and 30+ minutes) and the examples (51 runs), with `--check` against `eval/results/macos-*` | pass: every count is equal (assertions, dropped, permutations, DT pairs, mean `coiFrac`/`coiDepthFit`, coverage). Runs over 1 s differ by at most 2% in time; shorter ones vary more |
| A2 the macOS full suite on `d90e39d` (`v3-138-gd90e39d`), all labels | pass, 213 of 213 (1,931 s) |
| A1 Linux: the fixtures and examples with `--check` against `eval/results/macos-*` | first run: **not run**, HARM did not build (F-L1). After H11b: pass. All 97 runs (46 fixtures, 51 examples) have the Mac's counts in every column, `constructs` C2's timeout included (`eval/results/linux-*`) **Final (2026-10-08, after H11b–H11f, `v3-196-g29a0343`):** the examples (51 runs) still have the Mac's counts. The fixtures, on the new traces (H11e), equal H11e's Linux run in all 46 runs. Against the Mac's re-run: 40 of 46 equal; `structs` and `constructs` C0/C1/C3 differ (F-M2, H11e's "macOS checks") |
| A2 Linux `ctest` and harm-coi pytest | first run: **fail**, HARM did not build (F-L1). After H11b, on `v3-154-gc1735ca`: 206 of 213 pass (2,263 s, `ctest -j32`, Verilator 5.031). The 7 failures are the yosys cross-check (F-L3 below) **Final (2026-10-08, `v3-196-g29a0343`): pass, 226 of 226** (2,282 s), with Verilator 5.052, Icarus 13.0 and yosys 0.69 from `third_party`, including the 7 yosys cross-checks |
| A3 the Docker image | pass (after H11b): `docker/build.sh dev` builds HARM, Z3, harm-coi, Verilator and Icarus from `dev` @ `3b0a9ee`. Its fast tests pass, 172 of 172 (`ctest -LE slow`, 1,677 s) **Final (2026-10-08): pass.** `docker/build.sh ms/H11-linux` builds HARM with Verilator 5.052, Icarus 13.0 and yosys 0.69 from `third_party` (H11d), and its fast tests pass, 192 of 192 |
| A4 every `./harm` command in the README runs on a shipped example (`h11_readme_commands`) | pass |
| A5 `--version` prints `HARM <git describe>` (`h11_version`) | pass |

- **The tables:** `eval/results/macos-fixtures` (6 designs × C0–C7) and `eval/results/macos-examples` (17 examples × C0–C2).
  - The fixtures ran on `v3-131-g917e103 (dirty)`. The uncommitted part was the `--version` code (`7c36fa3`), the only source change since; A1's re-run on HEAD gives the same counts.
  - Assertions per configuration, fixtures:

    | Design | C0 | C1 | C2 | C3 | C4 | C5 | C6 | C7 |
    |---|---|---|---|---|---|---|---|---|
    | counter | 80 | 80 | 72 | 80 | 65 | 51 | 9 | 5 |
    | arbiter | 75 | 68 | 53 | 75 | 31 | 32 | 36 | 23 |
    | fsm | 96 | 85 | 71 | 96 | 73 | 61 | 46 | 27 |
    | multipath | 94 | 94 | 94 | 94 | 8 | 9 | — | — |
    | structs | 1,526 | 1,522 | 1,491 | 1,526 | 730 | 322 | 0 | 0 |
    | constructs | 4,438 | 4,388 | timeout | 4,438 | 2,135 | 1,862 | 101 | 2 |

  - **Examples, C0 → C1 → C2:** most are unchanged. The changes:
    - `sub_platform1k` 91 → 89 → 69;
    - `sobel` 30 → 17 → 9, fault coverage 100% in all three;
    - `process` 138 → 135 → 135;
    - `process_trace_end_sva` 76 → 73 → 73.
- **Cross-check with earlier milestones:**
  - **H3b:** `sub_platform1k` 89 → 69 with `--atom-premises`, as measured there.
  - **The regression baselines:** the examples' C0 counts equal them. Examples: `process` 138, `svaFunctions` 112, `sub_platform1k` 91, `sobel` 30 (plus its coverage section), `csvCheck` 0 (a check-mode example whose template fails).
  - **H10's predicate counts** explain C6:
    - `multipath` has no predicates, so it has no C6/C7 rows;
    - `structs` has one (`bus::valid`), so its only candidate is `G(x -> x)`, discarded as trivial: 0 assertions.
  - **H7/H8's search-space numbers** came from the fixtures' own configurations, with fixed-placeholder templates such as `G(P0 -> X P1)`.
    - The evaluation starts from `--generate-config`, which has decision-tree templates only. A permutation there is just the choice of a consequent, and a consequent is always in its own cone. So the permutation counts never drop (e.g. 34 → 34), and the filter acts on the decision-tree pairs instead (`structs` 11,965 → 7,411; `constructs` 65,858 → 56,892).
    - The direction matches H7/H8: the filter shrinks the search in every design.
- **Findings, checked by hand:**
  - **C5 (`exact`) gives more assertions than C4 on `arbiter` (32 vs 31) and `multipath` (9 vs 8).** On `multipath`, C4's two antecedents for `y` are 5 cycles long (`r2 ##1 !r2 ##1 r2 ##1 !a ##1 a`). C5 removes the candidates at the wrong distance, so the greedy tree finds three short ones (`!r2 && a`, `!r1 ##1 a`, `!a ##2 a`). This is not a bug: fewer candidates change which tree HARM builds.
  - **`constructs` C6's mean `coiFrac` is 0.022.** This is correct, not a bug:
    - the RTL's predicates are its conditions, and nearly all are on inputs (`sel` case labels, `a`, `b`, `s`, `rst`);
    - an input's cone is empty, and `q`'s cone is `{d, rst}`;
    - so 98 of the 101 assertions have no antecedent leaf in their consequent's cone (inputs predicting inputs, or `sel` predicting `q`): stimulus correlations, which rank mode scores 0;
    - C7's filter keeps the 2 structural ones (`rst |-> !q`).
    - For Paper A: on a small design, the RTL's predicates alone (C6) mostly give stimulus correlations; C7 is the intended combination.
  - **Cost of the reductions on large outputs:**
    - `structs`: mining 43 s, C1 148 s, C2 1,214 s;
    - `constructs`: C1 305 s, C2 over 1,800 s.
    - `--reduce implies` and `--atom-premises` grow with the square of the number of assertions. Recorded in `eval/LINUX.md` and for trivergence; making them faster is for after the release.
- **Fix during the run: the examples manifest.** It had trace paths in `args`, relative to the repository, while HARM runs in a temporary directory, so every example failed on a missing trace. The trace arguments were moved to the `trace` field, which is resolved from the repository root, and `faults` was added for `faultCov` and `sobel`. This changes no HARM behaviour, only the evaluation's input.

### Linux evaluation (2026-10-06, Ubuntu 22.04 x86_64, g++ 11.4.0, branch `ms/H11-linux` from `dev` at `1dc0609`)
- **Environment:**
  - The default `c++` is g++ 11.4.0, used for `third_party/install_all.sh` (Z3 4.13.4) and HARM (D-010). CMake 3.31.10.
  - There is no system `python3.12`. The venv was made with `uv venv --python 3.12` (CPython 3.12.6) instead of `python3.12 -m venv`. pyslang 12.0.0, pytest and jsonschema are installed.
  - The yosys cross-check is skipped: the only yosys here is 0.47, older than 0.67.
  - Verilator 4.210 is first on `PATH`. The AssertLLM2 traces were made with trivergence's image (Verilator 5.053).
- **`build/harm --version`:** none, because the build fails. HEAD is `v3-144-g1dc0609`.
- **After H11b (merged into this branch from `dev`):**
  - `build/harm --version`: `HARM v3-154-gc1735ca`.
  - The simulation oracles need Verilator ≥ 5. The checks above were run with OSS CAD Suite's Verilator 5.031, first on `PATH` and set with `-DVERILATOR_FOUND`.
- **`ctest` (A2) in detail:**
  ```
  97% tests passed, 7 tests failed out of 213
  Total Test time (real) = 2263.35 sec
  The following tests FAILED:
    h5_xcheck_yosys_{counter,arbiter,fsm,hier,structs,multipath,constructs} (Failed)  coi xcheck
  ```
  - Every Verilator oracle, `h5_unit` and the `h5_*` tests pass.
  - `ImplicationTest` passes in 1,688 s, under its 3,600 s timeout (F-L2, H11b).
- **The local designs (§4a, A1):** the counts are equal to the Mac's.
  - **Times:** Linux is slower on the runs over 5 s, by 1.2–1.4× (`structs` C2 1,505 s against 1,214 s), and 2.3× on `sub_platform1k` C2 (21.6 s against 9.4 s).
  - **Totals:** fixtures 4,146 s against 3,662 s; examples 139 s against 87 s.
- **Finding F-L3: the yosys probe accepts any yosys.** `tests/regression/CMakeLists.txt` (H5) registers the cross-check when `yosys -p "help read_slang"` exits with 0.
  - yosys exits with 0 even for an unknown command: it prints "No such command or cell type: read_slang".
  - With OSS CAD Suite's yosys 0.47 first on `PATH`, the 7 `h5_xcheck_yosys_*` tests are registered and fail:
    ```
    ERROR: No such command: read_slang (type 'help' for a command overview)
    yosys failed on counter
    ```
  - The cross-check is optional, and no yosys ≥ 0.67 is installed here.
  - **Fixed in H11c:** the probe runs `read_slang` on a one-line module (`cmake/HarmYosysProbe.cmake`).
- **Finding F-L1: HARM does not build on Linux (g++ 11, x86_64).** This blocks A1, A2, A3 and the evaluation.
  - The line is `src/exp/include/visitors/ExpToZ3Visitor.hh:73`, from H2 (`059d7de`), and it is the only compile error (`make -k`):
    ```
    ExpToZ3Visitor.hh:73:61: error: call of overloaded 'bv_val(long long unsigned int&, unsigned int&)' is ambiguous
       73 |   z3::expr bv(unsigned long long value) { return _ctx.bv_val(value, _U); }
    z3++.h:3806: candidate: z3::expr z3::context::bv_val(int, unsigned int)
    z3++.h:3807: candidate: z3::expr z3::context::bv_val(unsigned int, unsigned int)
    z3++.h:3808: candidate: z3::expr z3::context::bv_val(int64_t, unsigned int)
    z3++.h:3809: candidate: z3::expr z3::context::bv_val(uint64_t, unsigned int)
    ```
  - **Cause:** on LP64 Linux, `uint64_t` is `unsigned long`, so `unsigned long long` matches no overload exactly. On macOS, `uint64_t` is `unsigned long long`, which is why the Mac builds.
  - **Fix:** not applied here (`eval/LINUX.md`); it is a new milestone. A plausible fix is `bv(uint64_t)`, or a cast to `uint64_t` at the call.
  - **Status of the rest:**
    - `ctest`, the Docker image and the evaluation (§4a, §4b) did not run.
    - The `build/harm` in the checkout is a stale binary from 2026-09-07; it was not used.
- **AssertLLM2 (§4b): the designs are chosen and the manifest is written (`eval/manifests/assertllm2.json`); the run is blocked by F-L1.**
  - **Source:** AssertLLM2 at `f66fd20` (trivergence's pin), from `~/triad/data/assertllm2`.
  - **Traces, made with trivergence's flow without changing it.** trivergence was mounted read-only in `triad-toolchain:t3`.
    - The design was loaded with `triad_bench.m0_loader.load_design`, from loader YAMLs written outside trivergence.
    - The traces come from `triad_sim.verilator.VerilatorSimulator.run`: random stimulus, seed 1, 2,000 cycles, reset held for 2 cycles, scope `triad_tb::dut`.
    - Faults are the AssertLLM2 single-bug mutants (`buggy_artifacts/single_bug_mutants`), simulated with the same testbench and seed: 5 per design.
    - The traces are in `build/assertllm2/traces` (not committed), and the RTL paths in the manifest are absolute (`~/triad/data`).
  - **Screening:**
    - harm-coi (pyslang) elaborates 35 of the 83 designs with one inferred clock. The others have elaboration errors, several clocks or a timeout over 180 s.
    - From the small and medium ones, 15 were simulated, and 13 simulate with the golden RTL and all 5 mutants.
  - **Chosen (10):** `aes_cipher`, `uart`, `uart_to_bus`, `ethernet_smii_txrx`, `srdy-drdy-library` (`sd_scoreboard`), `ima_adpcm_encoder`, `ima_adpcm_decoder`, `sha3` (`keccak`), `gaussian_noise_generator` (`gng`), `video_stream_scaler`.
    - harm-coi runs on each with its trace.
    - Signals marked `unknown`: `sha3` 300, `gng` 62, `video_stream_scaler` 32. The rest have none.
  - **Excluded, and why:**
    - `rs_5_3_gf256`: Verilator rejects the RTL ("Duplicate declaration of signal: 'y'").
    - `spi_core`: the golden RTL fails its `full_case parallel_case` check under random stimulus (`simple_spi_top.v:235`).
    - `versatile_counter`: harm-coi needs `--include` for `` `include "versatile_counter_defines.v" ``, and the manifest format (`run_eval.py`) has no include directories.
    - `gost28147-89` and `present_cipher_encryption_core` simulate but were left out to keep 10. Both are crypto datapaths with 256/512-bit or 80-bit random inputs.
    - `i2c_slave`: its file set does not elaborate in pyslang (3 errors).
  - **AssertLLM2 table (after H11b and H11c; `eval/results/assertllm2`), 10 designs:**
    - `ethernet_smii_txrx` was removed from the manifest after F-L4 (an evaluation-input correction), then restored after H11c fixed it.
    - Its rows and `sha3`'s C6/C7 were re-run on `v3-168-g73b214f` (H11c merged).
    - The other rows cannot change with H11c: no other design has a vector not declared `[n:0]` or a signal over 511 bits.
    - **C0 (`--generate-config`) times out on every design tried,** even under the user's 10-minute cap (`--timeout 600`): `aes_cipher` C0–C4, and C0 of `uart`, `sha3` and `video_stream_scaler`.
      - The generated configuration has one template, `G({..#1&..} |-> P0)`, with `dtLimits="5D,3W,15A"`, over every Boolean signal (26 for `uart`). On random-stimulus traces the decision tree explores its whole space.
      - Checked by hand: `uart` C0 without `--fd` does not finish in 300 s, so the cost is mining, not fault coverage.
    - **So, by the user's choice, only C6/C7 (the RTL predicates) ran on every design.** The C0–C5 rows in the table are the measured timeouts, taken from the logs of the stopped runs.
    - For speed (the user's choice), the C6/C7 runs were split into 4 parallel `run_eval.py` processes of 8 threads each on the 32 cores. The times are therefore under load.

    | Design | C6 assertions | C6 s | C6 coverage | C7 assertions | C7 s | C7 coverage |
    |---|---|---|---|---|---|---|
    | `aes_cipher` | timeout | 600 | | timeout | 600 | |
    | `uart` | 1,209 | 12 | 60% | 410 | 6 | 60% |
    | `uart_to_bus` | 34,466 | 278 | 60% | timeout | 600 | |
    | `srdy-drdy-library` | 507 | 6 | 60% | 277 | 7 | 60% |
    | `ima_adpcm_encoder` | 3,259 | 57 | 80% | 809 | 169 | 80% |
    | `ima_adpcm_decoder` | 2,670 | 71 | 60% | 790 | 132 | 60% |
    | `ethernet_smii_txrx` (after H11c) | 344 | 10 | 60% | 84 | 4 | 40% |
    | `sha3` (after H11c) | 1,547 | 24 | 60% | 398 | 13 | 60% |
    | `gaussian_noise_generator` | 17,096 | 273 | 60% | 902 | 86 | 40% |
    | `video_stream_scaler` | 13,392 | 157 | 20% | 3,327 | 154 | 20% |

    - Coverage is the share of the 5 single-bug mutants that the mined assertions detect (`--fd`).
    - C7 reduces C6's output by 1.8–19× (filter `exact` plus the reductions), and its mean `coiFrac` and `coiDepthFit` are 1.0. Coverage is unchanged except on `gaussian_noise_generator` (60% → 40%).
  - **Finding F-L4: HARM rejects ascending vector ranges in a VCD.** `ethernet_smii_txrx` declares `input [1:10] state`, and HARM stops on it: "Reverse bit direction not supported, vectors must be defined like this: [MSB:LSB] with MSB > LSB". **Fixed in H11c (D-028)**, together with SystemVerilog vector indexing.
  - **Finding F-L5: harm-coi emits predicates that HARM cannot parse.** On `sha3`, the H10 predicates include `f_permutation_::out == 1600'd0`, and HARM rejects the configuration: "Constant ''d0' is wider than 511 bits". **Fixed in H11c:** harm-coi drops predicates wider than 511 bits, with the reason.
  - **Differences from the Mac:** the counts are equal on every local design (A1). Linux is 1.2–1.4× slower on the longer runs.
    - F-L1 (fixed in H11b).
    - F-L2 (`ImplicationTest` timeout, fixed in H11b).
    - F-L3, F-L4 and F-L5 (fixed in H11c).
    - The environment needs Verilator ≥ 5 first on `PATH`.
- **GoldMine (§4c):** not run (optional).

### Final Linux checks (2026-10-08, `ms/H11-linux` with `dev` merged at `29a0343`, after H11b–H11f)
- **Full `ctest`:** 226 of 226 (2,282 s). The tools are from `third_party` and the user's plain `PATH` (no borrowed Verilator).
- **Docker:** the image builds with the three tools, and its fast tests pass, 192 of 192.
- **Local designs (§4a):**
  - the fixtures (46 runs, new traces) give the same counts as H11e's Linux run;
  - the examples (51 runs) give the same counts as the Mac.
- **The Mac part (`eval/MACOS.md`), done on `ms/H11-macos`** (H11e's "macOS checks"):
  - the Mac `ctest` with the H11d tools: 226 of 226;
  - the Mac fixture table on the new traces, and the Mac/Linux `--check`: 40 of 46 runs equal; `structs` and `constructs` C0/C1/C3 differ (F-M2, deferred by the user);
  - `install_verilator.sh` failed on macOS (F-M1), fixed in H11g.
- **Findings F-L1 to F-L10 found on Linux, all fixed:**
  - F-L1, F-L2: H11b;
  - F-L3, F-L4, F-L5: H11c;
  - F-L6, F-L7, F-L8, F-L10: H11e (D-029);
  - F-L9: H11f.

## H11b: HARM builds on Linux (F-L1) (2026-10-07, Ubuntu 22.04 x86_64, g++ 11.4.0, Z3 4.13.4)
The fix: `ExpToZ3Visitor::bv` takes `uint64_t` instead of `unsigned long long` (plus `#include <cstdint>`). On macOS the two are the same type. Before the fix, the failing evidence is the Linux build log in H11's "Linux evaluation" (F-L1).

| Test | Result |
|---|---|
| A1 `make` on Linux, all targets | pass. No other compile error appeared behind F-L1. `build/harm --version`: `HARM v3-145-g4c5bc7c (dirty)` (dirty = this fix, uncommitted at the time) |
| A2 `Z3EquivalenceTest` on Linux | pass (39.5 s) |
| A3 Linux `ctest`, all labels | 205 of 206 pass. The exception, `ImplicationTest`, passes but exceeds ctest's timeout (F-L2 below). Details below |
| A4 macOS build and `ctest` | **pending**: to be run by the user on the Mac (the type is identical there) |
| A5 H0 regression baselines on Linux | pass: all 25 `regression_*` tests and the `determinism` label (29 tests) |

- **A3 in detail (`ctest -j32`; 2,067 s):**
  - **First full run: 175 of 206 pass.**
    - 30 failures are the Verilator oracles (`verilator_replay_*`, `coi_{reproduce,influence,depths}_*`, `h5_{influence,reproduce}_*`).
    - The Verilator first on `PATH` here is 4.210, which has no `--binary` ("%Error: Invalid option: --binary").
  - **Verilator re-run: all 37 Verilator-dependent tests pass.** This is the 30 plus 7 that already passed, with Verilator 5.031 (OSS CAD Suite, `-DVERILATOR_FOUND` and `PATH`). This was an environment problem, not HARM.
  - **`ImplicationTest`:** see F-L2.
  - **The yosys cross-check (7 tests) is not registered:** the yosys here is 0.47, without `read_slang`, which is optional (`eval/LINUX.md`). This makes 206 tests, against 213 on the Mac.
  - **`h5_*` (16 tests) and `h5_unit` (harm-coi's pytest) run:** the Python is 3.12.6 from `uv`, with pyslang 12.0.0.
- **Finding F-L2: `ImplicationTest` exceeds ctest's default 1,500 s timeout on Linux.**
  - Alone (`ctest -R ImplicationTest --timeout 7200`), it passes in 1,598 s. Inside the full parallel run it hit the timeout.
  - `generatedPairsAreSoundOnAllShortTraces` alone takes 369 s.
  - On the Mac, the whole suite passed in 1,931 s, so the test runs well under the limit there. Linux (g++ 11, this machine) is slower.
  - **Resolved, by the user's choice (2026-10-07):** `ImplicationTest` gets a `TIMEOUT` of 3,600 s (`tests/CMakeLists.txt`). The test itself is unchanged.
    - The `slow` label was considered: it only lets `ctest -LE slow` skip the test, and does not change the timeout.
- **Environment note for `eval/LINUX.md`:** the simulation oracles need Verilator ≥ 5 (`--binary --timing`). On this machine the default `verilator` is 4.210, so Verilator 5 must be first on `PATH` and set with `-DVERILATOR_FOUND`.

## H11c: the Linux findings F-L3, F-L4 (D-028), F-L5 (2026-10-07, Ubuntu 22.04 x86_64, g++ 11.4.0, Verilator 5.031)
Tests written first and committed failing in `a3260aa`. F-L3 and F-L5 were fixed in `d20dfdd`, F-L4/D-028 in `1885f94`, and `--split-logic` in `02ac25b`.

| Test | Result |
|---|---|
| A1 `h11c_yosys_probe` (F-L3): a fake yosys that exits 0 for `help` but cannot run `read_slang` is refused; one that can is accepted | pass. With the real yosys 0.47 here, the 7 `h5_xcheck_yosys_*` tests are no longer registered ("has no read_slang: … skipped") |
| A2 `h11c_vcd_ranges` (F-L4): `[1:10]` and the same values declared `[9:0]` mine the same assertions (2,436 each); `--split-logic` writes `asc[1]`…`asc[10]`, `off[3]`…`off[10]`, and HARM loads it | pass |
| A3/A3b/A3c `VectorIndexTest` (D-028) | pass, 4 of 4 |
| A5 harm-coi pytest (F-L5): a 1600-bit and a 512-bit comparison are dropped with the reason, while a 511-bit one and an 8-bit one are kept | pass (36 of 36) |
| A6 `h11c_emit_config_wide` (F-L5): HARM accepts the configuration emitted next to a 1600-bit register | pass |
| A7 Linux `ctest`, all labels | 209 of 210 on `1885f94` (2,184 s). The one failure was `h11c_vcd_ranges`, extended mid-run for `--split-logic` (see below). After `02ac25b`, all 31 affected tests pass (`h11c_*`, `VectorIndexTest`, the 25 `regression_*`, `h11_readme_commands`, `h11_version`) |
| H0 regression baselines | pass, byte-identical: D-028 changes nothing for `[n:0]` vectors and for variables without a declared range |

- **A3b is the independent check.**
  - A Verilator testbench (`tests/input/h11c/tb.sv`, `gen.sh`) declares `asc [1:10]`, `off [10:3]`, `d [7:0]` and `one [0:0]`, and drives random values.
  - Every cycle, it prints 14 selects: single bits, part-selects and whole-range selects.
  - HARM evaluates the same selects on the dumped VCD, and all 41 × 14 values are equal.
  - The fixture records the Verilator version (`generated_with.txt`).
- **A3:** out-of-range indices (`asc[0]`, `asc[11]`, `off[2]`, `off[11]`) and selects against the declared direction (`asc[6:3]`, `off[3:6]`, `d[2:5]`) are errors.
- **A3c:** printing and copying keep the source indices (`asc[3:6]`, `off[6:3]`, …).
- **Found during the implementation: `--generate-config --split-logic`** wrote `x[0]`…`x[size−1]`, out of range under D-028 for `[1:10]` or `[10:3]`. It now writes the declared indices (`main.cc`, `declaredIndex`). A2 was extended first and failed: "misses asc[10], off[8], off[9], off[10]".
- **The VCD parser was regenerated with bison 3.8.2,** the version that made the committed `VCDParser.cpp`. Its diff is the edited action plus `#line` numbers. The scanner, unchanged, was not regenerated: this machine's flex gives a different output.
- **Real designs (AssertLLM2, the H11 Linux traces, C6/C7, 10-minute cap, 8 threads, two runs in parallel):**

  | Design | Finding | C6 assertions | C6 s | C6 coverage | C7 assertions | C7 s | C7 coverage |
  |---|---|---|---|---|---|---|---|
  | `ethernet_smii_txrx` (`input [1:10] state`) | F-L4 | 344 | 10 | 60% | 84 | 4 | 40% |
  | `sha3` (1600-bit `f_permutation_::out`) | F-L5 | 1,547 | 25 | 60% | 398 | 13 | 60% |

  Both failed before H11c: HARM rejected the trace, or rejected the emitted configuration. Added to the H11 AssertLLM2 table on `ms/H11-linux` after the merge, and `ethernet_smii_txrx` restored to its manifest. Re-run there on `v3-168-g73b214f`, with the same counts.

## H11d: Verilator, Icarus and yosys in `third_party` (2026-10-07, Ubuntu 22.04 x86_64, g++ 11.4.0; macOS in H11e's "macOS checks")
A2 was written first and committed failing in `62dfed3`.

| Test | Result |
|---|---|
| A1 the scripts install the pinned releases into `third_party` (Linux) | pass: `Verilator 5.052 2026-09-05`, `Icarus Verilog version 13.0 (stable)`, `Yosys 0.69+post`, and `read_slang` works. **macOS: Icarus and yosys pass; Verilator only with `CPATH` (F-M1, H11e's "macOS checks")** |
| A2 `h11d_tool_lookup`: `third_party` is preferred over `PATH`; Verilator < 5 and yosys without `read_slang` are treated as missing; only `third_party` directories go first on the tests' `PATH` | pass |
| A3 full `ctest` with the `third_party` tools and the user's plain `PATH` (no OSS CAD Suite) | 208 of 218 pass (2,361 s). The 7 `h5_xcheck_yosys_*` tests run on Linux for the first time and pass (`constructs`: 26 signals, 0 unsound, 1 over-approximated). The 10 failures are findings F-L6, F-L7, F-L8 below, all Verilator 5.052 against fixtures and oracles made with older versions. **macOS: 226 of 226 (H11e's "macOS checks")** |
| A4 the Docker image | **pending**: the first build failed on a network error while cloning antlr4 (see below) |
| H0 regression baselines | pass, byte-identical (all `regression_*`, `determinism`) |

- **Fixed while running the scripts:**
  - **`install_yosys.sh`:** the environment's `PYTHON=python3.10` (a bare name) was ignored by CMake, whose own search found `/usr/local/bin/python3.6`, too old for slang's generators (`str.removesuffix`). The script now passes an absolute Python ≥ 3.9.
  - **`install_iverilog.sh`:** the version step (`iverilog -V | head -1`) died of SIGPIPE under `pipefail`, after a good install.
  - **`docker/build.sh`:** used the git ref as image tag, which fails for a branch with `/`.
  - **`install_antlr.sh`:** a network error during its clone ("Connection reset by peer") let the script go on and install a wrong tree (headers in `/antlr4-runtime`). HARM's CMake then failed with "Could NOT find ANTLR4". The script now stops at the first failure (`set -euo pipefail`), and re-runs still work.
- **Only `third_party` directories are prepended** to the tests' `PATH`. A first version also prepended `/usr/bin` (the system `iverilog`), which would shadow the user's other tools. A2 checks it.
- **Finding F-L6: the replay oracle's control assertions are invalid SystemVerilog** (`verilator_replay_temporal2v`, `verilator_replay_edit`).
  - `tests/oracle/verilator_replay.py:203` builds each control by negating the consequent with `!`. For a property consequent (`##3 v2`, `s_eventually …`, `… until …`), IEEE 1800 requires `not`:
    ```
    %Error: ctl.sv:11:49: syntax error, unexpected ##, expecting IDENTIFIER-for-type
       11 |   a0: assert property (@(posedge clk) (v1 |-> !(##3 v2))) else $display("FAIL a0 %0t", $time);
    ```
  - Verilator 5.031 accepted it; 5.052 does not. HARM's own SVA (the `sim` build) is not affected.
- **Finding F-L7: the H4/H5 fixture traces are not reproducible with another Verilator** (`coi_reproduce_{counter,arbiter,fsm,hier,structs,multipath}`, `h5_reproduce_constructs`).
  - The testbenches draw their stimulus from seeded `$urandom`, and Verilator 5.052's generator gives a different sequence for the same seed. `clk` is identical, while the inputs (`rst`, `en`, …) and everything downstream differ.
  - 5.052 also drops the empty `$rootio` scope and renumbers the VCD identifiers (form only).
- **Finding F-L8: `perturb.py influence` assumes both traces have the same signals** (`h5_influence_constructs`).
  - It stops with `KeyError: 'unnamedblk1::i'`. The loop variable of an unnamed block is in the committed trace (Verilator 5.031) and not in 5.052's.

## H11e: fixtures and oracles independent of the Verilator version (2026-10-07, Ubuntu 22.04, Verilator 5.052, Icarus 13.0, yosys 0.69 from `third_party`; D-029)
A2 was written first and committed failing in `9cdf233`. A1, A3 and A4 were existing tests failing with Verilator 5.052 (H11d's findings).

| Test | Result |
|---|---|
| A1 the 7 `*_reproduce_*` tests with Verilator 5.052 | pass |
| A2 `h11e_stim_{counter,arbiter,fsm,hier,structs,multipath}`: the same stimulus under Verilator and Icarus | pass; it failed before (Verilator's and Icarus' `$urandom` differ from the 4th edge). `h5/constructs` is not included, because Icarus 13 does not parse its RTL ("Errors in port declarations") |
| A3 `verilator_replay_{newops,temporal2v,edit,ex3}` | pass. `temporal2v`: 635 assertions, all checked as printed; 45 controls by monitor |
| A3b `verilator_replay_monitor_selftest`: the `s_eventually` control monitor on 6 hand-labelled traces (`\|->`, `\|=>`, same cycle, a `##1` antecedent) | pass |
| A4 `h5_influence_constructs` | pass |
| A5 full Linux `ctest`, 225 tests | 224 pass (2,275 s). The one failure is `Z3EquivalenceTest` (SIGSEGV), finding F-L9, fixed in H11f (not on this branch) |
| A6 the fixture evaluation re-run on the new traces (`eval/results/linux-fixtures`, HARM on `ms/H11e-fixtures`) | done, 46 runs. The Mac table re-run on 2026-10-08: `--check` differs for `structs` and `constructs` C0/C1/C3 (F-M2, "macOS checks" below) |

- **Findings handled (D-029):**
  - **F-L6:** the replay controls use `not`.
  - **F-L7:** stimulus from `tests/input/stim.svh`, traces regenerated.
  - **F-L8:** `perturb.py` compares only shared signals.
  - **F-L10 (option (a)):** the oracle mines with `--trace-end sva`. With HARM's default, the mined assertions with an `s_eventually` still pending at the end failed in Verilator at `$finish` (IEEE 1800). With `sva` they are not mined (`temporal2v`: 653 assertions before, 635 after).
- **The `s_eventually` controls:** Verilator 5.052 compiles `a |-> not (s_eventually p)` and `a |-> always (!p)` but never fails them, with no warning. The minimal repro:
  - `a` at cycle 1 and `p` at cycle 4 must fail at 45 ps;
  - a plain `assert property (!p)` in the same testbench does fail at 45.

  These controls are checked by a monitor instead (option (a), by the user), validated by A3b.
- **Expectations that changed with the traces, and why:**
  - `h8/constructs_coi.json` and `h9/constructs_partial_coi.json`: `unnamedblk1::i` removed from `unknown`. Verilator 5.052 does not dump this loop variable, and harm-coi on the new trace gives the same file (checked).
  - **H9 A2 (option (b), by the user):** `y_loop` (an output no cone uses) is the signal listed as unknown. The proposition is `y_loop != 1'b0`. HARM's report equals the hand-written `expected_constructs.json` with the name changed and nothing else.
- **No other expectation changed:**
  - The H4–H10 regressions on the new traces pass as they are: they check properties (soundness, filter invariants, simulation non-influence), not stored values.
  - `h6/multipath_rank_expected.txt` passes unchanged.
- **A6, assertions per configuration on the new traces** (old traces in brackets, from `macos-fixtures`; equal values shown once):

  | Design | C0 | C1 | C2 | C3 | C4 | C5 | C6 | C7 |
  |---|---|---|---|---|---|---|---|---|
  | counter | 135 (80) | 135 (80) | 113 (72) | 135 (80) | 110 (65) | 79 (51) | 14 (9) | 5 |
  | arbiter | 95 (75) | 89 (68) | 57 (53) | 95 (75) | 56 (31) | 74 (32) | 49 (36) | 32 (23) |
  | fsm | 75 (96) | 65 (85) | 60 (71) | 75 (96) | 58 (73) | 48 (61) | 47 (46) | 24 (27) |
  | multipath | 104 (94) | 104 (94) | 104 (94) | 104 (94) | 6 (8) | 9 | — | — |
  | structs | 1,839 (1,526) | 1,833 (1,522) | timeout (1,491) | 1,839 (1,526) | 751 (730) | 271 (322) | 0 | 0 |
  | constructs | 4,215 (4,438) | 4,195 (4,388) | timeout | 4,215 (4,438) | 1,675 (2,135) | 1,484 (1,862) | 145 (101) | 2 |

  - The counts change because the stimulus changed (F-L7), not HARM.
  - **`structs` C2 now times out at 1,800 s:** it has 1,839 assertions instead of 1,526, and `--reduce implies` and `--atom-premises` grow with the square of that number (H11's note).
  - **Same patterns as before:** C5 (`exact`) can still exceed C4 (`arbiter` 74 against 56, `multipath` 9 against 6): fewer candidates change the tree HARM builds (H11's analysis). C7 stays the smallest everywhere.

### macOS checks (2026-10-08, branch `ms/H11-macos` from `dev` @ `746e191`)
macOS 15.3.2 (Darwin 24.3.0) arm64, Homebrew g++-13 13.3.0, HARM `v3-187-g746e191`. Tools from `third_party`: `Verilator 5.052 2026-09-05`, `Icarus Verilog version 13.0 (stable)`, `Yosys 0.69+post` (`read_slang: ok`). harm-coi: Python 3.12.9, pyslang 12.0.0.

| Check | Result |
|---|---|
| H11d A1, the three scripts | Icarus and yosys: pass. **Verilator: fails, finding F-M1** (below); it builds with `CPATH=/opt/homebrew/opt/flex/include` and nothing else changed |
| H11b/H11c A4, H11d A3, H11e A5: full `ctest` in a fresh `build-mac/`, the three tools found in `third_party` | pass, **226 of 226** (1,902 s), the same count as Linux. `ImplicationTest` 1,480 s. The 7 `h5_xcheck_yosys_*` run (`constructs`: 26 signals, 0 unsound, 1 over-approximated, as on Linux) |
| H11e A6, the fixtures on the new traces, `--check` against `linux-fixtures` (`eval/results/macos-fixtures`, 76 min) | **fails, finding F-M2** (below). 40 of 46 runs equal Linux; `structs` and `constructs` C2 time out at 1,800 s as on Linux |

- **Finding F-M1: `install_verilator.sh` does not build on macOS.**
  - `tools_common.sh` puts Homebrew's `flex` first on `PATH`, but Homebrew's flex is keg-only and its `FlexLexer.h` is on no include path (the SDK has none). Verilator's build stops at:
    ```
    In file included from ../V3ParseLex.cpp:30:
    V3Lexer_pregen.yy.cpp:368:10: fatal error: FlexLexer.h: No such file or directory
    make[2]: *** [V3ParseLex.o] Error 1
    ```
  - Linux is not affected: the distribution's flex installs the header in `/usr/include`.
  - All checks above use the Verilator built with `CPATH=/opt/homebrew/opt/flex/include CC=gcc-13 CXX=g++-13 bash install_verilator.sh`.
  - **Fixed in H11g** (`ms/H11g-flex-header`, awaiting review): `tools_setup` puts the Homebrew formulas' `include/` on `CPATH`.
- **Finding F-M2: the assertion counts of `structs` and `constructs` differ between macOS and Linux** in the configurations without a COI filter:

  | Design | C0 | C1 | C3 |
  |---|---|---|---|
  | structs | 1,800 (Linux 1,839) | 1,794 (1,833) | 1,800 (1,839) |
  | constructs | 4,220 (4,215) | 4,200 (4,195) | 4,220 (4,215) |

  - C3's `coi_frac`/`coi_depth_fit` move with it (`structs` 0.465/0.345 against 0.466/0.349; `constructs` 0.422/0.374 against 0.424/0.376). C4–C7 and the other four designs are equal.
  - **Not a nondeterminism on the Mac:** `structs` C0 run again by hand gives 1,800 three times (`--max-threads 8` twice, `--max-threads 1` once), from the same generated config (`--generate-config`, SHA-1 `820b2a29ab651bc8dd4f6391c8744c387102030d`: 2 `<prop>`, 5 `<numeric>` with K-means clustering `K,10Max,0.01WCSS`).
  - C0 has no COI and no reduction, so the difference is already in the mining (or in the generated config) on these traces. The H0 baselines, byte-identical on both systems, do not cover it.
  - **Deferred by the user (2026-10-08):** it does not block the release.
  - **A platform difference, not a stale table:** Linux's final re-run on `ms/H11-linux` (`v3-196-g29a0343`, whose HARM sources equal `dev`'s) gives the same 1,839/1,833/4,215/4,195 as H11e's Linux run. The same sources give different counts on macOS and Linux.
  - **Linux data (2026-10-08, the hand-off's step 3; HARM `v3-190-g4590037` on `ms/H11g-flex-header`, whose HARM sources equal `dev`'s; g++ 11.4.0):**
    - `--generate-config` on `structs` gives a `gen.xml` with SHA-1 `820b2a29ab651bc8dd4f6391c8744c387102030d`, **the same as the Mac's**.
    - From that config, C0 mines 1,839 assertions with `--max-threads 8` and with `--max-threads 1`.
    - So the difference is in the mining (and its qualification), not in `--generate-config`. It is deterministic on each system and independent of the thread count. The K-means lead (`<numeric>` clustering) is still open: the clustering runs at mining time, not in `--generate-config`.
    - **Not the compiler:** the Linux Docker image (`samger/harm:ms-H11-linux`: Ubuntu 24.04, x86_64, g++ 13.3, the Mac's compiler version) gives the same `gen.xml` SHA-1 and 1,839 assertions (`--max-threads 8`).
      - The difference follows the platform: macOS's libraries, or the architecture (arm64 against x86_64).
      - **Lead:** on arm64, GCC contracts multiply-adds into FMA by default (`-ffp-contract=fast`). This changes floating-point rounding, e.g. in K-means clustering at mining time.
      - The next experiments are in `eval/HANDOFF_FM2.md`.
  - **The Mac experiments (2026-10-08, `ms/H12-fm2` from `dev` @ `ecf9ac2`; HARM sources equal to `746e191`'s; macOS 15.3.2 arm64, g++-13 13.3.0). The cause is found: FMA contraction in the decision-tree score.**
    - **FMA off, whole HARM** (`-DCMAKE_CXX_FLAGS=-ffp-contract=off`, `build-nofma/`): `structs` C0 **1,839** and `constructs` C0 **4,215**, Linux's counts. Same `gen.xml` as the default build (`structs` `820b2a29…`, `constructs` `aff9a6a6…`). The default build on the same Mac: 1,800 and 4,220.
    - **Bisection by build target** (`-ffp-contract=off` added to chosen targets' `flags.make` in a scratch build, `build-cls/`; `structs` C0):

      | Contraction off in | Count |
      |---|---|
      | `clustering` only (the K-means lead) | 1,800 |
      | the `harm` executable and all of `src/miner` | 1,839 |
      | `src/miner/utils`, or the `miner` library | 1,800 |
      | all of `src/miner/modules` | 1,839 |
      | `propertyQualification` only | 1,800 |
      | **`propertyMiner` only** | **1,839** |

    - **In `propertyMiner`, only two functions are fused** (`objdump`, default build): `getConditionalEntropy` and `getCovScore` (`TLMiner/supportMethods.cc`), one `fmsub` each. The FMA-off build has none.
    - **The one used here is `getCovScore`:** the fixtures' template sets no heuristic, and the default is `COVERAGE` (`DTLimits.hh:99`). Its score `1 - (ATCT/CT) * (1 - ATCF/CF)` becomes a fused multiply-subtract, so the product is not rounded before the subtraction.
    - **Why it changes the assertions:** `AntecedentGenerator` sorts the candidates by gain and, with `-0.1E` (the generated template's effort), keeps only the best (`AntecedentGenerator.cc:518–527`). Candidates whose scores are equal or nearly equal are then ordered by their last bits, which FMA changes, so a different antecedent is kept and the decision tree grows differently.
    - **The same fragility without FMA:** a stand-alone copy of the entropy formula gives `H(p) != H(1-p)` in 7,266 of 19,900 mirrored pairs with contraction off, and in 9,626 with it on. HARM's choice among near-ties depends on rounding on every platform; x86_64 and arm64 agree only when neither contracts.
    - **Not the cause:** the K-means clustering (its `dkm` seed is fixed at 1, `dkm.hpp:293`), the thread count, `--generate-config`, and the compiler version.
  - **The fix:** H12 (`doc/plan/H12_PLAN.md`), awaiting the user's approval.

## H11f: the log files under concurrent writers (2026-10-07, Ubuntu 22.04, g++ 11.4.0; finding F-L9)
Tests written first and committed failing in `56a6d1a`; the fix is `6072328`.

| Test | Result |
|---|---|
| A1 `LogTest.deleteLastLineOnAnEmptyFile` | pass; before the fix it crashed with SIGSEGV, deterministically |
| A2 `LogTest.concurrentProcessesKeepOneValidLog`: 8 processes × 200 warnings in one directory | pass: all writers exit normally, and `warning.log` is one JSON array of 1,600 records. Before the fix, writers died with signal 11 |
| A3 `LogTest.concurrentThreadsKeepOneValidLog`: 8 threads × 200 warnings | pass, with the same checks; before the fix it crashed with SIGSEGV |
| A4 Linux `ctest`, all labels (Verilator 5.031, as for `dev`) | pass, 211 of 211 (2,314 s) |
| A4 the Docker image's fast tests on repeated `ctest -j` runs (the H11d symptom) | pass: the image built from `ms/H11f-log-race` (Ubuntu 24.04, g++ 13) passed its fast tests 4 times in parallel (`ctest -j -LE slow`), 177 of 177 each, with no crash. Before the fix, every parallel run crashed (3 of 3). A fifth run printed no result (the check did not record its exit status), so it is not counted; the run that replaced it recorded `ctest exit=0` |

- **The bug:** `deleteLastLine` (`misc.hh`) computed `lines.size() - 1` on a `size_t`, which underflows on an empty file.
  - A concurrent writer's truncation can empty the file between another writer's `isFileEmpty` and its read.
  - The gtests share `build/` as their working directory, so `ctest -j` (seen in the Docker image: `PropositionOracleTest` once, `Z3EquivalenceTest` twice, and `Z3EquivalenceTest` on Linux on H11e's branch) and HARM's own threads could crash.
- **The fix:**
  - `deleteLastLine` returns on an empty file.
  - `dumpWarningToFile`/`dumpErrorToFile` hold `flock(LOCK_EX)` on the log file and a mutex for the whole read-modify-write.
  - A nested log write from inside a failing log write is skipped (the message is still printed), so it cannot wait for its own lock.
- **Cost:** A2/A3 take 6–8 s for 1,600 warnings. Every record re-reads the whole file, which was already so before; the lock orders the writers but does not add work.

## H11g: `install_verilator.sh` on macOS, finding F-M1 (2026-10-08, macOS 15.3.2 arm64, Homebrew g++-13 13.3.0)
A1 was written first and committed failing in `0f5875e`; the fix is `972b22e`. F-M1 was found by the macOS checks on `ms/H11-macos` (H11e's "macOS checks" there).

| Test | Result |
|---|---|
| A1 `h11g_tools_common_flex`: `tools_setup` with macOS and Homebrew faked; the compiler must find the fake flex's `FlexLexer.h` | pass with `c++`, `g++-13` and `clang++`. Before the fix it fails with `g++-13` and `clang++` (checked again with the fix stashed) |
| A2 `install_verilator.sh` on the Mac with no `CPATH` (`env -u CPATH CC=gcc-13 CXX=g++-13`) | pass: `Verilator 5.052 2026-09-05`, no `FlexLexer.h` error |
| A3 `h11d_tool_lookup`, and the `verilator` label (5 tests) with the rebuilt Verilator | pass, 2 of 2 and 5 of 5. Linux unchanged by construction: the change is inside the `darwin` branch of `tools_setup` |
| A1 on Linux (Ubuntu 22.04, `c++` = g++ 11.4.0, 2026-10-08) | pass: `check_tools_common.sh` prints "ok: the compiler finds Homebrew flex's FlexLexer.h"; `h11g_tools_common_flex` and `h11d_tool_lookup` pass, 2 of 2 |

- **The fix:** on macOS, `tools_setup` prepends the `include/` of each Homebrew formula it already puts on `PATH` (bison, flex, gperf) to `CPATH`, keeping a user's `CPATH` after it.
- **Note on A1:** it first set `SDKROOT` to a fake path, which made Apple's `clang++` shim fail and ask to install the command-line tools. It now uses the real SDK on a Mac (`xcrun`), and any value elsewhere, where it is unused.
