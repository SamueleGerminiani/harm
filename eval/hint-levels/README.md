# The hint-level study

Scripts and data to reproduce the experiments of *How Much Does the Design Help Hardware Assertion Mining? Hint
Levels in HARM v4*. They measure what the RTL information given to HARM buys, from none to RTL relations, in cost,
output size and mutants killed.

These are evaluation scripts. They drive `harm-coi --emit-config` and `harm` from outside and add nothing to either
tool. The corpus, the mutator, the scoring and the coverage are those of `eval/mutants/`; HARM's own configurations are
those of `eval/run_eval.py`.

## The arms

| Arm | What HARM is given |
|---|---|
| `none` | HARM's own `--generate-config`: every trace signal, no RTL |
| `L0` | `harm-coi` predicates and cones; one template `G({..#1&..} \|-> P0)` |
| `L0+roles` | L0 with `--hints`: roles, placement, one template per target class (`\|->` combinational, `\|=>` registered) |
| `rel` | L0+roles with `--relations`: `x == $past(e)`, `$stable(x)`, reset-value consequents and reset templates |
| `deep` | L0+roles, then a second pass on cut traces: `G({P0} \|-> P1 W P2)`, `G({P0} \|-> !P1 W P2)` over the design's 1-bit flags and state encodings |

What all the arms share:
- **HARM's arguments:** `--reduce implies --atom-premises --sva --reset <reset> --max-threads <n>`, and a deadline at
  80% of the time left less 5 s.
- **Scoring:** `--fd <fault traces> --find-min-subset`. A kill is an assertion that holds on every held-out golden
  trace and fails on one of a mutant's traces. An assertion that fails on a golden trace is a false positive and
  kills nothing.
- **Dropped assertions:** an antecedent that needs the reset active, and trivially true long-range forms.
- **Levels:** each assertion is labelled L2 when its antecedent is only the reset's inactive value or its end, L1
  when a consequent is an RTL relation, and L0 otherwise.

`arms.py` holds the definitions. `cut.py` is the trace cut: of every run of cycles in which no long-range atom
changes, it keeps the first two.

## Files

| File | What it does |
|---|---|
| `arms.py` | the arms as `harm-coi` and HARM command lines; the level rule; the deep recipe |
| `cut.py` | the trace cut for the deep arm |
| `run_arms.py` | runs arms on `eval/mutants`' prepared designs and scores them; writes `results.csv` |
| `filter_check.py` | sorts the kills the cone filter costs (R against R+F) into three causes |
| `tables.py` | the letter's tables from the CSVs |
| `reproduce.sh` | every step in order |
| `results/` | the CSVs behind the letter's tables |
| `tests/` | the scripts' tests (run by ctest; T4 needs a prepared directory, `HINT_LEVELS_PREPARED`) |

## Reproducing

With the Docker image `samger/harm:v4.1` (or a build of this repository), Verilator 5.034, and this repository at the
letter's tag:

```
eval/hint-levels/reproduce.sh /path/to/out                      # every step
eval/hint-levels/reproduce.sh /path/to/out prepare arms tables  # some steps
```

| Step | What | Time on the original runs |
|---|---|---|
| `fetch` | PULP common_cells v1.40.0 (pinned) | seconds |
| `prepare` | traces (directed tests, then 5,000 random cycles), 100 mutants per design, activation | 2-3 h |
| `configs` | HARM's six configurations on the 10 base designs, 600 s per run | 1.5 h |
| `assertllm2` | the same configurations on AssertLLM2, without fault traces | 1.5 h |
| `arms` | the five arms on the 10 base designs, deep 3 times, 3,600 s per run | 5 h |
| `depth` | the 8 depth variants, L0+roles and deep | 2.5 h |
| `deep` | the 4 designs where deep kills more, L0+roles and deep | 30 min |
| `filter` | R and R+F, and the filter's lost kills | 40 min |
| `tables` | the letter's tables | seconds |

**Machines:** two Linux machines (24 and 20 cores), 3 runs at a time with 6 HARM threads each.

**What varies between runs:**
- **The deep arm's cut is wall-clock based.** It ran 3 times; the repeats agreed exactly in kills and assertions.
- **Times depend on the machine,** and include the fault check.
- **Kills, assertions and false positives** are the same on any machine for every other arm.

**AssertLLM2:** the `assertllm2` step needs the AssertLLM2 designs and their golden traces under `build/assertllm2`
(see `eval/LINUX.md`). They are not distributed here, and the letter reports only assertion counts and times for them.

## The data in `results/`

| File | Rows |
|---|---|
| `arms.csv` | per design and arm: status, assertions, time, kills (all, outputs), false positives, kills by level; deep as the median of 3 repeats |
| `configurations-pulp.csv`, `configurations-assertllm2.csv` | per design and configuration: status, assertions, time (and kills on PULP) |
| `rq3.csv` | the four designs where deep kills more, every run, with the killed mutants' ids |
| `rq3-depth.csv` | the depth variants, every run |
| `filter.csv` | per design: kills by R and R+F, lost, gained, and the three causes |
