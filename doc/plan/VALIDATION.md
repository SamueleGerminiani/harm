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

## H11: evaluation, documentation, `--version`, Docker (2026-10-06, macOS arm64, g++-13; the Linux part is pending)
Tests written first and committed failing in `917e103` (`h11_version`, `h11_readme_commands`). `--version` implemented in `7c36fa3`.

| Test | Result |
|---|---|
| A1 `eval/run_eval.py` reproduces its own table: the fixtures re-run on HEAD (40 runs: all but C2, whose two runs take 20 and 30+ minutes) and the examples (51 runs), with `--check` against `eval/results/macos-*` | pass: every count is equal (assertions, dropped, permutations, DT pairs, mean `coiFrac`/`coiDepthFit`, coverage). Runs over 1 s differ by at most 2% in time; shorter ones vary more |
| A2 the macOS full suite on the release commit | see below |
| A2 Linux `ctest` and harm-coi pytest | **pending** (`eval/LINUX.md` §2) |
| A3 the Docker image | **pending**: the Docker daemon is not running here (`eval/LINUX.md` §3) |
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
