# H11b plan: HARM builds on Linux (finding F-L1, found in H11's Linux checklist)

*Status: approved 2026-10-06; reviewed and merged into `dev` 2026-10-07. A4 on the Mac: pass, 226 of 226 (2026-10-08, `ms/H11-macos`). F-L2: `ImplicationTest` gets `TIMEOUT 3600` (the user's choice, 2026-10-07). Branch: `ms/H11b-linux-build` (from `dev` @ `1dc0609`). Effort: 0.5 d, plus the Linux checklist re-run (~1 h of machine time).*

## The bug (H11 VALIDATION, branch `ms/H11-linux`)
- **F-L1:** HARM does not compile on Linux x86_64 (Ubuntu 22.04, g++ 11.4.0, Z3 4.13.4 from `third_party/install_z3.sh`).
  ```
  src/exp/include/visitors/ExpToZ3Visitor.hh:73:61: error: call of overloaded 'bv_val(long long unsigned int&, unsigned int&)' is ambiguous
     73 |   z3::expr bv(unsigned long long value) { return _ctx.bv_val(value, _U); }
  ```
- **Cause:** `z3::context::bv_val` is overloaded for `int`, `unsigned`, `int64_t` and `uint64_t`. On LP64 Linux, `uint64_t` is `unsigned long`, so `unsigned long long` matches none exactly, and the conversions tie. On macOS, `uint64_t` is `unsigned long long`, which is why the Mac builds.
- **Origin:** H2 (`059d7de`). It is the only compile error (`make -k`). The targets that depend on `exp` were not compiled, so further Linux-only errors may still appear behind it.

## The fix
- `ExpToZ3Visitor::bv` takes `uint64_t` instead of `unsigned long long`.
  - On macOS this is the same type, so the Mac build and its behaviour are unchanged by construction.
  - On Linux it is the exact `bv_val(uint64_t, unsigned)` overload.
- **Values:** all call sites pass small values (widths, shift amounts, `1`), and the literal path already uses `bv_val((uint64_t)…, 64)` or the decimal-string overload. No value is narrowed.
- **Scope:** if the build then stops at another error of the same kind (an integer-type portability error between macOS and Linux), it is fixed the same way and listed here.
  - **Out of scope:** any test that fails on Linux once HARM builds, and any count that differs from the Mac. These are findings: recorded in VALIDATION and brought back to the user, not fixed in H11b.

## Tests
No new test is needed to show the bug: on Linux, the existing suite does not build at all. Before the fix, the Linux build log (in H11's VALIDATION) is the failing evidence.

| # | Test | Kind |
|---|---|---|
| A1 | `make` on Linux (g++ 11.4.0, D-010): HARM and every test target build | build |
| A2 | `Z3EquivalenceTest.*` on Linux: hand-labelled pairs, exhaustive small variables, random wide variables (64-bit and wider, so `bv` is used with `_U > 64`), timeout never means equivalent | gtest |
| A3 | Linux `ctest`, all labels, with harm-coi's pytest (`h5_*` not skipped); the summary goes in VALIDATION | ctest |
| A4 | macOS: the build and `ctest` stay green. The type is identical there, so this is a check that nothing else moved; to be run by the user on the Mac | ctest (Mac) |
| A5 | The H0 regression baselines byte-identical on Linux (part of A3) | regression |

## Validation
- A2 is independent of the changed line: it compares Z3's verdicts with HARM's own evaluation on enumerated and random assignments.
- A5 shows that mining output on Linux equals the Mac's for every baseline.

## After H11b
Once it is merged into `dev`, `ms/H11-linux` takes `dev` and the Linux checklist (`eval/LINUX.md` §1–4) is re-run on it:
- ctest;
- Docker;
- the fixtures and examples with `--check`;
- the AssertLLM2 manifest already written there.
