# H24 plan: propositions for data, both polarities and the end of reset (harm-coi)

*Status: draft, for the user's approval. Asked by the user (2026-10-12) after the miner portfolio's D1 scorecard: HARM missed 23 of 37 diagnostic bugs; "investigate why the bugs were not covered by harm and how we can improve"; then "write the H24 plan". Branch `ms/H24-rtl-relations` from `dev` @ `80372ed`. Effort: about 3 d (HARM part 2 d, the portfolio's part and the measurement 1 d).*

## Why
The portfolio's D1 corpus (`~/miner-portfolio/corpus/d1`: 12 small designs, 49 bugs in six categories) scored HARM (with `--hints all`, H22) at 14 of 37 bugs; satminer 19, GoldMine 17. The misses were traced bug by bug (portfolio `doc/plan/VALIDATION.md`, D1). HARM's mining is not the cause; its alphabet is:

| Cause | Bugs missed | Fact |
|---|---|---|
| 1. A signal with no proposition | 8 | harm-coi takes propositions from RTL conditions, case labels, enum values and reset values (H10). A signal that is only ever assigned (a data output `p`, `out_data`, `dout`; a combinational flag `walk`, `zero`) has none, so no assertion can read it. |
| 2. No data relation | 5 | The bug breaks a relation such as `y == a - b` a cycle later, or "`data` keeps its value while `req` is high"; harm-coi offers only comparisons with constants (`op == 3'd1`, `y == 8'd0`). |
| 3. One polarity of a 1-bit flag | several (e.g. `updown`) | A flag's predicate comes from its reset value only (`!ovf`, `!unf`, `!carry`, `!sat`, `!req`); as a consequent it lets HARM say "the flag stays low", never when it rises. |
| 4. Reset behaviour | 7 | HARM mines reset assertions (`rst \|=> y == 8'b0`), but the portfolio gives every candidate trivergence's `disable iff (rst)`: an assertion triggered by `rst` high is then vacuous, and the portfolio's adapter drops it (correctly). Wrong reset values and registers left unreset are then out of reach. |
| 5. Not explained yet | 3 | the propositions exist; looked at again after 1–4 |

Checked by hand on the D1 traces (HARM `dev` @ `80372ed`, edited configurations):
- `updown` with `ovf` and `unf` added: HARM mines `!up && cnt == 4'b0 && down |=> unf` and `!down && cnt == 4'b1011 && up |=> ovf` (65 assertions instead of about 20).
- `alu` with `y == (($past(a, 1) - $past(b, 1)) & 8'hff)`, the same with `+`, and the carry: HARM mines `op == 3'b1 |=> y == ($past(a) - $past(b) & 8'b11111111)`, the sum and the carry relation (D1's `alu/B01`, `alu/B02`).
- `regbank` with `$fell(rst)` and a same-cycle template: HARM mines `$fell(rst) ##1 1'b1 |-> cfg1 == 8'b1010` and the other reset values (D1's `regbank/B01`, `B02`). In the first cycle after the reset `rst` is low, so `disable iff (rst)` does not switch the check off; `$fell` is in the portfolio's SVA subset and in HARM's grammar.

## What changes
1. **Data relations from assignments** (harm-coi). For a target `x` in the cones:
   - a non-blocking assignment `x <= e` in a clocked process (outside the reset branch): the proposition `x == ($past(e, 1) & M)`, `M` the mask of `x`'s width (so `e`'s wider result is compared as the RTL assigns it);
   - a continuous or combinational assignment `x = e`: `x == (e & M)`;
   - the condition under which the assignment happens is not part of it: finding it is the miner's job (`op == 3'd1 |=> y == …`).
   Every signal `e` reads must be visible (as for every harm-coi predicate); a relation whose `e` is a constant is the existing constant comparison; at most 8 relations per target (the first in source order) and an expression of at most 16 operators, the others counted as dropped.
   Placement (H22): a registered relation is a consequent of the next-cycle class (`|=>`), a combinational one of the same-cycle class (`|->`).
2. **Propositions for assigned-only signals:** a 1-bit target with no predicate gets `x` and `!x`; a wider one gets its relations (1) only.
3. **Both polarities of a 1-bit flag:** wherever harm-coi emits `!x` (or `x`) from a reset value, the other polarity too, with the same placement.
4. **The end of reset:** with `--reset R`, the proposition `$fell(R)` (`$rose(R)` for an active-low reset), an antecedent of the same-cycle class. The one-cycle offset seen above (`$fell(rst) ##1 1'b1 |->` where `$fell(rst) |->` was expected) is investigated first: either HARM samples `$fell` a cycle late (a HARM bug, fixed here with a test) or the reset values appear a cycle later in these traces (then documented).
5. **Opt-in:** all of 1–4 under one new harm-coi option, `--relations`, off by default (HARM v4's rule: new features are opt-in; the H0 baselines stay byte-identical).
6. **The portfolio's part** (`~/miner-portfolio`, its own commits): the HARM adapter passes `--relations`; its reset rule becomes "drop an assertion that reads the reset, except through `$fell`/`$rose` of it"; `disable iff` is unchanged. trivergence's contract is unchanged.

## Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Form of the relations | (a) `x == $past(e)` for registered, `x == e` for combinational, masked (b) also multi-cycle (`$past(e, k)`) | **(a)**: a pipeline is covered stage by stage (`m3 == $past(m2)`); (b) only if D1 shows a gap |
| Q2 | Which targets | (a) every assignment target in the cones, capped (8 relations, 16 operators) (b) outputs only | **(a)**: D1's misses are on internal stages too (`m2`, `m3`, `od`) |
| Q3 | Switch | (a) one option `--relations` for 1–4, off by default (b) part of `--hints-use all` | **(a)**: opt-in, measured on its own, H22's hints unchanged |
| Q4 | Reset | (a) `$fell(reset)` and the portfolio's narrowed reset rule (b) leave reset out | **(a)** |
| Q5 | Relations restate the RTL | (a) accept: they are mined from the golden RTL, as filter mode already assumes (HARM warns: "COI filter mode assumes the RTL is correct"); they catch a changed design (a mutant, a regression), not a bug the golden RTL already has (b) outputs only | **(a)**, documented in the README next to filter mode's warning |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| R1 | harm-coi on hand-written RTL snippets: `x <= e` in a clocked process gives `x == ($past(e, 1) & M)`; under an `if` the same relation; one per `case` arm; `assign x = e` gives `x == (e & M)`; the reset branch gives none; invisible signals drop the relation; the caps hold and the dropped ones are counted | hand-written expected propositions |
| R2 | 1-bit targets: an assigned-only one gets `x` and `!x`; a reset-value predicate gets its other polarity, same placement | hand-written |
| R3 | `--reset rst` gives `$fell(rst)`, `--reset !rst_n` gives `$rose(rst_n)`; no reset, none | hand-written |
| R4 | Every unconditional relation emitted for HARM's RTL fixtures and the new ones holds at every cycle of their golden traces after reset | an independent Python evaluator of the VCD (not HARM) |
| R5 | New fixtures `tests/input/h24/{alu,updown,regbank}` (copies of D1's designs and traces, recorded as such): HARM with `--relations` mines `op == 3'b1 \|=> y == …` (alu), `… cnt == 4'b0 && down \|=> unf` (updown) and `$fell(rst) … cfg1 == 8'b1010` (regbank) | hand-written expectations; ctest `h24_mine_*` |
| R6 | The `$fell` offset: HARM's value of `$fell(rst)` at each cycle of a hand-written trace equals the SystemVerilog definition | hand-written trace |
| R7 | Without `--relations`, harm-coi's output and the H0 baselines are byte-identical (`ctest -L "coi\|regression"`) | ctest |
| R8 | Portfolio (container): the adapter keeps `$fell(rst) … \|-> cfg1 == 8'h0a` and drops `rst \|=> …`; OpenFPV proves the kept one on `regbank` and finds a CEX on D1's `regbank/B01` variant | pytest |
| R9 | Portfolio, measured: the D1 scorecard with `--against` the baseline (HARM's row per category; no bug HARM caught before is lost), and the cost on P1's designs (sha3, ima_adpcm_encoder, uart; filter): HARM's mining time, candidates, proofs | VALIDATION |

## Documents
DECISIONS D-038; README (`--relations`, the filter-mode note, Q5); harm-coi README; VALIDATION H24; PLAN row; RELEASE_NOTES_v4; the report's reference section; DEVELOPER_GUIDE (the relation extraction); TRIVERGENCE_IMPACT (facts: new propositions with `$past`/`$fell`, all in the portfolio's subset).

## Not in scope
- Multi-cycle relations (`$past(e, k)`, Q1 b) and relations across modules beyond what the cones already flatten.
- Propositions from an LLM (H22's LLM hints).
- Any change to trivergence's contract (`disable iff`).
