# harm-coi

Reads SystemVerilog RTL and writes the cone-of-influence file (`coi.json`, schema `doc/schemas/coi.v1.json`) that HARM's COI rank and filter modes read (`<coi file="…" mode="rank|filter"/>`). The front end is [pyslang](https://pypi.org/project/pyslang/) (slang's Python bindings), pinned to 12.0.0 (D-006).

## Install
Python ≥ 3.11 (pyslang has no wheels for older versions):
```
python3.12 -m venv .venv
.venv/bin/pip install -e 'tools/harm-coi[test]'      # [test] adds pytest and jsonschema
```

## Use
```
harm-coi --top <module> --files <f.sv>... [--define NAME[=VALUE]]... [--include DIR]...
         --vcd-scope <tb::dut> --vcd-recursion <r> [--vcd <trace.vcd>] [--clock <clk>]
         [--max-depth 3] [--edges edges.txt] [--predicates] [--emit-config cfg.xml] [-v] -o coi.json
```
- `--vcd-scope` and `--vcd-recursion` are HARM's `--vcd-ss` and `--vcd-r`. Names are HARM's: relative to the scope, `::` between sub-scopes (`g[1]::w`, `bus::valid`, `c::mode`), D-013.
- **`--vcd` (recommended): the trace decides which signals are visible.**
  - A packed struct dumped as one vector (Icarus, or Verilator without `--trace-structs`) is one signal: the union of its fields.
  - A trace signal that the RTL does not produce (e.g. the variable of a `for` loop that Verilator dumps as `unnamedblk1::i`) is listed as `unknown`.
  - Without `--vcd`, every signal and declared parameter at most `r` sub-scopes deep is visible, with struct fields as Verilator `--trace-structs` names them.
- `--clock`: the sampling clock. By default it is inferred: the one signal that every register's clock comes from, through wires and ports. Several clocks are an error.
- `--edges`: also writes the direct edges in the `edges.txt` format of the H4 fixtures (`target <- source @delay`, `target x`, `unknown x`).
- `--predicates`: also harvests the RTL's predicates into `coi.json → predicates` (below).
- `--emit-config <file.xml>`: writes a starter HARM configuration from them (implies `--predicates`).
- `-v`: prints why each signal is unknown, and why each predicate was dropped.

As a library: `harm_coi.cli.main(argv)` returns the exit code.

### Example
The `counter` fixture of HARM's tests (`tests/input/coi/counter/`): a mod-10 counter, `cnt` a register, `wrap = en && cnt == 9`. `cnt` depends on itself, `en` and `rst` one cycle or more back (saturated: also beyond `--max-depth`), `wrap` also on `cnt` and `en` in the same cycle, and the inputs on nothing:
<!-- example -->
```
$ harm-coi --top counter --files tests/input/coi/counter/rtl/counter.sv \
    --vcd-scope tb::dut --vcd-recursion 0 --vcd tests/input/coi/counter/trace.vcd \
    --predicates --emit-config $OUT/counter.xml -o $OUT/counter_coi.json
$ python3 -c "import json; d = json.load(open('$OUT/counter_coi.json')); [print(t, [(s['sig'], s['depths']) for s in v['sources']]) for t, v in d['targets'].items()]; print([p['expr'] for p in d['predicates']])"
cnt [('cnt', [1, 2, 3]), ('en', [1, 2, 3]), ('rst', [1, 2, 3])]
en []
rst []
wrap [('cnt', [0, 1, 2, 3]), ('en', [0, 1, 2, 3]), ('rst', [1, 2, 3])]
["cnt == 4'd0", "cnt == 4'd9", 'en', 'rst']
```
The emitted `counter.xml` has these four predicates as propositions with `origin="rtl"` and a `<coi file="counter_coi.json" mode="rank"/>`; HARM mines from it with `harm --vcd tests/input/coi/counter/trace.vcd --clk clk --vcd-ss tb::dut --vcd-r 0 --conf $OUT/counter.xml`.

## What a cone means
- **Depth = register crossings, measured as HARM samples** (just before each rising edge, D-005): `q <= d` gives `q <- d @1`.
  - Combinational logic, continuous assignments and port connections: `@0`.
  - Paths through invisible signals are collapsed and their delays summed.
  - The closure up to `--max-depth` follows `tests/coi/closure.py`: `saturated` when the source also reaches the target beyond `--max-depth`.
- **Control dependencies:** the conditions of `if`, `case` (selector and item expressions) and `?:` are sources of what they control.
- **A register not assigned on every path holds its value:** it is a source of itself (`@1`).
- **Asynchronous controls** (`always_ff @(posedge clk or posedge rst)`, where the body reads `rst` and not `clk`): `q <- rst` at depths 0 and 1.
- **A register on the falling edge of the clock:** depths 0 and 1.
- **Blocking temporaries:**
  - a variable local to a process or function is replaced by its sources;
  - a visible signal assigned once in a process and read later in it is a source itself (`y <- t @0`), as well as through its sources.
- **Function calls:** the arguments and the module-level signals the function reads.
- **Bit and part selects** are signal-level: a write to `r[0]` keeps the other bits (`r <- r @1`), and the index is a source.
- **The clock is never a source** (D-013). A visible alias of it (e.g. a submodule's clock port) is a target with no sources.
- **Parameters** are targets with no sources.

## RTL predicates (`--predicates`, D-023)
- **What is harvested:**

  | Kind | From | Predicate |
  |---|---|---|
  | Condition | `if (c)`, `c ? x : y` | `c`; for a compound `c` (`&&`, `\|\|`, `!`), also each atom (comparison or 1-bit signal, without `!`) |
  | Case label | `case (s) L:` | `s == L` (not `default`) |
  | Enum (FSM) value | a variable of an enum type | `v == C` for every value `C` |
  | Comparison | `==`, `!=`, `<`, `<=`, `>`, `>=` with a constant side, anywhere | the comparison |
  | Reset value | the first `if` of a clocked process whose branch assigns only constants | `reg == value` |

  The reset rule is structural, so a data condition of the same shape (`if (x) y <= 1'b1; else y <= 1'b0;`) also yields `y`.
- **Written in HARM's syntax and names:**
  - the signal on the left; constants (enum values and parameters included) as sized decimal literals with the signal's width (`state == 2'd1`, `cnt == 4'd9`);
  - a 1-bit comparison as the signal or its negation (`prio == 1'b0` is `!prio`).
- **Each record** has `origin: "rtl"`, `src` (`file:line`, comma-separated if harvested more than once) and `targets`:
  - for conditions and labels, the signals assigned under them;
  - for comparisons, the signal assigned from the expression;
  - for enum values and reset values, the variable.
- **Dropped (counted, listed with `-v`):** predicates on signals that are not visible, on local variables (e.g. a `for` loop's condition), comparisons whose constant does not fit the signal, predicates on a signal or constant wider than HARM's 511-bit limit (H11c, F-L5), and expressions that cannot be translated.
- **Not seen:** elaboration-time conditions (`if` in a `generate`).
- **`--emit-config`** writes one context:
  - the predicates with `loc="a, c, dt"` and `origin="rtl"`;
  - `<coi file="…" mode="rank"/>` pointing at the written `coi.json`;
  - `--generate-config`'s template and sorts.

  For GoldMine-style mining, change the mode to `filter` (and `depth`, H8).

## Unknown, never dropped
A signal goes to `unknown` (HARM treats it as in every cone, D-017) when:
- it is driven by a latch (`always_latch`, or an `always_comb` that does not assign it on every path);
  - `unique` and `priority` are not trusted to make a `case` complete: a `case` is complete only with a `default`, or with constant items that cover every selector value;
- it is driven by a register on another clock or on both edges;
- it is driven by an `inout` port, a gate primitive, a task call, a function that writes signals, a timing control inside a process, or another unsupported statement;
- slang reports a driver that harm-coi does not model;
- it is in the trace but not produced by the RTL (with `--vcd`);
- its cone reaches an unknown signal within `--max-depth`.

## Tests
- `tools/harm-coi/tests` (pytest): constructs, with hand-written expected edges.
- `ctest -L coi` in HARM's build:
  - the H4 fixtures (equality with the hand-written cones);
  - a simulation non-influence check;
  - an optional cross-check against yosys (label `xcheck`): it runs when CMake finds a yosys with `read_slang` (`third_party/install_yosys.sh` builds yosys 0.69 with it), and is skipped otherwise.
- Configure CMake with `-DHARM_COI_PYTHON=<venv>/bin/python`.
