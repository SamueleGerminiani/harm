# H11f plan: the log files under concurrent writers (finding F-L9)

*Status: approved 2026-10-07 by the user ("fix F-L9"); reviewed and merged into `dev` 2026-10-08. Branch: `ms/H11f-log-race` (from `dev` @ `e429f47`). Effort: 0.5 d.*

## The bug (found in H11d's Docker check)
- **Symptom:** in the Docker image, the fast tests crash intermittently with SIGSEGV under `ctest -j`: `PropositionOracleTest` once, `Z3EquivalenceTest` twice. None crashed in 40 runs alone.
- **Mechanism:** every warning or error is appended to `warning.log`/`error.log` in the working directory by a read-modify-write (`src/logging/src/message.cc`):
  1. check that the file is not empty;
  2. `deleteLastLine` reads it, truncates it and rewrites it without its last line (`]`);
  3. the new record is appended.

  The gtests share one working directory (`build/`). Another process can truncate the file between steps 1 and 2. `deleteLastLine` then reads zero lines, and `lines.size() - 1` (a `size_t`) wraps to 2^64 − 1, so the loop reads past the vector (`src/utils/include/misc.hh:460`).
- **Also affected:** HARM's own threads (`--max-threads`) log through the same code, and interleaved writers can corrupt the JSON even without a crash.

## The fix
1. **`deleteLastLine`** returns at once on an empty file. The loop bound cannot underflow.
2. **Serialized writes:**
   - `dumpWarningToFile` and `dumpErrorToFile` hold an exclusive lock for the whole read-modify-write: `flock(LOCK_EX)` on the log file (POSIX; Linux and macOS), plus a process-wide `std::mutex` for HARM's threads.
   - Every writer that uses this code waits for the others, so the file stays a valid JSON array.
- **Unchanged:** the files' names, place and format.

## Tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | `deleteLastLine` on an empty file returns, and leaves it empty. Before the fix this test crashes (deterministic, no race needed) | gtest (`LogTest`) |
| A2 | 8 processes (`fork`), 200 warnings each, in one directory: all exit normally, and `warning.log` is one JSON array with 1,600 records | gtest |
| A3 | 8 threads, 200 warnings each, in one process: the same | gtest |
| A4 | Linux `ctest` green; the Docker image's fast tests pass on repeated `ctest -j` runs (the H11d symptom) | ctest, docker |
