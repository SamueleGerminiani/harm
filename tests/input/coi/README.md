# COI fixture corpus (H4)

Small RTL designs with a trace and a **hand-written** cone of influence for every visible signal. They are the shared ground truth for `harm-coi` (H5), HARM's COI rank and filter modes (H6–H8) and predicate harvesting (H10).

## Layout of each fixture
- `rtl/*.sv`: the design.
- `tb.sv`: seeded random stimulus on the falling clock edge. `+seed=<n>` selects the seed (default 1) and `+vcd=<file>` the dump file. Under `` `ifdef PERTURB `` it includes `perturb.svh`, used by the simulation checks.
- `build.sh <dir> [vcd] [verilator args]`: builds with Verilator and runs it.
- `trace.vcd`: the committed trace (seed 1, 200 cycles).
- `edges.txt`: **hand-written from the RTL**. Only the *direct* dependencies between visible signals, `target <- source @delay`, where delay is the number of registers crossed. Paths through signals that are not visible are written as one edge with their total delay.
- `expected_coi.json`: derived from `edges.txt` by `tests/coi/closure.py`, a mechanical transitive closure up to `max_depth` (D-005). Review `edges.txt`, not the JSON.

All fixtures use `vcd_scope = tb::dut`, clock `clk` and `max_depth = 3`. HARM names signals relative to the scope, with `::` between sub-scopes (D-013).

## Designs

| Design | Difficulty | Direct edges (see `edges.txt`) | Notable cone facts |
|---|---|---|---|
| `counter` | register feedback, combinational output | `cnt <- {cnt, en, rst} @1`; `wrap <- {en, cnt} @0` | `wrap` depends on `en` and `cnt` at every depth 0..3, and on `rst` from depth 1. All saturated, because the feedback is unbounded |
| `arbiter` | combinational grant and a priority register in a loop | `gnt <- {req, prio} @0`; `prio <- {gnt, prio, rst} @1` | `gnt` is in its own cone from depth 1 (through `prio`) |
| `fsm` | `typedef enum` state; outputs decoded from the state | `state <- {state, go, stop, rst} @1`; `busy, finished <- state @0` | `busy` and `finished` do not influence each other or the state; `go` and `stop` reach the outputs only from depth 1 |
| `hier` | `generate` loop of a parameterised `stage`; recursion 1 hides the stage ports | `g[0]::w <- din @1`; `g[i]::w <- g[i-1]::w @1`; `dout <- g[2]::w @0` | a pure pipeline (not saturated): `dout` gets `din` exactly at depth 3. A stage is never influenced by a later one. The parameters `N` and `W` are dumped as constant signals: targets with no sources |
| `structs` | packed struct fields (`--trace-structs`) and an interface instance | `bus::data <- x @1`; `bus::valid <- xv @1`; `c::mode <- m @1`; `c::val <- {bus::data, bus::valid, c::val} @1` | field-level separation: `c::mode` depends only on `m`, and `c::val` never on `m` |
| `multipath` | one source at two depths for one target; an independent output | `r1 <- a @1`; `r2 <- r1 @1`; `rb <- b @1`; `y <- {a, r2} @0`; `z <- rb @0` | `y` gets `a` at depths 0 and 2 (not 1). `z` never depends on `a`, and `y` never on `b` |

## Checks (`ctest -L coi`)
- **`check_coi.py`:** the schema (`doc/schemas/coi.v1.json`) and the extra rules. The names must be exactly the signals HARM sees in `trace.vcd` (HARM itself is asked, through `--generate-config`).
- **`perturb.py reproduce`:** a fresh build reproduces `trace.vcd`.
- **`perturb.py influence`:** forcing any signal outside a target's cone never changes the target.
- **`perturb.py depths`:** reported only. A one-cycle pulse on a source shows an effect on the target at each claimed depth.
