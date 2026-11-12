# H1c plan: end-of-trace strength (D-015)

*Status: approved 2026-10-05 with D-016 (a), an option with the default unchanged; done, approved 2026-10-05. Branch: `ms/H1c-liveness` (from `dev` @ H3). Effort: 1–1.5 d.*

## Goal
When HARM prints an assertion in SVA, it should judge the end of the trace as a simulator judges what HARM prints: weak operators pending at the end hold, and strong ones fail.

## Findings from the investigation (2026-10-05)
- **F1. The planned oracle is not available.**
  - Verilator 5.034 rejects `s_eventually` ("Unsupported: s_eventually"), and also `##[1:$]` and `eventually [m:n]`.
  - Icarus has no concurrent assertions.
  - No free simulator on this machine can confirm what a simulator reports at the end of a simulation for a strong property.
- **F2. Trivergence is not affected today.**
  - Its HARM adapter (`triad_mining/harm.py`, `_UNSUPPORTED`) discards every mined line containing `eventually`, `s_eventually`, `until` or `nexttime`.
  - Its simulator is Verilator (F1), and its formal back ends (EBMC, OpenFPV) exclude liveness.
  - So mined liveness never reaches trivergence. The note added to TRIVERGENCE_IMPACT.md in H3 ("treat mined liveness as candidates to recheck") overstated the risk, and will be corrected.
- **F3. Strength is not only `F`.** It comes from the polarity of each operator after negations are pushed inward:
  - `F p` (printed `s_eventually`) is strong;
  - `!X p` (printed `not nexttime p`) is `s_nexttime !p`, which is strong: it fails on the last cycle;
  - `!(p W q)` (printed `not (p until q)`) is `!q s_until !p`, which is strong.

  Under the IEEE 1800 finite-trace semantics (Annex F), a strong property is not satisfied by a trace that ends before it completes. HARM treats all of these as weak. This also affects one H3 hand label: `G(a -> X !b)` and `G(a -> !X b)` are equivalent in HARM's current semantics, but not in SVA's.
- **F4. Other HARM users are affected.** The `process` example mines with `G(P0 |-> F(P1))`, `G(P0 |-> !X(P1))` and `G(P0 |-> !(true until P1))`, and 51 of its 143 baseline lines contain `F`. Changing the default changes their results.

- **F5 (during implementation): SVA printer precedence bug**, fixed; see VALIDATION H1c F-a.
- **F6 (during implementation):** Spot 2.9.7's `from_ltlf` reads `X` as weak; see VALIDATION H1c F-b.

## Decisions to approve
### D-016: how strong operators are judged at the end of the trace
- **(a) Option, default unchanged (recommended):** `--trace-end sva`. Under it, a pending instance at the end of the trace fails if, after pushing negations inward, the consequent's pending obligation is strong (`F`, `s_nexttime`, `s_until`). Without the option, HARM behaves exactly as today. Mined output stays reproducible for current users, and trivergence loses nothing (F2).
- **(b) New default:** the same rule, always on. It is what D-015 said, but it changes `process` and any user's liveness results.
- **(c) Drop H1c:** given F2, it is only for users who replay HARM's SVA in a commercial simulator. Correct the impact doc, and record the gap in README.

## Scope (if a or b)
1. **The evaluator:**
   - for each consequent, the automaton's pending states are classified as weak or strong;
   - a state is strong when its residual formula cannot be satisfied by stopping here, i.e. it is not accepting in the LTLf-with-weak-next sense;
   - this is computed once per template with Spot, so the cost is zero per evaluation;
   - at the end of the trace, a pending instance in a strong state counts as `F`.
2. **The H3 model** uses the same classification, so reduction stays exact for the chosen semantics. The H3 oracles run with the option on and off.
3. **`--dump-assertion-info`** reports the semantics used.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | Hand-derived end-of-trace verdicts on short traces for `F`, `!X`, `!(W)`, `X`, `W`, nested forms, with and without the option (about 30 cases) | gtest |
| A2 | **Independent oracle:** a small evaluator written from IEEE 1800 Annex F (finite-trace weak/strong semantics) in Python, for HARM's printed SVA subset. It agrees with HARM (option on) on every boolean trace up to length 5 for about 300 generated assertions | ctest |
| A3 | `process` with the option: the hand-checked set of assertions that are dropped, with the reason for each | regression |
| A4 | Without the option, all baselines byte-identical; H3 oracles still 0 unsound | regression |

## Validation (independent)
- A2 is the independent oracle. It is derived from the standard's semantics, not from HARM's code. A simulator is not available (F1).
- **Pending (Linux or lab machine):** a Questa/VCS replay of a few `s_eventually` / `not nexttime` cases, to confirm that tools report failures at the end of a simulation as the standard says. This is recorded as open, not claimed.

## Files
- **Modified:**
  - `AutomataBasedEvaluator.*` (strong pending states);
  - `TemplateImplication.cc` (end-of-trace verdict);
  - `ImplicationReducer.cc`;
  - globals, CLI, `main.cc`, README, `doc/plan/*`, including the TRIVERGENCE_IMPACT correction (F2).
- **New:**
  - `tests/endOfTraceTests.cc`;
  - `tests/oracle/sva_finite_semantics.py`;
  - the `process_trace_end_sva` regression case.
