# H1 plan: proposition and SVA language fixes

*Status: approved 2026-10-05 (D-002 as proposed; Verilator via Homebrew), in progress. Branch: `ms/H1-language` (from `dev` @ H0). Effort: **4–5 d**, revised up from 2–3 d in PLAN.md (see "Effort" below).*

## Findings from the investigation (2026-10-05)
- **F1. Variables are not tokens in the grammar.** `addTypeToExp` (`propositionParsingUtils.cc`) replaces every declared variable name with `«name,type»` by string substitution, longest first, before ANTLR runs. Anything that is not a declared name, a keyword or a supported literal causes a lexer error, and the whole run aborts.
- **F2. Constants.** The grammar has `[size]'b…` (`VERILOG_BINARY`), `0b…`, `0x…` and decimal integers. `8'd9`, `4'hA`, `'h1F` and the fill literals `'0 '1 'x 'z` are lexer errors.
- **F3. No expression nodes exist for concatenation, replication, `?:` or `===`/`!==`.** Each new node type means a new `ope` entry, `GenericExpression` aliases, an `evaluate` implementation, and entries in `visitorExpList.hh` and the copy, printer and generic visitors (6 files reference each node, e.g. `LogicBitSelector`).
- **F4. Existing x/z semantics.** `Logic operator==` returns false when either side contains x/z. How `!=` behaves with x/z has not been characterised yet; H1's oracle test will establish it (see A2).
- **F5. `G(P0)` is a parse error** (`TemporalParserHandler.cc:704`), and `TemplateImplication` additionally requires `G(… -> …)` ("The template must contain an implication").
- **F6. SVA output** (`--sva`) prints `always (…)`, `nexttime`, `true` and the `::` hierarchy separator:
  - `true` is not SystemVerilog;
  - `u_core::state` is package-scope syntax, not a hierarchical reference;
  - `always` and `nexttime` are valid IEEE 1800-2009, but Verilator and EBMC do not accept them.

  Trivergence's A6 fixture lists exactly these rewrites (`code/tests/fixtures/m0/harm/normalize_cases.yaml`).
- **F7. `messageError` calls `exit(1)`**, so a bad `<prop>` aborts the run. Skipping invalid propositions needs a scoped "throw instead of exit" mode around proposition parsing.
- **F8. Tools on this Mac:** `iverilog` is installed; it evaluates 4-valued expressions but not concurrent assertions. **Verilator is not installed.**

## Scope

### 1. Constants (grammar + handler)
- **Based literals:** `[size]'[s](b|o|d|h)<digits>`, with `x`/`z`/`?` digits for `b`/`o`/`h`, and whole-value `x`/`z` for `d` (as in SV).
- **Width:** the stated size, or 32 when unsized, as in SV. Out-of-range values are truncated with a warning. `s` makes the constant signed.
- **Fill literals `'0 '1 'x 'z`:** these take the width of the other operand of the binary operator, or of the context. A fill literal with no sized context is an error.
- The existing forms are unchanged.

### 2. New operators (expression library + grammar + handler)

| Operator | Node(s) | Operand types | Result |
|---|---|---|---|
| `{a, b, …}` | `LogicConcat` (n-ary) | logic, int (declared width), bool (1 bit) | unsigned logic, width = sum |
| `{N{a, …}}` | `LogicReplicate` | N: constant > 0 | unsigned logic |
| `c ? a : b` | `IntTernary`, `LogicTernary`, `FloatTernary`, `PropositionTernary` | c: boolean; a and b: same kind | kind of a and b |
| `===`, `!==` | `LogicCaseEq`, `LogicCaseNeq` | logic | bool (2-valued, bitwise identity including x/z) |

Notes:
- **Precedence** follows SystemVerilog: `?:` lowest, concatenation and replication as primaries.
- **Braces:** the proposition grammar already uses `{` only for `inside {…}`; concatenation is distinguished from it syntactically. *Inline* propositions inside templates are parsed by the temporal grammar, where `{…}` means a SERE. **Concatenation is supported in `<prop>`/`<numeric>`, not inline in templates.** This is documented, and an error message says so.
- **Spot:** propositions reach Spot as atoms. The implementation must confirm that the new nodes never leak into a Spot formula string. Acceptance test A5 covers this end to end.

### 3. Hierarchy separator
- **Input:** for every declared name containing `::`, `addTypeToExp` also substitutes its dotted spelling (`u_core.state` → `«u_core::state,…»`). Only declared names are affected, so floats and `.substr` are untouched.
- **Output:** in SVA output (`--sva`, `--sva-assert`), `::` is printed as `.`. Other output languages keep `::`.

### 4. Invariant templates
- **Accepted forms:** `G(P0)` and `G(<boolean layer>)` without an implication and without DT operators. A DT operator needs an antecedent, so with one this stays an error, with a clear message.
- **Internal form:** desugared to `G(true -> φ)`, with the template marked as an invariant.
- **Printing:** as `G(φ)`, SVA `always (φ)` (`--sva`), or `φ` (`--sva-assert`).
- **Metrics:** the contingency table is computed as for `true -> φ`. The README will say that causality-type metrics are meaningless for invariants.

### 5. SVA printing (decision D-002)
Proposed rules:

| Construct | `--sva` today | `--sva` after H1 | `--sva-assert` after H1 |
|---|---|---|---|
| `true` / `false` | `true` | `1'b1` / `1'b0` | same |
| `p \|-> nexttime q` (q boolean) | `nexttime` | `p \|=> q` | same |
| `p \|-> nexttime[n] q` / nested nexttime (q boolean) | `nexttime nexttime q` | `p \|-> ##n q` | same |
| nexttime over a non-boolean property | `nexttime` | unchanged (valid SV) | unchanged |
| hierarchy `a::b` | `a::b` | `a.b` | same |
| outer `always (…)` | `always (…)` | **kept** (valid SV; backward compatible) | dropped, inside `assert property (@(posedge <clk>) …);` |

- **Rationale:**
  - `|=>` and `##n` are equivalent to `|-> nexttime` for a boolean consequent: a sequence used as a property is weak by default in assertions, like `nexttime`;
  - they are accepted by every tool we use;
  - keeping `always` in `--sva` avoids gratuitous changes for current users.
- **Not in the "after H1" table:** I will check whether `--sva-assert` is currently written to `--dump-to` files (the table printout showed nothing) and fix it if not.

### 6. `--skip-invalid-props`
- **Mechanism:**
  - a scoped error mode in `hlog`: while a `<prop>`/`<numeric>` is being parsed, `messageError` throws `harm::ParseError` instead of calling `exit`;
  - `ManualDefinition` catches it, prints a warning with the reason, and drops that proposition;
  - a summary line gives the count of dropped propositions.
- **Without the flag,** behaviour is unchanged: the run aborts.
- **Templates:** errors in templates stay fatal; there's no partial template.

## Out of scope
- New temporal operators.
- Concatenation inline in templates.
- Signed fill literals.
- `'{…}` assignment patterns.
- Real (float) literals in based form.
- Changing existing `==`/`!=` x/z semantics. If A2 shows they differ from SV, that is reported as a finding with a proposed decision, not changed in H1.

## Acceptance tests (written first; they must fail before the implementation)

| # | Test | Kind |
|---|---|---|
| A1 | Parser and printer unit tests for every new literal and operator: parse → print → parse round trip; evaluation on hand-written 4-valued vectors | gtest, hand-written expectations |
| A2 | **Oracle test for proposition semantics:** about 1,000 random expressions using the new literals and operators, plus the existing `==`, `!=`, relational and bitwise operators, over random widths (1–70 bits) and random 4-valued values. HARM's truth value must equal "the SV value is `1'b1`" as computed by **iverilog** (`$display`). The fixture is generated by `tests/oracle/gen_iverilog_fixture.py`, committed, and needs no iverilog at test time. Mismatches in pre-existing operators are reported, not hidden: they go in a separate, explicitly listed expected-difference file that you approve | gtest + generated fixture |
| A3 | `.` alias: propositions using `a.b` and `a::b` give identical expressions; a float like `1.5` and `.substr` are unaffected | gtest |
| A4 | Invariant templates: `G(P0)` mines the known invariants of a small CSV fixture; `G(..&&..)` without an implication gives the clear error | gtest + regression case |
| A5 | **End to end:** a new regression case whose config uses every new operator in `<prop>`s and `G(P0)` templates, mined from a CSV fixture, with a hand-checked expected output (proves nothing leaks into Spot) | regression |
| A6 | **Trivergence's A6 cases**, copied into `tests/input/m0_normalize_cases.yaml`: each HARM-format assertion printed with `--sva-assert` (body only) must equal trivergence's expected `out`. The 4 `null` cases must print as valid SV, now that HARM handles them | gtest |
| A7 | `--skip-invalid-props`: a config with 2 invalid and 3 valid propositions mines with the 3 valid ones and warns twice. Without the flag, the exit code is non-zero | regression (two cases) |
| A8 | All H0 regression and determinism tests stay green. Only `process` and `edit` (the `--sva` cases) may change, per D-002. Their new baselines are reviewed by hand and recorded | regression |

## Validation (independent)
- **Proposition semantics:** iverilog oracle (A2). It is independent of HARM's evaluator.
- **SVA printing:** two layers.
  1. **Round trip:** HARM's own SVA parser reads the printed SVA back, and the result must evaluate identically on the regression traces. This catches printer bugs, but is not independent.
  2. **Independent:** for the A5 and A6 assertions plus the `process`/`edit` outputs, run **Verilator** (`--assert`) on a generated testbench that replays the CSV trace. The assertion must fail on exactly the cycles where HARM's evaluator says it fails. **This needs Verilator**: either `brew install verilator` on this Mac (your approval needed), or run it on the Linux machine, whose trivergence image has Verilator. Without either, this item stays pending in VALIDATION.md and H1 is not marked done.

## Files
- **Grammar:** `src/antlr4/propositionParser/grammar/proposition.g4` (regenerated with the existing `regenerateAllParsers.sh`) and `temporal.g4` (invariant form).
- **Handler:** `PropositionParserHandler.cc`/`.hh` and `propositionParsingUtils.cc` (dotted alias); `TemporalParserHandler.cc`.
- **Expression library:**
  - `src/exp/include/expUtils/ope.hh`;
  - `formula/expression/GenericExpression*.hh` plus new `Concat.hh`, `Ternary.hh`;
  - visitors (`visitorExpList.hh`, Copy, Printer, Exp);
  - `src/utils` (`Logic` helpers for concat and case equality).
- **Templates:** `src/miner/utils/src/TemplateImplication.cc` (invariant flag and printing).
- **Error handling:** `src/logging` (scoped throw mode), `ManualDefinition.cc`, `commandLineParser.cc`, `globals`.
- **Tests:** new `tests/propositionLanguageTests.cc`, `tests/oracle/*`, `tests/input/m0_normalize_cases.yaml`, regression cases and baselines.
- **Docs:** `README.md` (new syntax; SVA output rules), `doc/plan/{DECISIONS,VALIDATION,PLAN,TRIVERGENCE_IMPACT}.md`.

## Effort
4–5 d instead of 2–3 d. The new expression nodes touch the operator enum, aliases, evaluation and four visitors. Fill literals need context-dependent sizing. And the oracle generator plus Verilator replay are new infrastructure, which later milestones (H2) reuse.

## Decisions needed before starting
1. **D-002 (SVA printing):** approve the table in §5, in particular *keeping* `always (…)` in `--sva` and dropping it only in `--sva-assert`.
2. **Verilator:** install it with Homebrew on this Mac, or run the independent printer validation on the Linux machine?
