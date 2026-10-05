# HARM → trivergence: impact on trivergence's plan and code

*Maintained in the HARM repo, updated whenever a HARM milestone changes something trivergence uses or could use. Last update: 2026-10-05 (H0, H1, H2 on `dev`; H4 awaiting review).*

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
| H4 | `ms/H4-coi-contract` (head) | yes; not yet merged into `dev`, awaiting review | — |

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

**[recommended] D-011 (decided in HARM: an SV-semantics option will come in milestone H1b): x/z semantics.**
- HARM's comparisons with x/z operands are false, and `!` then makes them true. So a mined `!(a == b)` can hold in HARM but fail in Verilator on traces with x. This is the likely root cause of M0 #33.
- Until D-011 is decided, triage should treat "HARM holds, simulator fails on x-valued cycles" as a known semantic gap, not as a bug in the RTL.

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

### H3: semantic redundancy reduction with Spot (planned)
- New `--reduce implies` and `--dump-implications <json>`.
- **[recommended]** Use them in trivergence stage 5 (suite selection) as a cheap, design-independent first pass before `FormalOracle.implies` (T8a). HARM's implication is *logical*, with no design and no reset, so it never needs a solver run on the RTL.

### H4: COI contract (awaiting review, branch `ms/H4-coi-contract`)
- **Contract:** `doc/schemas/coi.v1.json`, plus the rules in `tests/coi/check_coi.py`.
  - **Names** are relative to `meta.vcd_scope`, with `::` between sub-scopes: exactly what HARM sees with `--vcd-ss <scope> --vcd-r <recursion>`. Trivergence's adapter passes `--vcd-ss traces.scope --vcd-r=16`, so a `coi.json` for trivergence must record the same scope and recursion.
  - **Depth** counts register crossings (D-005), measured as HARM samples traces: the values just before each rising edge, which is the Preponed-region view of SVA (VCD dumps record the end of the time step). So a register is one cycle behind its inputs, i.e. `G(a -> X q)`, and HARM's verdicts match what trivergence's simulator assertions see.
- **[optional]** The fixture corpus `tests/input/coi/` (6 designs with traces and hand-written cones) can serve as small sanity designs for trivergence's oracle and COI work (T9).

### H4–H9: COI hints (planned)
- **Contract:** `coi.json` v1 (H4). It is produced by `harm-coi` (H5), a Python tool in the HARM repo that can run inside trivergence's image (pyslang or yosys-slang, both already in the image).
- **[recommended] Rank mode (H6):**
  - the adapter writes `<coi file=... mode="rank"/>` and `origin="spec|rtl"` on propositions;
  - add `<sort exp="coiFrac"/>`;
  - this keeps HARM's "behaviour" view independent from the RTL, since nothing is pruned.
- **[optional] Filter mode (H7/H8):** GoldMine-style mining. It assumes the RTL is correct, so use it only as a *baseline* in Paper A, never in the method's triage.
- **[recommended] Out-of-cone report (H9):** a spec-derived proposition outside a target's structural cone is a new disagreement signal: "spec says A affects B, RTL says it cannot". It is a candidate input to B4 triage.

### H10: RTL predicate harvesting (planned)
- **[optional]** `harm-coi --emit-config` gives a hint set built from the RTL alone. Useful as the "no LLM" arm of the B3 ablation.

### H11: evaluation (planned)
- HARM-side results on about 10 AssertLLM2 designs will run on the Linux machine, and can reuse trivergence's benchmark loaders (F4) if available.

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
