# H45-mutant-eval plan: bug-finding on open designs with classical mutants, for the HARM v4 paper

*Status: approved by the user 2026-11-13 ("Approve as drafted"; Q1 (a), Q2 (a), Q3 (a), Q4 (b): no v3-vs-v4 table). Asked by the user (2026-11-13: "should we use different designs with more
classical mutants (such as stuck-at) for this paper?" ... "yes, do it"). Owner: the portfolio's Mac session. Branch
`ms/H45-mutant-eval` from `dev` (`f8d01c9`).*

## Why
The paper advertises HARM v4. Its evaluation needs a bug-finding result. H44's mutant coverage cannot be published:
- H44 measured it on AssertLLM2 with AssertLLM2's own bug variants (`a2-M_*`), which is the measurement of
  trivergence's unpublished Paper A. trivergence, 2026-11-13: the lead decides; counts, times and reduction on
  AssertLLM2 are cleared.
- 5 mutants per design move coverage in steps of 20 points.

HARM's examples with faulty traces (`faultCov`, `sobel`, `paperRE`, `bl_master`) have no RTL, so they cannot show
harm-coi. This milestone builds a corpus that the paper owns: open designs that are not in any of trivergence's
corpora, each with many classical mutants.

## What is measured
For each design, the configurations of H44 (C0, R, R+F, R+F+X, RR, RR+F+X), mined on golden traces, scored on the
mutants' traces:
- **assertions, wall time** (as in H44);
- **mutation score:** killed / activated. A mutant is *activated* when its trace differs from the golden trace on the
  same stimulus; a mutant that is never activated cannot be caught by any trace-based assertion, so it is reported
  apart (count per design), not as a miss;
- **killed on outputs only:** the score again, counting only mutants whose difference reaches a top-level output
  (closer to how a bug is seen in practice);
- per mutation operator (stuck-at-0, stuck-at-1, inversion, operator, constant), to show which kinds of bug each
  configuration catches.

Kill = an assertion mined on the golden traces fails on the mutant's trace (HARM's `--fd`, unchanged).
Mining and scoring use different stimulus seeds: assertions mined on seed 1 (golden), mutants simulated with seed 2,
golden seed 2 checked first (an assertion that fails on golden seed 2 is a false positive and is reported, not
counted as a kill).

## The corpus
**Designs:** 8-10 public designs, single clock, synthesizable, in SystemVerilog (packages, parameters, structs where
the design has them: what GoldMine cannot read), all from PULP `common_cells` (Solderpad 0.51), pinned to one commit.
Candidates: `fifo_v3`, `stream_fifo`, `spill_register`, `fall_through_register`, `rr_arb_tree`, `stream_arbiter`,
`lzc`, `delta_counter`, `stream_register`, `lfsr`, `id_queue`, `plru_tree`, `ecc_encode`/`ecc_decode`; the final list
is those that pass the selection criteria, preferring variety (FIFOs, arbiters, counters, datapath).
*Overlap check (trivergence, 2026-11-13):* common_cells are in none of trivergence's corpora (AssertLLM2, the A5 twins,
the post-cutoff set, HierSVA, FVEval, AssertionBench, Hack@DAC). Hack@DAC's Ariane/PULP SoCs vendor common_cells
files, but none of their bug-carrying modules; the paper says so in one sentence. OpenTitan is left out entirely
(`pwm` and `rv_timer` are in trivergence's OpenTitan corpus, `pwm` in its held-out split; the `prim_*` cells sit
inside those IPs, and Paper D's planned real-bug sources include OpenTitan bugs). OpenCores cores only if needed, and
only after trivergence checks the names (its AssertionBench split holds many OpenCores modules).
The sources are fetched by a script, not copied into HARM (`eval/mutants/fetch.sh`), like `eval/LINUX.md` does for
AssertLLM2.

**Selection criteria**, checked by a script: elaborates with pyslang and Verilator; one clock; harm-coi runs on it;
the golden run of R finishes in 600 s.

**Stimulus:** one testbench per design (`eval/mutants/<design>/tb.sv`), constrained random with a seed, a reset, and
directed phases where random stimulus would not reach a state (a full FIFO, an arbiter with all requests). Trace
length fixed per design (default 5,000 cycles). The testbench drives only the design's ports; written for this
evaluation and recorded as such.

**Mutants** (`eval/mutants/mutate.py`, pyslang, source level, one change per mutant):
- **stuck-at-0 / stuck-at-1** of one bit of a signal at its driver (the right-hand side of the assignment, or the
  register's next value, forced to 0 or 1 on that bit); the classical fault model, as MCY/Yosys `mutate` (`const0`,
  `const1`) but on the SystemVerilog source, which Yosys cannot read for these designs;
- **inversion** of one bit at its driver (`inv`);
- **operator replacement** (`+`/`-`, `&`/`|`, `&&`/`||`, `==`/`!=`, `<`/`<=`) and **condition negation**
  (`if (c)` to `if (!c)`);
- **constant** off by one (`k` to `k±1`).
Up to 100 mutants per design, sampled with a fixed seed across operators in fixed proportions (stuck-at 50%,
inversion 10%, operator 25%, condition and constant 15%); every mutant must compile (else resampled); mutants
equivalent on the stimulus are just "not activated".

## Tests (written first, committed failing)
| # | Test |
|---|---|
| T1 | `mutate.py` on a fixture (`tests/input/h45/`: a counter and an FSM, a few lines each): every mutant differs from the original in exactly one place, compiles with Verilator, and has the operator and location it claims |
| T2 | stuck-at semantics: a stuck-at-1 of bit `i` of a register makes that bit 1 at every cycle after reset in simulation; stuck-at-0 likewise |
| T3 | sampling is deterministic: the same seed gives the same mutants; proportions as stated |
| T4 | activation: a mutant whose trace equals golden is "not activated"; one that differs only internally is "activated, internal" |
| T5 | scoring: on the fixture, a hand-checked set of assertions gives the expected killed / activated / false-positive counts |
| T6 | `run_eval.py` with a mutants manifest reproduces H44's numbers on one AssertLLM2 design (no regression of the driver) |
The tests live in `eval/mutants/tests/` (pytest), run by `ctest` like harm-coi's.

## Output
`eval/results/mutants-v4/results.md` and `.csv`: per design and configuration, assertions, time, activated, killed
(all / outputs only), score, false positives, per operator; and the corpus table (design, source, licence, lines,
signals, mutants generated / activated). A VALIDATION entry.
Nothing goes to trivergence beyond the design list check, and nothing goes to the paper without the user.

## Questions for the user
| # | Question | Options | Recommendation |
|---|---|---|---|
| Q1 | Where the corpus runs | (a) the Mac only (b) saturn for the mining runs | **(a)** first; (b) only if the full set exceeds an hour, with your go and trivergence told first |
| Q2 | Mutation tool | (a) our pyslang mutator (b) Yosys `mutate` on Verilog-only designs | **(a)**: SystemVerilog is the point of the paper; (b) would drop the SV designs |
| Q3 | Mutants per design | (a) 100 (b) 50 (c) all | **(a)**: steps of about 1 point after activation, runs stay short |
| Q4 (answered: b) | Also a v3-vs-v4 table on HARM's examples (`faultCov`, `sobel`, `paperRE`, `bl_master`, no RTL: assertions, time, fault coverage) | (a) yes, in this milestone (b) no | **(a)**: cheap (tag `v3` built once), and it is the "updated HARM" story |

## Cost
Testbenches and the mutator are most of the work: about 2-3 days. Runs: about 10 designs x 6 configurations x (1
golden + 100 mutants) trace checks; mining dominates, minutes per design on the Mac. 
