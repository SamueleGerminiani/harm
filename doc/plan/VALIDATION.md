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
