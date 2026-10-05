# Decisions

One entry per decision: context, decision, alternatives, consequences. Numbering follows `PLAN.md` §3; IDs above D-009 are added as they come up.

## D-010: one C++ toolchain for HARM and all third-party libraries (2026-10-05, H0)
- **Context:** on the development Mac, `harm` aborted at start-up (`malloc: pointer being freed was not allocated`), even for `--help`. The dependencies had been built against three C++ runtimes, all loaded into one process:
  - Spot: gcc-12 `libstdc++`;
  - ANTLR and HARM: gcc-13 `libstdc++`;
  - Boost: Apple `libc++`, because `b2` ignores `CC`/`CXX`.

  The install scripts did not pin a compiler.
- **Decision:**
  - Build every dependency and HARM with **Homebrew g++-13**, chosen by the user.
  - `third_party/install_*.sh` honour `CC`/`CXX` (Boost through an explicit `b2` toolset) and record the compiler in `<prefix>/.harm_toolchain`.
  - CMake warns at configure time when a recorded compiler differs from HARM's, or when the record is missing.
  - Boost is built `--with-regex` only: it is the only compiled Boost library HARM links; the rest is header-only.
- **macOS SDK finding:**
  - Homebrew gcc-13 (13.3.0) cannot compile a hello-world against its default sysroot, the newest Command Line Tools SDK (15.4). It fails with errors in `_stdio.h` and `_Alignof`, and `configure` reports "cannot run C compiled programs".
  - It works with the Xcode 15.2 SDK, which is the one CMake passes for HARM.
  - So on macOS the scripts set `SDKROOT=$(xcrun --show-sdk-path)` unless `SDKROOT` is already set.
- **Alternatives considered:**
  - Apple clang with `libc++` for everything. It avoids the SDK issue, but the user chose g++-13.
  - Developing in Docker (Linux only). It leaves macOS broken.
- **Consequences:** anyone building on macOS with Homebrew gcc needs an SDK their gcc supports. The README says so.
