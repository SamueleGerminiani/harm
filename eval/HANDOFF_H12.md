# H12 on Linux: the checks after the Mac (hand-off, 2026-10-08)

For the Linux session. H12 fixes F-M2, the macOS/Linux difference in the fixture counts. It is done and validated on the Mac; Linux has to show that nothing changed there.

**Never modify trivergence** (`~/trivergence`). `main` is not touched: the user decides the release. Do not merge `ms/H12-fm2`: the user reviews it.

## What H12 is (details: `doc/plan/H12_PLAN.md`, VALIDATION "H12")
- **The cause of F-M2:** on arm64, GCC fused `1 - a*b` in the decision-tree score (`getCovScore`, and `getConditionalEntropy` with `ENT`) into one instruction, so the product was not rounded. Among near-equal candidates the kept antecedent changed, and so did the assertions.
- **The fix (`f06d03a`):** `add_compile_options("-ffp-contract=off")` in the top-level `CMakeLists.txt`.
- **Expected on Linux:** no change. x86_64 without `-mfma` never fused these operations.
- **New tests:**
  - `h12_structs_count`: `structs` mines 1,839; label `slow`, about 150 s.
  - `ScoreTest`: the two scores equal a reference that rounds every operation, bit for bit.
- **The Mac:** `ctest` 229 of 229. The fixture table with `--check` against `eval/results/linux-fixtures`: 46 of 46 equal.

## What the Linux session does
1. **Get the branch and build it in a fresh build directory** (so the new flag is in every target):
   ```
   git status                                   # clean
   git fetch origin && git switch ms/H12-fm2    # tracks origin/ms/H12-fm2
   cmake -S . -B build-h12 -DCMAKE_BUILD_TYPE=Release -DHARM_COI_PYTHON=$PWD/build/harm-coi-venv/bin/python
   make -C build-h12 -j$(nproc)
   build-h12/harm --version
   grep -c ffp-contract=off build-h12/src/miner/modules/CMakeFiles/propertyMiner.dir/flags.make   # >= 1
   ```
2. **Full `ctest` (A4 Linux):**
   ```
   cd build-h12 && ctest -j$(nproc) 2>&1 | tee ctest-h12.log | tail -30
   ```
   - **Expected:** 229 of 229, with `ScoreTest` and `h12_structs_count` passing.
   - The H0 baselines (`regression_*`, `determinism`) must pass unchanged.
3. **The fixture table (Linux must be unchanged), about 75 minutes:**
   ```
   python3 eval/run_eval.py eval/manifests/fixtures.json /tmp/linux-fixtures-h12 \
       --harm $PWD/build-h12/harm --python $PWD/build/harm-coi-venv/bin/python \
       --check eval/results/linux-fixtures/results.csv
   ```
   - **Expected:** no "differs" line. The committed Linux table stays as it is, so the output goes to `/tmp`.
   - Because the Mac table is now equal to Linux's, this also shows the two systems agree.
4. **Record** in `doc/plan/VALIDATION.md`, on `ms/H12-fm2`:
   - In the "H12" entry, replace "**Linux: pending**" in A4 with the `ctest` summary, the HARM version, and the fixture `--check` result.
   - In `PLAN.md` and `H12_PLAN.md`, replace "the Linux run pending" with the result.
   - Commit, push, and tell the user.
5. **If something fails** (a test, or a count that changed on Linux): record it with its output, push and stop. Don't fix it: a fix is a new milestone.

## After Linux
The user reviews `ms/H12-fm2` and merges it into `dev`. The release (`main`, tag `v4`) is still the user's decision.
