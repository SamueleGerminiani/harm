# H32 plan: the decision tree's known solutions in text order

*Status: approved by the user 2026-10-16 ("I approve H32"). Owner: the portfolio's Mac session. Asked by the user 2026-10-16 ("ok, plan the fix as H32") after the investigation of trivergence's F7 parity failure. Branch `ms/H32-dt-known-order` from `dev` @ `8217f1c`. Effort: about half a day, plus a Linux run.*

## Why
trivergence's F7 tools tests on miner portfolio v1.0.2 passed 4 of 5. The one failure is the strict parity test for harm-rel on AssertLLM2's `i2c_slave`. HARM ran twice on byte-identical inputs (3 VCDs, `config.xml`, `coi.json`, `hints.json`, the same arguments, `--max-threads 4`) and kept 11,039 assertions in one run and 11,037 in the other.

## Investigation (scratch builds, not committed)
- **Not Z3.** HARM's Z3 queries have a 1,000 ms wall-clock timeout, the first suspect. A build that logs every query showed the slowest of 3,736 on these inputs takes 6 ms, none times out, and each query's work count is identical between runs. On the miner portfolio's corpus (80 runs): the slowest of 12,730 took 19 ms.
- **Reproduced on the Mac** with trivergence's inputs: 2 of 8 runs, and earlier 1 of 8, kept 4 more assertions, all of one family: `X ##1 clearStartStopDet |-> CurrState_SISt == 4'b1111` with `X` one of `!clearStartStopDet`, `!next_writeEn`, `!writeEn` (two signals). trivergence's extra 2 are of this family.
- **It needs several permutations at once.** With the consequent domain cut to the one proposition, 200 of 200 runs gave the same output. With 13 consequents (one template), 8 of 40 runs differed, and always in the same 4 assertions.
- **The cause**, found by logging this permutation's decision tree in 8 full runs: the logs agree up to one candidate, which one run stores as a solution and another skips as already known. `AntecedentGenerator::isKnownSolution` (`src/miner/modules/src/propertyMiner/TLMiner/AntecedentGenerator.cc:395`) turns the current antecedent into a text key after `DTSolution::sortByWidth()`. Without its argument that sorts each group of propositions by `shared_ptr` comparison, which is by memory address. The same antecedent can be built from different proposition objects (the negated candidates are created for each permutation), so its key depends on where the objects were allocated, which depends on how the threads interleave. A solution is then known in one run and new in another.
- This is the only use of the address order. The output path (`TLMiner.cc:510`) already sorts by text (`sortByWidth(true)`).

## Change
0. (With the tests, behaviour unchanged.) The key is built by a new `DTSolution::key(bool multidimensional)`, which `isKnownSolution` calls, so that a unit test can reach it.
1. `DTSolution::key` sorts with `sortByWidth(true)`: the key lists each group's propositions in text order, the same for any objects of the same text.
2. `sortByWidth`'s default argument is removed, so that every caller states its order; a comment says why address order must not reach the output.

The key is a canonical text after the change, so two antecedents with the same propositions are always recognised as the same. This can change which solutions a tree reports, deterministically, on designs other than `i2c_slave`; the measurement below says whether it does.

## The fix, tried in the scratch build
- `i2c_slave` harm-rel, 4 full runs: all identical, 11,041 assertions. That is the usual 11,037 plus the 4 of the family above, now always found; nothing lost.
- The 13-consequent cut, 20 runs: all identical (before: 8 of 40 differed).
- The miner portfolio's corpus (fixtures and D1, harm and harm-rel, 2 runs each, 80 runs): every kept set identical to HARM before the fix.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `DTSolutionTest.keyIgnoresObjectOrder`: two solutions with the same proposition texts in distinct objects, picked so that their address order differs from their text order, give the same known-solution key, and the key lists the texts in order. Fails today | the texts |
| T2 | `i2c_slave` harm-rel (trivergence's inputs, not committed: AssertLLM2 stays with trivergence) 8 runs and the 13-consequent cut 40 runs, all identical, with the real build | the runs themselves |
| T3 | The H0 regression baselines and the whole `ctest` on macOS and Linux | no other change, or every change listed |
| T4 | The miner portfolio's corpus (fixtures and D1, harm and harm-rel, 40 runs): the kept sets compared with `dev` @ `8217f1c`; any difference listed and explained | the measurement |
| T5 | trivergence's F7 tools tests on the next portfolio release, including the A4 parity test on `i2c_slave` | its acceptance |

## If the output changes
If T3 or T4 shows assertions that change on a fixture or a corpus design, the change is a change of default output. It is recorded as a new decision with the changed sets, and the baselines are updated only with the user's approval.

## After H32 (not in this milestone)
- The miner portfolio needs a release with HARM's pin moved past H32 (a small portfolio milestone, v1.0.3, its own plan), so that trivergence can rerun its F7 tests.
- Found on the way: harm-rel on `i2c_slave` has 2.29 M implication pairs, above `--implies-max-pairs`' default of 2,000,000, so its implication step is skipped and its 11,000 assertions all go to formal proof (trivergence's test took 50 minutes). Whether the cap or its default should change is a separate question for the user.
