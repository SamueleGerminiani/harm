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
