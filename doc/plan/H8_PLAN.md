# H8 plan: depth-aware COI filter

*Status: approved 2026-10-06 (D-007 after the hand check, D-020); done, awaiting review. Branch: `ms/H8-depth-filter` (from `dev` @ H5). Effort: 3–4 d.*

## Goal
H7's filter mode keeps an antecedent proposition if its signals are in the consequent's cone, at any depth. H8 also uses the **depths** in `coi.json`: a proposition is kept only where its cycle offset from the consequent is one at which its signals can influence the consequent.

**Example** (`multipath`: `y` gets `a` at depths 0 and 2, never 1):

| Assertion | Offset of `a` before `y` | `depth="any"` (H7) | `depth="bounded"` | `depth="exact"` |
|---|---|---|---|---|
| `G(a -> y)` | 0 | kept | kept | kept |
| `G(a -> X y)` | 1 | kept | kept (1 ≤ 2) | **pruned** (1 is not a depth) |
| `G(a -> X X y)` | 2 | kept | kept | kept |
| `G(a -> X X X y)` | 3 | kept | **pruned** (3 > 2, not saturated) | **pruned** |

**What changes:**
- **Opt-in only:** a new attribute, `<coi … mode="filter" depth="any|bounded|exact"/>`.
- **The default `any` is H7 exactly.** Rank mode, filter mode without `depth`, and every baseline are unchanged.
- Like H7, this assumes the RTL is correct, so it is for the GoldMine-style baseline, not for trivergence's triage.

## Findings from the investigation (2026-10-06)
- **F1. The `depth` attribute does not exist yet.**
  - PLAN §H6 sketched `depth="any|bounded|exact"`, but H6 and H7 shipped only `mode`.
  - H8 adds it, for `mode="filter"` only. In rank mode, `coiDepthFit` already ranks by depth, so `depth` with `mode="rank"` is an error.
- **F2. D-007 from the code: in every operator, a decision-tree index has a fixed cycle offset from the consequent.** It does not depend on how many items the tree adds later.
  - **`|->` and `|=>`** (`DTNext::generateFormulas`, "dynamic shift"): the antecedent is built as `dM ##N … ##N d1 ##N d0`, so index 0 is always the last element.
    - Index `i` is `i·N` cycles before the end of the antecedent.
    - Its offset from a consequent leaf `q` is `i·N + off(q)`, where `off(q)` is `q`'s offset from the end of the antecedent: +1 for `|=>`, plus any `X`/`##k` in the consequent.
    - **Checked on real output:** in `counter`, `rst ##1 1'b1 |-> cnt == 4'b0` has `rst` at index 1, one cycle before `cnt`.
  - **`->`** (no shift): the antecedent is `d0 ##N d1 … ##N dM` from a fixed start, so the offset is `off(q) − i·N`. It can be negative (the item comes after the consequent), and then it never fits.
  - **`..&&..`:** a single index, so every candidate has the same offset. **`..#N&..`:** like `##N`, with several propositions per index.
  - **The `-1` index of the ordered operators** becomes `currDepth + 1` when the item is inserted, so the index is known when a candidate is evaluated. Unordered operators try every index.
  - **To characterise in H8:**
    - templates with other events in parallel with the operator (`_parallelDepth`);
    - templates where offsets are not fixed (`DTNCReps`, or `until`/`F` in the consequent). These fall back to cone membership, as D-014 already does for unknown offsets.
- **F3. The offsets are computed, not hard-coded per operator.** For each template and index `i`, a marker proposition is placed at `i`, and the instantiated formula goes through `leafOffsets`, the function behind `coiDepthFit` (D-014).
  - So the filter and the rank metric cannot disagree about offsets.
  - The hand-written D-007 table is the test of this computation (A1).
- **F4. Oracles.**
  - **Plain templates:** the PLAN's oracle holds exactly: filter output = rank output post-filtered with `coiFrac == 1 && coiDepthFit == 1`. A permutation is kept or pruned by a property of the assertion itself.
  - **Decision trees:** that equality fails, as in H7 (F2): the tree is greedy, so pruning changes what it explores.
  - **H7's per-consequent oracle still works when the operator has a single index:** `..&&..`, or `..#1&..`/`..##1..` limited to one index (`1D`).
    - With one index there is one offset, so exact depth filtering is the same as restricting the tree's domain to the propositions that fit it.
    - That restriction can be written in a configuration, since DT operators take domain restrictions (`..&&..(id)`).
  - **Several indices:** there is no equality oracle, because a configuration cannot restrict a domain per index. They are covered by:
    - soundness: every output assertion fits, checked with offsets computed independently in Python from the assertion text;
    - the D-007 table;
    - mutation tests.
- **F5. No RTL for `bl_master`** (H7 F4) or the other examples, so the PLAN's "report on `bl_master`" cannot be done. The report covers the 5 fixtures HARM can load and H5's `constructs` design.

- **F6 (found while writing A1): `leafOffsets` put the consequent of `->` at the end of a multi-cycle antecedent.** HARM evaluates it from the start of the antecedent; checked by mining:
  - `G({a ##1 b} -> X c)` holds with `c` one cycle after `a`, but `leafOffsets` said 2;
  - for `G(a && X b -> X c)` it said "unknown".

  `coiDepthFit` (H6) was therefore wrong for those templates; plain `G(a -> X b)` was not affected. **Fixed in H8,** since the filter needs it. Rank mode's metric changes only for `->` templates with multi-cycle antecedents, and H3's depth cutoff uses the same offsets.
- **F7 (found by A4): `--sva` prints `G({s} -> X c)` as `s |=> c`.**
  - In SVA that anchors `c` at the end of `s`, while HARM mined it anchored at the start, so the printed SVA does not say what HARM checked. A correct translation is `(s) implies nexttime c`.
  - **Not fixed in H8:** it changes printed output, and needs its own decision. Only `->` templates with a multi-cycle antecedent are affected. No example and no trivergence template uses them; only H8's test configurations do.
  - A4 reads the Spot-LTL text instead, which keeps the distinction.
- **F8 (found by A4):** the Spot-LTL text prints `X(p)` without parentheses (`Xen && wrap` for `X(en && wrap)`), which Spot itself would read as `(X en) && wrap`. A printing ambiguity, not fixed. A4's parser follows HARM's convention.

## Decisions to approve
### D-007: decision-tree index → cycle offset
- **The table above (F2),** for `|->`, `|=>`, `->`, step `N`, and consequents with `X^k`/`##k`.
- **Recorded in DECISIONS once it has been checked by hand** on mined fixture assertions, as the PLAN asks.

### D-020: depth modes of the filter
For an antecedent proposition at offset `d` before a consequent leaf (same leaf rule as `coiDepthFit`, D-014), with `v` a variable of the proposition and `c` a variable of the consequent leaf:
- **`exact`:** every `v` has some `c` with `d` among the depths of `v` in `cone(c)`, or `d > max_depth` and `v` saturated.
  - So **filter output has `coiDepthFit = 1`** (a check, A4).
- **`bounded`:** every `v` has some `c` with `0 ≤ d ≤` the largest depth of `v` in `cone(c)`, or `d ≥ 0` and `v` saturated.
  - This is "never deeper than the structure allows". It tolerates imprecise depths below the maximum.
- **`any`** (the default): H7, signal level.
- **Unchanged from D-017:**
  - unknown signals and unknown consequents keep everything;
  - a proposition without variables is kept;
  - an unknown offset (`until`, `F`, repetitions) falls back to cone membership.

## Scope
1. **`ManualDefinition`:** parse `depth`. Unknown values are an error; so is `depth` with `mode="rank"`.
2. **`CoiInfo`:** one rule, `fits(propVars, d, consequentVars, Depth)`, used both by the filter and by `computeCoiMetrics`'s `depthFit`, so that `exact` and `coiDepthFit` cannot drift apart.
3. **Plain templates:** H7's `permutationInCone` also checks offsets, using `leafOffsets` on the loaded formula.
4. **Decision trees:**
   - per template, the offset of every index (F3), computed once;
   - in `AntecedentGenerator::findCandidates`/`findCandidatesNumeric`, a (candidate, index) pair that does not fit is skipped. The test comes from `TLMiner` as a predicate, so `AntecedentGenerator` stays COI-agnostic.
5. **Statistics:** the (candidate, index) pairs before and after, next to H7's counts, in the info messages and in `coiFilter` in `--dump-assertion-info`, which also records `depth`.
6. **Docs:** README, DECISIONS, VALIDATION, TRIVERGENCE_IMPACT.

## As built (2026-10-06): differences from the plan above
- **`leafOffsets`** also reads template formulas: through a placeholder, the proposition currently loaded. Plain-template pruning uses this, and keeps H7's rule that placeholders shared by antecedent and consequent are not filtered. Assertion formulas have no placeholders, so the other callers are unchanged.
- **The D-007 table is computed with a marker variable** (`$harm_dt_index_marker`, not a valid signal name), not by pointer: `copy()` copies propositions.
- **`DTOperator`** gained `insertionIndex(depth)` and `getNumIndices()`. `DTAnd` has one index.
- **A2:** the post-filter applies the Python D-020 rule to offsets parsed from the text, for both modes. For `exact`, HARM's `coiDepthFit == 1` must also select the same set. The plan said "the dump's offsets" for `bounded` only; this is more independent.
- **A4 parses the Spot-LTL text, not the SVA** (F7).
- **After the mutation test,** two plain templates were added to every configuration: `G({P0 ##1 P1} |=> P2)` and `G(P0 -> X X X X P1)`. The reason is in VALIDATION.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | **D-007 table:** the computed offset of each index equals the hand-written table. Templates: `{..##1..}\|-> P0`, `\|=> P0`, `\|-> X P0`, `\|-> ##2 P0`, `-> X P0` (including a negative offset), `..##2..` (step 2), `..#1&..`, `..&&..\|-> X P0`, one with a parallel event, and one with an unknown offset | gtest |
| A2 | **Plain templates,** 5 fixtures + `constructs`: filter `exact` = rank post-filtered with `coiFrac == 1 && coiDepthFit == 1`; filter `bounded` = rank post-filtered with the `bounded` rule computed in Python from `coi.json` and the dump's offsets | regression (python) |
| A3 | **Single-index decision trees** (`..&&..`, and `..#1&..` with `1D`): H7's per-consequent oracle, with the tree's domain also restricted to the propositions that fit the offset. `restrict_config.py` gains `--depth exact\|bounded`, and computes the offset itself from the template. The union of rank runs = filter output | regression (python) |
| A4 | **Soundness, every template (multi-index trees included):** every output assertion fits under the selected mode, with offsets computed by a small Python parser of the printed SVA (`##k`, `&&`, `\|->`, `\|=>`, `nexttime`/`X`), independently of HARM's `leafOffsets`. Also `coiDepthFit == 1` in the dump for `exact` | regression (python) |
| A5 | **Unchanged default:** H7's tests and every baseline byte-identical; determinism across thread counts with `depth="exact"`; errors for an unknown `depth` value and for `depth` with `mode="rank"` | regression |
| A6 | **Report:** permutations, (candidate, index) pairs, assertions and time, for `any`/`bounded`/`exact`, on the 5 fixtures and `constructs` | report |

## Validation (independent)
- **A3:** the restricted configurations come from a separate script that reads `coi.json` and computes offsets itself. HARM runs them in rank mode, with no filter code.
- **A4:** offsets parsed from the output text, not from HARM.
- **D-007, checked by hand:** for each operator, a few mined fixture assertions are read and their offsets counted by hand. The checks go in VALIDATION.
- **Mutation tests of A1–A4** (not in the PLAN, as in H7). Planted bugs:
  - offset off by one;
  - `|=>` treated as `|->`;
  - the sign of `->` reversed;
  - `bounded` and `exact` swapped;
  - the saturation rule dropped.
- **The cones themselves** were validated by simulation in H4 and H5.

## Out of scope
- Depth-aware ranking: it already exists as `coiDepthFit` (H6).
- The out-of-cone report (H9).
- An equality oracle for multi-index trees, which does not exist (F4).

## Files
- **Modified:** `ManualDefinition.cc`, `Context.hh`, `CoiInfo.*`, `TLMiner.cc`, `AntecedentGenerator.*`, `Qualifier.cc` (dump), `tests/coi/restrict_config.py`, `tests/coi/check_filter.py`, `tests/regression/CMakeLists.txt`, README, `doc/plan/*`.
- **New:** `tests/coiDepthTests.cc` (A1), `tests/coi/sva_offsets.py` (A4), `tests/input/h8/*.xml`, and `tests/input/h8/constructs_coi.json`: harm-coi's output for `constructs`, committed so that the tests do not need pyslang.
