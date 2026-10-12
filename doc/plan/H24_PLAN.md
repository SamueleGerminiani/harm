# H24 plan: propositions for data, both polarities and the end of reset (harm-coi)

*Status: approved by the user (2026-10-12: "yes H24, with your proposed changes": Q1–Q5 as recommended, Q3 as changed below, Q6 added, the filter-mode and signed-range fixes added). Asked by the user (2026-10-12) after the miner portfolio's D1 scorecard: HARM missed 23 of 37 diagnostic bugs; "investigate why the bugs were not covered by harm and how we can improve"; then "write the H24 plan". Branch `ms/H24-rtl-relations` from `dev` @ `80372ed`. Effort: about 3 d (HARM part 2 d, the portfolio's part and the measurement 1 d).*

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
4. **The end of reset:** with `--reset R` (`--reset !R` for an active-low reset), the reset-value predicates are also consequents of a fixed template `G({$fell(R)}|-> P0(3))` (`$rose(R)` for active-low). Checked on D1's `regbank` trace (2026-10-12): it mines `$fell(rst) |-> cfg1 == 8'b1010` and the other reset values, with no offset; the `##1` offset seen with `$fell(rst)` as an ordinary antecedent came from the decision tree, not from HARM's `$fell`.
5. **Fixed antecedents for unconditional relations:** a relation from an assignment under no condition (a clocked process's `x <= e` outside the reset branch, a continuous assignment) holds whenever the reset was inactive, so it goes to `G({!R}|=> P0(4))` (registered) or `G({!R}|-> P0(5))` (combinational) instead of the decision tree, which otherwise adds unrelated antecedents (`!rst |=>`, `op == 3'b1 ##2 1'b1 |=>`, seen on `alu`). Checked: `!rst |-> carry == $past(r) >> 8`. A conditional relation stays in its class's decision-tree template (the miner finds the condition). Without a reset, unconditional relations use the class templates.
6. **Numerics (Q6):** `<numeric>` for the delta of a register whose assignments read it (`x - $past(x)`: counters, accumulators) and for the values of a wide target with no predicate (`x`), placed in the target's class. Found (2026-10-12): a numeric must share its domain with a `<prop>` ("Placeholder domain is not defined" otherwise); `cnt - $past(cnt)` on `updown` gave no assertion with either template, while `m3 - $past(m2)` (constant 0) did. Investigated first (test R10); if HARM cannot mine varying numeric consequents, Q6 is reduced to the wide-signal values and recorded.
7. **HARM fix and corrections found while implementing (2026-10-12):**
   - (a) **fixed:** in COI `filter` mode, a proposition written in the template itself (`{!rst}`, `{$fell(rst)}`) was cone-filtered like a mined antecedent, so a data register without a reset lost every relation (`!rst |=> m3 == $past(m2)` on `pipemul`). Only what placeholders load is filtered now (`TLMiner.cc`, `permutationInCone`). The first diagnosis ("numerics reading several signals are dropped") was wrong: the numeric case showed the same filtering.
   - (b) **not a HARM bug:** a `<numeric>` in a consequent domain is clustered once over the whole trace into `==`/range propositions; with `K` clustering the deltas of `updown` gave none (so its domain was empty: "Placeholder domain is not defined"). With contiguous clustering (`C,10Max,==`) HARM mines `cnt == 4'b0 && up && !down |=> cnt - $past(cnt) == 4'b1` and the decrement and wrap values. harm-coi writes `C,10Max,==` (only `==`: no open ranges, which OpenFPV cannot build, portfolio F-P9).
   - (c) **to confirm (R11):** the "signed range printed unsigned" observation. HARM reads a trace's logic values unsigned and prints unsigned literals; SystemVerilog compares a signed variable with an unsigned literal unsigned, so the two may agree. Checked with OpenFPV on `satacc`; harm-coi no longer emits ranges either way.
8. **Opt-in, then the default (Q3 as changed):** 1–6 under one new harm-coi option, `--relations` (it needs `--hints`: the classes and the fixed templates are hints), off during H24 so that it is measured against today's output; at H24's sign-off, if D1 shows no loss and the cost is acceptable, it becomes harm-coi's default and `--no-relations` restores today's output (harm-coi's affected baselines updated once, recorded). The H0 baselines (HARM without harm-coi) are unaffected either way.
9. **The portfolio's part** (`~/miner-portfolio`, its own commits): the HARM adapter passes `--relations`; its reset rule becomes "drop an assertion that reads the reset, unless every reading is `$fell`/`$rose` of it or its inactive value (`!rst`, `rst_n`)", since only an antecedent that needs the reset active is vacuous under `disable iff`; `disable iff` is unchanged. trivergence's contract is unchanged.

## Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Form of the relations | (a) `x == $past(e)` for registered, `x == e` for combinational, masked (b) also multi-cycle (`$past(e, k)`) | **(a)**: a pipeline is covered stage by stage (`m3 == $past(m2)`); (b) only if D1 shows a gap |
| Q2 | Which targets | (a) every assignment target in the cones, capped (8 relations, 16 operators) (b) outputs only | **(a)**: D1's misses are on internal stages too (`m2`, `m3`, `od`) |
| Q3 | Switch | (a) one option `--relations`, off during H24, the default at sign-off with `--no-relations` (b) part of `--hints-use all` | **(a)** (the user, 2026-10-12) |
| Q4 | Reset | (a) `$fell(reset)` and the portfolio's narrowed reset rule (b) leave reset out | **(a)** |
| Q6 | Numerics | (a) `<numeric>` for register deltas and wide signals' values, with the two HARM fixes (b) none | **(a)** (the user, 2026-10-12) |
| Q5 | Relations restate the RTL | (a) accept: they are mined from the golden RTL, as filter mode already assumes (HARM warns: "COI filter mode assumes the RTL is correct"); they catch a changed design (a mutant, a regression), not a bug the golden RTL already has (b) outputs only | **(a)**, documented in the README next to filter mode's warning |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| R1 | harm-coi on hand-written RTL snippets: `x <= e` in a clocked process gives `x == ($past(e, 1) & M)`; under an `if` the same relation; one per `case` arm; `assign x = e` gives `x == (e & M)`; the reset branch gives none; invisible signals drop the relation; the caps hold and the dropped ones are counted | hand-written expected propositions |
| R2 | 1-bit targets: an assigned-only one gets `x` and `!x`; a reset-value predicate gets its other polarity, same placement | hand-written |
| R3 | `--reset rst` gives `$fell(rst)`, `--reset !rst_n` gives `$rose(rst_n)`; no reset, none | hand-written |
| R4 | Every unconditional relation emitted for HARM's RTL fixtures and the new ones holds at every cycle of their golden traces after reset | an independent Python evaluator of the VCD (not HARM) |
| R5 | New fixtures `tests/input/h24/{alu,updown,regbank}` (copies of D1's designs and traces, recorded as such): HARM with `--relations` mines `op == 3'b1 \|=> y == …` (alu), `… cnt == 4'b0 && down \|=> unf` (updown) and `$fell(rst) … cfg1 == 8'b1010` (regbank) | hand-written expectations; ctest `h24_mine_*` |
| R6 | The fixed templates: `G({$fell(rst)}\|-> P0)` on `regbank` gives exactly the reset values; `G({!rst}\|=> P0)` on `alu` gives `y == $past(r) & 8'hff` with no other antecedent; HARM's `$fell` at each cycle of a hand-written trace equals SystemVerilog's | hand-written |
| R10 | Numerics and the filter: `cnt == 4'b0 && up && !down \|=> cnt - $past(cnt) == 4'b1` on `updown`; in `filter` mode `!rst \|=> m3 == $past(m2)` and `!rst \|-> p == m3` on `pipemul` (fixed antecedents not filtered) | hand-written expectations; ctest `h24_numeric_delta`, `h24_fixed_filter` |
| R11 | A cluster of a signed variable prints signed (`acc inside {[-12'sd4:-12'sd1]}` or an equivalent SystemVerilog compares as signed), checked with OpenFPV's trace check on `satacc` | hand-written; container |
| R7 | Without `--relations`, harm-coi's output and the H0 baselines are byte-identical (`ctest -L "coi\|regression"`) | ctest |
| R8 | Portfolio (container): the adapter keeps `$fell(rst) \|-> cfg1 == …` and `!rst \|=> …`, drops `rst \|=> …` and `rst \|\| clr \|=> …`; OpenFPV proves the kept `$fell` one on `regbank` and finds a CEX on D1's `regbank/B01` variant | pytest |
| R9 | Portfolio, measured: the D1 scorecard and D1b's hunt scorecard with `--against` their baselines (HARM's rows per category; no bug HARM caught before is lost), and the cost on P1's designs (sha3, ima_adpcm_encoder, uart; filter): HARM's mining time, candidates, proofs | VALIDATION |

## Documents
DECISIONS D-038; README (`--relations`, the filter-mode note, Q5); harm-coi README; VALIDATION H24; PLAN row; RELEASE_NOTES_v4; the report's reference section; DEVELOPER_GUIDE (the relation extraction); TRIVERGENCE_IMPACT (facts: new propositions with `$past`/`$fell`, all in the portfolio's subset).

## Not in scope
- Multi-cycle relations (`$past(e, k)`, Q1 b) and relations across modules beyond what the cones already flatten.
- Propositions from an LLM (H22's LLM hints).
- Any change to trivergence's contract (`disable iff`).
