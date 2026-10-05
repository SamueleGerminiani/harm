# H5 plan: `harm-coi`, the cone-of-influence generator

*Status: plan, awaiting approval. Branch: `ms/H5-harm-coi` (from `dev` @ H7). Effort: 0.5 d spike + 3–4 d.*

## Goal
`harm-coi` reads the RTL and writes the `coi.json` that HARM's rank and filter modes use (H6, H7). Until now that file was written by hand for the H4 fixtures. It must run on Linux (trivergence) and on macOS.

```
harm-coi --top <module> --files <f.sv>... [--define ...] [--include ...]
         --vcd-scope <tb::dut> --vcd-recursion <r> [--vcd <trace.vcd>]
         [--max-depth k] -o coi.json
```

## What the generator must get right (from H4 and D-005, D-013)
1. **Names as HARM sees them:**
   - scope-relative;
   - `::` between sub-scopes (`g[1]::w`, `bus::valid`, `c::mode`);
   - limited to the VCD recursion;
   - every visible signal is a target (D-013), including constant parameters that simulators dump (`hier`'s `N`, `W`), which become targets with no sources.

   With `--vcd`, the names are checked against the trace, as HARM does.
2. **Depth = register crossings, measured as HARM samples** (before the rising edge): a register is one cycle behind its inputs. Paths through invisible signals collapse into one edge, with their delays summed.
3. **Control dependencies:** in `if (en) cnt <= cnt + 1`, `en` influences `cnt`. The same holds for `case` selectors and the conditions of `?:` and `if`/`case` in `always_comb`.
4. **Field-level precision** for packed structs (`c::mode` depends only on `m`) and interface members.
5. **The clock is never a source; reset is a normal source** (D-013).
6. **Saturation is reported,** not hidden: feedback loops give depth sets up to `max_depth` with `saturated: true` (D-005).

## H5a: spike, and D-006 (to decide after it)
Candidates for the RTL front end:

| | pyslang (slang's Python bindings) | yosys + yosys-slang (JSON netlist) | Verible |
|---|---|---|---|
| **Install** (probed 2026-10-06) | `pip install pyslang` (12.0, wheels for macOS arm64 and Linux): works | yosys 0.51 from Homebrew/apt. **yosys-slang must be built from source** against yosys, with the same compiler and C++ runtime as yosys (D-010's mixed-runtime crash is the risk) | parser and formatter: no elaboration |
| **Elaborates the 6 fixtures** | **yes, 0 errors** (probed) | to measure | no: parameters, `generate`, interfaces, structs are not resolved |
| **Names → VCD scopes** | hierarchy kept (`g[1]`, `bus`, `c`) | flattening renames (`g[1].st.q`); to map back | — |
| **Control dependencies** | to compute from `if`/`case`/`?:` in the AST (our code) | explicit: they are mux select inputs | — |
| **Field and bit precision** | to compute (selects on structs) | bit-level in the netlist; field names to recover | — |
| **Depth** | registers = `always_ff` / nonblocking on the clock edge (our code) | `$dff` cells: easy | — |
| **Reuse for H10** (predicate harvesting: `if`/`case` conditions, FSM constants) | direct: the conditions are in the AST | lost: lowered to muxes and constants | parser only |

- **Spike, 0.5 d:**
  - **pyslang:** a minimal cone extractor (continuous assigns, `always_ff`/`always_comb`, `if`/`case`/`?:`) on `counter` and `structs`, compared with `expected_coi.json`.
  - **yosys:** install, build yosys-slang, and check name mapping and field precision on `hier` and `structs`.
  - Report both against the table above, and stop for D-006.
- **My expectation, to confirm or refute in the spike: pyslang.**
  - It is the only candidate that installs and elaborates everything today on both platforms.
  - It keeps names and conditions, which H10 needs.
  - The extra work is our own dataflow and control-dependency walk, which the H4 fixtures and the simulation check validate.
  - **Verible is not a candidate.** It parses but does not elaborate, so `generate`, parameters and interfaces would have to be reimplemented.

## H5b: the tool (after D-006)
- `tools/harm-coi/`: a Python package with its own `pyproject.toml` and a pinned front-end version, a CLI as above, and unit tests (pytest).
- **Direct edges:** `target <- source @delay`. Collapsing through invisible signals, then a transitive closure up to `max_depth`.
  - The closure reuses `tests/coi/closure.py`'s rule, so that the hand fixtures and the generator follow the same D-005 semantics; the edge extraction is new.
- **Output:** `coi.v1` JSON, validated by `tests/coi/check_coi.py`.
  - `meta.generator` records `{"name": "harm-coi", "version": …, "frontend": …}`.
  - Signals the tool cannot analyse (e.g. driven by unsupported constructs) go to `unknown`, never silently dropped.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | **Exact match** (order-insensitive) with the hand-written `expected_coi.json` on all 6 H4 fixtures, including `hier` (HARM cannot load its trace, F-b of H7, but `harm-coi` doesn't need HARM) | ctest (python) |
| A2 | **Direct edges** equal the hand-written `edges.txt` on all 6 fixtures (a finer check than A1, since the closure can hide edge errors) | ctest |
| A3 | **Simulation non-influence** (`perturb.py influence`, H4) re-run on the generator's output for every fixture: forcing a signal outside a target's cone never changes the target | ctest (verilator) |
| A4 | Unit tests on constructs not in the fixtures, with hand-written expected edges: `case` with default, nested `if`, `?:`, function calls, a blocking temporary in `always_comb`, bit selects, an unsupported construct going to `unknown` | pytest |
| A5 | Runs on Linux. Recorded as pending, like the other Linux checks | — |

## Validation (independent)
- **The hand fixtures** (A1, A2) and **simulation** (A3).
- **A signal-level cross-check with the other front end:** yosys `select -list %ci*` if pyslang is chosen, or pyslang if yosys is, on the fixtures that yosys can read. It runs once and its result is reported.

## Out of scope
- Predicate harvesting (H10).
- Building the generator into HARM's C++.
- Real-size designs: there is no RTL for `bl_master` or `camellia` here. The first real designs will be trivergence's, on Linux.

## Decisions
- **D-006 (front end):** decided after the spike, with your approval.
- **Approve now:** the CLI and the plan above.
