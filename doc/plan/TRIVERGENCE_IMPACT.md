# HARM → trivergence: impact on trivergence's plan and code

*Maintained in the HARM repo, updated whenever a HARM milestone changes something trivergence uses or could use. Last update: 2026-10-06 (H1d, H8, H9, H10, H1b and H3b on `dev`).*

**Who reads this:** whoever develops trivergence (on the Linux machine). Trivergence is never modified from the HARM development machine; this file is the hand-off.

**How to use it:**
- §1 tells you which HARM commit to pin and what it brings.
- §2 has one entry per HARM milestone, with the concrete trivergence changes (files, PLAN milestones) and how to verify them.
- §3 lists proposed changes to trivergence's `docs/plan/PLAN.md` that follow from the HARM plan. They need the trivergence lead's approval and a `DECISIONS.md` entry there.

Each item is marked **[required]** (trivergence breaks or gives wrong results without it), **[recommended]**, or **[optional]**.

Trivergence references below are as of trivergence commit `37b10e2` (2026-10-05).

---

## 1. HARM versions

| HARM milestone | Commit / branch | Pushed? | Trivergence pins today |
|---|---|---|---|
| (baseline) | `a8c302b` | yes | **this one** (`HARM_VERSION` in `triad_mining/harm.py`; `HARM_COMMIT` in `code/docker/Dockerfile.toolchain`, in 2 places) |
| H0 | `dev` @ `abe060dc4a41098a515108aa30a53a913698a707` | yes | — |
| H1 | `dev` @ `778c43b6044bbb53dbfd372a9f1aec629c725eb5` | yes | — |
| H2 | `dev` @ `19d7ed2e6ef8a708965d87ebf28810b8c15cb1cf` | yes | — |
| H4 | `dev` @ `ce7628a5219c1509ad49e104bad570b856bcf3bc` | yes | — |
| H6 | `dev` @ `1e3b6f6175409ae8d103ceb95a466f864cd0bc78` | yes | — |
| H3 | `dev` @ `53a4d8fbaf45142eed529e427d061beb20dfa499` | yes | — |
| H1c | `dev` @ `745bc9f0a852027fb1f42160354aaabfc7544b8f` | yes | — |
| H7 | `dev` @ `942b583a15eb4b55c4674127a41c331102dc216f` | yes | — |
| H5 | `dev` @ `927b856e7a9639627a026ab4530363e40f954804` | yes | — |
| H1d | `dev` @ `b608a90046d630c8e9ff30d2b3a51c8290dd4db4` | yes | — |
| H8 | `dev` @ `366374a06511672e5c3405cd3ea64e8beb6793f3` | yes | — |
| H9 | `dev` @ `28e606d4dacf5f73a76cd3a1dea7379196e912f2` | yes | — |
| H10 | `dev` @ `63b5ff84ea3b987bc848222ef2dc174f03dd0dd2` | yes | — |
| H1b | `dev` @ `165328a7208875a0659d409b857a828f08710ea6` | yes | — |
| H3b | `dev` @ `244b4f83a18e0eb1fc8dfede9c1533bd798678f2` | yes | — |

**Branches:**
- HARM `main` stays the stable public version until the whole HARM plan is done (after H11).
- New work lands on HARM **`dev`**, one merge per reviewed milestone.

**Rule:** pin only commits that are on HARM `dev` (or `main`), never a milestone branch. Update `HARM_VERSION` and both `HARM_COMMIT` arguments together, and re-run `make e2e`. The Dockerfile's `git clone` + `git checkout <commit>` works for `dev` commits as is.

---

## 2. Per-milestone impact

### H0: deterministic output and toolchain (on `dev`)
What changed in HARM: see `doc/plan/DECISIONS.md` (D-001, D-010).
- HARM's output (order, `--max-ass` cut, `--find-min-subset`) is now identical across runs and thread counts.
- Ranking ties are broken by assertion text.
- `--fd` faulty traces are sorted and shuffled with a fixed seed.
- The install scripts honour `CC`/`CXX` and build Boost with `regex` only.

Impact on trivergence:
1. **[required] Docker build check.**
   - What to check: `Dockerfile.toolchain` runs `sh ./install_all.sh` with the default `cc`/`c++` (gcc on Ubuntu 24.04), then `cmake` with the same compiler. That combination is consistent and should work unchanged.
   - What changed in the build: Boost now builds only `libboost_regex` (`COPY .../boost/lib` still works) and with `toolset=gcc` set explicitly.
   - Verify: build the image at the new commit and run `harm --help` inside it. **This has not been tested on Linux yet.**
2. **[recommended] Remove the determinism workarounds in `HarmMiner.mine`** (`code/packages/triad-mining/src/triad_mining/harm.py`):
   - `--max-threads 1` can become N threads, which is faster on the 32–64-core server;
   - the comment "multi-threaded HARM picks a different top --max-ass set on every run" no longer applies.
3. **[recommended] Revisit the "simplest first (length, text)" top-50 selection** that replaced HARM's ranking (M0_REPORT #31; flagged there "to revisit in A3/B3"):
   - **Option a, use HARM's ranking:** pass `--max-ass 50` and keep HARM's order.
   - **Option b, keep the current rule:** keep it as an explicit, documented trivergence policy.

   Either way, it's a trivergence decision, worth a `DECISIONS.md` entry.
4. **Expected effect of bumping to H0 with no other change:**
   - the *set* of mined assertions is unchanged; H0 only changed order and `--find-min-subset`, which trivergence does not use;
   - since the adapter selects by (length, text), `make e2e` should give **identical candidates, verdicts, triage and kills**. If it doesn't, report it back; that would be a HARM regression.
5. **[optional]** HARM now has its own regression suite (`ctest -L regression`, `ctest -L determinism`). Running it once on the Linux server would close H0's pending Linux validation.

### H1: proposition and SVA language fixes (on `dev`)
What changed in HARM: `doc/plan/H1_PLAN.md`, DECISIONS D-002 and D-011, README "SystemVerilog Syntax in Propositions".

| Adapter workaround (trivergence `triad_mining/harm.py`) | M0 item | After H1 |
|---|---|---|
| `to_harm_expr`: decimal/hex constants → sized binary | #7 | **Remove.** HARM accepts `8'd9`, `4'hA`, `'h1F` (oracle-tested against iverilog) |
| `to_harm_expr`: `'0` → `0` | #29 | **Remove.** HARM accepts `'0 '1 'x 'z` next to a sized operand |
| `harm_incompatibility`: drops concatenation, `?:`, unsized literals, `===` | #29 | **Remove, or keep only as a safety net.** All four are supported. Exceptions: a ternary used as an operand must be parenthesized (as in SV), and concatenation needs ≥ 2 items |
| `.` → `::` in proposition hierarchy | — | **Remove.** `u_core.state` is accepted |
| Invariants written as `G({..&&..} \|-> P0)` | #8 | **Use `G(P0)`.** HARM prints it back as `G(p)` / `always (p)` |
| `normalize_harm_sva`: `true` → `1'b1`, `\|-> nexttime` → `\|=>`, `::` → `.` | #9 | **Remove.** HARM's `--sva` output already has these forms. HARM checked trivergence's own A6 cases: all 9 supported inputs print exactly trivergence's expected `out`. The 3 "unsupported" ones now print as valid SV (`a \|-> ##2 b`, `a \|-> s_eventually b`, `a until b`). **The A6 fixture `normalize_cases.yaml` will need new inputs** (golden fixture: needs approval) |
| One bad proposition aborts the run | #29 | **Use `--skip-invalid-props`** and log the warnings (`Invalid proposition skipped: '<exp>'`) |

**[required] Two behaviour changes to know before bumping:**
1. **F10, a bug in the current pin `a8c302b`:** propositions with a **bit selection** (`r[7:4]`) were evaluated and printed with swapped bounds in every mined assertion (`r[4:7]`). Any trivergence mining run whose hints contained bit selections was affected. Re-run those after bumping.
2. **SVA text changes** (D-002): if any trivergence code or fixture matches HARM's raw `--sva` text, expect `|=>`, `##n`, `1'b1`, `.` and `s_eventually`.

**[recommended] D-011 (decided in HARM, H1b: documented, no SV-semantics option): x/z semantics.**
- **The rule:** in HARM, x/z counts as false wherever a value becomes a truth value (comparisons, values used as conditions), and `!` then makes it true. So a mined `!(a == b)` can hold in HARM but fail in a simulator on cycles where `a` has x/z. In the other direction, `a != c` with a known differing bit is false in HARM but true in SV. See the README table, "x and z values".
- **M0 #33** (`!(sda == 1'b0)` on an inout net) *may* be this case if the VCD records `z` for the released `sda`. M0 attributes it to inout sampling (#24); worth checking whether the trace has `z` there.
- **Triage:** treat "HARM holds, simulator fails" on cycles with x/z as this known difference, not as an RTL bug.
- **In hints:** prefer `===`/`!==` when x/z matter (`sda !== 1'b0`). They are exact in both HARM and SV.
- **Traces:** Verilator traces are 2-state, so the difference arises only where x/z do appear (e.g. tri-state/inout nets, or 4-state simulators).

**[recommended]** After bumping, re-baseline `test_harm_adapter.py` A5/A6 and `tools/test_harm.py` A11 (with approval). `make e2e` should give the same candidate *set* where no bit selection was involved. Candidate text changes (SVA tokens) are expected.

**[optional]** `tests/oracle/verilator_replay.py` in HARM replays HARM's assertions in Verilator. Trivergence's trace view does the same thing with its own harness, so the two results can be cross-checked.

### H2: proposition equivalence with Z3 (on `dev`)
What changed in HARM: `doc/plan/H2_PLAN.md`, DECISIONS D-003. HARM now has `--reduce equiv`.
1. **[required] Docker image.**
   - `install_all.sh` now also builds **Z3 4.13.4** from source (several minutes) into `third_party/z3`. CMake requires it unless `-DHARM_WITH_Z3=OFF`.
   - The `harm-build` stage needs nothing new: Z3 is built with the stage's own compiler, and its CMake build needs only `build-essential` and Python. But the runtime stage must also copy `third_party/z3/lib` into `/opt/harm/lib`, next to Spot, ANTLR and Boost, or `harm` will not start.
2. **[recommended] Use `--reduce equiv` in `HarmMiner.mine`.**
   - It merges mined candidates that differ only in how a proposition is written. That matters once the LLM hints (`intent_to_hints`) and RTL-harvested predicates (H10) overlap.
   - It is sound under HARM's x/z semantics, so it never merges `!=` with `!(==)`.
   - It costs one Z3 call per pair of distinct propositions over the same variables.
3. **[optional]** `expression::smt::checkEquivalence` can decide equivalence of two HARM propositions in C++ (exact 4-valued semantics). It isn't exposed on the command line; tell HARM if trivergence needs it as a tool, e.g. to deduplicate hints before mining.

### H3: semantic redundancy reduction with Spot (on `dev`)
- **New options:**
  - `--reduce implies`, which includes `equiv`;
  - `--keep stronger|weaker|ranked`;
  - `--dump-implications <json>`: `{"version": "1", "implications": [{"context", "dropped", "kept": [...], "relation": "implied|implies|equivalent"}]}`.
- **[recommended]** Use them in trivergence stage 5 (suite selection) as a cheap, design-independent first pass before `FormalOracle.implies` (T8a). HARM's implication is *logical*, with no design and no reset, so it never needs a solver run on the RTL.
- **What "implies" means** (D-004 as amended): A ⇒ B is claimed only if it holds both over infinite words (what SVA and formal tools see) and on every finite trace as HARM evaluates it.
  - Dropping B is therefore safe for both trivergence's simulator checks and its formal oracle.
  - It is incomplete: some true implications are not found. Never treat "not dropped" as "not implied".
- **Limits that matter to trivergence:**
  - Only safety assertions `G(antecedent -> consequent)` with a fixed-length antecedent are reduced.
  - Assertions spanning more than 10 cycles are always kept.
  - Implications between atoms (`x > 5 ⇒ x > 3`) are not used (H3b).
- **[recommended] Prefer `--keep stronger`** (the default) for suite selection. `ranked` keeps the better-scored side, which can be the weaker assertion.
- **Semantics (D-015):** HARM judges mined assertions as a simulator does: weak at the end of the trace. Its reduction requires the implication both on finite traces and over infinite words.
  - **Corrected in H1c:** an earlier version of this note said to recheck mined liveness assertions. That was overstated: trivergence's adapter already discards every mined line with `eventually`, `s_eventually`, `until` or `nexttime` (`_UNSUPPORTED` in `triad_mining/harm.py`), so they never reach its simulator or oracles.
- **[optional]** The `kept` list lets trivergence show, for each dropped candidate, which kept assertion covers it: useful in triage reports.

### H1c: end-of-trace semantics and SVA brackets (on `dev`)
- **SVA printing fix (affects every user of `--sva`):** HARM now brackets SVA output by SVA's operator precedence. Before, `(b W c) && X X F d` was printed `b until c and nexttime nexttime s_eventually d`, which SystemVerilog reads differently. HARM's existing baselines are unchanged, because the bug needs `and`/`or` combined with `until` or `s_eventually`.
  - **[optional]** Trivergence's adapter rejects `until` and `s_eventually` anyway, so it is not affected today. If it ever accepts them, it needs this fix.
- **`--trace-end sva`:** mined assertions are judged at the end of each trace as a SystemVerilog simulator judges them. Pending `s_eventually`, `not nexttime` and `not (… until …)` fail; weak operators hold. The default (`harm`) is unchanged.
  - **[optional]** Pass `--trace-end sva` if the adapter starts accepting liveness or `not nexttime` lines. It costs nothing for the safety assertions trivergence uses today.
- **`--dump-assertion-info`** has a new top-level field, `"traceEnd": "harm"|"sva"`. It is additive; existing readers are unaffected.

### H4: COI contract (on `dev`)
- **Contract:** `doc/schemas/coi.v1.json`, plus the rules in `tests/coi/check_coi.py`.
  - **Names** are relative to `meta.vcd_scope`, with `::` between sub-scopes: exactly what HARM sees with `--vcd-ss <scope> --vcd-r <recursion>`. Trivergence's adapter passes `--vcd-ss traces.scope --vcd-r=16`, so a `coi.json` for trivergence must record the same scope and recursion.
  - **Depth** counts register crossings (D-005), measured as HARM samples traces: the values just before each rising edge, which is the Preponed-region view of SVA (VCD dumps record the end of the time step). So a register is one cycle behind its inputs, i.e. `G(a -> X q)`, and HARM's verdicts match what trivergence's simulator assertions see.
- **[optional]** The fixture corpus `tests/input/coi/` (6 designs with traces and hand-written cones) can serve as small sanity designs for trivergence's oracle and COI work (T9).

### H6: COI rank mode (on `dev`)
- **[recommended] In `hints_to_xml`,** for designs with a `coi.json`:
  - write `<coi file="…" mode="rank"/>` (path relative to the hints XML);
  - add `origin="spec"` (or `llm`) to each proposition;
  - add a sort metric such as `<sort exp="coiDepthFit"/>` next to the existing frequency sort.

  Mined candidates are then ranked by structural plausibility as well as by trace frequency, with the LLM hints still the source of the propositions.
- **[recommended] Read `--dump-assertion-info <json>`** instead of parsing HARM's text output. It gives every kept assertion with its contingency counts, final score, `coiFrac`/`coiDepthFit`/`coiUnknown`, and per proposition its text, offset, variables and `origin`. This is the per-proposition provenance that the M0 #27 fix (B4) needs: a mined candidate whose antecedent propositions are spec-derived *and* structurally plausible is a different case from one HARM assembled from unrelated signals.
- **[optional] B3 ablation:** the same hints with and without `<coi>`, comparing the ranking of known-good assertions.
- **Note:** a `coi.json` must use the same scope and recursion as the adapter's `--vcd-ss`/`--vcd-r` (see H4). HARM refuses a coi file naming signals that are not in the trace, and warns if the scope differs.

### H7: COI filter mode (on `dev`)
- `<coi file="…" mode="filter"/>` never tries antecedent propositions outside the consequent's cone.
  - On the fixtures, it cuts permutations by 48–90% and the output by 39–82%.
  - `--dump-assertion-info` reports the search space under `coiFilter`.
- **[optional] Use it only as a baseline** (GoldMine-style) in Paper A, never in the method's triage: it assumes the RTL is correct, and HARM warns about this.
- **Not "rank mode minus out-of-cone assertions"** for decision-tree templates (D-018). If Paper A compares rank and filter, it should state this. Filter mode's guarantee is the output of rank mode on per-consequent restricted configurations.

### H5: `harm-coi` generator (on `dev`)
- **What it is:** `tools/harm-coi/`, a Python package (pyslang 12.0.0, D-006). It reads the RTL and writes the `coi.json` that rank mode (H6) and filter mode (H7) read. Until now that file was written by hand.
  ```
  harm-coi --top <top> --files <rtl>.sv... --vcd-scope <traces.scope> --vcd-recursion 16 \
           --vcd <trace.vcd> [--clock clk] -o coi.json
  ```
- **Dependencies:**
  - Python ≥ 3.11 and `pyslang==12.0.0`. Trivergence already pins this exact version (`code/packages/openfpv/pyproject.toml`), and its other packages accept it (`pyslang>=7`). It can be installed into the same environment: `pip install <harm>/tools/harm-coi`.
  - No yosys, no C++ build.
- **[required, when trivergence uses `coi.json`] Pass `--vcd` and the adapter's scope and recursion** (`--vcd-r=16`, `triad_mining/harm.py:188`).
  - `triad_sim/verilator.py` traces with `--trace`, without `--trace-structs`, so packed structs are dumped as single vectors.
  - With `--vcd`, harm-coi names them as the trace does, as the union of the fields (D-019). Without it, it would write field names (`c::mode`) that HARM rejects ("names signals that are not in the trace").
- **[recommended] Read `unknown`.**
  - Signals harm-coi cannot model go there instead of being dropped: latches, other clock domains, `inout`, unsupported statements, and trace signals without an RTL source, such as loop variables Verilator dumps.
  - So does everything whose cone reaches one of them within `max_depth`.
  - HARM treats `unknown` as in every cone (D-017), so a design with many unknowns gets little pruning in filter mode and neutral `coiUnknown` metrics in rank mode. `-v` prints the reason for each.
- **[recommended] Clock:** pass `--clock` for designs with several clocks; harm-coi refuses to guess. Registers on another clock are `unknown`.
- **[optional] T9 cross-check:** `tests/coi/xcheck_yosys.py` compares harm-coi's signal-level cones with a yosys netlist (`read_slang`, yosys ≥ 0.67). It could be pointed at OpenFPV's AIGER-level COI on shared designs.
- **Answer to §4, "where should the generator run":** it needs only the RTL file list, top, scope and a trace. It can run once per design in the benchmark loaders (F4), or in stage 3 next to the simulation that produces the trace. It takes well under a second on the fixtures; large designs are untested.

### H1d: printing fixes (on `dev`)
- **SVA (`--sva`, `--sva-assert`):** HARM's `->` with an antecedent longer than one cycle is now printed with the meaning HARM mined (D-021):
  - `G({a ##1 b} -> X c)` → `a ##1 b |-> c`. It was `a ##1 b |=> c`, which puts `c` a cycle late.
  - Other forms: `$past(c, k)`, or `(…) implies …`.
  - **[none required]** Trivergence's templates (`|->` with decision trees, single-cycle `G(p0 -> p1)`) print exactly as before.
  - **[optional]** If a template like `G({..##1..} -> X P0)` is ever added, its SVA is now correct. It may contain `$past` or `implies`: check that the adapter and the formal tools accept them. Verilator accepts `$past`; `implies` is IEEE 1800, and tool support varies.
- **Spot-LTL text** (the default output and the `text` field of `--dump-assertion-info`): `X(a && b)` keeps its brackets. It was printed `Xa && b`.
  - **[optional]** Only relevant if trivergence parses the Spot text; it reads `--sva`.

### H3b: atom-implication premises (on `dev`)
- **`--atom-premises`** (with `--reduce implies`) also drops assertions implied through facts between comparisons, proved with Z3 under HARM's semantics:
  - `G(cnt > 4'd8 -> b)` drops `G(cnt > 4'd9 -> b)`;
  - mutually exclusive FSM states are used too.
  - On `sub_platform1k` (the camellia design) the output goes from 89 to 69 assertions; the reduction takes 5.3 s instead of 0.9 s.
- **[optional] Stage 5 / suite selection:** useful once trivergence mines with numeric candidates or H10's RTL predicates. With Boolean-only LLM hints it changes nothing (H3b measurement).
  - `--dump-implications` records then carry `premises`, the facts the claim used.
- **[none required]** Without the option, `--reduce implies` is unchanged.

### H8: depth-aware COI filter (on `dev`)
- `<coi … mode="filter" depth="bounded|exact"/>` also uses the depths of the cone (D-020).
  - **Example:** `y` gets `a` at depths 0 and 2. `G(a -> X y)` is kept by `bounded` and pruned by `exact`; `G(a -> X X X y)` is pruned by both.
  - On the fixtures, `exact` cuts the output by a further 26–46% below H7's filter mode (`depth="any"`), and `bounded` by 5–25% (VALIDATION, H8).
- **[optional] The A3 baseline:** if Paper A uses "HARM + COI filter" as the GoldMine-style structural baseline, `depth="exact"` is the closest to GoldMine's cycle-accurate cones. Use the same caveat as H7: it assumes the RTL is correct.
- **[none required]** Rank mode is unchanged, except for one fix. `coiDepthFit` now places the consequent of `->` at the start of a multi-cycle antecedent, as HARM evaluates it (H8 F6). Trivergence's templates use `|->` and single-cycle `->`, which are not affected.
- **SVA printing of `->` with a multi-cycle antecedent (H8 F7): fixed in H1d** (see the H1d entry).

### H9: out-of-cone report (on `dev`)
- **`--dump-coi-report <file.json>`** lists, for each consequent proposition of a context with `<coi>`, the antecedent propositions whose signals cannot influence it, with their `origin` and the signals outside the cone (D-022). It is computed from the hints and `coi.json`, before mining, and works in rank mode.
  - **Example:** in `multipath`, `y`'s cone is `{a, r1, r2}`. A hint proposition `a && b` with `origin="spec"` is reported against `y` with `outside: ["b"]`.
- **[recommended] B4 triage:** after `hints_to_xml` writes the hints with `origin="spec"` (H6) and a `<coi>`, add `--dump-coi-report` to the HARM call and read it.
  - A spec proposition in `outOfCone` of a spec consequent is a "spec says A influences B, RTL says it cannot" disagreement, independent of what HARM mines.
  - `unknown` entries are not disagreements: the cone file could not decide them (e.g. signals harm-coi marked unknown).
- **[none required]** Without the option, nothing changes.

### H10: RTL predicate harvesting (on `dev`)
- **`harm-coi --predicates`** adds the RTL's own predicates to `coi.json`, in HARM's syntax with `origin: "rtl"` (D-023):
  - conditions, case labels, FSM (enum) states, comparisons with constants, reset values;
  - e.g. `state == 2'd1`, `cnt == 4'd9`, `!prio`.
- **`harm-coi --emit-config <cfg.xml>`** writes a ready-to-run HARM configuration from them.
- **[optional] B3, the "RTL hints" arm of the ablation** (vanilla / LLM hints / RTL hints / both):
  - run `--emit-config` per design;
  - for the "both" arm, append the predicates to `hints_to_xml`'s propositions; their `origin` keeps the two sources apart in `--dump-assertion-info`.
  - With `--reduce equiv`, LLM and RTL propositions that are equivalent are merged (H2).
- **[optional] B4:** a spec proposition that matches no RTL predicate is not evidence of a bug by itself. Predicates on invisible signals are dropped.

### H11: evaluation, `--version`, Docker (on `dev`; release to `main` deferred)
- **`harm --version`** prints `HARM <git describe>` (e.g. `v3-140-g1234abc`). trivergence can record it with every mining run, to know which HARM produced a result.
- **The Linux checklist `eval/LINUX.md`** is run on trivergence's machine:
  - the full `ctest`;
  - the Docker image;
  - the evaluation on about 10 AssertLLM2 designs, through `eval/run_eval.py` with a manifest written from `eval/manifests/assertllm2.template.json`. It can reuse trivergence's benchmark loaders (F4) and its Verilator traces (`triad_sim`).
- **The Docker image** (`docker/build.sh [ref]`, default `dev`) contains HARM with Z3, harm-coi, Verilator and Icarus. It can be trivergence's way to pin a HARM build.
- **Measured costs that matter for the pipeline** (macOS, `eval/results/macos-fixtures`):
  - `--reduce implies` and `--atom-premises` grow with the square of the number of assertions. On 1,500–4,400 assertions they take minutes (`structs` C2 1,214 s; `constructs` C2 over 30 minutes).
  - trivergence's top-50 selection (M0 #31) keeps the inputs small. If trivergence reduces whole mining outputs, it should budget for this, or reduce after the selection.
- **`main` is unchanged** until the user releases: trivergence should pin `dev` (or a commit) meanwhile.

### H14: documentation and the v4 report (on `ms/H14-v4-report`)
- **No change to anything trivergence uses:** no code, option or output format changed.
- **Useful to read:** `doc/MIGRATING_v3_to_v4.md` lists every output change since v3 (what trivergence's adapter rewrote: `true`, `::`, `nexttime`); the report (`doc/report/`, `make -C doc/report`) explains the reduction and COI semantics, with the decision behind each.

### H16: `--check-dump-eval` file names (on `dev`; D-030)
- **The format changed** (trivergence's T12 A5 test reads these files):
  - files are named `<k>_<text>.csv`, `k` the order in which HARM checks the assertions; `<text>` is readable but not unique: **do not derive names from assertion text any more**;
  - `index.json` in the dump directory maps every file to its `context` and its exact `spot` and `sva` text. A5 should look an assertion up there (by its SVA text, or by its position among the `check` templates);
  - every row has `t, Ant, Shift, Con, Ass`. For assertions without a shift (`G(a -> b)`), v3 wrote only `t` and `Ant`, all on one line: any workaround for that can go;
  - a long assertion no longer stops HARM (it exited with code 1 over 255 bytes of name), and no file is overwritten.
- **Not changed:** check mode still evaluates attempts lying inside a reset interval, which SVA `disable iff` would skip; trivergence keeps its post-processing for that (an SVA-style reset is recorded in PLAN §H16, undecided).

### H15: the proposition table (on `dev`; D-031)
- **No change trivergence needs.** `--dump-prop-table <file>` is new and opt-in; nothing else in HARM's output changes.
- **What it could use:** every proposition of a context (hint propositions, `origin`, numeric expansions) with its value at every sampled cycle, plus the trace's files and reset segments (`prop-table` v1, README). trivergence could read propositions' truth values per cycle from it instead of evaluating them itself, with HARM's x/z rule (D-011). The consumer it was made for is the miner portfolio's SAT miner (`~/miner-portfolio`, S1).

### H17: findings left open by H15/H16 (on `dev`; D-032, D-033)
- **Bitwise operators on CSV `bool`s** (D-032): hints written as `a ^ b`, `~a & c` over `bool` columns now parse (they stopped HARM before). VCD signals are `logic` and were never affected. In templates, `&` and `|` remain temporal.
- **Trace directories in path order** (D-033): a multi-trace run (`--vcd-dir`/`--csv-dir`) numbers its cycles the same way on every machine. Mined assertions are unchanged.
- **Float `<numeric>` exclusions** (`...,2E`) now exclude the value; nothing changes without a float exclusion.

### H18: operators as in C and SystemVerilog (on `ms/H18-not-precedence`; D-034)
- **Hints are now read as C and SystemVerilog read them:** `!x == y` is `(!x) == y`; `x & y == y` is `x & (y == y)`; `(x > 0) == y` compares numbers. Before, HARM read `!(x == y)`, `(x & y) == y`, `(x > 0) == (y != 0)`: an LLM-written hint in C/SV style could have meant something else to HARM. Hints written with explicit brackets are unaffected.
- **Newly accepted in hints:** `x-1` without blanks, unary minus, comparisons as numbers, `bool` columns in arithmetic.
- **HARM's printed propositions re-parse to themselves** (before, `x - (y - k)` printed as `x - y - k`, and `!(q inside {..})` as `!q inside {..}`, which SystemVerilog reads differently): SVA trivergence takes from HARM is now faithful in these cases.
- **Not yet (H19):** shifts by at least the width stop HARM; signed/unsigned mixing follows C for `logic`.

---

## 3. Proposed changes to trivergence's `docs/plan/PLAN.md`
These are suggestions; the trivergence lead decides them, with a `DECISIONS.md` entry each.

| Trivergence item | Proposed change | Depends on HARM |
|---|---|---|
| **A3** (classical miners as generators) | Add "HARM + COI filter mode" as the structural, GoldMine-style baseline alongside GoldMine. GoldMine lacks SystemVerilog support and is fragile, so this also covers designs GoldMine can't run | H7/H8 |
| **B3** (hinted mining) | Extend the acceptance comparison from "hinted vs vanilla HARM" to four arms: vanilla, LLM hints, COI hints (rank, plus harvested predicates), and both | H6, H10 |
| **B4** (triage rules) | (a) Mined candidates: use HARM `origin` provenance per proposition, which helps the M0 #27 fix. (b) Add the out-of-cone report as an evidence source | H6, H9 |
| **Stage 5 / suite selection** | HARM `--reduce implies` before OpenFPV design-level implication | H3 |
| **M0 #31 deviation** | Re-decide the top-50 selection policy (see H0, item 3) | H0 |
| **T9** (COI coverage) | No change. OpenFPV's AIGER-level COI and HARM's `coi.json` serve different purposes. Cross-checking them on shared designs would be cheap extra validation for both | H5 |
| **Schedule** | B3 and B4 should not start their HARM-dependent parts before H1 and H6 are merged; A3's COI baseline waits for H8 | — |

## 4. Open questions for trivergence
- Should trivergence keep its own selection policy (length, text) or adopt HARM's ranking now that it's deterministic?
- Should HARM's COI generator run inside the trivergence pipeline (stage 3), or be precomputed per design by the benchmark loaders (F4)?

## 5. The miner portfolio
The classical-miner portfolio for trivergence's A3 (HARM, a new SAT-based miner, GoldMine) is planned and developed on the Mac in its own repository, `~/miner-portfolio`, with its own hand-off file (`doc/TRIVERGENCE_HANDOFF.md`). HARM's part is H15 (`--dump-prop-table`).

