# Decisions

One entry per decision: context, decision, alternatives, consequences. Numbering follows `PLAN.md` §3; IDs above D-009 are added as they come up.

## D-010: one C++ toolchain for HARM and all third-party libraries (2026-10-05, H0)
- **Context:** on the development Mac, `harm` aborted at start-up (`malloc: pointer being freed was not allocated`), even for `--help`. The dependencies had been built against three C++ runtimes, all loaded into one process:
  - Spot: gcc-12 `libstdc++`;
  - ANTLR and HARM: gcc-13 `libstdc++`;
  - Boost: Apple `libc++`, because `b2` ignores `CC`/`CXX`.

  The install scripts did not pin a compiler.
- **Decision:**
  - Build every dependency and HARM with **Homebrew g++-13**, chosen by the user.
  - `third_party/install_*.sh` honour `CC`/`CXX` (Boost through an explicit `b2` toolset) and record the compiler in `<prefix>/.harm_toolchain`.
  - CMake warns at configure time when a recorded compiler differs from HARM's, or when the record is missing.
  - Boost is built `--with-regex` only: it is the only compiled Boost library HARM links; the rest is header-only.
- **macOS SDK finding:**
  - Homebrew gcc-13 (13.3.0) cannot compile a hello-world against its default sysroot, the newest Command Line Tools SDK (15.4). It fails with errors in `_stdio.h` and `_Alignof`, and `configure` reports "cannot run C compiled programs".
  - It works with the Xcode 15.2 SDK, which is the one CMake passes for HARM.
  - So on macOS the scripts set `SDKROOT=$(xcrun --show-sdk-path)` unless `SDKROOT` is already set.
- **Alternatives considered:**
  - Apple clang with `libc++` for everything. It avoids the SDK issue, but the user chose g++-13.
  - Developing in Docker (Linux only). It leaves macOS broken.
- **Consequences:** anyone building on macOS with Homebrew gcc needs an SDK their gcc supports. The README says so.

## D-001: deterministic output (2026-10-05, H0)
- **Context:** with identical inputs, HARM's output order changed with the number of threads and from run to run. Before the fix, 8 of 17 determinism tests failed. The `--max-ass` cut and the fault-coverage minimum subset could also change *which* assertions are reported (trivergence M0 #31). Five sources were found:
  1. `TLMiner` appended each permutation's assertions in thread-completion order;
  2. `extractUniqueAssertionsFast` iterated a pointer-hashed `unordered_set`, which is address-dependent even with one thread;
  3. ranking sorted on the score only, so ties were in arbitrary order;
  4. the fault-coverage code iterated id-keyed maps, and assertion ids come from a global counter incremented as threads create assertions;
  5. `--fd` faulty traces came in the directory order, which is unspecified, and VCD traces were then shuffled with a **random seed** (for an early outlook on coverage in the progress bar). Fault ids changed on every run, and with them the greedy set cover's tie-breaking, even with one thread.
- **Decision:**
  1. Collect per `(template index, permutation index)` in a `std::map`, and concatenate in key order.
  2. Deduplicate in input order; the first occurrence of a key is kept.
  3. Ranking order: `final score desc`, then `toString() asc`.
  4. The fault loop follows the order of `selected`. The set cover receives its candidate sets sorted by assertion text.
  5. Sort the faulty-trace list, then shuffle VCD traces with a fixed seed (`std::mt19937{0}`). This keeps the early-outlook intent and makes it reproducible.
- **Consequences:**
  - Output is identical across runs and thread counts on all 19 regression cases, including the `--max-ass 10` ones.
  - The ordered baseline is frozen after this change. Set changes against the pre-fix baseline are listed in `VALIDATION.md` (H0).
  - Fault ids in logs are now stable, but they differ from those of earlier HARM versions.

## D-002: SVA printing (2026-10-05, H1, approved)
- **Context:** HARM's `--sva` output contained `true` (not SystemVerilog), `::` (package scope, not a hierarchical reference), and `always`/`nexttime`. The last two are valid IEEE 1800-2009 but rejected by Verilator and EBMC. Trivergence rewrites all of these in an adapter (M0 #9).
- **Decision (both `--sva` and `--sva-assert`):**
  - `true`/`false` → `1'b1`/`1'b0`;
  - `p |-> nexttime q` → `p |=> q` and `nexttime[n]` → `##n`, when `q` is boolean;
  - `a::b` → `a.b`.
- **The outer `always (…)`:** kept in `--sva` (valid, and backward compatible). Dropped in `--sva-assert`, which prints `assert property (@(posedge <clk>) …);`.
- **Validation:** Verilator replay of printed assertions against HARM's own evaluation. Verilator is installed on the development Mac with Homebrew.

## D-011: x/z semantics of propositions (2026-10-05, H1). **Decided: option (a), documented in H1b (2026-10-06); option (b) not adopted**
- **Finding (H1 oracle, A2):** HARM's propositions do not follow SystemVerilog when values contain x/z.
  - **HARM's rule:** a relational or equality comparison (`== != < <= > >=`) is **false** if either operand contains an x or z bit. Boolean operators (`! && ||`) then work on 2-valued results.
  - **SV's rule:** the comparison yields x, or a known 0/1 when known bits already decide it (e.g. `!=` with a known differing bit is 1). `!`, `&&`, `||` propagate x (Kleene logic). An assertion treats a final x as false.
  - **Consequences:**
    - `!(a == b)` is **true** in HARM but x (false) in SV when `a` has x bits;
    - `4'bx10x != q4` is always false in HARM, but 1 in SV when a known bit differs.
  - **Evidence:** iverilog oracle over 32 random 4-valued rows. Of 300 random pre-H1 expressions, 78 differ from SV on at least one row. All 300 match the rule above exactly, which confirms it describes HARM's behaviour precisely.
- **Impact:** a HARM-mined assertion with a negated proposition can hold on a trace in HARM but fail in an SV simulator on the same trace when x/z values are present. It *may* explain HARM/Verilator disagreements like trivergence M0 #33 (`!(sda == 1'b0) |=> !writeEn` on an inout net, where the VCD can record `z`). Trivergence's M0 report attributes #33 to how the inout net is sampled (#24), so the link is unproven.
- **Status:** H1 keeps the current semantics, as its plan states. The oracle checks new operators against HARM's rule (the "HARM model" column) and reports the SV gap.
- **Options:**
  - (a) keep it and document it in the README;
  - (b) add SV-faithful three-valued semantics as an option (e.g. `--sv-xsemantics`);
  - (c) make SV semantics the default. This changes mining results on traces with x/z.

  Proposed: (b), as a new milestone after H1. The oracle fixture already contains the SV column needed to validate it.
- **Additions found during implementation (H1):**
  - **Unbounded `F` is printed as `s_eventually` in SVA.** `eventually` without a range is not SystemVerilog, and `F` is the strong, unbounded form. The parser accepts `s_eventually` as input.
  - **Edit rules keep matching the pre-D-002 printing.** `<edit>` rules are matched against the printed SVA text, with spaces removed. With `1'b1`, a rule such as `##@(N,b) @(P,c)` with `c=="true"` would silently stop matching: `##2 1'b1` becomes `##21'b1`. While edit rules are matched and applied, HARM prints SVA as before (`clc::legacySvaPrinting`), so existing users' edit rules keep working. The output still follows D-002.
  - **Updated test expectations:** `svaParserPrinterTests` (parse_print3, parse_print7, parse_print8) now expect `|=>`, `##9` and `s_eventually`.
  - **Regression:** the `process` baseline was re-captured. Its new output equals the old one with the D-002 rewrites applied mechanically (checked as sets; same count, 138 assertions in 4 contexts). `edit` is unchanged.

- **Decision (2026-10-06, H1b, by the user): option (a).**
  - **Why not (b):** in HARM a proposition is true or false, and a proposition and its negation are complementary. The decision trees' negated candidates, negated consequents and the H2/H3 reductions rely on that.
  - **SystemVerilog's semantics would break it:** `!(a == b)` needs the inner comparison to carry x to the `!`. That means three-valued evaluation, or an equivalent "definitely 1 / definitely 0" pair of Boolean evaluations, and with either one both `a == b` and `!(a == b)` are false on x cycles.
  - The plan for (b) (D-024) is withdrawn.
- **HARM's rule, measured precisely** (H1b; pinned by `tests/input/h1b`):
  - wherever a 4-valued value becomes a truth value, x/z counts as false;
  - comparisons are false if any operand bit is x/z;
  - a value used as a condition is true only with a known 1 bit;
  - `!`/`&&`/`||` are then two-valued; `===`/`!==` are exact.

  The SystemVerilog values of the pinned cases were checked against IEEE 1800-2017 (§11.4.4, §11.4.5, §11.4.7, §16.6) and with iverilog 12.0. They differ on 9 of 23 cases, in both directions.
- **Documented** in the README ("x and z values"), with what to do: mine after reset, use `===`/`!==` when x/z matter, and treat the disagreement as known in triage.

## D-012: fixes stay on `dev` until the final merge (2026-10-05)
- **Context:** H1 found bugs that also affect the stable `main` used by other people, notably F10 (bit selections evaluated and printed with swapped bounds) and F9 (variable names corrupting literals).
- **Decision (user):** no hotfix on `main`. All fixes stay on `dev` and reach `main` with the final merge after H11.
- **Consequence:** until then, `main` users keep these bugs. Trivergence must pin `dev` commits (TRIVERGENCE_IMPACT.md).

## D-003: Z3 equivalence of propositions (2026-10-05, H2, approved; revised from PLAN.md §3)
- **Context:** the original proposal ("never merge propositions with x/z constants or `===`; 2-valued otherwise") is unsound. Variables can hold x/z at run time, and under HARM's rule (D-011) `a == c` and `!(a != c)` then differ.
- **Decision:**
  - Encode HARM's evaluator exactly: each logic signal is a value bit-vector plus an x-mask and a z-mask, and each operator follows `Logic`'s implementation.
  - Constructs not encoded exactly become opaque atoms, keyed by their text. This is sound but incomplete.
  - A timeout or unknown result means "not equivalent".
- **Z3:** built from source in `third_party/` with HARM's compiler (D-010), behind the CMake option `HARM_WITH_Z3` (default ON).

## D-005: COI depth convention (2026-10-05, H4, approved)
- **Depth = number of register crossings on a path from source to target.**
  - 0 means combinational: the source's value now can affect the target now.
  - d means the source's value d cycles ago can affect the target now.
- **Depths are counted on traces sampled as HARM samples them:** the values just before each rising edge. That is the Preponed-region view of SVA concurrent assertions; VCD dumps record the end of the time step instead. In practice a register is one cycle behind its inputs (`q <= a` gives `G(a -> X q)`).
- All depths are listed up to `max_depth`. A register's own feedback puts it in its own cone at depths 1, 2, ….
- `saturated: true` marks a source with paths deeper than `max_depth`.

## D-013: COI sources and targets (2026-10-05, H4, approved)
- **Targets:** every signal visible in the trace under the recorded VCD scope.
- **Sources:** visible signals only. Paths through invisible nets are followed through.
- The clock is never a source; reset is an ordinary source.

## D-014: COI rank metrics (2026-10-05, H6, approved)
For a mined assertion `G(antecedent -> consequent)`, with leaves = its atomic propositions and leaf offsets = the cycle at which each is evaluated, relative to the start of the antecedent:
- **`coiFrac`:** fraction of the antecedent leaves (those with variables) whose variables are **all** in the union of the cones of the consequent's variables.
- **`coiDepthFit`:** fraction of antecedent leaves whose every variable `v` has a consequent leaf `q` and variable `c` with `offset(q) - offset(leaf)` among the depths of `v` in `cone(c)`, or above `max_depth` when saturated. When an offset is unknown (under `until`, `eventually`, `release`, repetitions or ranges), cone membership is enough.
- **No antecedent leaves** (e.g. an invariant): both are 1.
- **`coiUnknown`:** antecedent leaves with a variable `coi.json` does not know. They count as in the cone and fitting: never penalised, but counted.

## D-004: implication reduction semantics (2026-10-05, H3, approved)
- Assertions are compared with Spot (infinite-word LTL). Only pairs where **both** formulas are syntactic safety are reduced; others are always kept.
- **Why:** for safety formulas, A ⇒ B over infinite words implies that every finite trace violating B also violates A. Dropping B then loses nothing for HARM's finite-trace evaluation or for simulation.
- **Amendment (2026-10-05, during H3 implementation, approved with H3): the "Why" is wrong at the trace end.** The A2 oracle refuted `G({b ##2 !a} |-> X (b && !b))` ⇒ `G({b ##2 !a} |-> (b && !b))` on a 3-cycle trace. Both formulas are false on infinite words, and B fails on the trace. A does not fail, because HARM evaluates the consequent with a deterministic Spot automaton whose atoms are the boolean *leaves*. It cannot see that `b && !b` is false, so the `X` instance is still pending at the trace end, and a pending instance counts as holding. A trace violating B therefore need not violate A in HARM's evaluation, even though A is a bad prefix in theory.
  - **Fix: A ⇒ B is claimed only if it holds in both semantics.**
    - (1) As before, Spot containment over infinite words, which serves SVA, simulators and formal tools.
    - (2) An exact model of HARM's evaluator (`AutomataBasedEvaluator`):
      - each antecedent is a fixed-length sequence of boolean steps;
      - each consequent is the same deterministic, complete Spot automaton over leaves that HARM builds, with leaf conditions mapped to atoms;
      - an instance starts on every cycle;
      - a consequent fails when it reaches the rejecting sink;
      - an instance still pending at the end holds.

    The model explores every finite trace by a breadth-first search over (pending instances of A, pending instances of B), and A ⇒ B is refuted when B fails while A has not.
  - Assertions whose antecedent is not a fixed-length boolean sequence are never reduced: `[*]`, `##[m:n]`, and `&&` with operands of different lengths. Neither are those without `G(… -> …)`.
  - This only removes claims, so it does not change the approved policy. It is stricter (more conservative) than the approved wording.

## D-008: which assertion is kept (2026-10-05, H3, approved)
- **Default `--keep stronger`:** when A ⇒ B and not B ⇒ A, keep A and drop B. `--keep weaker` and `--keep ranked` are options.
- Equivalent assertions: keep the one with the smallest text.

## D-015: finite and infinite semantics (2026-10-05, after H3, approved)
- **Mining and qualification keep HARM's simulator semantics.** An assertion fails only if an instance fails inside the trace, and an instance still pending at the end holds. For the default weak SVA properties, this is what a simulator reports at the end of a simulation, including the leaf-level evaluation (a simulator also waits for the next clock to evaluate `X (b && !b)`).
- **Reduction (`--reduce implies`) requires both semantics:** the finite-trace semantics above and infinite words (D-004 as amended). So a dropped assertion is covered for both trivergence's simulator checks and its formal oracle.
- **Not done, deliberately:**
  - a global `--trace-end strong` option, where pending means failed. It would make every `G(a -> X b)` fail when `a` holds on the last cycle;
  - exact infinite-word evaluation of mined assertions, with atom-level monitors. It would cost one automaton per candidate instead of one per template, and would only change verdicts in the last cycles for contradictory or valid leaf combinations.
- **To fix (H1c):** HARM prints `F` as `s_eventually` (D-002), which is strong, but evaluates a pending `F` as holding. A liveness assertion HARM accepts could therefore fail in a simulator at the end of the simulation. Liveness operators get the strong end-of-trace semantics instead.

## D-016: end-of-trace strength (2026-10-05, H1c, approved)
- **`--trace-end harm` (default): HARM's current behaviour, unchanged.** A consequent instance still pending at the end of a trace holds. This is the *weak view* of the truncated-path semantics (Eisner et al., 2003), under which every operator is treated as weak at the end.
- **`--trace-end sva`: the *neutral view*,** which is what IEEE 1800 says for the end of a simulation:
  - weak operators pending at the end hold: `nexttime`, `until`, `always`, weak sequences;
  - strong ones fail: `s_eventually`, and the strong operators that negation produces, i.e. `not nexttime p` = `s_nexttime not p` and `not (p until q)`.
  - Only verdicts that are *pending* in HARM's evaluation can change, and only from unknown to failed. Instances that HARM decides inside the trace keep their verdict.
- **Why an option, not the default:**
  - It changes other users' results: 106 of the 138 lines of the `process` baseline use a strong operator.
  - Trivergence discards mined liveness anyway (H1c F2).
- **`--reduce implies`** follows the selected semantics in its finite-trace check (D-004 as amended).

## D-017: "in the cone" for COI filtering (2026-10-05, H7, approved)
- **The same leaf rule as D-014,** so that filter and rank modes share one definition. An antecedent proposition is in the cone of a consequent if **every** variable of the proposition is a source of **some** variable of the consequent.
- A signal marked unknown in `coi.json` counts as in the cone. A consequent with an unknown variable keeps every antecedent. Propositions without variables are kept.
- A placeholder that appears in both the antecedent and the consequent is not filtered.

## D-018: COI metrics in filter mode (2026-10-05, H7, approved)
- Filter mode still computes `coiFrac`, `coiDepthFit` and `coiUnknown`, so the same `<sort>` works in both modes. After filtering, `coiFrac` is 1 for every assertion.
- **Filter mode is not "rank mode minus out-of-cone assertions"** for decision-tree templates. Pruning changes what the greedy tree explores, so filter mode can find in-cone assertions that rank mode misses (H7 F2). Its guarantee is the output of rank mode on a configuration restricted, by hand, to each consequent's cone.

## D-006: `harm-coi` front end (2026-10-06, H5a). **Decided: (a) pyslang**
- **Options:**
  - (a) the **pyslang** elaborated AST, with our own dataflow and control-dependency walk;
  - (b) the **yosys + sv-elab** (formerly yosys-slang) JSON netlist.
- **Spike results:** `H5_PLAN.md`, section "H5a results".
  - pyslang reproduces all 6 H4 fixtures exactly.
  - yosys needs yosys ≥ 0.67 (OSS CAD Suite on macOS), loses struct fields and parameters, and lowers the conditions that H10 needs.
- **Decided (user, 2026-10-06): (a) pyslang 12.0.0**, pinned. yosys stays an optional signal-level cross-check: it runs only when a yosys with `read_slang` is found, and is not a dependency.

## D-019: `harm-coi` conventions (2026-10-06, H5, approved)
These complete D-005 (depth) and D-013 (sources and targets) for what the H4 fixtures did not settle. The guiding rule: a cone may be too large, never too small. Where the RTL leaves a doubt, the signal goes to `unknown`, which HARM treats as in every cone (D-017).
- **Visible names come from the trace when `--vcd` is given.**
  - A packed struct dumped as one vector is one signal, the union of its fields. Icarus does this, and so does Verilator without `--trace-structs`, as trivergence runs it.
  - A trace signal that the RTL does not produce is `unknown` (e.g. a `for` variable dumped as `unnamedblk1::i`).
  - Without `--vcd`: depth ≤ recursion, with Verilator `--trace-structs` field names.
- **Clock:**
  - `--clock`, or the single root that every register's clock comes from through wires and ports; several roots are an error.
  - A visible alias of the clock (a submodule's clock port) is a target with no sources, and is never a source.
  - A register on another clock or on both edges is `unknown`.
  - A register on the falling edge of the sampling clock: depths 0 and 1.
- **Asynchronous controls** (event-list signals the body reads, e.g. `posedge rst`): depths 0 and 1.
- **Blocking assignments:**
  - a process-local variable is replaced by its sources;
  - a visible signal assigned exactly once in a process (outside loops) and read later in it is also a source at the reader's own sample (`y <- t @0`). Forcing `t` changes `y`, and `G(t -> y)` is a real assertion that filter mode must not prune (H5 finding F2).
- **Combinational latches** (`always_latch`, or an `always_comb` output not assigned on every path) are `unknown`.
  - `unique` and `priority` are not trusted to make a `case` complete: if the uncovered value occurs, the output holds its value.
  - A `case` is complete only with a `default`, or with constant items covering every selector value.
- **`unknown` propagates:** a target whose cone reaches an unknown signal within `max_depth` is unknown.
- **`meta.generator.version`** is `"<harm-coi version> (pyslang <version>)"`.
  - The plan had a separate `frontend` field, but the coi.v1 schema allows only `name` and `version` (`additionalProperties: false`), and a schema change would need a new contract version.
- **Oracle (`tests/coi/perturb.py influence`):**
  - a (source, target) pair whose two names are one net in the simulator (same VCD identifier: a port and the signal connected to it, or `assign y = x` merged by Verilator) is not checked, because forcing one forces the other;
  - a name on the clock's net is never forced (D-013);
  - the skipped pairs are printed. On the H4 fixtures this removes 2 pairs (`hier` dout/g[2]::w, `multipath` z/rb), which passed before.

## D-020: depth modes of the COI filter (2026-10-06, H8, approved)
`<coi … mode="filter" depth="any|bounded|exact"/>`. `depth` with `mode="rank"` is an error, and so is an unknown value.

For an antecedent proposition at distance `d` cycles before a consequent leaf (the offsets of D-014, computed by `leafOffsets`), with `v` a variable of the proposition and `c` a variable of the consequent leaf:
- **`any`** (the default): H7, signal level (D-017).
- **`exact`:** every known `v` has some consequent leaf and `c` such that `d` is among the depths of `v` in `cone(c)`, or `d > max_depth` and `v` is saturated.
  - This is `coiDepthFit`'s leaf rule. The metric and the filter share one function (`CoiInfo::fits`), so filter output has `coiDepthFit = 1`.
- **`bounded`:** the same, with `0 ≤ d ≤` the largest depth of `v` in `cone(c)`, or `d ≥ 0` and `v` saturated.
- **Unchanged from D-017:**
  - unknown signals and unknown consequent signals keep the proposition;
  - a proposition without variables is kept;
  - placeholders shared by antecedent and consequent are not filtered;
  - an offset that is not fixed falls back to cone membership.
- **Plain templates:** a permutation is removed if any antecedent leaf does not fit.
- **Decision trees:** a (candidate, index) pair is skipped if the candidate does not fit at that index's distance (D-007). The tree is greedy, so filter output is not rank output post-filtered (as in D-018).

## D-007: decision-tree index → cycle distance to the consequent (2026-10-06, H8, checked by hand)
Index `i` of a decision-tree operator (`dtNext<i>`, `..#N&..` level `i`) is at a fixed distance, in cycles, before each consequent leaf. The distance does not depend on how many items the tree adds later. Step `N` (`..##N..`, `..#N&..`); `off(q)` = offset of consequent leaf `q` from where the consequent starts (`X`, `##k` in the consequent).

| Implication | Antecedent layout | Distance of index `i` to leaf `q` |
|---|---|---|
| `\|->` | `dM ##N … ##N d1 ##N d0` (index 0 is the last cycle) | `i·N + off(q)` |
| `\|=>` | same | `i·N + 1 + off(q)` |
| `->` | `d0 ##N d1 … ##N dM` from the start, which the consequent shares | `off(q) − i·N`, negative when the item comes after the consequent |
| `..&&..` | one index | as index 0 |

- **Other events in the antecedent shift every index alike:**
  - `{..##1..;v4} |-> c`: `i + 1`;
  - `{v4;..##1..} -> X c`: `−i`.
- **Offsets that are not fixed** (`F`, `until`, repetitions, ranges): unknown, so cone membership only.
- **Computed, not hard-coded:** HARM places a marker at each index and runs `leafOffsets`, the function behind `coiDepthFit`. `tests/coiDepthTests.cc` checks 12 template shapes against this table.
- **Checked by hand on mined `counter` assertions (H8 VALIDATION):**

  | Assertion | Index | Hand-counted distance | Table |
  |---|---|---|---|
  | `G({rst ##1 cnt == 4'b0} \|=> cnt == 4'b0)` | 1 (`rst`) | 2 | `\|=>`: 1 + 1 = 2 |
  | `G({rst ##2 true} \|-> cnt == 4'b0)` | 2 | 2 | `\|->`: 2 |
  | `G({##1 en ##1 cnt == 4'b0} -> X(en && wrap))` | 2 (`cnt`) | −1 | `->`: 1 − 2 = −1 |
  | `G({!en && cnt == 4'b0} \|-> X cnt == 4'b0)` | `..&&..` | 1 | 1 |

## D-021: printing of `->` in SVA, and brackets in Spot LTL (2026-10-06, H1d; fixes H8 findings F7 and F8)
- **F7, SVA:** HARM's `->`/`=>` start the consequent with the antecedent (as in Spot and PSL). SVA's `|->`/`|=>` start it at the antecedent's end, so they are equivalent only for a single-cycle antecedent.
  - **A multi-cycle antecedent `s`** that is a sequence of fixed length (last cycle `n−1`), with a Boolean consequent after `k` cycles of `X` (+1 for `=>`), is printed re-anchored at its end, with `j = k − (n−1)`:
    - `j = 0`: `s |-> c`;
    - `j = 1`: `s |=> c`;
    - `j > 1`: `s |-> ##j c`;
    - `j < 0`: `s |-> $past(c, −j)`.

    These are forms Verilator and EBMC accept (see D-002).
  - **Otherwise** (a property antecedent such as `a && X b`, a variable-length sequence, or a non-Boolean consequent): `(s) implies <consequent>`, or `(s) implies nexttime (<consequent>)` for `=>`. IEEE 1800 `implies` starts both sides at the same cycle.
  - **Unchanged:** a single-cycle antecedent, `|->`/`|=>`, and the legacy SVA printing that `<edit>` rules are matched against (D-002), so existing edit rules keep matching.
- **F8, Spot LTL:** Spot binds `X`, `F`, `!`, `U`/`W` and `R` tighter than `&&`/`||`, and `&&` tighter than `||`.
  - A proposition whose top operator is a Boolean connective (`&&` with more than one item, `||`, `^`, `==`/`!=` between propositions) is printed in brackets under those operators. A `||`, `^`, `==` or `!=` one is also bracketed under a property `&&`.
  - `G(…)` already prints its brackets. SVA and PSL are unchanged: there, Boolean operators bind tighter than property operators.
- **Baseline change:** `sub_platform1k` only. In 46 of its 91 assertions, `|-> X<a && b>` becomes `|-> X(<a && b>)`. Nothing else changes: same assertions, same order (checked by applying the rewrite to the old baseline).
- **Validation:** `tests/oracle/h1d_spot_equivalence.py`. Spot (`ltlfilt`) checks that the new texts mean HARM's formulas and that the old ones do not.

## D-022: the out-of-cone report (2026-10-06, H9, approved)
- **`--dump-coi-report <file>`** pairs each consequent proposition with each antecedent proposition or numeric of the same context. It is computed when the configuration is loaded, and mining is unchanged.
- **Consequents** are propositions in the `c` and `ac` domains. **Antecedents** are propositions in every other domain (`a`, `ac`, `dt`, local ids) and numerics not only in `c`. A proposition is not paired with itself.
- **The rule is D-017's, variable by variable:**
  - an antecedent is **out of the cone** if a known variable of it is a source of no consequent variable (listed in `outside`), even if it also has unknown variables;
  - otherwise it is **unknown** if it has a variable `coi.json` does not know (`unknownVariables`);
  - if a consequent variable is unknown, the consequent's cone is unknown (`coneUnknown`) and every antecedent is listed as unknown;
  - in-cone pairs are not listed.
- **Format `coi-report` v1:** `{"version": "1", "contexts": [{"name", "coi": <path> | null, "consequents": [{"text", "origin", "variables", "coneUnknown", "outOfCone": [{"text", "origin", "numeric", "variables", "outside"}], "unknown": [{…, "unknownVariables"}]}]}]}`. Texts are HARM's printing; lists are sorted by text.
- **Origins** are looked up by the printed text. For numerics, the printed text is now also a key, besides the configuration text. Propositions expanded from a numeric (`loc="dt"`) carry no origin; that is unchanged from H6.
- **Signal level only.** Depths ("in the cone, but not at the spec's delay") are a possible extension.

## D-023: RTL predicate harvesting (2026-10-06, H10, approved)
- **Harvested** (`harm-coi --predicates`, into `coi.json → predicates`; schema unchanged):
  - conditions of `if` and `?:`, with each atom of a compound condition;
  - `s == L` for each case label;
  - `v == C` for every value of an enum-typed variable;
  - comparisons with a constant side anywhere;
  - reset values: the first `if` of a clocked process whose branch assigns only constants. The rule is structural; a data condition of that shape also yields the register's value.
- **Translation into HARM propositions:**
  - visible names only (H5's mapping); the others are dropped and counted;
  - the signal on the left, constants as sized decimal literals of the signal's width;
  - a 1-bit comparison as the signal or `!signal`;
  - syntactic deduplication: one record per text, with `src` joined and `targets` united.
  - Elaboration-time conditions and conditions on local variables are not harvested.
- **`--emit-config`:** one context (not one per target, as PLAN §H10 said):
  - the predicates with `loc="a, c, dt"` and `origin="rtl"`;
  - `<coi mode="rank">`;
  - `--generate-config`'s template and sorts.

  Filter mode (H7, H8) gives the per-target restriction on that one context.

## D-025: atom-implication premises (2026-10-06, H3b, approved after the measurement)
- **`--atom-premises`** (needs `--reduce implies`) and **`--atom-premises-max <N>`** (default 2000). Opt-in: `--reduce implies` alone is H3, unchanged.
- **The facts:** for every pair of canonical atoms (H2 tokens) over a common variable, Z3 is asked whether `p → q`, `q → p` and `p → ¬q` are valid. The encoding is `checkEquivalence`'s, so x/z are included (D-011).
  - Only a proof gives a fact. A timeout, an unknown result or opaque constructs give none.
  - The queries are capped: beyond the cap they are skipped, with a message. The result stays sound.
- **The facts become premises of both of H3's checks:**
  - Spot: `G(facts) ∧ A ⊆ B`;
  - HARM's finite-trace model: only atom valuations that satisfy the facts.

  Premises can only add implications, never remove one. Pairs of assertions linked only by a fact become candidates too.
- **Soundness:** the facts hold on every cycle of every trace HARM evaluates, and over 2-valued values (formal tools). SystemVerilog's own x semantics remain the documented gap of D-011.
- **`--dump-implications`:** a record whose claim needed facts gets an optional `"premises"` list (texts `p -> q`). The format version stays "1", because the field is additive.
- **Measurement before approval** (`H3b_PLAN.md`): on outputs with numeric ranges or FSM states, at least 16–22% of the survivors of `--reduce implies` are redundant; on Boolean-only outputs, none.

## D-028: vector indexing follows SystemVerilog (2026-10-07, H11c, approved by the user; fixes finding F-L4)
- **Ranges from the VCD:** HARM keeps each vector's declared range `[l:r]`.
  - Ascending ranges (`[1:10]`) are accepted. Before, the VCD parser stopped on them.
  - A VCD writes the value with the left declared index first, so the bits are read as before.
- **Selects:** on a variable with a declared range, `x[i]` and `x[a:b]` use SystemVerilog indices.
  - Index `i` is the bit `|i − r|` from the right.
  - An index outside the range is an error.
  - So is a part-select against the declared direction (`x[a:b]` needs `a ≥ b` when `l ≥ r`, and `a ≤ b` when `l < r`).
- **Unchanged:**
  - **Vectors declared `[n:0]`** behave as before, except that a reversed part-select (`x[0:3]`) is now an error, as in SystemVerilog. No test, example or baseline uses one.
  - **Variables without a declared range** (CSV traces, variables built in code) keep the old meaning: positions counted from the right from 0, in either order (`opeTests` pins this).
  - **A select on an expression** (not a variable) keeps positions.
- **Output:** a select keeps the indices it was written with (`BitSelector` source indices). SVA, PSL and Spot print them, so a mined assertion reads as the RTL.
- **`--generate-config --split-logic`** writes each bit with its declared index (`asc[1]`…`asc[10]`, `off[3]`…`off[10]`), no longer `0..size−1`.
- **Limits, documented (README):**
  - Packed multi-dimensional vectors are seen flattened by the VCD.
  - Bit-blasted vectors (one `$var` per bit) give no direction, so the highest index is taken as the MSB (as before). They get a declared range only when their indices are contiguous.
  - Verilator's unpacked-array elements (`mem[0] [7:0]`) are separate variables, as before.
- **Why:** H10's harm-coi writes SystemVerilog indices (the RTL's), so before D-028 its bit-select predicates on vectors not declared `[n:0]` were misread. AssertLLM2's `ethernet_smii_txrx` declares `[1:10]`.
- **Validation:** `VectorIndexTest` compares every select, every cycle, with the values Verilator prints for the same trace (`tests/input/h11c/gen.sh`). `h11c_vcd_ranges` checks that `[1:10]` and `[9:0]` mine the same assertions.

## D-029: fixtures and oracles independent of the Verilator version (2026-10-07, H11e, approved by the user; findings F-L6, F-L7, F-L8, F-L10)
- **Fixture stimulus:** the 7 fixture testbenches (`tests/input/coi/*`, `tests/input/h5/constructs`) draw their stimulus from `tests/input/stim.svh`, a xorshift32 written in SystemVerilog, instead of a simulator's `$urandom`.
  - Verilator 5.052's `$urandom` gives a different sequence from 5.031's for the same seed, so the committed traces could not be reproduced (F-L7).
  - The traces were regenerated once (Verilator 5.052) and now reproduce on any simulator. `h11e_stim_*` checks that Verilator and Icarus give the same stimulus.
- **The replay oracle** (`tests/oracle/verilator_replay.py`):
  - **Negation:** it negates a property consequent with `not`, not `!` (F-L6).
  - **End-of-simulation semantics:** it mines with `--trace-end sva` (D-016), the semantics a simulator uses at the end of a simulation, which Verilator 5.052 implements for `s_eventually` (F-L10).
  - **`s_eventually` controls:** Verilator 5.052 never fails `A |-> not (s_eventually P)`. These controls are checked by a monitor, validated on hand-labelled traces (`verilator_replay_monitor_selftest`).
- **The influence check** (`tests/coi/perturb.py`) compares only signals both traces have (F-L8).
- **What changed with the traces:**
  - Verilator 5.052 no longer dumps the loop variable `unnamedblk1::i`. It was removed from `h8/constructs_coi.json`'s unknown list (the same as harm-coi's output on the new trace).
  - H9's acceptance A2 needed a signal listed as unknown: `y_loop` (an output no cone uses) took that role in the hand-edited `h9/constructs_partial_coi.json`. The expected report is unchanged except for the name.
- **HARM is not changed.**

## D-030: `--check-dump-eval` file names and `index.json` (2026-10-08, H16, approved by the user; finding from trivergence's T12 A5 test)
- **The problem:** each checked assertion's CSV was named after its Spot text with every character outside `[A-Za-z0-9-_.+()[]#=>|:]` deleted. Different assertions overwrote each other's file without a warning (`x != y` and `x <= y`; `a && b`, `a & b` and a signal `ab`; `!a` and `a`; the same assertion in two contexts). A name over 255 bytes made HARM exit with code 1. No file could be mapped back to its assertion.
- **File names:** `<k>_<text>.csv`. `k` = 0, 1, 2, … is the order in which HARM checks the assertions in the run (contexts in order, `check` templates in configuration order); it makes the name unique. `<text>` is the old sanitized text cut to 100 bytes, only for people reading `ls`: it is not unique and not part of the contract. (The user chose this over `<k>.csv`.)
- **`index.json`** (version `1`) in the dump directory, written at the end of the run: `{"version": "1", "assertions": [{"file": "<k>_<text>.csv", "context": "<name>", "spot": "<Spot-LTL text>", "sva": "<SVA text>"}, …]}`, in check order. It is the contract: consumers find an assertion's file through it.
- **Never an exit:** a file that cannot be opened gives a warning and `"file": null` in the index; the run continues.
- **Rows:** every row has the five header fields `t, Ant, Shift, Con, Ass`. v3 wrote Shift, Con, Ass and the newline only for assertions with a shift; for `G(a -> b)` the whole file was one line. For an assertion without a shift, Shift is the evaluator's shift (0). Rows of assertions with a shift are unchanged.
- **Unchanged:** the dump directory is still removed and re-created; stdout, the mined assertions and every other output are byte-identical (the H0 baselines).
- **Not decided here:** an SVA-style reset for check mode (`disable iff`), recorded in PLAN §H16.

## D-031: the proposition table, `prop-table` v1 (2026-10-08, H15, approved by the user: Q1–Q3 (a))
- **Purpose:** `--dump-prop-table <file>` gives another miner (the miner portfolio's SAT miner, `~/miner-portfolio` S1) HARM's propositions and their values, so it needs neither a VCD reader nor an evaluator, and inherits D-005 (sampling), D-011 (x/z) and D-028 (vector indices).
- **Which propositions:** per context, every `<prop>` and every proposition HARM expands from a `<numeric>` with plain domains, as loaded with the configuration, in configuration order. One entry per text (Spot LTL, `prop2String`), with the union of its domains. `origin` is looked up by text, as `--dump-assertion-info` does (D-022: expansions have none).
- **Bracketed numerics (Q1 a):** `loc="[dt]"`/`"[n]"` numerics are clustered by the decision tree during mining, per template, permutation and tree depth; they have no per-context propositions. They are listed in `unexpanded_numerics` (text, domains) only. A configuration that wants them in the table writes a plain domain.
- **When (Q2 a):** written after the configuration is read, before mining; HARM then runs as usual. Its other output does not change (checked: stdout with and without the option).
- **Format (Q3 a):** one JSON object: `format` `"prop-table"`, `version` `"1"`, `harm`, `sampling` (`{"input": "vcd", "clock", "edge": "posedge", "values": "preponed"}` or `{"input": "csv"}`), `length`, `traces` (`file`, `first`, `last`, in merge order; files that read as empty are not listed), `segments` (the trace's cuts as inclusive `[first, last]`: file ends and, with `--reset`, reset-interval ends), `contexts` (`name`, `propositions` [`id`, `text`, `domains`, `source` `prop`|`numeric`, `numeric`, `origin`, `values`], `unexpanded_numerics`). `values` is a string of `length` characters, `1` true, `0` false. A packed body can be a v2 if sizes call for it (1 byte per cycle and proposition).
- **Domains** are written as in `loc`: `a`, `c`, `ac`, `dt`, or the domain number; sorted in that order.
- **Not changed:** the order of `--vcd-dir`/`--csv-dir` files (unspecified, the directory's order); `traces` records it.

## D-032: bitwise operators on `bool` operands (2026-10-09, H17, approved by the user: option (a))
- **The problem:** `&`, `|`, `^`, `~` were `numeric` rules only, and a CSV `bool` variable is a `boolean`: `a ^ b` was a parse error (found in H16). SystemVerilog accepts them on 1-bit values. VCD signals are `logic` and already worked.
- **How:** a `bool` variable is a `numeric` **only as an operand of a bitwise operator**. When HARM types the variables of an expression (`addTypeToExp`), a `bool` variable whose nearest non-blank neighbour is `^`, `~` (before it) or a single `&`/`|` (not `&&`, `||`, `|->`, `|=>`), and which does not follow `!`, is written `«x,bit»` instead of `«x,bool»`; the lexer token `BIT_VARIABLE` is a `logicAtom` only. No parse that works today can change: the grammar has no new ambiguity.
  - Letting every `bool` be a `numeric` would have made parses that work today ambiguous (`a == b`, `$past(a)`, concatenations) and changed their trees.
  - A first implementation used a semantic predicate in the grammar that looked at the neighbouring tokens. ANTLR ignores a predicate during prediction once the decision has consumed a token, so `(a)`, `!(a)`, `(a) == b` became parse errors (caught by `Z3EquivalenceTest`'s hand-labelled pairs). It was replaced by the token above; `BitwiseBoolTest` now covers those forms.
- **Semantics:** the `bool` is a 1-bit unsigned value (new cast node `BoolToLogic`), zero-extended against wider operands; the result is true where it has a known 1 bit (D-011). Z3 encodes it as a 1-bit value that is never x/z.
- **Printing:** the cast prints as its operand: `a ^ b` prints `a ^ b` (option (a); option (b), the concatenation's `a ? 1'b1 : 1'b0`, was unreadable). Concatenations keep their printing.
- **Not accepted (errors, as before):** a parenthesised or negated operand: `(a && b) ^ c`, `(a) ^ b`, `!a ^ b`. HARM's `!` binds looser than `^` (`!p ^ q` with `logic` operands reads `!(p ^ q)`; SystemVerilog reads `(!p) ^ q`): accepting `!a ^ b` would have given the same reading to `bool`s.
- **Templates:** there `&` and `|` are temporal operators (`G(a & b -> c)` is `{a & b}`, unchanged), so in a template only `^` and `~` mark a `bool` variable (`addTypeToExp(..., inTemplate)`).
- **The parsers** (the proposition parser and the temporal parser, which imports it) were regenerated with ANTLR 4.13.2 (the runtime's version; the tool jar from Maven Central, SHA-1 `7df86c34…` checked against Maven's). Regenerating the unchanged grammars first reproduced the committed files byte for byte.

## D-033: trace directories in path order (2026-10-09, H17, approved by the user)
- `--vcd-dir` and `--csv-dir` sort the files by path (byte order) before reading them, as `--fd` does before its fixed shuffle (D-001). The directory's order is unspecified and differed between machines (on the Mac, `examples/multiTrace` was read `counter5, counter4, counter1, …`).
- **Effect:** the cycle numbering of a multi-trace run (the merged trace, `--dump-prop-table`'s `traces` and `segments`, failing sub-traces) is the same on every machine. The mined assertions did not depend on the order: the `multiTrace`, `process` and `process_trace_end_sva` baselines are byte-identical.

## D-034: operators bind and convert as in C and SystemVerilog (2026-10-09, H18, approved by the user: option A, Q1 (b), Q2 (a), Q3 (a), the split H18/H19/H20)
- **The reference:** IEEE Std 1800-2017 Table 11-2 (precedence), §11.4.4 (comparisons give 0 or 1), §11.4.7 (`!`), §11.8.1; C11 §6.5 (N1570). An audit of 1,154 expressions against Icarus Verilog (cross-checked with the standard) found the deviations below (`doc/plan/H18_PLAN.md`).
- **Precedence**, from the tightest: selects; unary `! ~ - +`; `* /`; `+ -`; `<< >>` (one level); `< <= > >= inside`; `== != === !==` (one level); `&`; `^`; `|`; `&&`; `||`; `?:`. All binary operators are left-associative.
- **Changes of meaning** (hand-written text; nothing in `examples/` or `tests/` was affected, and HARM's printed output never wrote these forms unbracketed):
  - `!x == y` is `(!x) == y` (was `!(x == y)`); likewise `!x < y`, `!p ^ q`, `!v + 1`;
  - `x & y == y` is `x & (y == y)` (was `(x & y) == y`); likewise `^` and `|`;
  - `(x > 0) == y` compares numbers, the comparison as 0 or 1 (was `(x > 0) == (y != 0)`);
  - `x >> y << k` is `(x >> y) << k`; Boolean `a != b == c` is `(a != b) == c`.
- **Newly accepted:** comparisons as numbers (`(a < b) + 1`, `x < y < z`), unary `-` and `+`, `x-1` without blanks (number tokens no longer carry a sign; a negative literal is a unary minus folded into the constant), `bool` operands of arithmetic, shifts and comparisons (1-bit unsigned), a bracketed Boolean as a number (`(a && b) ^ c`), `!a ^ b` (`(!a) ^ b`; H17 had to reject it).
- **x/z (Q1 (b)):** a numeric `!v` is 2-valued, 1 where `v` has no known 1 bit, as HARM's `!` always was (no new 4-valued logic). A comparison with an x/z operand is false (D-011), so its 1-bit value is 0.
- **How:** comparisons and `!` are numeric operators in `proposition.g4`; their 1-bit result is the comparison wrapped in `BoolToLogic` (D-032). When a number is used as a Boolean, the handler gives back the original Boolean, so every expression that parsed before keeps its tree (`!a`, `!(x == y)`, `a == b`, `(c ? x > 0 : y > 0)`) and Boolean expressions are not slowed down. The order of the `boolean` rule's alternatives resolves the ambiguities deliberately (comments in the grammar); no semantic predicates (H17's lesson). A `bool` variable becomes a 1-bit number when it is the operand of a numeric operator (`addTypeToExp`, generalising D-032's marking); template arrows and, in templates, `&` and `|` do not count. New nodes `IntNeg`, `LogicNeg`, `FloatNeg` (unary minus); Z3 encodes `IntNeg` exactly and the others opaquely.
- **Printing** follows the same table, so every printed proposition re-parses to the same values and text: a right operand of the same level keeps its brackets (`x - (y - k)`, `x / (y * k)`, `x >> (y << k)`); a select brackets a non-primary operand (`(x + y)[1:0]`); `inside` is relational (`!(q inside {1,5})`) and prints its values as written, without a trailing blank; a unary minus over a negation prints `-(-x)`.
- **Not decided here:** evaluation findings E1–E6 and literal printing R4 (H19), missing operators L4 (H20). Each H19 difference is listed in `tests/oracle/fixture_h18/cases.txt`.
