# H21 plan: leftovers from H19

*Status: planned, awaiting approval. Branch: `ms/H21-leftovers` (from `dev` @ `ccf06e8`). Effort: 0.5 d, plus a full `ctest`. Linux: not scheduled (the user, 2026-10-10).*

| # | Leftover | From | Fix |
|---|---|---|---|
| L1 | `warning.log` and `error.log` are JSON arrays rewritten whole on every message (`deleteLastLine` reads every line and writes all but the last). The cost of a message grows with the file: a 21,636-line `warning.log` in `build-mac` slowed `Z3EquivalenceTest` 15-fold (VALIDATION, H19; a known limitation in the release notes) | H19 | Under the existing lock (H11f, F-L9), the writer looks at the file's last two bytes. If they are `]\n`, the new record overwrites them, followed by `]\n` again. The bytes written are the same as today, at a constant cost per message. A file that does not end in `]\n` (edited by hand, or cut by a crash) takes today's path, so nothing changes for it |
| L2 | `ExpToZ3Visitor.cc` says division is opaque because "division by zero aborts HARM"; since H19 (D-035) it gives x for `logic` and 0 for C integers | H19 | The comment gives the current reason: Z3's `bvudiv`/`bvsdiv` by zero (all ones, or ±1) differs from D-035's x/0, so division stays opaque. No code change |
| L3 | `build-mac/` (the Mac build directory used since H11) shows as untracked | H11 | `.gitignore`: `build-*/` (no tracked path matches) |

The local branch `ms/H20-missing-operators` stays: every milestone keeps its branch.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| A1 | `LogTest.appendCostDoesNotGrowWithTheFile`: on a `warning.log` of 50,000 records, 2,000 more warnings take less than 2 s (today: one rewrite of the whole file per warning) and leave one valid array of 52,000 records | timing, with a wide bound; `expectValidLog` |
| A2 | `LogTest.sameBytesAsBefore`: three warnings and one error give exactly the text today's code writes (fixed timestamps aside) | today's output |
| A3 | `LogTest.unterminatedFileKeepsTheOldBehaviour`: a log whose last line is not `]` is handled as today | today's output |
| A4 | The existing `LogTest` tests (concurrent processes and threads, the empty file) pass unchanged; one full `ctest`; the H0 baselines byte-identical | ctest |

## Documents
VALIDATION; PLAN status; H21 in the release notes and the report (their milestone tables; `h14_doc_coverage` fails until then); the release notes' known limitation on the logs removed (it moves to "fixed"); the report's portability section (F-L9 paragraph: a sentence on the constant cost). No DECISIONS entry (no behaviour or format changes) and no TRIVERGENCE_IMPACT entry (trivergence does not read the logs).
