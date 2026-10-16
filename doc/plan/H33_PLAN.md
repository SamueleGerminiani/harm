# H33 plan: no default cap on `--reduce implies`

*Status: signed off by the user 2026-10-16 ("ok, I approve"); approved by the user 2026-10-16 ("I approve H33, remove the cap"). Owner: the portfolio's Mac session. Branch `ms/H33-implies-no-cap` from `dev` @ `b60a8f4` (H32 merged). Effort: about an hour, plus a Linux run.*

## Why
`--implies-max-pairs` (H29) skips the implication step for a context with more than 2,000,000 pairs by default. harm-rel on AssertLLM2's `i2c_slave` has 2.29 M pairs, so its step is skipped and all 11,041 assertions go to formal proof (trivergence's F7 test: 50 minutes). The user asked whether the reduction is always cheaper than proving what it drops; the miner portfolio measured it (2026-10-16, scratch script, not committed):

- **Corpus** (fixtures and 11 D1 designs, harm and harm-rel, 36 runs; d1-traffic not measured, its prover hung): the step checked 40,583 pairs in 9.2 s and dropped 384 assertions; proving those with OpenFPV (bound 20, timeout 120 s) takes 964 s of prover time. Proving all 1,772 candidates takes 4,237 s.
- **Loss:** 4 of the 384 dropped assertions are PROVEN while the assertion kept in their place is refuted (two assertions, each in harm and harm-rel: `fsm`, and `d1-reqack`'s `ack && st == 2'b10 |=> st == 2'b10`). The step is sound; the loss comes from keeping the stronger of two assertions before proof.
- **`i2c_slave` harm-rel without the cap:** the step takes 139 s on an M-series Mac (about 180 s on Linux) and drops 2,550 of 11,041 assertions, about 2 h of prover time at the corpus's mean of 3–4 s per proof (OpenFPV does not elaborate this design today, so this is an estimate).

## Change
1. `clc::impliesMaxPairs` defaults to 0 (no cap). `--implies-max-pairs <N>` stays: a user may still set a cap, and the record still says `maxPairs` and `skipped`.
2. The option's help, the README, the release notes, the report (reduction cost, limitations, the options table) and this milestone's rows; the report's milestone count.
3. Decision D-041 records the user's decision.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `check_implies_pairs.py`: `--reduce implies` without `--implies-max-pairs` records `maxPairs` 0 and `skipped` false. Fails today (`maxPairs` 2000000) | the decision |
| T2 | The H0 regression baselines and the whole `ctest` on macOS and Linux | no other change (no baseline reaches 2 M pairs) |
| T3 | `i2c_slave` harm-rel (trivergence's inputs, not committed) with the default arguments: the step runs (not skipped) and its kept set equals the earlier uncapped run's | the measurement |
| T4 | trivergence's F7 tools tests on the next portfolio release | its acceptance |

## After H33
The miner portfolio's v1.0.3 moves HARM's pin to `dev` with H32 and H33 (its own plan); trivergence reruns F7.
