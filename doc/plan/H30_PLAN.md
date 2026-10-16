# H30 plan: one message at a time on the console

*Status: signed off by the user 2026-10-16 ("I sign off H30"); approved by the user 2026-10-16 ("I approve it"). Owner: the portfolio's Mac session. Asked by the user 2026-10-16 ("yes, plan the LogTest fix"), after H29's Linux run. Branch `ms/H30-console-lock` from `dev` @ `f230470`. Effort: about two hours, plus a Linux run.*

## Why
On Linux, `LogTest.concurrentThreadsKeepOneValidLog` (H11f) crashes now and then with SIGSEGV: 1 of 277 tests in H29's run; run alone it passed 4 of 5 times, and `--repeat until-fail:30` crashed. It passed 60 of 60 on the Mac.

The cause:
- `messageWarning` writes `warning.log` under `logMutex`, then prints to `std::cout` **outside** any lock. `messageInfo` and `messageError` print the same way.
- The test points `std::cout` at one `std::ostringstream` and lets 8 threads warn at once. A string stream is not thread-safe, so its buffer is corrupted.
- In HARM's own runs, `std::cout` is the real stdout. The standard makes that free of data races, so HARM does not crash. But the characters of messages from different threads can interleave, so a warning can be printed with another one's text inside it. With `--silent`, `std::cout` has no buffer, and the threads all set its error flag at once, which is a smaller race of the same kind.

## Change
1. **A console mutex in `src/logging/src/message.cc`.** `messageInfo`, `messageWarning` and `messageError` each build their text in a local string. They then write it to `std::cout` or `std::cerr` and flush, holding a new `consoleMutex`.
   - This is a separate mutex from `logMutex`, so printing never waits for a log file's `flock`.
   - The order stays the same: the log file first, then the console. The text printed is the same, byte for byte.
2. **The test.** H11f's test keeps its sink, which the lock now makes safe. It also checks that the sink holds exactly 1,600 whole warnings.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `LogTest.consoleMessagesDoNotInterleave`: 8 threads warn 200 times each into a test stream buffer. The buffer notices when two threads are inside it at once, and a short pause inside it makes such an overlap near certain without the lock. Fails today; passes after the change | no overlap; 1,600 whole `[WARNING]` blocks in order |
| T2 | The same for `messageInfo` | as T1 |
| T3 | `concurrentThreadsKeepOneValidLog` also checks its sink: 1,600 whole warnings | as T1 |
| T4 | The printed text of one info, one warning and one error is unchanged (an error is checked in a death test) | today's text |
| T5 | Linux (trivergence's session): `ctest --repeat until-fail:50 -R LogTest` with no crash, then the whole `ctest` | today's crash |
| T6 | Mac: the whole `ctest` | no other change |

## Not in H30
- The progress bar, which TLMiner's worker threads update, already prints under its own mutex. HARM's other direct `std::cout` writes (printed assertions, debug dumps compiled out) come from one thread at a time. H30 leaves them alone.
- The two console locks are separate, so a message and a progress-bar redraw can still mix on screen, as they do today.
- The portfolio needs no new release. Its HARM pin moves to H30 at its next release.
