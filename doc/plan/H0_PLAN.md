# H0 plan: baseline and safety net

*Status: approved 2026-10-05 (toolchain: g++-13), in progress. Branch: `ms/H0-baseline`. Effort: about 1.5 d, plus the toolchain rebuild (step 0).*

## Findings from the investigation (2026-10-05)

### F1. The macOS build on this machine does not run
- HARM builds, but `build/harm --help` aborts with `malloc: pointer being freed was not allocated`. The previously installed `install/harm/bin/harm` aborts the same way.
- **Cause:** the dependencies were built against three different C++ runtimes, and all of them are loaded into one process:
  - Spot: gcc-12 `libstdc++`;
  - ANTLR and HARM: gcc-13 `libstdc++`;
  - Boost: Apple `libc++`.
- The install scripts do not pin a compiler. They used whatever `CC`/`CXX` was set when they ran.
- **Consequence:** `ctest` cannot be trusted on this machine right now. When I first ran it, all 35 tests passed, but a re-run of `ex3` shows the example tests abort at load time.

### F2. The example tests are smoke tests only
`examples/CMakeLists.txt` runs `harm` and checks only the exit code. No mined output is ever compared against an expected result.

### F3. Three sources of nondeterministic output
1. **Collection order depends on threads.** `TLMiner.cc:328` appends each template's assertion pack to `_collectedAssertions` in completion order, which depends on thread timing.
2. **Deduplication order depends on memory addresses.** `Qualifier::extractUniqueAssertionsFast` (`Qualifier.cc:80`) iterates an `unordered_set<AssertionPtr>`, which is hashed by pointer. Its output order depends on allocation addresses, even with one thread.
3. **Ties are broken arbitrarily.** `Qualifier::sortAssertionsWithMetrics` (`Qualifier.cc:436`) uses `std::sort` on `_finalScore` only, so the order among equal scores is arbitrary. Ties at the `--max-ass` cut-off change *which* assertions are kept (trivergence M0 #31).

## Scope

### Step 0: consistent toolchain (prerequisite, needs your approval)
- Rebuild Spot, ANTLR and Boost under `third_party/` with **one** compiler, and build HARM with the same one.
- **Compiler (user's choice):** Homebrew g++-13. On macOS this needs `SDKROOT` set to the Xcode SDK, because gcc-13 cannot parse the newest Command Line Tools SDK (D-010).
- Make `third_party/install_*.sh` honour `CC`/`CXX` explicitly and print the compiler they use. Make `CMakeLists.txt` warn when the dependencies were built with a different compiler than HARM. Implemented with a marker file (`<prefix>/.harm_toolchain`) rather than `otool`/`ldd`.
- It takes about 30–45 min (mostly Spot) and **overwrites the current libraries in `third_party/` and `install/`**. The ones there now don't work anyway.
- **Alternative:** develop and test in the Linux Docker image (`docker/`). The Docker daemon is not currently running on this machine, and the plan requires macOS to work too, so this would only postpone the problem.

### Step 1: regression harness, capturing the current behaviour
- `tests/regression/cases.cmake`: the example command lines (copied from `examples/CMakeLists.txt`), each with `--max-threads 1 --psilent` and `--dump-to <tmp>`.
- `tests/regression/run_case.sh <name> <harm args…>`: runs HARM, normalises the dump (strips ANSI colour codes, trailing spaces, and paths that depend on the run), and compares it with `tests/regression/baseline/<name>.txt`.
- **Two comparison modes:**
  - `--set`, order-insensitive: the multiset of assertions, used **before** the determinism fix;
  - `--ordered`: the exact sequence, used **after** it.
- `tests/regression/update_baseline.sh`: rewrites the baseline. It is only used with explicit approval, and every use is recorded in `VALIDATION.md`.
- Registered as ctest tests with the label `regression`, so `ctest -L regression` runs them. `bl_master10k` and `sobel` get the extra label `slow`.

### Step 2: deterministic output
Each fix is small and local:
1. **Collection:** `_collectedAssertions` is indexed by template position (each template's slot is filled under the existing mutex), and the packs are concatenated in template order.
2. **Deduplication:** `extractUniqueAssertionsFast` iterates the input vector, keeping the first occurrence, instead of the pointer-hashed set. The set is still used for lookups.
3. **Ranking:** the comparator becomes `(_finalScore desc, toString() asc)`. If two assertions have identical strings they are duplicates already removed by step 2. This is D-001.
4. **Other uses:** I'll check `sampleAssertionsByConDiversity` and the fault-coverage minimum subset for the same patterns. Any other source found is fixed only if it affects output order; otherwise it's noted in the report.

### Step 3: freeze the ordered baseline
After step 2, the `--set` comparison must still pass on every case that has no `--max-ass` cut. Then the ordered baseline is frozen. Cases with a cut (`sobel`: `--max-ass 1000 --sample-by-con`) may change their *set*. That change is listed in D-001 and reviewed by hand.

### Docs
- `doc/plan/DECISIONS.md` with D-001 (tie-break) and D-010 (single C++ runtime).
- `doc/plan/VALIDATION.md` with the H0 entry.
- The `PLAN.md` status board updated.
- README Quick start: a note to build all dependencies and HARM with the same compiler, and how to choose it.

## Out of scope
- Any change to mining, metrics or output format other than ordering.
- Performance work, and the Linux CI setup. GitHub Actions is suggested as a later task; it is not part of the HARM plan yet.
- Fixing the `sobel` test, which writes `ass.txt` into the source tree (it is git-ignored). Noted only.

## Acceptance tests (written before the step 2 changes)
| # | Test | Must fail before step 2? |
|---|---|---|
| A1 | `ctest -L regression` passes in `--set` mode against the baseline captured in step 1 (all 16 examples) | no (it is the safety net) |
| A2 | **Thread independence:** for each non-slow case, the ordered outputs of `--max-threads 1` and `--max-threads 8` are identical | yes, expected to fail on at least one case (F3.1); if it never fails, I'll say so rather than claim a fix |
| A3 | **Run independence:** 3 runs with `--max-threads 8` give identical ordered output | yes, expected to fail on at least one case (F3.1–F3.3) |
| A4 | **Cut stability:** `ex3` and `bl_master1k` with `--max-ass 10` give identical output across 3 runs with 8 threads | yes, if ties exist at the cut |
| A5 | The full existing `ctest` suite passes on macOS (after step 0) | n/a |
| A6 | The ordered regression passes after the freeze | n/a |

A2–A4 are run by `tests/regression/determinism.sh`, registered as `determinism_<case>` ctests with the label `determinism` (serial, because they use 8 threads). Baseline comparisons are `regression_<case>` with the label `regression`. `slow` marks `bl_master10k` and `sobel` in both.

## Validation evidence
- Before freezing, I'll check 3 baseline files by hand (`ex3`, `vendingMachine`, `bl_master1k`) against a direct HARM run. Each assertion must be present and none invented.
- I'll record the set-vs-ordered comparison from step 3, and list every set change caused by the `--max-ass` cut in D-001.
- Linux: the regression suite is run on the Linux machine at the end of H0, if you can run it there. Otherwise it's marked pending in `VALIDATION.md`.

## Files touched
- **New:**
  - `tests/regression/{CMakeLists.txt, cases.cmake, run_case.sh, determinism.sh, update_baseline.sh, baseline/*.txt}`
  - `doc/plan/{DECISIONS.md, VALIDATION.md}`
- **Modified:**
  - `tests/CMakeLists.txt` (`add_subdirectory(regression)`)
  - `src/miner/modules/src/propertyMiner/TLMiner/TLMiner.cc` and `.hh`
  - `src/miner/modules/src/propertyQualification/qualifier/Qualifier.cc`
  - `third_party/install_{spotltl,antlr,boost}.sh`
  - `CMakeLists.txt` (C++ runtime check)
  - `README.md` (compiler note)
  - `doc/plan/PLAN.md` (status)
