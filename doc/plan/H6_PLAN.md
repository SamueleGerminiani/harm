# H6 plan: COI rank mode

*Status: proposed 2026-10-05, awaiting approval. Branch: `ms/H6-coi-rank` (from `dev` @ H4). Effort: 2–3 d.*

## Goal
HARM reads a `coi.json` (H4 contract) for a context and exposes **metric variables** that score each mined assertion by how plausible it is structurally. Nothing is pruned: `<sort>` and `<filter>` decide what to do with the scores. This is the mode trivergence will use, where COI hints sit next to LLM hints (PLAN §1 goal 2).

## Definitions (decision D-014, needs approval)
These apply to a mined assertion `G(antecedent -> consequent)`:
- **Leaves** are its atomic propositions (boolean-layer instances). A leaf's **variables** are the trace signals it reads. Leaves without variables (e.g. the `true` in `a ##1 true`) are ignored.
- **Offset of a leaf:** the clock cycle at which it is evaluated, relative to the start of the antecedent.
  - Boolean layer: the current cycle.
  - `##n` and `;`: +n and +1.
  - `:` (fusion): +0.
  - `X^n` / `nexttime[n]`: +n.
  - `|->` / `->`: the consequent starts at the end of the antecedent; `|=>` / `=>`: one cycle later.
  - Under `until`, `eventually`, `release`, repetitions and ranges, the offset is **unknown**.
- **Cone of the consequent** = the union of the cones (from `coi.json`) of the consequent's variables.
- **`coiFrac`** = fraction of antecedent leaves whose variables are **all** in the cone of the consequent. An assertion with no antecedent leaves (e.g. an invariant) scores 1.
- **`coiDepthFit`** = fraction of antecedent leaves for which every variable `v` has some consequent leaf `q` and variable `c` in `q`, such that `offset(q) − offset(leaf)` is one of the depths of `v` in the cone of `c`, or is deeper than `max_depth` when `v` is saturated.
  - If either offset is unknown, membership in the cone is enough.
  - Also 1 without antecedent leaves.
- **`coiUnknown`** = number of antecedent leaves with a variable that `coi.json` does not know: listed in `unknown`, or not a target at all. Such leaves count as in the cone and depth-fitting; they are **never treated as out of the cone** (H4 contract). HARM warns once per unknown variable.
- **No `<coi>` in the context:** a metric that uses these variables is a configuration error.

## Scope
1. **XML:** `<coi file="path" mode="rank"/>` inside `<context>`. The path is relative to the configuration file.
   - `mode="filter"` is rejected with "not supported before H7".
   - The JSON is parsed with Boost.PropertyTree (header-only, already available) and checked against the v1 rules that HARM depends on: version, the names, sorted depths.
2. **Consistency with the trace:** each `coi.json` target and source must be a trace variable. When HARM reads a VCD, it compares `meta.vcd_scope`/`vcd_recursion` with `--vcd-ss`/`--vcd-r`. A mismatch gives a warning; names missing from the trace give an error, listing them.
3. **Offsets:** a function `leafOffsets(formula)` → `{leaf → optional offset, in antecedent?}` in `src/miner/utils`.
4. **Metrics:** `coiFrac`, `coiDepthFit` and `coiUnknown`, computed per assertion in the qualifier before filtering and ranking, and added to `Metric::availableFeatures`.
5. **Provenance:** an optional `origin="…"` on `<prop>`/`<numeric>` (free text, e.g. `spec`, `rtl`, `llm`), stored with the proposition.
6. **`--dump-assertion-info <file.json>`:** a JSON sidecar with one record per kept assertion and context. A record has:
   - the text;
   - every metric variable's value (CT counts, `complexity`, the coi metrics when available);
   - the leaves, each with its text, offset, variables and `origin`.

   This is how trivergence gets scores and provenance without parsing the text output. `--dump-to` output is unchanged.

## Out of scope
- Pruning (H7, H8).
- The out-of-cone report (H9).
- Computing cones (H5).

## Acceptance tests (written first)

| # | Test | Kind |
|---|---|---|
| A1 | **Offsets:** about 15 hand-written formulas, each with the expected offset per leaf: boolean, `##n`, `;`, `:`, `X X`, `\|=>`, sequences in the antecedent with a delay in the consequent, `until` (unknown), DT-mined shapes | gtest |
| A2 | **Metrics by hand:** about 20 assertions over the `multipath` fixture's signals with its `expected_coi.json`, each with hand-computed `coiFrac`/`coiDepthFit`/`coiUnknown`. Cases: in and out of the cone, right and wrong depth (`a` is at depths 0 and 2 for `y`, not 1), sequences, `X`, `\|=>`, unknown signals, an invariant, a constant leaf | gtest |
| A3 | **Configuration errors:** a metric using `coiFrac` without `<coi>`; `mode="filter"`; a missing file; a version ≠ 1; a name not in the trace. Each gives the expected message | regression (`PASS_REGULAR_EXPRESSION`) |
| A4 | **End to end:** `multipath` with `<coi mode="rank">` and `<sort exp="coiDepthFit"/>`. The ordered output and the `--dump-assertion-info` values match a hand-checked expectation | regression |
| A5 | **No change without `<coi>`:** every H0–H4 regression and determinism test stays byte-identical | regression |

## Validation
- Rank mode decides no verdicts, so hand computation (A1, A2, A4) is the validation, as the PLAN states.
- The metric definitions are fixed in D-014 *before* the tests are written.
- A4 runs on a fixture whose cones were validated by simulation in H4.

## Files
- **New:** `src/miner/utils/{include,src}/CoiInfo.*` (JSON loading and checks, cone queries); `src/miner/utils/{include,src}/LeafOffsets.*`; tests `tests/coiMetricsTests.cc`, `tests/input/h6/*`.
- **Modified:** `Context.hh` (coi), `ManualDefinition.cc` (`<coi>`, `origin`), `Assertion.hh` (coi features), `Metric.cc`, `Qualifier.cc` (compute before metrics; sidecar dump), `commandLineParser.cc`, `globals`, `main.cc`, `README.md`, `doc/plan/*`.

## Decision needed before starting
**D-014:** the metric definitions above. In particular:
- `coiFrac` requires *all* of a leaf's variables to be in the cone;
- unknown variables count as in the cone and fitting, and are counted separately;
- offsets under unbounded operators are unknown and then only cone membership counts.
