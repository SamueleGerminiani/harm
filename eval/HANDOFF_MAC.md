# Hand-off from the Mac to the Linux session (2026-10-08)

The Mac part of `eval/MACOS.md` is done. This file says where its results are and what the Linux session does next.

**Never modify trivergence** (`~/trivergence`), on Linux or on the Mac. It is read-only from HARM's sessions.

## Where things are
| Branch | Contents | Status |
|---|---|---|
| `ms/H11-macos` | The Mac checks, **with `ms/H11-linux` merged in** (`cbb597a`). The two sessions' edits to `PLAN.md` and `VALIDATION.md` are reconciled here. This file is here | pushed; awaiting the user's review |
| `ms/H11g-flex-header` | H11g: the fix for F-M1 (from `dev` @ `746e191`) | pushed; awaiting the user's review; the Linux run of A1 is open (step 2 below) |
| `ms/H11-linux` | Unchanged since `cbb597a`. Everything on it is now also on `ms/H11-macos` | do not commit there any more |

`dev` has not moved (`746e191`). Nothing is merged into `dev` or `main`: the user reviews first.

## The Mac results (details: `doc/plan/VALIDATION.md`, H11e's "macOS checks")
- **Setup:** macOS 15.3.2 arm64, Homebrew g++-13 13.3.0, HARM `v3-187-g746e191`. Verilator 5.052, Icarus 13.0, yosys 0.69 (`read_slang: ok`) from `third_party`.
- **`ctest`:** 226 of 226 (1,902 s), the same count as Linux. The 7 yosys cross-checks run (`constructs`: 26 signals, 0 unsound, 1 over-approximated, as on Linux).
- **F-M1: `install_verilator.sh` did not build on macOS.**
  - It stopped at `FlexLexer.h: No such file or directory`: Homebrew's flex is keg-only.
  - **Fixed in H11g:** `tools_setup` puts the Homebrew formulas' `include/` on `CPATH`, inside its `darwin` branch only. Done on the Mac: A1 to A3 pass.
- **F-M2: the fixture counts differ between macOS and Linux.** It is **deferred by the user** and does not block the release.

  | Design | C0 | C1 | C3 |
  |---|---|---|---|
  | structs | Mac 1,800, Linux 1,839 | 1,794 / 1,833 | 1,800 / 1,839 |
  | constructs | Mac 4,220, Linux 4,215 | 4,200 / 4,195 | 4,220 / 4,215 |

  - The other 40 of 46 runs are equal.
  - **A platform difference:** Linux's final re-run (`v3-196-g29a0343`, the same HARM sources as `dev`) still gives 1,839. On the Mac, `structs` C0 gives 1,800 every time, with 8 threads or 1.
  - **A lead, not checked:** the generated config clusters every numeric with K-means. Floating point and `<random>` differ between macOS's libm and glibc, and between g++ 11 and 13.

## What the Linux session does
1. **Get the reconciled branch:**
   ```
   git status                                   # clean
   git fetch origin
   git switch ms/H11-macos                      # tracks origin/ms/H11-macos
   ```
   Read this file and H11e's "macOS checks" in `doc/plan/VALIDATION.md`.

2. **H11g on Linux (required, a few minutes):**
   ```
   git switch ms/H11g-flex-header
   bash tests/regression/check_tools_common.sh $PWD             # must print "ok: ..."
   cmake -S . -B build && make -C build -j$(nproc)
   (cd build && ctest -R "h11g_|h11d_tool_lookup")              # 2 of 2
   ```
   - A1 fakes macOS and Homebrew, so it runs on Linux.
   - Record the result in `doc/plan/VALIDATION.md`, H11g's table on that branch: one line, "Linux: A1 pass with `<compiler>`". Then commit and push `ms/H11g-flex-header`.
   - **If it fails:** record the output there, push and stop. Don't fix it.

3. **F-M2 data (optional; collect only, no fix, it is deferred):**
   ```
   mkdir -p /tmp/structs && cd /tmp/structs
   R=<harm checkout>; H=$R/build/harm
   T="--vcd $R/tests/input/coi/structs/trace.vcd --clk clk --vcd-ss tb::dut --vcd-r 1"
   $H $T --conf gen.xml --generate-config --psilent --isilent
   sha1sum gen.xml                  # the Mac: 820b2a29ab651bc8dd4f6391c8744c387102030d
   $H $T --conf gen.xml --max-threads 8 --psilent --dump-assertion-info info.json
   python3 -c "import json;print(len(json.load(open('info.json'))['assertions']))"   # Mac 1800
   ```
   - **Equal `gen.xml`:** the difference is in the mining.
   - **Different `gen.xml`:** the difference is already in `--generate-config`. Keep both files for the next milestone.
   - **Record:** add one bullet to F-M2 in `VALIDATION.md` on `ms/H11-macos`, then commit and push.

4. **Then stop and tell the user.** The user reviews and merges into `dev`, in this order:
   1. `ms/H11g-flex-header`;
   2. `ms/H11-macos`. It contains `ms/H11-linux`, so that branch needs no separate merge.

   The release (`main`, tag `v4`) is the user's decision.

## Not committed on the Mac
`build-mac/` and the logs (the tool builds, `ctest`, the fixture run).
