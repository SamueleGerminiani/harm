# H13 plan: profiling is opt-in (`HARM_PROFILE`)

*Status: approved 2026-10-08 by the user ("fix, add the HARM_PROFILE option; no need to rerun all the tests"); done, awaiting review. Branch: `ms/H13-profile` (from `dev` @ `ad00f9a`). Effort: 0.5 h.*

- **The problem:** since v2 (`70ca1c0`), GCC builds were linked with `--profile`. Every HARM run, even `--version`, wrote a 2.6 MB `gmon.out` in its working directory.
  - Nothing was compiled for profiling (no `-pg`), so `gprof` found "no time accumulated".
  - It affected Linux and the Mac (g++-13).
- **The fix:**
  - The unconditional `add_link_options("--profile")` is removed.
  - A new CMake option, `HARM_PROFILE` (default OFF), compiles and links with `-pg` for a real `gprof` profile.
  - HARM's output does not change.
- **Test:** `h13_no_gmon`, written first and failing: a default build run in an empty directory writes no `gmon.out`.
- **Validation (reduced, by the user's choice):** `h13_no_gmon` plus two existing tests, and a `HARM_PROFILE=ON` build whose `gmon.out` `gprof` reads. The full `ctest` is not re-run: the change is a link flag, and HARM's code is unchanged.
