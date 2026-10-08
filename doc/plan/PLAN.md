# HARM extension plan: semantic reduction and RTL-derived (COI) hints

*Drafted 2026-10-05. Approved 2026-10-05.*

## 0. Goals and ground rules

### 0.1 Goals
1. **Semantic redundancy reduction.** Remove assertions that are equivalent to, or implied by, other mined assertions. The logic is ported from USM-T (Z3 proposition canonicalisation, Spot language containment).
2. **RTL-derived hints.** HARM optionally reads a cone-of-influence (COI) description computed from the RTL and uses it in one of two ways:
   - **rank mode:** COI metrics that only re-order or score assertions. This is for trivergence, where COI hints are combined with the LLM's spec-derived hints;
   - **filter mode:** prune the search space before mining. This is traditional, GoldMine-style mining, and it assumes the RTL is correct (golden RTL).
3. **Proposition-language fixes** that trivergence currently works around in its adapter (M0_REPORT #7–#10, #29, #31).

HARM itself stays **source-agnostic**: the RTL is parsed by a separate generator (`harm-coi`), which communicates with HARM only through a versioned JSON file.

### 0.2 Rules (same as trivergence)
1. Work on **one milestone at a time**. A milestone starts only when its dependencies are `done` and it has been approved.
2. **Plan first:** for each milestone, propose the files, interfaces and **acceptance tests**, and wait for approval.
3. **Tests before implementation.** Never weaken, skip or delete a test to make it pass.
4. **Independent validation** for every semantic component (equivalence, implication, COI): brute-force enumeration, another tool, simulation, or hand-checked fixtures. Tests written alongside the code are not enough on their own.
5. **Default behaviour is unchanged.** Every new feature is opt-in. The H0 regression baseline must stay byte-identical unless a milestone explicitly changes it, and the change is recorded in `doc/plan/DECISIONS.md`.
6. **Done** means:
   - acceptance tests are green;
   - `ctest` is green on Linux and macOS (arm64);
   - the regression baseline is green, or its change is documented;
   - a `doc/plan/VALIDATION.md` entry exists;
   - `doc/plan/TRIVERGENCE_IMPACT.md` is updated if the milestone changes anything trivergence uses or could use;
   - the work is committed on `ms/<ID>-<slug>`.

   Then stop for review.
7. **Versioned contracts:** the `coi.json` schema (H4), the new XML elements and attributes, the new CLI options and the implication dump format. Any change needs a DECISIONS entry.
8. Trivergence is **not modified from this machine**. The changes it needs (code and plan) are kept up to date in `doc/plan/TRIVERGENCE_IMPACT.md`, the hand-off for the Linux machine. §4 below is the original summary.

### 0.3 Branches
- **`main`** is the stable HARM used by other people. Nothing from this plan reaches it until the whole plan is done (after H11). Then `dev` is merged into `main` in one reviewed step, with a release tag.
- **`dev`** is the integration branch. Each milestone branch `ms/<ID>-<slug>` starts from `dev` and is merged back into `dev` (no fast-forward) after its review is approved.
- Branches are pushed to `origin`. Fixes needed on `main` meanwhile (bugs reported by users) go to `main` and are then merged into `dev`, never the other way.

### 0.4 Status values
`todo` → `planned` → `in-progress` → `awaiting-review` → `done` (merged into `dev`); also `blocked(<reason>)` and `deferred`.

---

## 1. Milestones

Each milestone lists: **Depends on · Effort (working days with Claude Code) · Scope · Out of scope · Deliverables · Acceptance · Validation.**

### H0: Baseline and safety net
- **Depends on:** none · **Effort:** 1–1.5 d
- **Scope:**
  - A regression harness: run every `examples/*` configuration with `--max-threads 1`, store the normalised outputs under `tests/regression/baseline/`, and add a ctest that compares against them.
  - **Deterministic ranking:** a stable tie-break (score, then canonical string) so that the `--max-ass` cut and the multi-threaded runs give identical output (M0 #31).
  - Branch, `doc/plan/` skeleton (`PLAN.md`, `DECISIONS.md`, `VALIDATION.md`).
- **Out of scope:** any behavioural change other than tie-breaking.
- **Acceptance:**
  1. The regression test passes on Linux and macOS.
  2. Three runs with `--max-threads 1` and three runs with `--max-threads 8` produce identical output on every example, including with `--max-ass 10`.
- **Validation:** the baseline is reviewed by hand on 3 examples before it is frozen. The tie-break changes the baseline once; that change is recorded as D-001.

### H1: Proposition and SVA language fixes
- **Depends on:** H0 · **Effort:** 2–3 d
- **Scope** (each item has a test):
  - **Constants:** sized decimal and hex (`8'd9`, `4'hA`, `'h1F`) and unsized fill literals (`'0`, `'1`, `'x`, `'z`) (M0 #7, #29).
  - **Operators:** concatenation `{a, b}` and replication `{4{a}}`; ternary `?:`; case equality `===` / `!==` with 4-valued semantics (M0 #29).
  - **Hierarchy separator:** `.` accepted as an alias of `::` (in propositions only).
  - **Invariant templates:** `G(P0)` without an implication (M0 #8).
  - **SVA output:** `true`/`false` printed as `1'b1`/`1'b0`; `|-> nexttime` printed as `|=>` (M0 #9).
  - **Robustness:** `--skip-invalid-props` drops (with a warning) a proposition that fails to parse, instead of aborting the whole run (M0 #29).
- **Out of scope:** new temporal operators.
- **Acceptance:**
  - parser and printer unit tests for every item;
  - the M0 normalisation cases (copied into `tests/input/` as a hand-written fixture) parse and print as expected;
  - every SVA output line from the regression examples is accepted by Verilator `--assert` (Verilator lint only).
- **Validation:**
  - evaluation of the new operators is checked against Verilator simulation on a small fuzzed set (random expressions × random 4-valued vectors);
  - the SVA printing change updates the baseline (D-002).

### H1c: end-of-trace strength for liveness operators (D-015)
- **Depends on:** H1, H3 · **Effort:** 1 d
- **Scope:**
  - A pending `F` (printed `s_eventually`) at the end of the trace counts as failed, as in an SVA simulator. Weak operators are unchanged.
  - The H3 finite-trace model follows the same rule.
- **Acceptance:** a Verilator replay of mined liveness assertions agrees with HARM's verdicts at the end of the trace. Existing safety baselines are unchanged.
- **First step:** confirm the mismatch with a Verilator test before changing anything.

### H1b: SystemVerilog x/z semantics as an option (D-011)
- **Depends on:** H1 · **Effort:** 2–3 d
- **Scope:**
  - An option (e.g. `--sv-xsemantics`) under which propositions follow SystemVerilog: comparisons give 0/1/x, and `!`, `&&`, `||` use Kleene logic.
  - A proposition holds only where its value is 1.
  - The default stays HARM's current semantics.
- **Acceptance:** the H1 iverilog oracle's **SV column** matches on all 1,000 expressions with the option on. The model column still matches with it off.
- **Validation:** the existing iverilog fixture is the independent oracle. A Verilator replay on a trace with x values is not possible, because Verilator is 2-state; so a 4-state check by iverilog simulation of the proposition layer is used instead.

### H2: Z3 back end and proposition canonicalisation
- **Depends on:** H0 (H1 recommended first, so that the new operators are covered) · **Effort:** 3–4 d
- **Scope:**
  - **Z3 dependency:** add `install_z3.sh` to `third_party/` behind a CMake option `HARM_WITH_Z3` (default ON). Without Z3, HARM falls back to syntactic behaviour with a warning.
  - **Port `ExpToZ3Visitor`** from USM-T to HARM's current `exp`, including `Logic` (≤ 511 bits) mapped to Z3 bit-vectors, signedness, and floats (or `UNSUPPORTED`).
  - **X/Z semantics (decision D-003):** propositions that contain `x`/`z` constants or `===` are **never merged** (they are marked unsupported for canonicalisation). The rest use 2-valued semantics.
  - **Canonicalisation:** propositions proven equivalent (Z3 query with a timeout; a timeout means "not equivalent") are mapped to one representative.
  - Integrate canonicalisation into `extractUniqueAssertionsFast`, so that the existing fast filter merges equivalent propositions. It is enabled by `--reduce equiv` or a higher level (H3); the default stays syntactic.
- **Out of scope:** temporal reasoning.
- **Acceptance:**
  - a hand-labelled fixture of about 60 proposition pairs (equivalent / not, mixed widths, signed, `$past`, `inside`) is classified correctly;
  - when the solver times out, the pair is reported "not equivalent" and nothing is merged.
- **Validation:** **brute-force enumeration** as an independent oracle: for every pair with total input width ≤ 16 bits, all assignments are enumerated with HARM's own evaluator and the result is compared with Z3. Pairs above that width rely on the hand labels.

### H3: Semantic redundancy reduction (Spot)
- **Depends on:** H2 · **Effort:** 3–4 d
- **Scope:**
  - **CLI option `--reduce none|syntactic|equiv|implies`** (default `syntactic` = current behaviour).
  - **Abstraction:** each assertion becomes a Spot formula over the canonical tokens from H2; parsed formulas and pair results are cached (as in USM-T).
  - **Pair checks:** `equiv` uses `spot::are_equivalent`; `implies` uses `spot::contains`. Candidates are bucketed by shared variables (USM-T's `getNumberOfCommonVariables`) and by consequent signature, to avoid an n² comparison.
  - **Policy option `--keep stronger|weaker|ranked`** (default `stronger`), and a deterministic tie-break between equivalent assertions (shortest, then the H0 order).
  - **Implication dump `--dump-implications <file.json>`:** `{kept, dropped, relation}`. Consumers: trivergence stage 5, and debugging.
  - **Semantics note (D-004):** HARM evaluates finite traces, while Spot reasons over infinite words. Decide whether the LTLf translation (`spot/tl/ltlf.hh`, already used in USM-T) is needed for templates with `F`/`U`, or whether such assertions are excluded from implication reduction.
- **Out of scope:**
  - implications between atoms (`x>5 ⇒ x>3`), which is H3b;
  - implication modulo the design, which belongs to trivergence's OpenFPV T8a.
- **Acceptance:**
  - a hand-labelled fixture of about 50 assertion pairs (`EQUIVALENT | A_IMPLIES_B | B_IMPLIES_A | NONE`, including HARM template shapes with `##n`, `X`, DT conjunctions and sequences) is classified correctly;
  - on `bl_master` and `camellia`, `--reduce implies` finishes within 2× the time of `--reduce syntactic` (or the measured factor is reported, with a profile).
- **Validation:**
  - **soundness:** for every dropped assertion, the assertion that implies it must hold on every trace position where the dropped one is evaluated. This is checked on the input traces and on random traces with HARM's evaluator, and gives a necessary condition for soundness;
  - **cross-check:** the same pairs go through USM-T's `semantic_equivalence` evaluator, and the two must agree.

### H3b (optional): Atom-implication premises
- **Depends on:** H3 · **Effort:** 1–2 d
- **Scope:** Z3-proven implications between canonical atoms are added to Spot's checks as `G(p → q)` premises. This finishes USM-T's commented-out `check_implies`. The number of atom pairs is capped.
- **Acceptance:** the fixture pairs that need atom implication move from `NONE` to the right label, and no other label changes.

### H4: COI contract and RTL fixture corpus
- **Depends on:** H0 · **Can run in parallel with:** H1–H3 · **Effort:** 2 d
- **Scope:**
  - **`coi.json` schema v1** (`doc/schemas/coi.v1.json`):
    - meta: design, top, clock, generator, version;
    - per target signal (VCD-resolved full names): a list of `{sig, depths: [int], bits?: [..]}`;
    - optional `predicates: [{expr, origin: "rtl", src: "file:line"}]` for H10;
    - an `unknown` list for signals the generator could not resolve.
  - **Depth convention (D-005):** depth = the number of register crossings between the source and the target; depth 0 = combinational.
  - **RTL fixture corpus** `tests/input/rtl/`, about 6 small designs:
    - counter;
    - round-robin arbiter;
    - FSM with an enum;
    - a hierarchical design with parameters and a `generate` loop;
    - an SV interface or struct;
    - a design with a combinational feedback-free multi-path (several depths for one signal).
  - For each design: a testbench, a simulated VCD (Icarus or Verilator; the script is committed, the VCD too if small), and a **hand-written expected `coi.json`**.
- **Acceptance:** each hand-written `coi.json` validates against the schema, and every signal name appears in its VCD.
- **Validation:** each expected COI is reviewed by hand. An empirical non-influence check by simulation: toggling a signal claimed *outside* a target's cone, with the stimulus otherwise fixed, never changes that target.

### H5: `harm-coi` generator
- **Depends on:** H4 · **Effort:** 0.5 d spike + 3–4 d
- **Scope:**
  - **H5a, spike and decision (D-006):** yosys + yosys-slang JSON netlist vs. the pyslang elaborated AST, judged on the H4 corpus for:
    - name mapping back to VCD scopes;
    - parameters, generate blocks and interfaces;
    - bit-level precision;
    - ease of computing depth;
    - ease of later predicate harvesting (H10).
  - **Tool:** `tools/harm-coi/` (Python, own `pyproject.toml`), a CLI `harm-coi --top T --files … [--targets …] [--max-depth k] -o coi.json`. It must run on Linux and macOS.
  - **Per-target cone:** fan-in with a depth set, bounded by `--max-depth`. Saturation is reported, not hidden.
- **Out of scope:** predicate harvesting (H10); embedding the generator in HARM's C++ build.
- **Acceptance:** on all H4 fixtures the output equals the hand-written `coi.json` (exact match, order-insensitive).
- **Validation:**
  - the hand fixtures;
  - a cross-check of signal-level cones against `yosys select %ci*` (if pyslang is chosen) or against pyslang (if yosys is chosen);
  - the H4 simulation non-influence check, re-run on the generator's output.

### H6: COI rank mode in HARM
- **Depends on:** H4 (uses the hand-written `coi.json`, **not** H5) · **Effort:** 2–3 d
- **Scope:**
  - **XML:** `<coi file="…" mode="rank" depth="any|bounded|exact"/>` per context, parsed in `ManualDefinition.cc` and stored in `Context`.
  - **Signal extraction:** the variables referenced by each proposition or numeric; the targets are the consequent's variables.
  - **Metric variables** in `Metric.cc`:
    - `coiFrac`: the fraction of antecedent propositions whose signals are all in the union of the consequent signals' cones;
    - `coiDepthFit`: the fraction placed at a delay contained in the depth set.
  - **Unknown signals** (absent from the JSON) are counted separately (`coiUnknown`). They are never treated as out-of-cone, and a warning is printed.
  - **Provenance:** an optional `origin="spec|rtl|auto|…"` attribute on `<prop>`/`<numeric>`, carried to the output (`--dump-to` and the debug data).
- **Out of scope:** any pruning.
- **Acceptance:**
  - metric values equal hand-computed values on about 20 fixture assertions;
  - without `<coi>`, the output is byte-identical to the baseline;
  - `<sort exp="coiFrac"/>` re-orders as expected on one fixture.
- **Validation:** hand computation (rank mode does not decide verdicts).

### H7: COI filter mode, signal level
- **Depends on:** H6 · **Effort:** 2–3 d
- **Scope:**
  - `mode="filter"`: per consequent, automatic local domains restrict antecedent placeholders and DT operators to in-cone propositions. This works for both plain placeholders and DT operators.
  - A one-time warning: "filter mode assumes the RTL is correct; behaviour removed or added by an RTL bug cannot be mined".
  - Statistics: the size of the search space before and after, and the run time.
- **Acceptance:**
  1. **Equivalence oracle:** on every fixture, the output of `mode="filter"` equals the output of `mode="rank"` post-filtered with `coiFrac == 1` (same traces and configuration, `--max-threads 1`, no `--max-ass` cut).
  2. No output assertion has an out-of-cone antecedent proposition.
- **Validation:** acceptance 1 is the independent check, because it compares pruning before mining with filtering after mining.

### H8: Depth-aware COI filter in the decision tree
- **Depends on:** H7 · **Effort:** 3–4 d
- **Scope:**
  - First, **characterise** how the DT `depth` index in `AntecedentGenerator::findCandidates` maps to the cycle offset from the consequent, for every template shape (consequent with `X^n`, `##n`, `|=>`). The result is a hand-checked table in DECISIONS (D-007).
  - Then skip candidates whose signals' depth sets do not contain the offset (`depth="exact"`), or that are above the maximum depth (`depth="bounded"`).
- **Acceptance:**
  1. **Equivalence oracle:** filter output with `depth=exact` equals rank output post-filtered with `coiFrac == 1 && coiDepthFit == 1`.
  2. The search-space reduction is reported for every fixture and for `bl_master`.
- **Validation:** as for H7, plus the D-007 table checked by hand on the fixtures.

### H9: Out-of-cone report
- **Depends on:** H6 · **Effort:** 1 d
- **Scope:** `--dump-coi-report <file.json>`, which lists, for each target, the propositions (with `origin`) whose signals are outside the target's cone. A spec-origin proposition that falls outside the cone is a candidate for a "spec says A influences B, RTL says it cannot" disagreement, which is trivergence's input.
- **Acceptance:** the report equals the hand-computed lists on the fixtures.

### H10: RTL predicate harvesting
- **Depends on:** H1, H5 · **Effort:** 3–4 d
- **Scope:**
  - `harm-coi --predicates` collects the following into `coi.json → predicates`:
    - `if` and `case` conditions;
    - case labels and FSM state constants;
    - comparison constants;
    - reset values.
  - `harm-coi --emit-config` writes a starter HARM XML (one context per target, propositions with `origin="rtl"`, `<coi>` element, default templates). It is the RTL-aware counterpart of `--generate-config`.
- **Acceptance:**
  - harvested predicates equal hand-labelled lists on the H4 fixtures;
  - every harvested predicate parses in HARM (H1).
- **Validation:** hand labels; Z3 canonicalisation (H2) removes duplicates, and the count is reported.

### H11: Evaluation, documentation and release
- **Depends on:** H3, H8, H9, H10 · **Effort:** 3–5 d (compute mostly on the Linux machine)
- **Scope:**
  - **Configurations compared:** vanilla HARM; `--reduce implies`; COI rank; COI filter (signal level and depth level); harvested predicates. All run on the H4 fixtures, `examples/`, and about 10 AssertLLM2 designs (on the Linux machine).
  - **Measures:**
    - number of assertions;
    - run time;
    - redundancy removed;
    - fault coverage with `--fd` where faulty traces exist.
  - **Paper A preview:** a comparison with GoldMine on the designs it supports.
  - README sections (`<coi>`, `--reduce`, `harm-coi`), Dockerfile (Z3 and the generator's dependencies), and a release tag.
- **Acceptance:** a results table reproducible from one script; the Docker image builds; the README examples run.

---

## 2. Dependencies and order

```
H0 ─┬─ H1 ─┬─ H2 ── H3 ── (H3b)
    │      └──────────────────────────┐
    └─ H4 ─┬─ H5 ──────────────────── H10 ─┐
           └─ H6 ─┬─ H7 ── H8              ├─ H11
                  └─ H9 ───────────────────┘
```

- **Track R (reduction):** H1 → H2 → H3. It needs no RTL.
- **Track C (COI):** H4 → H6 → H7 → H8 uses the hand-written `coi.json`, so the HARM side does not wait for the generator (H5).
- **Suggested sequence for one person:** H0, H1, H4, H2, H6, H3, H7, H5, H8, H9, H10, H11. This order gives trivergence something usable early: H1 (fewer adapter workarounds), then H6 (rank mode), then H3 (reduction).
- **Total:** about 30–40 working days, plus H3b if needed.

## 3. Decisions to settle (DECISIONS.md)

| ID | Question | Proposed default |
|---|---|---|
| D-001 | Tie-break rule for ranking | score, then canonical string |
| D-002 | SVA printing of `true` and `nexttime` | `1'b1`, `\|=>` |
| D-003 | X/Z in Z3 canonicalisation | never merge propositions with x/z or `===` |
| D-004 | Finite vs infinite semantics in implication | decide in H3 after testing templates with `F`/`U` |
| D-005 | COI depth definition | register crossings; 0 = combinational |
| D-006 | Generator back end | pyslang (decided after H5a) |
| D-007 | DT depth ↔ cycle offset mapping | characterised in H8 |
| D-008 | Default `--keep` policy for implications | `stronger` |
| D-009 | Z3 as a hard or optional dependency | optional (`HARM_WITH_Z3`, default ON) |

## 4. Hand-off notes for trivergence (do on the Linux machine)
*Superseded by `doc/plan/TRIVERGENCE_IMPACT.md`, which is maintained per milestone.*

- **After H1:**
  - bump `HARM_VERSION`;
  - remove `to_harm_expr` constant rewriting, the `'0` workaround and the compatibility filter, or keep the filter only as a safety net;
  - remove the SVA normaliser's `true`/`nexttime` rewrites;
  - use `--skip-invalid-props`.
- **After H0:** re-evaluate the adapter's "shortest first, top 50" selection now that HARM's ranking is deterministic (M0 #31).
- **After H3:** run HARM with `--reduce implies` and consume `--dump-implications` in stage 5, before OpenFPV's design-level implication.
- **After H6:**
  - the adapter writes `<coi mode="rank">` and `origin` on propositions;
  - add `coiFrac` to the sort;
  - B3 ablation: LLM hints vs. COI hints vs. both.
- **After H9:** feed out-of-cone spec propositions to triage as a disagreement signal.

## 5. Deferred
- **Diversity-aware `--max-ass` selection using USM-T's syntactic similarity (opal).** Opal needs x86 SIMD, so it requires sse2neon or a scalar fallback for arm64.
- **Hybrid (GED) similarity inside HARM:** too costly; it stays in USM-T.
- **Extracting a shared `harm-core` library that USM-T links instead of its fork:** a separate track, to stop the two cores from drifting further.

## 6. Status board

| ID | Title | Status |
|---|---|---|
| H0 | Baseline and safety net | done |
| H1 | Proposition and SVA language fixes | done |
| H1b | x/z semantics: documented, no SV option (D-011 option a) | done |
| H1c | End-of-trace strength (D-015, D-016) | done |
| H1d | Printing fixes F7 (SVA `->`), F8 (Spot parentheses) | done |
| H2 | Z3 back end and canonicalisation | done |
| H3 | Semantic redundancy reduction | done |
| H3b | Atom-implication premises | done |
| H4 | COI contract and RTL fixtures | done |
| H5 | `harm-coi` generator | done |
| H6 | COI rank mode | done |
| H7 | COI filter mode, signal level | done |
| H8 | Depth-aware COI filter | done |
| H9 | Out-of-cone report | done |
| H10 | RTL predicate harvesting | done |
| H11 | Evaluation, docs and release | merged into `dev`; the Linux checks (`ms/H11-linux`) and the macOS checks (`ms/H11-macos`) reviewed and merged into `dev` 2026-10-08; F-M2 (Mac/Linux fixture counts) deferred; release to `main` deferred until the user says so |
| H11b | HARM builds on Linux (F-L1) | done (A4 on the Mac: pass) |
| H11c | Linux findings F-L3 (yosys probe), F-L4 (VCD ranges, SystemVerilog indexing, D-028), F-L5 (wide predicates) | done (A4 on the Mac: pass) |
| H11d | Verilator, Icarus and yosys in `third_party` (Linux and macOS) | done (macOS: F-M1 fixed in H11g) |
| H11e | Fixtures and oracles independent of the Verilator version (F-L6, F-L7, F-L8, F-L10; D-029) | done (macOS: `ctest` pass; fixture counts differ from Linux, F-M2: fixed in H12) |
| H11f | Log files under concurrent writers (F-L9) | done |
| H11g | `install_verilator.sh` on macOS: Homebrew flex's `FlexLexer.h` (F-M1) | done |
| H12 | The same assertions on macOS arm64 and Linux x86_64: FMA contraction in the decision-tree score (F-M2) | done (macOS and Linux: `ctest` 229 of 229, fixtures 46 of 46 equal) |
