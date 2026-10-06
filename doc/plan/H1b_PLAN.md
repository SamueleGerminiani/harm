# H1b plan: SystemVerilog x/z semantics as an option (D-011 option b)

*Status: plan, awaiting approval. Branch: `ms/H1b-x-semantics` (from `dev` @ H10). Effort: 2–3 d.*

## Goal
An option under which HARM's propositions are evaluated as SystemVerilog evaluates them on 4-valued (x/z) values, so that a mined assertion holds in HARM exactly where it holds in a simulator. The default stays HARM's current semantics.

**The gap (D-011), on a trace where `a` has x bits:**

| Proposition | HARM today | SystemVerilog |
|---|---|---|
| `a == b` | false (a comparison with x/z is false) | x, i.e. does not hold |
| `!(a == b)` | **true** | x, does not hold |
| `4'bx10x != q4`, with a known bit different | false | **1**, holds |
| `p \|\| !p`, with `p` = x | **true** | x, does not hold |

So, today, `G(!(a == b) -> c)` can be mined from a trace where a simulator would never see the antecedent hold. That is the likely cause of trivergence's M0 #33 disagreements.

## Findings from the investigation (2026-10-06)
- **F1. Only the step from values to truth differs.** HARM's `Logic` values already compute x/z like SystemVerilog for arithmetic, bitwise operators, concatenation and literals (the oracle's "model" column differs from SV only at comparisons, and HARM matches the model everywhere). The difference is where a comparison becomes Boolean:
  - **HARM:** x becomes false at each comparison, and `!`, `&&`, `||` work on true/false;
  - **SV:** the comparison gives 0, 1 or x; `!`, `&&`, `||` propagate x (Kleene logic); only a final 1 holds.
- **F2. The independent oracle exists.** H1's iverilog fixture (`tests/oracle/fixture/cases.txt`: 1,000 expressions × 32 random 4-valued rows) has an **SV column**, computed by iverilog 12.0. Today SV and HARM differ on 337/700 new-syntax and 255/300 old-syntax expressions (at least one row each).
  - The fixture has no `$` functions and no `inside`, so the oracle cannot check them.
- **F3. `--reduce equiv`/`implies` (H2, H3) reason with two-valued atoms, which SV semantics breaks:**
  - Z3 merges `p || !p` with `true`, but under SV it is x when `p` is x;
  - Spot treats `p` and `!p` as complements, but under SV both can fail on the same cycle.

  So a reduction proven under HARM's semantics is not sound under SV's when 4-valued signals are involved.

## Decisions to approve
### D-024: the option and its scope
- **`--x-semantics harm|sv`** (default `harm`, unchanged), named like `--trace-end harm|sva` (D-016).
- **Under `sv`,** every proposition is evaluated three-valued, and **holds only where its value is 1**:
  - `==`, `!=`, `<`, `<=`, `>`, `>=` on 4-valued operands: 0 or 1 when the known bits decide it, else x. `==`/`!=` are decided by a known differing bit; relational operators are x if any operand bit is x/z;
  - `===`, `!==` are unchanged (never x);
  - a 4-valued value used as a Boolean (`q4`, `v[3]`): 1 if a known bit is 1, 0 if all bits are known 0, else x;
  - `!`, `&&`, `||` are Kleene logic; `^` and `==`/`!=` between Booleans give x if an operand is x;
  - `c ? p : q` with `c` = x gives `p` if `p` and `q` are equal and known, else x.
  - Variables declared 2-valued (`bool`, `int`, …) never have x, so nothing changes for them.
- **Not changed under `sv`** (no oracle covers them, F2), listed in the README:
  - `$` functions (`$onehot`, `$countones`, …) and `inside` keep HARM's semantics.
- **Reduction under `sv` (F3), conservative:**
  - `--reduce equiv` and `implies` do not merge or drop an assertion that has a proposition with a 4-valued variable;
  - those assertions are compared syntactically, and HARM warns once.
  - A Kleene-aware reduction (two Z3/Spot atoms per proposition, "is 1" and "is 0") is possible future work.
- **Everything else is orthogonal:** templates, temporal evaluation, `--trace-end`, COI.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | **iverilog oracle, SV column:** with `--x-semantics sv`, every one of the 1,000 fixture expressions holds exactly on the rows where SV is `1` (32,000 checks) | gtest (`PropositionOracleTest`) |
| A2 | **Unchanged default:** the same oracle with the option off still matches the model column; all baselines byte-identical; determinism | gtest, regression |
| A3 | **Hand cases** (gtest, expected values by hand): the four table rows above, plus: `q4` = `4'b00x0` (does not hold) vs `4'b01x0` (holds); a bit select on an x bit; `?:` with an x condition and equal or different arms; `===` unchanged; `$onehot` and `inside` unchanged (current values) | gtest |
| A4 | **Mining end to end:** a small CSV trace with x values. Hand-derived: with `harm`, `G(!(a == 4'd1) -> c)` is mined; with `sv` it is not (its antecedent never holds where `a` is x), and `G(a != 4'd1 -> c)` is. Contingency counts as hand-counted | regression |
| A5 | **Reduction fallback:** under `sv` with `--reduce equiv`/`implies`, two assertions that are equivalent only under HARM's semantics (`p \|\| !p` vs `true`, over a 4-valued `p`) are both kept, and the warning is printed once; with `harm`, behaviour as before | regression |

## Validation (independent)
- **The iverilog fixture** (A1) is the independent oracle: SV's own value per row. It is the 4-state check by simulation that the PLAN asks for; Verilator is 2-valued and cannot do it.
- **Mutation test of A1/A3/A5:**
  - Kleene `!` replaced by classical `!`;
  - `!=` with a known differing bit giving x;
  - a Boolean use of an x vector giving 1;
  - the reduction fallback removed.

## Out of scope
- Kleene-aware `--reduce` (F3).
- `$` functions and `inside` under SV (F2). They would need new oracle categories (the fixture is golden: regenerating it needs approval).
- Making `sv` the default (D-011 option c).

## Files
- **Modified:**
  - `src/exp/…`: a three-valued evaluation alongside the Boolean one, for the comparison, connective, cast, bit-select and ternary nodes; the Boolean `evaluate` uses it when the option is on;
  - `commandLineParser.cc`, `main.cc`, `globals.*`;
  - `ImplicationReducer.cc` and the H2 equivalence path (fallback);
  - README, `doc/plan/*`.
- **New:** `tests/xSemanticsTests.cc` (A3), `tests/input/h1b/*` (A4, A5).
