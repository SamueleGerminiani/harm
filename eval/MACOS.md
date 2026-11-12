# H11b–H11f on the Mac: checks to run in parallel with Linux

Everything here runs on the Mac (arm64, Homebrew g++-13, the compiler of the existing `third_party` libraries; D-010), by the user or a Claude session there. The session records the results itself, in the repository (see "Recording").

The release (merge into `main`, tag `v4`) waits for this, for the Linux part, and for the user's decision.

## In parallel on Linux (2026-10-08)
Branch `ms/H11-linux`, which has `dev` (H11b–H11f) merged in at `29a0343`:
- **Done:** the full `ctest`: 226 of 226, with Verilator 5.052, Icarus 13.0 and yosys 0.69 from `third_party` (2,282 s).
- **Running:** the Docker image (`docker/build.sh ms/H11-linux`) and its fast tests.
- **Next:** the local designs (`eval/LINUX.md` §4a).

The Linux fixture table on the new traces is already in `dev`: `eval/results/linux-fixtures` (H11e A6).

## What is open on the Mac
Every milestone since H11 was validated on Linux only. On the Mac:
- **A4 of H11b–H11e:** the build and `ctest` must stay green. For H11b, `uint64_t` is the same type on macOS, so the Mac is expected to be unchanged; H11c–H11f are cross-platform code.
- **H11d A1 and A3:** the three tool scripts on macOS, and `ctest` with them.
- **H11e:** `eval/results/macos-fixtures` is from the old traces and must be re-run on the new ones, so that `--check` can compare the Mac and Linux.
- **Not needed:** `macos-examples`. The examples do not use the fixture traces.

## Recording (for the session that runs this)
- **Branch:** `ms/H11-macos`, from `dev`. Commit there and push it. Do not merge it: the user reviews it first.
- **What to commit:**
  - `eval/results/macos-fixtures` (`results.csv`, `results.md`);
  - in `doc/plan/VALIDATION.md`: a short "macOS checks" paragraph at the end of the H11e entry, with the `ctest` summary, the tool versions, the `--check` outcome, and anything that differs from Linux;
  - in the H11b/H11c/H11d/H11e plan files and the `PLAN.md` status board: "macOS open" becomes the result.
- **Not committed:** `build-mac/` and logs.
- **If something fails, record it; don't fix HARM here.**
  - A failing test, a tool script that does not build, or a count different from Linux is a finding.
  - Write it in VALIDATION with the output, push, and stop.
  - A fix is a new milestone (plan, approval, failing tests first).

## 0. Get the code
Pull into the existing checkout (no fresh clone needed):
```
git status                    # must be clean; commit or stash local changes first
git fetch origin
git switch dev && git pull --ff-only     # dev @ 12044b5 or later
git switch -c ms/H11-macos
```

## 1. The tools (H11d)
- **Prerequisites (Homebrew):**
  ```
  brew install autoconf bison flex gperf help2man gawk readline tcl-tk libffi pkg-config cmake
  ```
- **Build only the three tools.** The libraries (antlr4, Spot, Boost, Z3) did not change, so there is no need to rebuild them:
  ```
  cd third_party
  CC=gcc-13 CXX=g++-13 bash install_verilator.sh
  CC=gcc-13 CXX=g++-13 bash install_iverilog.sh
  CC=gcc-13 CXX=g++-13 bash install_yosys.sh     # slang needs C++20: g++-13 is fine (or Xcode >= 16.4)
  cd ..
  ```
  - Use the compiler of the existing libraries (`third_party/*/.harm_toolchain`). The scripts set `SDKROOT` as the other scripts do.
  - `install_yosys.sh` uses `$PYTHON` or `python3`, which must be ≥ 3.9 (it is resolved to an absolute path).
  - **Expect:**
    - `third_party/verilator/.harm_version`: `Verilator 5.052`;
    - `third_party/iverilog/.harm_version`: `Icarus Verilog version 13.0`;
    - `third_party/yosys/.harm_version`: `Yosys 0.69…`, and the script prints `read_slang: ok`.
- **If a script fails:**
  - Record it (the failing step and its last lines) and go on with the other tools.
  - CMake treats a missing tool as missing: its tests are skipped, not failed.
  - Likely spots on macOS: Homebrew's `readline`/`libffi` are keg-only (yosys may need `CMAKE_PREFIX_PATH=$(brew --prefix readline):$(brew --prefix libffi)`), and the SDK seen by g++-13.

## 2. Build and test
Use a fresh build directory, so no tool path cached before H11d is reused:
```
mkdir build-mac && cd build-mac
CC=gcc-13 CXX=g++-13 cmake -DCMAKE_BUILD_TYPE=Release -DHARM_COI_PYTHON=<python with harm-coi> ..
make -j"$(sysctl -n hw.ncpu)"
./harm --version            # write it down
ctest -N | tail -1          # 226 if all three tools are found
ctest -j"$(sysctl -n hw.ncpu)" 2>&1 | tee ctest-mac.log | tail -30
```
- **The configure output** names each tool, e.g. `-- VERILATOR: …/third_party/verilator/bin/verilator (5.052)`. Check all three.
- **Linux had 226 of 226.** On the Mac, the count may differ only if a tool is missing, and then its tests are skipped, never failed.
- **Note:** `ImplicationTest` took 1,600–1,700 s on Linux (its timeout is 3,600 s since H11b).

## 3. The fixtures on the new traces (H11e, A6 on the Mac)
```
python3 eval/run_eval.py eval/manifests/fixtures.json eval/results/macos-fixtures \
    --python <python with harm-coi> --check eval/results/linux-fixtures/results.csv
```
- **About 75 minutes.** `structs` C2 and `constructs` C2 time out at 1,800 s on Linux, and a timeout is a measurement.
- **`--check` compares the counts with Linux.** HARM is deterministic, so they must be equal. A difference is a finding.
- **Expected on Linux (assertions):**

  | Design | C0 | C1 | C2 | C3 | C4 | C5 | C6 | C7 |
  |---|---|---|---|---|---|---|---|---|
  | counter | 135 | 135 | 113 | 135 | 110 | 79 | 14 | 5 |
  | arbiter | 95 | 89 | 57 | 95 | 56 | 74 | 49 | 32 |
  | fsm | 75 | 65 | 60 | 75 | 58 | 48 | 47 | 24 |
  | multipath | 104 | 104 | 104 | 104 | 6 | 9 | — | — |
  | structs | 1,839 | 1,833 | timeout | 1,839 | 751 | 271 | 0 | 0 |
  | constructs | 4,215 | 4,195 | timeout | 4,215 | 1,675 | 1,484 | 145 | 2 |

  If the Mac finishes `structs` C2 within 1,800 s while Linux timed out, the two rows differ only by the timeout. That is a measurement difference (the Mac was faster before), not a count difference: record it, not as a finding.

## 4. When done
- Commit (see "Recording") and push `ms/H11-macos`.
- Tell the user, who reviews it together with `ms/H11-linux`.
