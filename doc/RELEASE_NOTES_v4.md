# HARM v4: release notes

*For the `v4` release. The release (merging `dev` into `main` and tagging it `v4`) is deferred until the user decides; until then these notes describe `dev`. `harm --version` tells which build you run. Coming from v3? See also `doc/MIGRATING_v3_to_v4.md`. The full account, with how each part was validated, is the technical report in `doc/report/` (`make -C doc/report`).*

Every new feature is opt-in. With a v3 configuration and no new option, the output changes only as listed in the first section.

## Changes to default output
- **Deterministic order** (D-001): the same input gives the same output, run after run and for any `--max-threads`. Ties in the ranking are broken by the assertion's text. The `--max-ass` cut and the `--find-min-subset` covering subset are therefore reproducible too.
- **SVA printing** (`--sva`, `--sva-assert`; D-002):
  - `1'b1`/`1'b0` instead of `true`/`false`;
  - `p |=> q` and `##n` instead of `nexttime`;
  - `s_eventually` for unbounded `F`;
  - `a.b` instead of `a::b`;
  - brackets follow SystemVerilog's precedence (`(b until c) and (s_eventually d)`).

  The output is valid SystemVerilog accepted by Verilator. `<edit>` rules still match the old printing, so existing rules keep working.
- **`->` with a multi-cycle antecedent in SVA** (D-021): printed with its mined meaning (`G({a ##1 b} -> X c)` → `a ##1 b |-> c`). v3 put the consequent a cycle late.
- **Spot-LTL text** (the default output): `X(a && b)` keeps its brackets (D-021). v3 printed `Xa && b`, which Spot reads as `(X a) && b`.
- **Vector indices follow SystemVerilog** (D-028): on a vector declared `[1:10]` or `[10:3]` in the VCD, `x[i]` and `x[a:b]` use the declared indices, and an index outside the range is an error. Vectors declared `[n:0]` and CSV variables are unchanged. VCD traces with ascending ranges (`[1:10]`) load; v3 stopped on them.
- **Bug fixes that change results:**
  - a mined bit selection kept its bounds: v3 printed and evaluated `r[7:4]` as `r[4:7]` (H1, finding F10);
  - a variable name no longer corrupts a literal that contains it (`a` in `0xa`, `x` in `'b1x0`; H1, F9);
  - a template with more placeholders than propositions in their domain no longer hangs HARM (H7);
  - **evaluation** (H19, D-035): an operation with an unsigned operand is unsigned, also for C types (v3 followed C's rank rules, also for `logic`: `x < q` with a negative `int x` was true); a comparison is computed at its context's width (`ch << am == 0`); a decimal literal is 32 bits; `>>` is logical; a shift by the width or more gave an error and stopped v3, now 0; a `logic` division by zero aborted v3, now x; `(q + 4'bx) ^ 4'b1000` was true; CSV `integer`/`time` were 2-valued; `4'b0x01` printed `4'bx01` (a different constant). The H0 baselines did not change;
  - **operators** (H18, D-034): hand-written `!x == y`, `x & y == y`, `(x > 0) == y` now read as in C and SystemVerilog (v3 read `!(x == y)`, `(x & y) == y`, `(x > 0) == (y != 0)`); HARM's printed output always bracketed these forms, so mined assertions are unaffected;
  - **printing** (H18): a printed proposition re-parses to itself. v3 printed `x - (y - k)` as `x - y - k`, `(x + y)[1:0]` as `x + y[1:0]`, and `!(q inside {...})` as `!q inside {...}` (wrong SystemVerilog);
  - a float `<numeric>`'s excluded values (`clustering="...,2E"`) are compared with the values: v3 compared them with the cycle index, so it kept `f == 2` and dropped the value at cycle 2 instead (H17);
  - `--vcd-dir` and `--csv-dir` concatenate the files in path order (D-033), not the directory's order, which differs between machines; the cycle numbering of a multi-trace run (`--dump-prop-table`, failing sub-traces) is the same everywhere. The mined assertions did not depend on it;
  - on macOS arm64, the same assertions as on Linux x86_64 (H12, F-M2). v3 could choose a different decision-tree antecedent among near-equal scores, because GCC fused a multiply-subtract on arm64. The fix changes nothing on Linux x86_64.

## New in propositions (H1)
- **SystemVerilog syntax:**
  - sized and based literals (`8'd9`, `4'hA`, `'0`, `'1`);
  - concatenation and replication;
  - `?:`, `===`/`!==`;
  - hierarchical names with `.` or `::`.
- **Invariant templates** `G(P0)`, without an implication.
- **`--skip-invalid-props`:** skips a proposition that does not parse, with a warning, instead of stopping.
- **x/z values** follow HARM's documented rule, not SystemVerilog's: README, "x and z values" (D-011, H1b).
- **`origin="…"`** on `<prop>` and `<numeric>`, free text (e.g. `spec`, `rtl`), reported by `--dump-assertion-info` and `--dump-coi-report`.
- **Bitwise operators on CSV `bool` operands** (H17, D-032): `a ^ b`, `~a & c`, `a ^ q4`, as in SystemVerilog (v3 stopped with a parse error).
- **Operators bind and convert as in C and SystemVerilog** (H18, D-034): `!x == y` is `(!x) == y`; `x & y == y` is `x & (y == y)`; a comparison is a number (`(a < b) + 1`, `x < y < z`, `(x > 0) == y` compares numbers); unary `-` and `+`; `x-1` without blanks; `bool` operands of arithmetic and comparisons. The README has the precedence table.
- **Evaluation as in SystemVerilog** (H19, D-035): signed/unsigned rules, context-determined widths, 32-bit decimal literals, `>>>`/`<<<`, shifts and divisions by zero that never stop HARM, 4-state `integer`/`time`, literals that print as they re-parse. The README describes each rule.

## New options
| Option | What it does |
|---|---|
| `--reduce syntactic\|equiv\|implies` | remove redundant assertions: identical (default), equivalent propositions (Z3, H2), or implied assertions (Spot plus HARM's finite-trace model, H3) |
| `--keep stronger\|weaker\|ranked` | with `implies`: which side of an implication is kept |
| `--atom-premises`, `--atom-premises-max <N>` | with `implies`: also use facts between comparisons (`cnt > 9` ⇒ `cnt > 8`, exclusive FSM states; H3b) |
| `--dump-implications <file>` | the dropped assertions and what implies them, as JSON |
| `--dump-assertion-info <file>` | every kept assertion with its metrics, propositions, cycle offsets and origins, as JSON |
| `--trace-end harm\|sva` | how an obligation still pending at the end of a trace is judged: weak (default) or as a SystemVerilog simulator does (H1c, D-016) |
| `--dump-prop-table <file>` | every context's propositions and their value at every cycle (`prop-table` v1, H15, D-031), for miners that work on propositions (the portfolio's SAT miner) |
| `--dump-coi-report <file>` | for each consequent, the propositions outside its cone of influence (H9) |
| `--skip-invalid-props` | see above |
| `--version` | the version (`git describe`) |

**`--check-dump-eval <dir>` (a v3 option) has a new file format** (H16, D-030). v3 named each assertion's CSV after its text with some characters deleted, so different assertions could overwrite each other's file without a warning (`a != b` and `a <= b`), and a name over 255 bytes stopped HARM. v4 names the files `<k>_<text>.csv`, with `k` the order in which the assertions are checked, and writes `index.json`, which maps each file to its context and its exact Spot-LTL and SVA text. Every row now has all five columns; v3 wrote only `t` and `Ant` for an assertion without a shift (`G(a -> b)`).

## Cones of influence (`<coi>`; H4, H6–H9)
- **`<coi file="coi.json" mode="rank"/>`:** new metric variables `coiFrac`, `coiDepthFit` and `coiUnknown`, to sort or filter assertions by structural plausibility. Nothing is pruned.
- **`mode="filter"`:** never tries antecedents outside the consequent's cone, GoldMine-style; `depth="bounded|exact"` also uses the cone's depths (H8). Filter mode assumes the RTL is correct, and says so once.
- **The file format** is `doc/schemas/coi.v1.json`.

## New tool: harm-coi (`tools/harm-coi`; H5, H10)
- **What it does:** reads SystemVerilog RTL (with pyslang) and writes `coi.json`, the cone of every signal, with depths. With `--predicates` it also writes the RTL's own predicates (conditions, case labels, FSM states, comparisons, reset values). `--emit-config` writes a ready-to-run HARM configuration from them.
- **Install:** Python ≥ 3.11, `pip install -e tools/harm-coi`. See `tools/harm-coi/README.md`.

## Build, platforms and tests
- **Linux and macOS** (arm64): HARM builds and passes the same tests on both (H11b: the Linux build, F-L1), and mines the same assertions (H12).
- **Z3** is a new optional dependency (`third_party/install_z3.sh`, CMake option `HARM_WITH_Z3`, default ON).
- **One compiler for everything** (D-010): HARM and the libraries in `third_party` must be built with the same C++ compiler. The install scripts record it, and CMake warns on a mismatch.
- **`-ffp-contract=off`** for everything HARM's CMake builds (H12), so that floating-point scores round the same way on every platform.
- **Profiling is opt-in** (H13): `-DHARM_PROFILE=ON` builds for `gprof`. A default build no longer writes a `gmon.out` on every run.
- **The tools the tests use** (Verilator 5.052, Icarus Verilog 13.0, yosys 0.69 with `read_slang`) have install scripts in `third_party` (H11d, H11g; `install_all.sh --no-tools` skips them). Without them, the tests that need them are skipped.
- **The Docker image** (`docker/build.sh [ref]`) includes Z3, harm-coi, Verilator and Icarus, and runs the fast tests while building.
- **The test suite** has grown from 35 to about 230 tests, with independent oracles: brute-force enumeration, iverilog and Verilator simulation, Spot, and hand-labelled fixtures (the report's validation chapter).

## Known limitations
- **The missing operators** `%`, `**`, reduction operators (`&v`, `|v`, …) and `~^` are H20 (optional).
- **The warning and error logs** (`warning.log`, `error.log`) are JSON arrays rewritten at their end on every message: in a working directory where they have grown large, a run that emits many warnings slows down (found in H19; delete them, or run in a fresh directory).
- **x/z values:** on cycles where a signal has `x` or `z` bits, HARM's verdicts can differ from a SystemVerilog simulator's (README, "x and z values").
- **Reduction cost:** `--reduce implies` and `--atom-premises` grow with the square of the number of assertions; on several thousand assertions they can take tens of minutes.
- **Ties in the decision tree** are decided by the last bit of a floating-point score. Platforms agree because they now round the same way (H12); a change of `libm` could still change a choice with `ENT`.
- **Some formulas the grammar accepts cannot be evaluated** (e.g. `F X X (a W c)`), and a trace signal named like an operator (`W`) cannot be loaded. Both predate v4.
- **The `camellia` example's configuration is not valid XML** (a raw `&`); `sub_platform` is the same design and runs.

## Where each change comes from
The plan is `doc/plan/PLAN.md`; each milestone has a plan (`doc/plan/H*_PLAN.md`) and a validation entry (`doc/plan/VALIDATION.md`); decisions are in `doc/plan/DECISIONS.md`.

| Milestone | What |
|---|---|
| H0 | regression baselines; deterministic output (D-001); one toolchain (D-010) |
| H1 | proposition and SVA language (D-002); F9, F10 |
| H1b | x/z semantics, documented (D-011) |
| H1c | `--trace-end` (D-015, D-016) |
| H1d | SVA `->` and Spot brackets (D-021) |
| H2 | Z3 back end, `--reduce equiv` (D-003) |
| H3 | `--reduce implies`, `--keep`, `--dump-implications` (D-004, D-008) |
| H3b | `--atom-premises` (D-025) |
| H4 | `coi.json` contract and RTL fixtures (D-005, D-013) |
| H5 | harm-coi (D-006, D-019) |
| H6 | COI rank mode, `origin` (D-014) |
| H7 | COI filter mode (D-017, D-018) |
| H8 | depth-aware filter (D-007, D-020) |
| H9 | `--dump-coi-report` (D-022) |
| H10 | RTL predicates, `--emit-config` (D-023) |
| H11 | evaluation, `--version`, Docker (D-026, D-027) |
| H11b | HARM builds on Linux (F-L1); `ImplicationTest` timeout (F-L2) |
| H11c | yosys probe (F-L3), vector ranges (F-L4, D-028), wide predicates (F-L5) |
| H11d | Verilator, Icarus and yosys in `third_party` |
| H11e | fixtures and oracles independent of the Verilator version (F-L6, F-L7, F-L8, F-L10; D-029) |
| H11f | log files under concurrent writers (F-L9) |
| H11g | `install_verilator.sh` on macOS (F-M1) |
| H12 | the same assertions on macOS and Linux (F-M2) |
| H13 | profiling opt-in (`HARM_PROFILE`) |
| H15 | `--dump-prop-table` (D-031) |
| H16 | `--check-dump-eval` file names and `index.json` (D-030) |
| H17 | bitwise operators on `bool` (D-032), float exclusions, sorted trace directories (D-033) |
| H18 | operators and printing as in C and SystemVerilog (D-034) |
| H19 | evaluation and conversions as in SystemVerilog (D-035) |
| H20 | (planned, optional) missing operators: `%`, `**`, reductions, `~^` |
