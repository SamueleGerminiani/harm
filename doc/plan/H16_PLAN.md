# H16 plan: `--check-dump-eval` file names (trivergence T12 A5 finding)

*Status: approved 2026-10-08 by the user (names (b), the row fix in scope). Branch: `ms/H16-check-dump-names` (from `dev` @ `ef396e3`; local only). Effort: 0.5 d, plus a full `ctest`.*

## The problem (reproduced on the Mac, HARM `ce3b5bd`)
- **Where:** `TemplateImplication::check()` (`src/miner/utils/src/TemplateImplication.cc`, the `checkDumpEvalDirectory` block). Each `check` assertion's CSV is named `sanitizeFilename(<Spot text>) + ".csv"`; `sanitizeFilename()` (`src/utils/include/misc.hh`) deletes every character outside `[A-Za-z0-9-_.+()[]#=>|:]`.
- **1. Silent overwrites.** Reproduced: `G(v2 != v4 -> v3)` and `G(v2 <= v4 -> v3)` both give `G(v2=v4->v3).csv`; four assertions, three files, no warning. Also reproduced: `a && b`, `a & b` and a signal `ab` collide; `!a` and `a` collide; so does the same assertion checked in two contexts (10 assertions, 5 files). `a ^ b`, listed in the PLAN entry, does not: Spot prints it with parentheses (`(x^y)==1`).
- **2. A long assertion kills the run.** A name over 255 bytes cannot be opened, and `messageErrorIf` exits with code 1, losing every other result (trivergence reproduced it with a 20-conjunct antecedent).
- **3. No way back.** Nothing maps a file to its assertion.
- **4. Found while reproducing (not in the PLAN entry): malformed rows.** The Shift, Con and Ass columns are written only inside `if (_applyDynamicShift || _constShift > 0)`, and so is the row's newline. For an assertion without a shift (`G(a -> b)`), the file is the header plus one line: `0, T, 1, F, 2, F, ...`. The consequent and the verdict are never written. **H15's oracle needs exactly these files**, so I propose fixing it here (one more line of the same block).

## The fix (D-030, a change of an output format)
| | Choice | Recommended |
|---|---|---|
| **File names** | (a) `<k>.csv`, where `k` = 0, 1, 2, … is the order in which HARM checks the assertions in the run (contexts in order, `check` templates in config order). Unique and bounded by construction | (recommended) |
| | (b) `<k>_<sanitized text truncated to 100 bytes>.csv`: still unique and bounded, readable in `ls`, but a second naming rule consumers might be tempted to parse. The index is the contract; the text part is only for people | **chosen by the user** |
| **Index** | `index.json` in the dump directory, written once at the end of the run: `{"version": "1", "assertions": [{"file": "0.csv", "context": "default", "spot": "<exact Spot text>", "sva": "<exact SVA text>"}, …]}`. `spot` is the string the old name was derived from; `sva` is what trivergence compares against. JSON-escaped, so commas, quotes and `{a, b}` concatenations are safe | |
| **Open failure** | A file that still cannot be opened (e.g. disk full) gives a warning and `"file": null` in the index; the run continues. Never an exit | |
| **Rows (item 4)** | Every row has the five header fields `t, Ant, Shift, Con, Ass`. For an assertion without a shift, Shift is the evaluator's shift (0); for the others nothing changes | |
| **`sanitizeFilename()`** | Unused after the fix (its only caller): removed | |

- Nothing else changes: the dump directory's handling (removed and re-created), stdout, the mined assertions and every other output stay byte-identical.

## Tests (written first, committed failing)
New fixture `tests/input/h16/` (a small hand-written CSV trace with Boolean signals `a`, `b`, `ab`, `c` and integers `x`, `y`; a config with two contexts) and a checker `tests/regression/check_dump_eval.py`, as ctest `h16_check_dump_eval` (label `regression`).

| # | Test | Fails today because |
|---|---|---|
| A1 | **Collisions:** `G(x != y -> c)`, `G(x <= y -> c)`, `G(a && b -> c)`, `G(a & b -> c)`, `G(ab -> c)`, `G(!a -> c)`, `G(a -> c)`, and `G(a -> c)` again in the second context: 8 assertions give 8 distinct files and 8 index entries | 3 files |
| A2 | **Long name:** a 20-conjunct antecedent (over 255 bytes of name), followed by a short assertion: HARM exits 0 and both have their dump | exit code 1 |
| A3 | **Mapping:** every index entry names an existing file, every `.csv` in the directory is in the index exactly once, and each entry's `spot` and `sva` are the exact expected texts (hand-written in the checker) | no index |
| A4 | **Contents, independent oracle:** the checker recomputes Ant, Con and Ass for every row from the CSV trace in Python (these templates are propositional, `->` and `|=>`) and compares them with the file the index maps the assertion to. This proves the mapping is right, not only that names are unique, and covers item 4 (five fields per row) | malformed rows, no index |
| A5 | Full `ctest` on the Mac (in the background, ~32 min); the H0 baselines byte-identical. Linux: pending, as for the earlier milestones | — |

## Documents
- `doc/plan/DECISIONS.md`: **D-030** (new names, `index.json` v1, row fix, no exit).
- `doc/plan/TRIVERGENCE_IMPACT.md`: an H16 entry. T12's A5 test must read `index.json` instead of guessing names, and can drop any workaround for `->` rows.
- `README.md` (the option's text), `doc/MIGRATING_v3_to_v4.md` (an output change since v3).
- `doc/plan/VALIDATION.md` (H16 entry), `doc/plan/PLAN.md` (status).

## Not in scope
- An SVA-style reset for check mode (`disable iff`): already recorded in PLAN §H16; a separate decision and milestone if wanted.
- Boolean `^` (`G(a ^ b -> c)` is a temporal parse error; `x ^ y == 1` on integers works): found while writing A1, recorded for a later fix.
- Anything about what is evaluated (semantics, multiple traces, sampling): H15 will rely on these files as they are, plus the fixes above.
