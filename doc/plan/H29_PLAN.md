# H29 plan: the pairs of `--reduce implies`

*Status: approved by the user 2026-10-15 ("ok, approved, go ahead", on the revised plan: measure first, a stricter pair filter, a cap with a recorded skip). Asked through the miner portfolio after trivergence's F7 tools tests. Branch `ms/H29-implies-pairs` from `dev` @ `bf490b0`. Effort: about half a day.*

## Why
trivergence's F7 tools tests run harm and harm-rel on AssertLLM2's `i2c_slave` (vcd depth 16, 3 traces of 2005 cycles) within 600 s. Both time out. On Linux, with no budget, HARM takes 642 s: mining takes 26 s, and `--reduce implies` takes 607 s. It checks 5,710,870 pairs among 6,481 assertions, one pair at a time, about 106 µs each, and drops 1,831.

`reduceByImplication` checks every pair of assertions that share an atom, or whose atoms are linked by a proved fact (H3b). Sharing an atom is a weak test: the reset, which most templates' antecedents read, links nearly everything. The loop is sequential. Each check builds Spot automata over a BDD dictionary (BuDDy) that is global and not thread-safe, so it cannot simply be spread over `--max-threads`.

## Measurement (before any change; scratch build, not committed)
An instrumented HARM counted both pair sets and could switch between them. It ran through the miner portfolio's adapter on its corpus (8 fixtures and 12 D1 designs, harm and harm-rel, 40 runs, Mac).
- **The stricter filter (a shared consequent atom) changes no output:** all 40 kept sets are identical. HARM's total time falls from 210 s to 76 s; on the largest case, traffic (harm-rel), pairs fall from 305,674 to 58,875 and time from 94 s to 26 s.
- **Checking HARM's finite model before Spot's automata** (the order the premise path already uses) gives identical output but is slower in total (365 s), so it is not part of H29.
- i2c_slave: see VALIDATION (measured on the Mac with trivergence's inputs).

## Change
1. **The pair filter.** A pair is checked when the two assertions share a consequent atom, or a proved fact links a consequent atom of one with a consequent atom of the other. Antecedent atoms no longer link pairs.
   - It is safe in the H3 sense: a pair left out is a possible implication not found, so an assertion is kept that could have been dropped. Nothing is dropped wrongly.
   - What it can miss: A ⇒ B where B's consequent shares no atom with A's, which holds only when B is vacuous under A (A makes B's antecedent impossible) or B's consequent follows from its antecedent alone. On the corpus it missed nothing.
2. **The cap `--implies-max-pairs N`** (default fixed from the measurements; `0`: no cap). When a context's pair count is above N, the implication step is skipped for that context. The equivalence step still runs (under `--reduce implies` it always does), so the kept assertions are those of `--reduce equiv`. HARM says so: "Implication: skipped, P pairs > N".
   - The default sits at least 2× above the corpus maximum under the new filter and well below what i2c_slave needs at the old filter. If both cannot hold, the user decides before the default is set.
3. **The record.** `--dump-assertion-info` gains `"implication": {context: {"pairs": P, "maxPairs": N, "skipped": bool, "dropped": D, "seconds": S}}` for every context reduced by `--reduce implies`.
4. **Docs.** Release notes and the report sections (H14's coverage test); the user guide's `--reduce` section.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/input/h29/`: assertions linked only through a reset in their antecedents. `--reduce implies` checks only the pairs sharing a consequent atom; the record gives that count | counted by hand |
| T2 | The H3 and H3b inputs keep the same assertions as before | the existing expected sets |
| T3 | `--implies-max-pairs 1` on T1's input: skipped, the record says so, and the kept set equals `--reduce equiv`'s | the equivalence step |
| T4 | `--implies-max-pairs 0` and a cap above the count: the same as without a cap | no change |
| T5 | `--implies-max-pairs` without `--reduce implies` exits with a message, as `--atom-premises` does | the existing rule |
| T6 | HARM's whole `ctest` on macOS and Linux | no other change |
| T7 | The miner portfolio's corpus (40 runs): the same kept sets as `bf490b0` | the measurement above |
