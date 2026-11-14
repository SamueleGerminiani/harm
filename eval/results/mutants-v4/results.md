# HARM v4 on PULP common_cells with classical mutants (H45-mutant-eval, 2026-11-14)

HARM's configurations (`eval/run_eval.py`, as in H44) on the mutant corpus (`eval/mutants/corpus.json`). Per design and
configuration, `results.csv` gives:
- assertions, time;
- false positives;
- mutants activated and killed, all and on outputs only, and per operator (`by_op`).

The bug-finding study by hint level that uses this corpus is miner-portfolio's HL1-hint-levels. Its results are in
that repository and are not repeated here.

## Setup
- **HARM:** this branch at 16011a2 (C++ of 1339b67), built in `h45-tools:1` (samger/harm:v4 plus Verilator 5.034).
- **Machine:** saturn (Linux, 20 CPUs, 22 GB, 6 HARM threads). Timeout 600 s per run.
- **Traces:** directed tests from reset, then a constrained-random phase of 5,000 cycles. Mining seeds 1-5; held-out
  seeds 101-103.
- **Mutants:** 100 per design (seed 1; fewer when the design has fewer sites). Only mutants activated on a held-out
  seed are counted, as "output" when an output differs, "internal" otherwise.
- **Kill:** `--fd <fault traces> --find-min-subset`. An assertion that fails on a held-out golden trace is a false
  positive and kills nothing; any other assertion that fails on a mutant's trace kills it.

## The corpus (PULP common_cells v1.40.0, Solderpad 0.51; wrappers and testbenches written for this evaluation)

| Design | Source files | Lines | Mutation sites | Mutants | Activated (output / internal) |
|---|---|---|---|---|---|
| spill_register | spill_register, spill_register_flushable | 149 | 119 | 100 | 100 / 0 |
| fall_through_register | fall_through_register, fifo_v3 | 209 | 134 | 100 | 77 / 13 |
| fifo_v3 | fifo_v3 | 152 | 218 | 100 | 91 / 1 |
| rr_arb_tree | rr_arb_tree, lzc, cf_math_pkg | 495 | 177 | 100 | 91 / 0 |
| id_queue | id_queue, lzc, onehot_to_bin, cf_math_pkg | 629 | 220 | 100 | 66 / 15 |
| lfsr | lfsr | 309 | 126 | 100 | 98 / 0 |
| plru_tree | plru_tree | 130 | 74 | 74 | 43 / 21 |
| delta_counter | delta_counter | 83 | 92 | 92 | 82 / 7 |
| exp_backoff | exp_backoff | 93 | 313 | 100 | 88 / 0 |
| credit_counter | credit_counter | 55 | 46 | 46 | 46 / 0 |
| lossy_valid_to_stream | lossy_valid_to_stream | 139 | 142 | 100 | 96 / 0 |
| stream_delay | stream_delay, counter, delta_counter, lfsr_16bit | 328 | 476 | 100 | 64 / 16 |

- **Mutants that compile:** all of them. No mutant was replaced as uncompiled or hung on these entries.
- **Depth variants:** the 8 `<design>_d<n>` entries are the same sources with one more define.
- **Coverage:** in miner-portfolio's HL1 results. Line coverage is below 90% only on code that cannot run with the
  corpus parameters.
- **The configuration runs:** the first 10 entries. The last two were added for HL1's RQ3.

## Kills by configuration (the first 10 designs; 839 activated mutants)

| Configuration | Designs finished | Killed | False positives | Assertions | Time (s, scoring included) |
|---|---|---|---|---|---|
| C0 (HARM's generated configuration) | 0 of 10 | | | | timeout on all |
| R (RTL predicates, COI rank) | 10 | 523 (62%) | 61 | 2,213 | 1,898 |
| R+F (plus the COI filter) | 10 | 464 (55%) | 25 | 1,190 | 1,127 |
| R+F+X (plus `--reduce implies --atom-premises`; = C7) | 10 | 464 (55%) | 22 | 726 | 833 |
| RR (RTL predicates and relations, rank) | 5 | 330 of 385 | 48 | 1,270 | 1,147 |
| RR+F+X | 10 | **718 (86%)** | 57 | 3,200 | 2,533 |

Per design (assertions; killed / activated):

| Design | R | R+F | R+F+X | RR | RR+F+X |
|---|---|---|---|---|---|
| spill_register | 214; 72/100 | 74; 69/100 | 63; 69/100 | timeout | 647; 100/100 |
| fall_through_register | 584; 59/90 | 367; 54/90 | 201; 54/90 | timeout | 982; 87/90 |
| fifo_v3 | 219; 55/92 | 98; 43/92 | 79; 43/92 | timeout | 198; 77/92 |
| rr_arb_tree | 490; 65/91 | 318; 65/91 | 99; 65/91 | timeout | 192; 65/91 |
| id_queue | 422; 44/81 | 209; 21/81 | 171; 21/81 | timeout | 721; 65/81 |
| lfsr | 27; 48/98 | 11; 48/98 | 11; 48/98 | 35; 75/98 | 17; 75/98 |
| plru_tree | 13; 31/64 | 5; 28/64 | 5; 28/64 | 16; 38/64 | 8; 36/64 |
| delta_counter | 81; 59/89 | 28; 51/89 | 24; 51/89 | 326; 88/89 | 131; 87/89 |
| exp_backoff | 76; 61/88 | 40; 61/88 | 40; 61/88 | 235; 83/88 | 118; 80/88 |
| credit_counter | 87; 29/46 | 40; 24/46 | 33; 24/46 | 658; 46/46 | 186; 46/46 |

Per operator, R+F+X / RR+F+X (killed of activated):

| Operator | Stuck-at-0 | Stuck-at-1 | Inversion | Operator | Condition | Constant |
|---|---|---|---|---|---|---|
| R+F+X | 69/204 | 155/257 | 111/154 | 67/125 | 44/59 | 18/40 |
| RR+F+X | 170/204 | 223/257 | 148/154 | 96/125 | 54/59 | 27/40 |

## What it shows
- **Without the RTL (C0),** HARM finishes no design within 600 s.
- **The COI filter (R → R+F)** halves the output and the false positives (61 to 25). It costs 59 kills, 23 of them on
  id_queue.
- **The reduction (+X)** removes 39% more assertions and changes no kill.
- **The relations (RR+F+X)** raise kills from 55% to 86% of activated mutants, on 9 of 10 designs (all but rr_arb_tree),
  at about 4× the assertions and 2.6× the false positives of R+F+X. Most of the gain is on stuck-at-0 faults (69 to
  170).
- **RR without the filter** times out on 5 designs.
