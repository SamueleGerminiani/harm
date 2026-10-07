# H11d plan: the simulation and synthesis tools in `third_party` (Linux and macOS)

*Status: approved 2026-10-07 (build from source); in progress. Branch: `ms/H11d-tools` (from `dev` @ `e429f47`). Effort: 1–2 d, plus long tool builds and the user's run on the Mac.*

## Why
The H11 Linux checklist needed tools that were not where HARM's build expects them:
- **Verilator:** the machine's default is 4.210, without `--binary`, so 30 oracle tests failed until a Verilator 5 was borrowed from another project's OSS CAD Suite.
- **yosys:** the only one is 0.47, without `read_slang`, so the yosys cross-check (7 tests) never runs on Linux.
- **The Docker image:** takes Verilator and Icarus from Ubuntu's packages, whose versions follow the distribution, not HARM.

The user asked for the most recent versions, installed locally like the other dependencies in `third_party`, on Linux and macOS.

## The tools and versions (latest stable releases, checked 2026-10-07 on GitHub)
| Tool | Version | Used by |
|---|---|---|
| Verilator | 5.052 | the simulation oracles: `verilator_replay_*` (H1), `coi_*` and `h5_influence_*` (H4, H5), the fixture generators (H1b, H11c) |
| Icarus Verilog | 13.0 | the 4-state fixture generator (`tests/oracle/gen_iverilog_fixture.py`, H1) |
| yosys, with `read_slang` | 0.69 | the H5 cross-check (`h5_xcheck_yosys_*`). Since 0.67, yosys builds slang and sv-elab in itself, from submodules included in the release tarball `yosys.tar.gz`; no separate plugin |

## Approach: build from the release sources (recommended), as the other `third_party` scripts do
- **Three new scripts,** in the style of `install_z3.sh`:
  - `install_verilator.sh`, `install_iverilog.sh`, `install_yosys.sh`;
  - each downloads one pinned release, builds it, installs it into `third_party/<tool>` (or a given prefix), and writes the version to `third_party/<tool>/.harm_version`;
  - they are added to `.gitignore`.
- **Compiler:**
  - The tools are separate programs, not linked into HARM, so D-010 (one C++ runtime) does not bind them. The scripts still use `CC`/`CXX` (default `cc`/`c++`) and, on macOS, the same `SDKROOT` handling.
  - slang (in yosys) needs C++20: GCC ≥ 11, Clang ≥ 17 or Xcode ≥ 16.4. The script checks this and stops with a clear message.
- **`install_all.sh`:** gains a `tools` part, run by default, with `--no-tools` to build only HARM's libraries. The tools are needed only for tests and validation, not to build or run HARM.
- **Prerequisites, system packages listed in the README, not installed by the scripts:**
  - **Linux (apt):** `autoconf flex bison help2man gperf perl gawk libfl-dev zlib1g-dev libreadline-dev tcl-dev libffi-dev pkg-config python3`, and CMake ≥ 3.28 for yosys (HARM needs 3.30).
  - **macOS (Homebrew):** `autoconf bison flex gperf help2man gawk readline tcl-tk libffi pkg-config cmake`.
  - macOS's own bison 2.3 is too old, so the scripts put Homebrew's bison and flex first on `PATH`.
- **Alternative, not recommended:** OSS CAD Suite's prebuilt bundle (`oss-cad-suite-<os>-<arch>-<date>.tgz`, 500–750 MB, Linux and macOS, x64 and arm64).
  - It is faster to install and has all three tools.
  - But it is large, its Verilator is often a development build, its tools come from a nightly date rather than the stable releases, and on macOS it needs quarantine removal.
  - It could be offered later as `install_tools_prebuilt.sh`.

## HARM's build and tests use them
- **CMake** looks first in `third_party/{verilator,iverilog,yosys}/bin`, then on `PATH`. The configure output names the path and version of each.
- **Version checks:**
  - Verilator must be ≥ 5. An older one is reported and treated as not found, so its tests are skipped, not failed. This is the H11 lesson.
  - yosys keeps the `read_slang` probe (H11c, F-L3).
- **Tests run with the chosen tools first on `PATH`:** the fixture scripts call `verilator` and `iverilog` by name. Each test gets `PATH` prepended via `ENVIRONMENT_MODIFICATION`, so the build's tools are used whatever the user's `PATH` is.
- **Docker:** the image runs the same three scripts instead of `apt-get install verilator iverilog`. It needs the prerequisites above from apt.
- **Docs:**
  - README "Dependencies": the scripts, the prerequisites per OS, the versions.
  - `eval/LINUX.md`: remove the borrowed-Verilator steps.

## Tests
| # | Test | Kind | Where |
|---|---|---|---|
| A1 | The three scripts install the pinned versions into `third_party` from a clean checkout. `verilator --version`, `iverilog -V` and `yosys -V` report 5.052, 13.0 and 0.69, and `yosys -p "read_slang …"` works | script run | Linux here; **macOS by the user** |
| A2 | CMake prefers `third_party` over `PATH`: with a fake old `verilator` and `yosys` first on `PATH`, the configure output names the `third_party` ones. With only a fake Verilator 4 available, its tests are skipped with a message, not registered as failing | regression (`cmake -P`, fake binaries, like `h11c_yosys_probe`) | both |
| A3 | Full `ctest` with the `third_party` tools and no tool on `PATH`, including the 7 `h5_xcheck_yosys_*` tests, never run on Linux before (213 tests). The H0 baselines byte-identical | ctest | Linux here; **macOS by the user** |
| A4 | The Docker image builds with the scripts, and its fast tests pass | docker | Linux here |

- If A3 shows a new failure (the cross-check has never run on Linux, and the tools are newer), it is a **finding**: recorded and brought to the user, not fixed in H11d.

## After H11d
Merge into `dev`, then into `ms/H11-linux`, and run the remaining checks there on the current state:
- the full `ctest`;
- the Docker image;
- the local designs with `--check` (§4a).
