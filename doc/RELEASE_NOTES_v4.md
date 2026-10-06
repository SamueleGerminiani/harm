# HARM v4: release notes (draft)

*Draft for the `v4` release. The release (merging `dev` into `main` and tagging) is deferred: until then this describes `dev`. `harm --version` tells which build you run.*

All new features are opt-in. Default results are unchanged except for the output changes listed first.

## Changes to default output
- **Deterministic order** (D-001): the same input gives the same output, independently of the number of threads; ties in the ranking are broken by text.
- **SVA printing** (`--sva`, `--sva-assert`; D-002):
  - `1'b1`/`1'b0` instead of `true`/`false`;
  - `p |=> q` and `##n` instead of `nexttime`;
  - `s_eventually` for unbounded `F`;
  - `a.b` instead of `a::b`.

  The output is valid SystemVerilog accepted by Verilator. `<edit>` rules still match the old printing.
- **`->` with a multi-cycle antecedent in SVA** (D-021): printed with its mined meaning (`G({a ##1 b} -> X c)` → `a ##1 b |-> c`), where it used to put the consequent a cycle late.
- **Spot-LTL text** (the default output): `X(a && b)` keeps its brackets (D-021).

## New in propositions (H1)
- **SystemVerilog syntax:**
  - sized and based literals (`8'd9`, `4'hA`, `'0`, `'1`);
  - concatenation and replication;
  - `?:`, `===`/`!==`;
  - hierarchical names with `.` or `::`.
- **`--skip-invalid-props`:** skips a proposition that does not parse, with a warning, instead of stopping.
- **x/z values** follow HARM's documented rule, not SystemVerilog's: README "x and z values" (D-011).
- **`origin="…"`** on propositions and numerics; reported by `--dump-assertion-info`.

## New options
| Option | What it does |
|---|---|
| `--reduce syntactic\|equiv\|implies` | remove redundant assertions: identical (default), equivalent propositions (Z3), or implied assertions (Spot + HARM's finite-trace model) |
| `--keep stronger\|weaker\|ranked` | with `implies`: which side of an implication is kept |
| `--atom-premises`, `--atom-premises-max` | with `implies`: also use facts between comparisons (`cnt > 9` ⇒ `cnt > 8`, exclusive FSM states) |
| `--dump-implications <file>` | the dropped assertions and what implies them, as JSON |
| `--dump-assertion-info <file>` | every kept assertion with its metrics, propositions, offsets and origins, as JSON |
| `--trace-end harm\|sva` | how an obligation still pending at the end of a trace is judged |
| `--dump-coi-report <file>` | for each consequent, the propositions outside its cone of influence |
| `--version` | the version (`git describe`) |

## Cones of influence (`<coi>`)
- **`<coi file="coi.json" mode="rank"/>`:** the metrics `coiFrac`, `coiDepthFit` and `coiUnknown`, to sort assertions by structural plausibility.
- **`mode="filter"`:** never tries antecedents outside the consequent's cone, GoldMine-style; `depth="bounded|exact"` also uses the cone's depths. Filter mode assumes the RTL is correct.
- **The file format is `doc/schemas/coi.v1.json`.**

## New tool: harm-coi (`tools/harm-coi`)
- **What it does:** reads SystemVerilog RTL (with pyslang) and writes `coi.json`, the cone of every signal, with depths. With `--predicates` it also writes the RTL's own predicates (conditions, case labels, FSM states, comparisons, reset values). `--emit-config` writes a ready-to-run HARM configuration from them.
- **Install:** Python ≥ 3.11, `pip install -e tools/harm-coi`. See `tools/harm-coi/README.md`.

## Build
- **Z3** is a new optional dependency (`third_party/install_z3.sh`, CMake option `HARM_WITH_Z3`, default ON). HARM and all third-party libraries must be built with the same compiler (D-010).
- **The Docker image** (`docker/build.sh [ref]`) includes Z3, harm-coi, Verilator and Icarus, and runs the fast tests while building.

## For details
The README, and `doc/plan/` (the plan, decisions D-001–D-027, and the validation of each milestone).
