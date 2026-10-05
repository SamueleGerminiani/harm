# H4 plan: COI contract and RTL fixture corpus

*Status: approved 2026-10-05 (D-005, D-013), in progress. Branch: `ms/H4-coi-contract` (from `dev` @ H2). Effort: about 2 d.*

## Goal
Fix the contract between the RTL side and HARM before either is built:
- the `coi.json` schema, which `harm-coi` (H5) writes and HARM (H6–H9) reads;
- a small corpus of RTL designs with traces and **hand-written** expected cones.

The corpus is the shared ground truth for H5 (generator), H6–H8 (HARM rank/filter modes) and H10 (predicate harvesting). That is why H6 can start without waiting for H5.

## Findings from the investigation (2026-10-05)
- **F1. Signal names.** HARM names VCD signals **relative to the `--vcd-ss` scope**, joining sub-scopes with `::`, e.g. `DUT::state`, `intf::a` for `--vcd-ss tbench_top --vcd-r 1`. `coi.json` uses exactly these names and records the scope and recursion depth they assume.
- **F2. Tools.** Verilator 5.034 simulates SystemVerilog fixtures with `--trace` (VCD), and supports `force`/`release` on internal signals, which the non-influence check needs. iverilog is not used here, because of its limited SystemVerilog support (interfaces, structs). `jsonschema` 4.23 is available for schema validation.

## Decisions to approve
### D-005: depth convention
- **Depth = number of register crossings** (flip-flop stages) on a path from the source to the target.
  - **Depth 0:** combinational. The source's value now can affect the target now.
  - **Depth d:** the source's value d cycles ago can affect the target now.
- **A source can reach a target at several depths.** `depths` lists all of them, up to `max_depth`.
- **A register's own feedback** (e.g. `cnt <= cnt + 1`) puts the register in its own cone at depth 1, 2, …. These are listed up to `max_depth`.
- **Saturation.** If a target has paths deeper than `max_depth`, `saturated: true` is set for the source on that path. HARM then treats the cone as complete only up to `max_depth`.

### D-013: what is a source and what is a target
- **Targets:** every signal HARM can see in the trace under the recorded scope, i.e. every signal that can appear in a consequent.
- **Sources:** signals HARM can see. Paths through signals HARM cannot see (unrecorded internal nets) are followed through, so that a visible source reaches a visible target at the right depth.
- **The clock is never a source**, since it is the sampling event. **Reset is a source like any other signal.**

## `coi.json` v1 (`doc/schemas/coi.v1.json`, JSON Schema 2020-12)
```json
{
  "version": "1",
  "meta": { "design": "counter", "top": "counter", "vcd_scope": "tb::dut", "vcd_recursion": 1,
            "clock": "clk", "max_depth": 4,
            "generator": { "name": "hand-written", "version": "" } },
  "targets": {
    "cnt":  { "sources": [ { "sig": "cnt",  "depths": [1, 2, 3, 4], "saturated": true },
                           { "sig": "en",   "depths": [1, 2, 3, 4], "saturated": true },
                           { "sig": "rst",  "depths": [1, 2, 3, 4], "saturated": true } ] },
    "wrap": { "sources": [ { "sig": "cnt", "depths": [0, 1, 2, 3, 4], "saturated": true }, ... ] }
  },
  "unknown": [],
  "predicates": []
}
```
- **`unknown`:** visible signals the generator could not resolve (e.g. from black boxes). HARM never treats them as out-of-cone (H6).
- **`predicates`:** filled by H10. The format is reserved here (`expr`, `origin`, `src`).
- **Constraints the schema can't express,** checked by `tests/coi/check_coi.py`:
  - `depths` is sorted and unique, with every value ≤ `max_depth`;
  - every name appears in the fixture's VCD under the recorded scope;
  - the clock is never a source.

## RTL fixture corpus (`tests/input/coi/<design>/`)
Six small designs, each chosen for one difficulty:

| Design | What it exercises |
|---|---|
| `counter` | mod-10 counter with enable and reset: self-feedback, depth saturation, combinational `wrap` (depth 0) |
| `arbiter` | 2-requester round-robin arbiter: grant depends on requests (depth 0) and on a priority register (depth 1) |
| `fsm` | 3-state FSM with `typedef enum`, an output decoded from the state, and an input that only affects the next state |
| `hier` | parameterised shift-register stage instantiated N=3 times by a `generate` loop, inside a top: hierarchy, parameters, depths 1..3 across instances |
| `structs` | a packed struct register and an SV interface (modport) between two modules: field-level sources |
| `multipath` | one input reaches an output both combinationally (depth 0) and through two registers (depth 2): several depths for one pair |

**Each design has:**
- `rtl/*.sv`;
- a testbench `tb.sv` with seeded random stimulus that dumps a VCD;
- `build.sh` (Verilator), plus the committed VCD (small: 200 cycles);
- **`expected_coi.json`, written by hand** from the RTL, before any generator exists;
- a short `README.md` that explains each cone, for review.

## Acceptance tests (written first)

| # | Test |
|---|---|
| A1 | `doc/schemas/coi.v1.json` is a valid JSON Schema. Every fixture's `expected_coi.json` validates against it, and passes `check_coi.py`'s extra checks (sorted depths, bounds, names present in the VCD under the scope, no clock source) |
| A2 | A set of **invalid** `coi.json` files (about 8: missing version, unsorted depths, depth > max_depth, clock as a source, unknown signal name, …) is rejected, each with the expected reason |
| A3 | Every fixture builds with Verilator and reproduces its committed VCD bit for bit (deterministic seeds) |
| A4 | **Non-influence by simulation** (validates the hand-written cones). For each target T and each visible signal S **not** in T's cone, a variant testbench `force`s S to random values from cycle 10 on, with otherwise identical stimulus. T's trace must equal the unperturbed one. Primary inputs are perturbed by changing the stimulus instead |
| A5 | **Depth evidence by simulation (reported, not failed).** For each (S, T, d) claimed, S is perturbed in a single cycle t, and the run is checked for whether T changes at t+d in at least one of 20 seeds. A claimed depth that never shows an effect is listed for review: it may be correct but hard to excite, or the hand-written cone may be wrong |

All of these run under ctest with the label `coi` (A3–A5 only if Verilator is found).

## Out of scope
- Generating cones from RTL (H5).
- Reading `coi.json` in HARM (H6).
- Per-bit cones (the optional `bits` field is reserved and not used in v1).

## Files
- `doc/schemas/coi.v1.json`
- `tests/coi/{check_coi.py, perturb.py, invalid/*.json}`
- `tests/input/coi/<design>/{rtl/*.sv, tb.sv, build.sh, trace.vcd, expected_coi.json, README.md}`
- `tests/regression/CMakeLists.txt` (label `coi`)
- `doc/plan/{DECISIONS,VALIDATION,PLAN,TRIVERGENCE_IMPACT}.md`

## Decisions needed before starting
1. **D-005 (depth = register crossings, all depths listed up to `max_depth`, saturation flag).**
2. **D-013 (targets = every visible signal; clock never a source; reset a normal source).**
