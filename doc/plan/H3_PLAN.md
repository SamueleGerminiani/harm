# H3 plan: semantic redundancy reduction with Spot

*Status: approved 2026-10-05 (D-004 safety only; D-008 keep stronger), in progress. Branch: `ms/H3-implies` (from `dev` @ H6). Effort: 3–4 d.*

## Goal
`--reduce implies` removes a mined assertion when a kept one implies it. `--dump-implications` writes the relation for other tools (trivergence stage 5). This builds on H2: propositions are first canonicalised with Z3, so that `cnt == 4'd9` and `4'd9 == cnt` are the same atom for Spot.

## Findings from the investigation (2026-10-05)
- **F1.** HARM links Spot 2.9.7, which has `spot::contains` and `spot::are_equivalent` (also on pre-translated automata), plus `formula::is_syntactic_safety()`.
- **F2. Atoms must keep their boolean structure.** HARM's decision trees produce leaves such as `a && b`. If a whole conjunction becomes one atom, Spot cannot see that `G({a} |-> c)` implies `G({a && b} |-> c)`, which is the most common redundancy in DT-mined sets. So abstraction stops at **maximal non-boolean subexpressions**: comparisons, logic-to-bool conversions, function calls. `&&`, `||`, `!` and `^` between them are kept and given to Spot.
- **F3. H2's canonical tokens (`@C3@`) are not valid Spot atoms.** H3 prints its own atom names (`p0`, `p1`, …) from the same equivalence classes.
- **F4. The number of pairs grows quickly.** A context can keep thousands of mined assertions. Every formula is translated to an automaton once, containment is checked on the automata, and only pairs that share at least one atom are compared (the USM-T heuristic). That is sound (it only misses implications, never invents one) but incomplete.

## Decisions to approve
### D-004: semantics of the implication check
- HARM evaluates assertions on finite traces; Spot reasons about infinite words. For **safety** formulas the two agree on what matters here: if A implies B over infinite words, every finite trace that violates B also violates A. So dropping B loses nothing for any trace or simulator on which A is checked.
- **Proposal:** reduce only pairs where **both formulas are syntactic safety** in Spot's sense. Others (with `F`, strong `U`) are always kept. Most HARM templates (`G`, `X`, `W`, `R`, `->`) are safety.

### D-008: which side to keep
- **Proposal: `--keep stronger` (default):** keep A, drop B when A ⇒ B and not B ⇒ A. The alternatives are `--keep weaker` (keep B), and `ranked`, which keeps whichever ranks higher among a group related by implication.
- **Equivalent assertions** (A ⇒ B and B ⇒ A): keep one, the smallest text, as in H2.
- **Order:** the reduction runs after the metric filters and before ranking, so the kept assertion is still ranked normally.

## Scope
1. **Abstraction:** H2's equivalence classes on the maximal non-boolean subexpressions (F2). The atom names are `p<k>`, valid for Spot.
2. **Reduction (`--reduce implies`):**
   - each formula is translated once;
   - pairs sharing an atom are checked with `contains`, both directions;
   - non-safety formulas are skipped (D-004);
   - the D-008 policy is applied.
3. **`--keep stronger|weaker|ranked`.**
4. **`--dump-implications <file.json>`:** for each dropped assertion, the kept assertion(s) that imply it, with the relation (`implies` or `equivalent`).
5. **Performance:** report the number of pairs checked, and the time. Acceptance on `bl_master` and `camellia` is the time with `--reduce implies` as a multiple of `--reduce syntactic`; the factor is reported, with a profile if above 2.

## Out of scope
- Implications between atoms (`x > 5 ⇒ x > 3`): H3b.
- Implication with respect to the design: trivergence's OpenFPV.
- Liveness pairs.

## Acceptance tests (written first)

| # | Test | Kind |
|---|---|---|
| A1 | **Hand-labelled pairs** (`tests/input/h3/pairs.txt`, about 50: `EQUIVALENT \| A_IMPLIES_B \| B_IMPLIES_A \| NONE \| SKIPPED`), in HARM's template shapes: `##n`, `X`, `\|=>`, DT conjunctions and sequences, `W`, `R`, invariants, a re-spelled proposition (via Z3), non-safety pairs that must be `SKIPPED`. Labels are reasoned and written before any implementation | gtest |
| A2 | **Bounded oracle in HARM's own semantics:** for every pair in A1, plus about 500 generated pairs over 3 boolean atoms (random template instances and mutations: added conjuncts, longer delays, `X` added or removed), evaluated with **HARM's evaluator** on every boolean trace of lengths 1..6 (2^(3L) traces each; up to 262,144 at L = 6). Wherever H3 claims A ⇒ B, no trace may make A hold while B fails. A claimed implication refuted by any trace is **unsound** and fails the test | gtest |
| A3 | `--reduce implies` on a regression case built for it (DT-mined `G({..&&..} \|-> X c)` with many conjunction variants) gives the hand-checked reduced output and the expected `--dump-implications` | regression |
| A4 | Determinism of A3 across thread counts and runs | determinism |
| A5 | Without `--reduce implies`, every existing baseline stays byte-identical | regression |

## Validation (independent)
- **A2** checks Spot's answers against HARM's own finite-trace evaluation, which is how mined assertions are judged. It is exhaustive up to length 6.
- **Cross-check with USM-T's `semantic_equivalence`:** pending, because USM-T builds only on Linux.

## Files
- **New:** `src/miner/utils/{include,src}/ImplicationReducer.*`; `tests/implicationTests.cc`; `tests/input/h3/*`; regression case `h3_reduce_implies`.
- **Modified:** `PropositionCanonicalizer.*` (maximal non-boolean atoms; Spot names), `Qualifier.cc`, `commandLineParser.cc`, `globals`, `main.cc`, `README.md`, `doc/plan/*`.

## Decisions needed before starting
1. **D-004:** only safety pairs are reduced.
2. **D-008:** keep the stronger assertion by default; `--keep weaker|ranked` available.
