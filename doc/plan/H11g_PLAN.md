# H11g plan: `install_verilator.sh` on macOS (finding F-M1)

*Status: approved 2026-10-08 by the user ("fix it now"). Branch: `ms/H11g-flex-header` (from `dev` @ `746e191`). Effort: 0.5 h, plus a Verilator rebuild on the Mac.*

## The bug (found by the macOS checks on `ms/H11-macos`, H11e's VALIDATION entry there)
- **Symptom:** on macOS, `install_verilator.sh` stops at
  ```
  V3Lexer_pregen.yy.cpp:368:10: fatal error: FlexLexer.h: No such file or directory
  ```
- **Cause:** Homebrew's flex is keg-only. `tools_setup` (`third_party/tools_common.sh`) puts its `bin/` first on `PATH`, so the right `flex` runs, but its `include/` is on no include path, and the macOS SDK has no `FlexLexer.h`.
- **Linux is not affected:** the distribution's flex package installs the header in `/usr/include`.

## The fix
- On macOS, for each Homebrew formula `tools_setup` already puts on `PATH` (bison, flex, gperf), its `include/` directory, if present, is prepended to `CPATH`. GCC and Clang both read `CPATH`, and a `CPATH` the user set is kept after it.
- **Unchanged:** Linux, the scripts' arguments, the tool versions, and HARM.

## Tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | `h11g_tools_common_flex`: `tools_setup` with macOS and Homebrew faked, and a flex prefix whose `FlexLexer.h` holds a marker. The compiler, run with the environment `tools_setup` leaves, must preprocess `#include <FlexLexer.h>` to that file. Fails before the fix; runs on Linux and macOS | ctest |
| A2 | On the Mac: `install_verilator.sh` with no `CPATH` builds and reports `Verilator 5.052` | script run (Mac) |
| A3 | `h11d_tool_lookup` and the A1 test pass on the Mac; Linux unchanged by construction (the change is inside the `darwin` branch) | ctest |
