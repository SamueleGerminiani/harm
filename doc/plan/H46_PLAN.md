# H46-hint-levels-eval plan: scripts that reproduce the HARM v4 letter's experiments (draft, 2026-11-14, for the user's approval)

## Why
- The user, 2026-11-14: "put it in HARM as eval/hint-levels". The hint levels stay out of HARM's features: no new
  option, no change to `harm` or `harm-coi`.
- The letter for IEEE Embedded Systems Letters measures HARM by hint level (arms none, L0, L0+roles, rel and deep),
  labels each assertion L0, L1 or L2, and reports a long-range recipe (deep).
- These definitions live in the miner portfolio's HARM adapter, which is not public. The corpus, the mutator, scoring,
  coverage and HARM's configurations (`eval/mutants/`, `eval/run_eval.py`) already are.
- With this milestone, every number in the letter can be rebuilt from one HARM tag.

## What is added (`eval/hint-levels/`, evaluation code only)
1. **`arms.py`:** the five arms as HARM and `harm-coi` command lines, extracted from the portfolio adapter with the
   same behaviour. It covers:
   - `harm-coi --emit-config`, with `--hints` and `--relations` per arm;
   - the cone file in filter mode, `depth="exact"`;
   - HARM's arguments (`--reduce implies --atom-premises --sva --reset`, threads, and the deadline at 80% of the
     time left less 5 s);
   - the hard limit;
   - the reset-active drop;
   - the level rule (L0, L1, L2);
   - the deep recipe: the long-range templates over the 1-bit flags and state encodings that are not top inputs, the
     event-in-state template, two thirds of the budget for the first pass, and the trivial forms dropped.

   Only the Python standard library and HARM's own tools are used.
2. **`cut.py`:** the trace cut (keep the first 2 cycles of each run in which no atom changes), copied from the
   portfolio with its docstring's argument for stutter invariance.
3. **`run_arms.py`:** the driver, `run_arms.py <corpus.json> <prepared dir> <out> --arms … --repeats deep=3`. It runs
   each arm on `eval/mutants`' prepared designs, scores kills with HARM's `--fd --find-min-subset` (`score.py`'s rule:
   a failure on a held-out golden trace is a false positive and kills nothing), and writes `results.csv` with kills
   by level, long-range kills and the killed mutants' ids.
4. **`tables.py`:** the letter's tables (configurations, kills by arm, RQ3, the cone filter's lost kills) from the
   CSVs.
5. **`filter_check.py`:** the cone filter's lost kills (R against R+F), sorted into reset-input consequents, in-cone
   causes at another delay, and out-of-cone correlations.
6. **`reproduce.sh`:** the order of the runs, each step a call to an existing script (`mutants/fetch.sh`,
   `mutants_eval.py --configs prepare-only`, `run_eval.py`, `run_arms.py`), with the machine and time each took.
7. **`results/`:** the CSVs behind the letter's tables (assertion counts and times only for AssertLLM2), and a
   `README.md` for the directory:
   - what reproduces what;
   - the HARM commit and the Docker image;
   - which numbers depend on wall-clock time (deep's cut, the times);
   - the machines used.

   Neutral names throughout: no internal milestone or decision codes, no private paths or hostnames (HARM's public
   face).

## Not added
- Nothing in `src/` or `tools/harm-coi/`.
- None of the portfolio's other code: its classifier, prover, caches, containers, other miners, or trivergence
  integration.

## Tests (written first, committed failing; `eval/hint-levels/tests/`, run by ctest like `eval/mutants/tests`)
| # | Test | Expected |
|---|---|---|
| T1 | the directory imports nothing outside the standard library, `eval/mutants` and HARM's tools; no file names `trivergence`, a private path, a hostname or an internal code | pass |
| T2 | per arm, on two harm-coi fixtures: the configuration and command line `arms.py` writes equal the portfolio adapter's (the adapter's output recorded once as a fixture, so the test needs no portfolio) | identical |
| T3 | the level rule, the trivial-form drop and the cut on hand-made inputs, with the adapter's own test cases | as the adapter |
| T4 | end to end on lossy_valid_to_stream and id_queue (prepared corpus): L0+roles, rel and deep give the same killed mutants as the letter's results (`slow` label) | identical |
| T5 | `tables.py` rebuilds the letter's tables from `results/` | identical numbers |

## Release
After sign-off: merge into `dev`, `dev` into `main`, tag `v4.1.1`. The code of `harm` and `harm-coi` is the same as
v4.1. The release notes say "evaluation scripts for the hint-level study" and nothing internal. A Zenodo DOI of the tag
can be made at submission.

## Questions for the user
| # | Question | Options | Recommendation |
|---|---|---|---|
| Q1 | Tag | (a) `v4.1.1` (no code change to the tools) (b) `v4.2` | **(a)** |
| Q2 | Docker image | (a) no new image: v4.1's image plus the repository at `v4.1.1` runs everything (b) `samger/harm:v4.1.1` too | **(a)** |

## Cost
About half a day, on the Mac: the extraction, five tests, the scripts and the README. T4 takes about 30 min.
