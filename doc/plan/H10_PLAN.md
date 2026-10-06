# H10 plan: RTL predicate harvesting

*Status: approved 2026-10-06 (D-023); in progress. Branch: `ms/H10-predicates` (from `dev` @ H9). Effort: 3–4 d.*

## Goal
`harm-coi` (H5) also reads, from the same pyslang AST, the predicates the designer wrote, and offers them to HARM as propositions with `origin="rtl"`:
- **`--predicates`** fills `coi.json → predicates`. The field is already in the coi.v1 schema (`expr`, `origin: "rtl"`, `src`, `targets`), so there is no contract change.
- **`--emit-config <file.xml>`** writes a starter HARM configuration from them. It is the RTL-aware counterpart of HARM's `--generate-config`, and the "no LLM" arm of trivergence's B3 ablation.

**Example** (`fsm` fixture):
```systemverilog
typedef enum logic [1:0] {IDLE = 2'd0, RUN = 2'd1, DONE = 2'd2} state_t;
always_ff @(posedge clk)
  if (rst) state <= IDLE;
  else case (state) IDLE: if (go) state <= RUN; ...
assign busy = (state == RUN);
```
gives, in HARM's syntax and names: `rst`, `go`, `stop`, `state == 2'd0`, `state == 2'd1`, `state == 2'd2`. Each has `targets` (the signals it controls or describes) and `src` (`fsm.sv:15`).

## What is harvested (D-023, to approve)
| Kind | From | Predicate | `targets` |
|---|---|---|---|
| Condition | `if (c)`, `c ? x : y`, in processes and continuous assignments | `c`; and if `c` is compound (`&&`, `\|\|`, `!`), also each atom of it | the signals assigned under it |
| Case label | `case (s) L: …` | `s == L`, one per label; `default` gives nothing | the signals assigned in the item |
| FSM state | a variable of an enum type | `v == C` for every enum constant `C`, even if never compared | `v` |
| Comparison | any `==`, `!=`, `<`, `<=`, `>`, `>=` with a constant side, anywhere in the RTL | the comparison | the signal it is assigned to, if any |
| Reset value | a constant assigned to a register under an asynchronous control of its process, or under the first `if` of an `always_ff` whose branch assigns only constants (`if (rst) cnt <= 0`) | `cnt == 4'd0` | the register |

**Translation into HARM's proposition language (H1):**
- **Names:** visible names as H5 computes them (`::`, struct fields, `--vcd`). A predicate on any signal that is not visible is **dropped** and counted (`-v` lists why).
- **Constants:** enum constants and parameters are replaced by their values, as sized literals with the width of the signal they are compared with (`state == 2'd1`, `cnt == 4'd9`). A 1-bit comparison is written as the signal or its negation (`prio == 1'b0` → `!prio`).
- **Not harvested:** elaboration-time conditions (`if (i == 0)` in a `generate`), which are constant in the trace.
- **Deduplication** is syntactic, after normalising (signal on the left, the same literal form). A predicate harvested twice keeps every `src` and the union of its `targets`. Z3 duplicates that survive are measured (validation).

### `--emit-config` (D-023)
- **One context, not one per target** (PLAN §H10 said "one context per target"):
  - every predicate with `loc="a, c, dt"` and `origin="rtl"`;
  - `<coi file="…" mode="rank"/>`;
  - `--generate-config`'s templates and sorts.

  One context per target would duplicate filter mode (H7/H8): the same restriction is `mode="filter"` on one context, a one-word change. And it would multiply the number of contexts by the number of signals.
- **The written `coi.json` keeps the predicates,** so the configuration and the cone file stay together.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | **Hand-labelled predicate lists** (`expr`, `targets`) on the 6 H4 fixtures and H5's `constructs`, written from the RTL. Includes the empty cases: `multipath` has no condition, and `hier`'s `if (i == 0)` is elaboration-time | ctest (python) |
| A2 | **Every predicate parses and evaluates in HARM:** the emitted configuration of each fixture is loaded by HARM on the fixture's trace, without `--skip-invalid-props`, and mining runs to the end | ctest |
| A3 | **Unit tests for the translation**, with hand-written expected text: enum constant, parameter, unsized literal (`'0`), invisible signal dropped, struct field and interface names, bit select (`gnt[0]`), `!=`/`<`, a 1-bit comparison, an async reset value, a compound condition and its atoms, an elaboration-time `if` not harvested | pytest |
| A4 | **`coi.json` with predicates** validates (`check_coi.py`, schema) | ctest |
| A5 | Runs on Linux (pending, as for H5) | — |

## Validation (independent)
- **The hand labels** (A1).
- **Z3 duplicates:** a gtest runs HARM's Z3 canonicaliser (H2) on each fixture's predicates and reports how many are equivalent to another one. harm-coi's normalisation should leave none; any found is reported and analysed, not silently accepted.
- **Trace sanity, reported:** on each fixture trace, every harvested condition is both true and false at least once. A predicate that never changes points at a harvesting bug or a constant condition.
- **Mutation test of A1–A3:**
  - enum value off by one;
  - an invisible signal not dropped;
  - literal width wrong;
  - reset-value rule missing.

## Out of scope
- Mining with the predicates beyond A2's smoke run. The B3 comparison is trivergence's (TRIVERGENCE_IMPACT).
- Origins for numerics expanded into propositions (the H9 note).
- Predicates on invisible signals rewritten through their cone.

## Files
- **Modified:**
  - `tools/harm-coi/src/harm_coi/` (`frontend.py` collects conditions, `cli.py` gains the options);
  - a new `predicates.py` (translation);
  - `tools/harm-coi/README.md`, README (`--generate-config` section), `doc/plan/*`.
- **New:** `tools/harm-coi/tests/test_predicates.py` (A3), `tests/coi/check_predicates.py` (A1, A2), `tests/input/h10/*_predicates.json` (hand labels), `tests/coiPredicateTests.cc` (the Z3 count).
