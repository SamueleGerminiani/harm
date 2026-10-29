# H39 plan: a deadline for mining and for the implication step, and a faster implication step

*Status: part of the miner portfolio's HX1 (`doc/plan/HX1_PLAN.md`, parts A-C, approved by the user 2026-10-29). Owner: the portfolio's Mac session. Branch `ms/H39-deadline` from `dev` @ `1b5b864`. Effort: two to three days.*

## Why
HARM writes nothing until it ends, and the portfolio kills it at its budget. On AssertLLM2's large designs (2,000 cycles, the portfolio's configuration) HARM mines in 24-113 s and then spends the budget in `--reduce implies`: `openmsp430` 12,730 assertions, 2,852,456 pairs checked in 1,010 s, 1,138 dropped (9 %); `xgate` (33,700), `pci_bridge` (49,213) and `10gemac` (90,626) were still reducing at 300-600 s. With harm-coi's relations (the portfolio's harm-rel), mining itself takes longer than the budget (`openmsp430`: 743 propositions, 758 permutations, not done at 240 s). A stack sample during the reduction: one thread, about half of it building strings (`Instance::key()`, sets of strings in `harmImplies`). After the pairs, the step keeps an n × n matrix of booleans and walks it in O(n²) three times (equivalence classes, the drops, the records): 90,626² bits is about 1 GiB.

## Change
- **`--deadline S`** (seconds from HARM's start, fractional): the implication step checks pairs while there is time and stops at `S`; a pair not checked counts as unrelated, so nothing is dropped that would not have been (sound, fewer drops, as H29's pairs left out, F4). The context's implication record (info.json) gains `unchecked` (pairs not checked) and `deadlineHit`. Mining's deadline defaults to `0.75 S`.
- **`--mine-deadline M`** (seconds from HARM's start): mining starts no template and no permutation after `M`; those under way finish. HARM prints "Deadline: mining cut, P of N permutations done" and goes on to qualify what was mined, and exits 0. info.json gains `"deadline": {deadline, mineDeadline, mineCut, permutationsDone, permutationsTotal}` when either option is given (a template not started counts its permutations in the total once generated; templates never started are counted as `templatesNotStarted`).
- **A faster implication step, the same result:** the relations of the checked pairs kept sparsely (only checked pairs can relate) instead of the n × n matrix, and the walks over them in O(pairs) instead of O(n²); integer keys in place of the strings the profile shows. The kept assertions, their order and `--dump-implications`' records are unchanged.
- Without either option nothing changes.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/regression/check_deadline.py` on `tests/input/h29`: `--deadline 0` with `--mine-deadline 1000` keeps `--reduce equiv`'s set, the record has `deadlineHit` and every pair unchecked; `--deadline 1000` gives the run without a deadline, `mineDeadline` 750 | the change |
| T2 | `tests/regression/check_reduce_same.py`: the kept assertions and the implication records on `h29`, `h3` (stronger, weaker, ranked), `h3b` and `h29` with `--atom-premises` equal H38's (`tests/input/h39/`, written at H38); and, as a measurement, the same on the portfolio's `openmsp430` configuration, with the time | the faster step |
| T3 | `check_deadline.py`: `--mine-deadline 0` starts no permutation, exits 0, records `mineCut`; `--deadline 8` alone gives `mineDeadline` 6; no option, no record | the change |
| T4 | ctest and harm-coi's pytest on the Mac and on Linux | no other change |
