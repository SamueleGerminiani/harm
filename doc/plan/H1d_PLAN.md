# H1d plan: printing fixes F7 and F8 (found in H8)

*Status: requested by the user on 2026-10-06 ("fix F7 and F8 now"). Branch: `ms/H1d-printing` (from `dev` @ H5; independent of H8). Effort: 0.5 d.*

## The bugs (H8 VALIDATION, checked with Spot's `ltlfilt`)
- **F7 (SVA):** HARM's `->` starts the consequent with the antecedent; SVA's `|->`/`|=>` start it at the antecedent's end. HARM prints every `->` as `|->`/`|=>`, which is wrong when the antecedent lasts more than one cycle.
  - **Example:** `G({a ##1 b} -> X c)`, with `c` one cycle after `a`, is printed `a ##1 b |=> c`, which puts `c` one cycle after `b`.
  - With a property antecedent (`G(a && X b -> X c)`) the output is not even valid SVA: `a and nexttime b |=> c`.
- **F8 (Spot LTL):** HARM's Spot printer drops parentheses that Spot's precedence needs. `X(en && wrap)` is printed `Xen && wrap`, which Spot reads as `(X en) && wrap`.
  - The same happens under `F`, `G`, `!`, `U`/`W`, `R`, and for `||` under a property `&&`.
  - SVA and PSL are not affected: there, Boolean operators bind tighter than property operators.

## The fix (D-021)
- **F7:** for `->` (and `=>`) whose antecedent is a sequence of fixed length `n > 1` cycles, and whose consequent is Boolean after `k` cycles of `X`, re-anchor at the antecedent's end, `j = k − (n − 1)`:
  - `j = 0`: `s |-> c`;
  - `j = 1`: `s |=> c`;
  - `j > 1`: `s |-> ##j c`;
  - `j < 0`: `s |-> $past(c, −j)`.

  These are forms that Verilator and EBMC accept. Otherwise (not a fixed-length sequence, or a non-Boolean consequent) print `(s) implies <consequent>`: IEEE 1800 `implies` starts both sides at the same cycle. A single-cycle antecedent is printed as before. `--legacy-sva` keeps the old printing.
- **F8:** in Spot LTL, a proposition whose top operator is a Boolean connective (`&&` with more than one item, `||`, `^`, `==`/`!=` between propositions) is parenthesized directly under `X`, `F`, `G`, `!`, `U`/`W`, `R`, and an `||`/`^` one under a property `&&`.

## Tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | `PrintingTest`: 8 F7 cases and 3 F8 cases, plus 9 unchanged ones (single-cycle `->`, `\|->`, `\|=>`, SVA of Boolean consequents), expected texts by hand | gtest |
| A2 | `h1d_spot_equivalence`: Spot checks that each new text means HARM's formula, and that each old text does not (control) | regression (python + ltlfilt) |
| A3 | Baselines: any change is listed, and its cause checked to be only F7 or F8 | regression |

## Validation
A2 is independent of HARM's printer: the meanings are written by hand and decided by Spot.
