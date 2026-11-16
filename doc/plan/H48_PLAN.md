# H48-none-arm plan: the none arm, bounded and complete (approved by the user 2026-11-15)

## Why
- The user, 2026-11-15: let the none arm "run until it finishes and report the results specifying how long it took
  and how many additional assertions it created", and "for B, let's try to run all 10 designs, use saturn to
  speed-up the evaluation".
- In the letter's runs, none timed out on 8 of 9 designs and wrote nothing: unlike the other arms, `run_none` passes
  no `--deadline`. On credit_counter, the one it finished, 320 s of its 2,542 s were mining and about 2,200 s were
  HARM's fault check (`--fd`), which runs on one thread whatever `--max-threads` says.

## 1. HARM: the fault check on `--max-threads` threads (`Qualifier::fbqUsingFaultyTraces`)
- The loop over fault traces is split among `--max-threads` workers. Each worker parses its own fault traces and
  checks every assertion on them; the per-assertion fault lists are merged and sorted by fault index afterwards, so
  `--find-min-subset` and `--dump-assertion-info` give the same output as the one-thread loop.
- The inner evaluation stays at one thread (as now), so threads do not multiply.
- No new option; `--max-threads 1` is the old behaviour.

## 2. `eval/hint-levels/arms.py`: two none variants (evaluation code)
- **`none`** (bounded, as the other arms): the same `--deadline` as every other arm (80% of the time left less 5 s).
  It reports what it mined by then, and how much of the search it finished (consequents done of the total, from
  HARM's log).
- **`none-full`**: no deadline and no timeout; reports mining time and fault-check time separately (HARM's
  "Time to mine" and the rest), and the assertion count.
- Both drop from `--generate-config`'s output the signals that are constant over all mining traces (parameters such as
  `WIDTH` and `NumLevels`). This uses only the traces, not the RTL. Everything else is HARM's own `--generate-config`.

## Tests (written first, committed failing)
| # | Test |
|---|---|
| T7 | the parallel fault check gives the same `info.json` (fault lists included) as `--max-threads 1`, on the two harm-coi fixtures and on 3 prepared designs (credit_counter, exp_backoff, spill_register, L0+roles) |
| T8 | `none` passes `--deadline`; `none-full` passes none; both drop the constant signals (a fixture with a constant parameter) |
| T9 | `tables.py` reports none and none-full (assertions, kills, false positives, mining and fault-check times, search done) |

Existing tests unchanged (T2's reference stays: L0-deep do not change). Full ctest before sign-off.

## Runs (after T7-T9 pass; saturn and jupiter, trivergence told first)
- **A, `none` bounded:** 10 designs, 3,600 s each, 6 threads, 3 at a time (as the other arms): about 4 h over both
  machines.
- **B, `none-full`:** 10 designs, one at a time per machine with all its threads (jupiter 24, saturn 20). Measured on
  the Mac, id_queue's mining alone would take about 5 h at 4 threads; I expect 1-3 h per large design on Linux, and
  about 10-20 h in all. If a design is still running after 24 h, I stop it and report the part done.
- Each run logs HARM's peak memory; jupiter and saturn keep their container limits (40 and 22 GB).

## The letter
Table and RQ2 text: none bounded with numbers instead of "timeout"; none-full's mining and fault-check times and
assertion counts against rel. The other arms' numbers do not change.

## Closing
VALIDATION entry, PLAN.md row, H48 in the report's milestone table; after the user's sign-off, `--no-ff` merges into
`dev` and `main`, tag `v4.1.3` (the HARM binary changes: the fault check), a GitHub release with neutral notes, and a
new Docker image `samger/harm:v4.1.3`.
