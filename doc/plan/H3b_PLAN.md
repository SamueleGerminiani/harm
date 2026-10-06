# H3b plan: atom-implication premises for `--reduce implies`

*Status: plan, awaiting approval. Branch: `ms/H3b-atom-premises` (from `dev` @ H1b). Effort: 2 d.*

## Goal
H3 compares assertions with their propositions abstracted to independent atoms, so it misses relations that hold only because of what the propositions mean.

**Example:** `G(cnt > 4'd8 -> b)` implies `G(cnt > 4'd9 -> b)`, because `cnt > 9` implies `cnt > 8`. H3 labels the pair `NONE`; it is the only such pair in H3's fixture (`tests/input/h3/pairs.txt:46`).

H3b proves facts between atoms with Z3 (H2), under HARM's semantics including x/z (D-011). It then gives them to both of H3's checks as premises:
- **`p ⇒ q`**, e.g. `cnt > 9 ⇒ cnt > 8`;
- **`p ⇒ ¬q`** (exclusion), e.g. `state == 2'd1 ⇒ ¬(state == 2'd2)`, which matters for FSM states.

## Measurement (2026-10-06, asked for by the user before deciding)
- **How:** how many assertions that survive `--reduce implies` would atom facts remove? Code in `doc/plan/h3b_measure/` (a spike, not a test).
  - **The rule:** two survivors of the same shape (the text with each proposition blanked) where, position by position, each antecedent proposition of B implies A's and each consequent proposition of A implies B's.
  - **Implications between propositions** are decided exactly for one-variable ranges and (in)equalities with `&&`/`||`/`!`, the forms numeric clustering and H10 produce, under HARM's x/z rule (D-011).
  - This is a sufficient condition, so the counts are **lower bounds** for H3b: Spot can also relate assertions of different shapes.
- **Results:** every regression example (as in `cases.cmake`), plus H10's `--emit-config` on the fixtures:

  | Case | `syntactic` | `implies` | + atom facts (lower bound) |
  |---|---|---|---|
  | `sub_platform1k` (numerics) | 91 | 89 | **−20 (22%)** |
  | H10 `fsm` (FSM states) | 46 | 38 | **−6 (16%)** |
  | `sobel` (numerics) | 30 | 17 | −1 |
  | H10 `constructs` | 101 | 99 | −3 (3%) |
  | H10 `counter`, `arbiter` | 9, 36 | 8, 31 | 0 |
  | `bl_master1k`/`10k`, `svaFunctions`, `fsm`, `vendingMachine`, `ex3`, … | 1–112 | same | 0 |

- **Examples, checked by hand:**
  - `G({!(state ∈ [5,12])} \|-> X …)` implies `G({state ∈ [0,4]} \|-> X …)` (`sub_platform1k`);
  - `G({!(state == 1) ##1 …} \|-> …)` implies `G({state == 0 ##1 …} \|-> …)` (FSM exclusion);
  - `G({!(p5 >= 136) ##1 …} \|-> …)` implies `G({p5 <= 135 ##1 …} \|-> …)` but not the converse, because `!(p5 >= 136)` is also true on x cycles.
- **Reading:**
  - the gain is real where propositions come from numeric clustering or FSM states: 16–22% of the survivors;
  - it is close to zero on Boolean-only configurations, like trivergence's LLM hints so far;
  - most regression examples produce few assertions (`--min-frank`, `--max-ass`), so they say little.

## How
1. **Facts:** for each pair of canonical atoms (H2 tokens) of the assertions being reduced that share a variable, ask Z3 whether `p → q` and `p → ¬q` are valid.
   - A new `smt::checkImplication`, beside `checkEquivalence`, with the same encoding: 4-valued variables with x/z, so a fact holds on every trace HARM can read.
   - A timeout or `Unknown` gives no fact.
   - The number of queries is capped. Beyond the cap, the remaining pairs are skipped and HARM prints a message, so the result is still sound, only weaker.
2. **Spot (infinite words):** A ⇒ B is checked as `(P ∧ A) ⊆ B`, where `P = G(⋀ facts)` over the atoms of A and B. Equivalence is checked under `P` as well.
3. **HARM's finite-trace model (D-004 amendment):** the breadth-first search over traces only uses letters (atom valuations) that satisfy the facts, because no real trace can violate them.
4. **`--dump-implications`:** a claim that needed facts lists them (`"premises": ["cnt > 4'd9 -> cnt > 4'd8"]`). The field is optional, so existing readers are unaffected (contract note in DECISIONS).

## Decisions to approve
### D-025: enabling
- **Proposed: opt-in, `--atom-premises`,** valid only with `--reduce implies` (an error otherwise). `--reduce implies` alone stays exactly H3, so its results and trivergence's pinned behaviour do not change.
- **Alternative:** on by default under `--reduce implies`. That gives more reduction for everyone using `implies`, but changes their output.
- **The cap:** 2,000 Z3 queries per reduction run by default, with `--atom-premises-max <n>`. Only atom pairs that share a variable are queried.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | **H3's fixture** (`pairs.txt`, 49 pairs): with `--atom-premises`, the `cnt > 9` / `cnt > 8` pair becomes `B_IMPLIES_A`, and no other label changes; without the option, all labels as in H3 | gtest |
| A2 | **New hand-labelled pairs** (`tests/input/h3b/pairs.txt`, about 20), labelled from the semantics before any implementation. They cover: <br>• ranges and equalities (`cnt == 9 ⇒ cnt > 8`) <br>• exclusion between FSM states <br>• stronger and weaker consequents (`G(a -> cnt == 9)` ⇒ `G(a -> cnt > 8)`) <br>• the shapes `X`, `\|=>`, `##n` and decision-tree conjunctions <br>• **x/z-sensitive pairs:** `G(a -> cnt != 4'd1)` ⇒ `G(a -> !(cnt == 4'd1))` but not the converse, since `!(cnt == 1)` holds on x cycles where `cnt != 1` does not (D-011) <br>• pairs that facts do not help (different delays, unrelated variables) | gtest |
| A3 | **Atom facts, unit tests** (hand-labelled atom pairs: implies / excludes / neither): unsigned and signed comparisons, widths, `==` vs ranges, `!=` vs `!(==)` under x/z, `===`; a forced timeout gives "neither" | gtest |
| A4 | **Unchanged without the option:** H3's tests, `--dump-implications` output and every baseline identical | regression |
| A5 | **The cap:** with `--atom-premises-max 1`, the reduction still runs, prints the message, and claims a subset of the uncapped claims | regression |

## Validation (independent)
- **Soundness on traces, with HARM's own evaluator** (H3's approach, extended to values). For every claim A ⇒ B made with premises, on A1/A2 and on generated pairs over `a`, `b`, `cnt`, check that wherever B fails A also fails.
  - The check uses random CSV traces in which `cnt` takes all 16 values plus x/z bits; about 2,000 traces of length 1–6 per pair.
  - The reduction code is not involved.
- **Atom facts, by enumeration:** every Z3 fact over a 4-bit variable is re-checked by evaluating both propositions with HARM's evaluator on all 4⁴ = 256 four-valued values.
- **Mutation test of A1–A3:**
  - facts used without the x/z encoding (2-valued);
  - premises given to Spot but not to the finite-trace model;
  - `p ⇒ q` added as `q ⇒ p`;
  - the cap ignored.
- **Performance:** `--reduce implies` with and without `--atom-premises` on `bl_master` and `camellia`, as in H3, with Z3 query counts and times.

## Out of scope
- Facts between more than two atoms (e.g. `a ∧ b ⇒ c`).
- Temporal facts, i.e. implication modulo the design (trivergence's OpenFPV, T8a).
- Facts in `--reduce equiv`: equivalence of whole propositions is already H2's.

## Files
- **Modified:** `smtEquivalence.*` (`checkImplication`), `ImplicationReducer.cc` (facts, premises in Spot and in the finite model, dump field), `commandLineParser.cc`, `main.cc`, `globals.*`, README, `doc/plan/*`.
- **New:** `tests/input/h3b/pairs.txt`, `tests/atomPremiseTests.cc` (A1–A3), `tests/oracle/h3b_soundness.py` or a gtest (the trace oracle).
