# H5 plan: `harm-coi`, the cone-of-influence generator

*Status: approved 2026-10-06; H5a spike done, D-006 pending. Branch: `ms/H5-harm-coi` (from `dev` @ H7). Effort: 0.5 d spike + 3–4 d.*

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

## H5a results (2026-10-06)
Code and probe: `doc/plan/h5a_spike/` (throwaway, kept for the record).

### pyslang 12.0.0
- **Install:** `pip install pyslang==12.0.0`. It needs **Python ≥ 3.11**; there is no wheel for macOS' system Python 3.9. Wheels exist for macOS arm64/universal2 and manylinux_2_28 x86_64/aarch64. Trivergence already requires Python ≥ 3.11.
- **Spike extractor** (`spike_pyslang.py`, ~370 lines): it walks continuous assigns, `always_ff`/`always_comb`, `if`/`case`/`?:` (control dependencies), port connections, and interface and struct members. Invisible signals are collapsed, and the output is `edges.txt` format.
- **On all 6 H4 fixtures, the direct edges equal the hand-written `edges.txt`, and `closure.py` on them equals `expected_coi.json`** (the A2 and A1 checks, done by hand).
- **Fixes needed on the way, all in our code, not pyslang:**
  - enum values and parameters are constants: reading them is not a dependency;
  - the implicit localparam that slang creates for a genvar in each generate block is not dumped by simulators, so it is not a target;
  - a clock reaches a submodule's `always_ff` through a port (`hier`): the clock property is propagated back through zero-delay edges.
- **`probe.sv`** (`case` with default, `?:`, function call, blocking temporary, bit select, partial register write): every edge is correct by hand. The function declaration is reported as an unknown member; it should be ignored.
- **Diagnostics:** 0 errors on every fixture.

### yosys + yosys-slang
- **yosys-slang is now "sv-elab", and has been built into yosys since 0.67.** As a plugin it supports only yosys 0.59–0.66, with clang ≥ 17 or GCC ≥ 11.
- **Homebrew's yosys is 0.51**, built with Apple clang 16, and the plugin does not compile against it (`RTLIL::Const` has no `append`). On macOS the only working route was the **OSS CAD Suite** binary bundle (yosys 0.69+190, 1.9 GB unpacked, ~500 MB download; not every daily release has a darwin-arm64 build). On Linux the same bundle exists (712 MB).
- **Elaborates the 6 fixtures:** yes (`read_slang; proc; flatten`).
- **Names:** after `flatten`, `hdlname` gives the hierarchy (`"g[1] w"`, `"bus data"`). But **aliased nets keep a single name** in `select %ci*`: `g[i].w` and the stage's `q` are one net, and the visible name was lost (`hier`). Mapping must work on net bits with all their aliases.
- **Fields: lost.** `c` is a single 5-bit wire; only the driver cell names (`$driver$c.mode`) mention the fields. Field precision needs the struct layout from somewhere else (that is, from slang).
- **Parameters:** not in the netlist (`hier`'s `N`, `W`). They would come from somewhere else too.
- **Depth:** `$dff` cells, easy. **Control dependencies:** explicit as mux selects.
- **H10 (predicate harvesting):** conditions are lowered to `$eq`/`$mux`/`$pmux` cells; the source text of `if`/`case` conditions is gone.

### Cross-check (the validation planned for H5b)
- `xcheck_json.py`: signal-level cones from yosys' JSON netlist, over net bits and all their aliases, with struct fields mapped from their bit ranges.
- **It agrees with the pyslang edges on all 6 fixtures.** The plain `select %ci*` version disagreed on `hier` and `structs`, but only because of the alias and field issues above.
- **On `probe.sv`, one spurious difference:** `t <- k`. It comes from the check's coarse cell model: a 2-bit `$buf` packs `t` and `y4`. yosys itself is right. For H5b, the check needs per-bit semantics for bitwise cells (or `splitcells`).

### Against the plan's table
| | pyslang | yosys + sv-elab |
|---|---|---|
| Install, macOS | pip wheel, Python ≥ 3.11 | Homebrew too old; OSS CAD Suite bundle (1.9 GB) or a source build of yosys ≥ 0.67 |
| Install, Linux | pip wheel (glibc ≥ 2.28) | OSS CAD Suite or a source build; distro packages are typically older than 0.67 |
| Elaborates the 6 fixtures | yes | yes |
| Names → VCD | direct, from `hierarchicalPath` | from `hdlname`, with alias resolution |
| Fields | yes | no (bits only) |
| Parameters as targets | yes | no |
| Control dependencies | our walk (done in the spike) | explicit |
| Depth | `always_ff` = 1 (done in the spike) | `$dff` |
| H10 | conditions in the AST | lowered |
| Result on the fixtures | **6/6 exact** (edges and closure) | 6/6 agree at signal level, with fields from an external layout |

### Recommendation for D-006: pyslang
The expectation is confirmed:
- pyslang alone reproduces the hand-written fixtures exactly;
- yosys needs a 1.9 GB bundle on macOS, plus a second source for fields and parameters (which would be slang anyway), and it loses what H10 needs.

**yosys stays as the independent cross-check** in H5b validation, as planned. It is optional: it runs only if a yosys with `read_slang` is found.

**Risk of the pyslang choice:** the dataflow and control-dependency walk is our code, so its correctness rests on the H4 fixtures, A4 and the simulation check (A3). The yosys cross-check is the guard for constructs not covered by those.

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
