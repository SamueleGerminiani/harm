# HARM v4: release notes

*HARM v4, released 2026-11-12. `harm --version` tells which build you run: `HARM v4` for the release, `HARM v4-<n>-g<commit>` for a later build of `dev`. Coming from v3? See also `doc/MIGRATING_v3_to_v4.md`. The full account, with how each part was validated, is the technical report in `doc/report/` (`make -C doc/report`).*

Every new feature is opt-in. With a v3 configuration and no new option, the output changes only as listed in the first section.

## Changes to default output
- **Deterministic order**: the same input gives the same output, run after run and for any `--max-threads`. Ties in the ranking are broken by the assertion's text. The `--max-ass` cut and the `--find-min-subset` covering subset are therefore reproducible too.
- **SVA printing** (`--sva`, `--sva-assert`):
  - `1'b1`/`1'b0` instead of `true`/`false`;
  - `p |=> q` and `##n` instead of `nexttime`;
  - `s_eventually` for unbounded `F`;
  - `a.b` instead of `a::b`;
  - brackets follow SystemVerilog's precedence (`(b until c) and (s_eventually d)`).

  The output is valid SystemVerilog accepted by Verilator. `<edit>` rules still match the old printing, so existing rules keep working.
- **`->` with a multi-cycle antecedent in SVA**: printed with its mined meaning (`G({a ##1 b} -> X c)` → `a ##1 b |-> c`). v3 put the consequent a cycle late.
- **Spot-LTL text** (the default output): `X(a && b)` keeps its brackets. v3 printed `Xa && b`, which Spot reads as `(X a) && b`.
- **Vector indices follow SystemVerilog**: on a vector declared `[1:10]` or `[10:3]` in the VCD, `x[i]` and `x[a:b]` use the declared indices, and an index outside the range is an error. Vectors declared `[n:0]` and CSV variables are unchanged. VCD traces with ascending ranges (`[1:10]`) load; v3 stopped on them.
- **Bug fixes that change results:**
  - a mined bit selection kept its bounds: v3 printed and evaluated `r[7:4]` as `r[4:7]`;
  - a variable name no longer corrupts a literal that contains it (`a` in `0xa`, `x` in `'b1x0`);
  - a template with more placeholders than propositions in their domain no longer hangs HARM;
  - **evaluation**: an operation with an unsigned operand is unsigned, also for C types (v3 followed C's rank rules, also for `logic`: `x < q` with a negative `int x` was true); a comparison is computed at its context's width (`ch << am == 0`); a decimal literal is 32 bits; `>>` is logical; a shift by the width or more gave an error and stopped v3, now 0; a `logic` division by zero aborted v3, now x; `(q + 4'bx) ^ 4'b1000` was true; CSV `integer`/`time` were 2-valued; `4'b0x01` printed `4'bx01` (a different constant). The regression baselines did not change;
  - **operators**: hand-written `!x == y`, `x & y == y`, `(x > 0) == y` now read as in C and SystemVerilog (v3 read `!(x == y)`, `(x & y) == y`, `(x > 0) == (y != 0)`); HARM's printed output always bracketed these forms, so mined assertions are unaffected;
  - **printing**: a printed proposition re-parses to itself. v3 printed `x - (y - k)` as `x - y - k`, `(x + y)[1:0]` as `x + y[1:0]`, and `!(q inside {...})` as `!q inside {...}` (wrong SystemVerilog);
  - a float `<numeric>`'s excluded values (`clustering="...,2E"`) are compared with the values: v3 compared them with the cycle index, so it kept `f == 2` and dropped the value at cycle 2 instead;
  - `--vcd-dir` and `--csv-dir` concatenate the files in path order, not the directory's order, which differs between machines; the cycle numbering of a multi-trace run (`--dump-prop-table`, failing sub-traces) is the same everywhere. The mined assertions did not depend on it;
  - on macOS arm64, the same assertions as on Linux x86_64. v3 could choose a different decision-tree antecedent among near-equal scores, because GCC fused a multiply-subtract on arm64. The fix changes nothing on Linux x86_64.
  - **`!` over a comparison in a template** prints with brackets, `!(x == c)`: the miner printed `!x == c`, which SystemVerilog and HARM read as `(!x) == c`, another property. A bare signal still prints `!b`; a parsed formula was already right;
  - **trace segments and the ranking**: a `|=>` (or offset) instance whose consequent falls past the end of its trace segment is pending, not judged on the next segment's first cycle; a decision-tree template expanded to `{a ##1 b} |=> c` gets the contingency table of the same text parsed. Some assertions with a `##` antecedent rank differently (the regression baselines `sub_platform1k`, `bl_master1h`, `svaFunctions` and `fsm` were rewritten, with the user's approval);
  - **concatenated VCD files**: `$past`, `$stable`, `$rose` and `$fell` do not read across the start of a file; a later one-file trace in the same run (a faulty trace of `--fd`) no longer uses an earlier trace's file starts;
  - **VCD times** past 2^31 units (2.1 ms at Verilator's 1 ps) are read correctly; `--dump-trace-as-csv` keeps each row's last character;
  - **a 1-bit VCD variable declared `[k:k]`** with `k` not 0 loads as a vector of range `[k:k]`, so `x` and `x[k]` name it; HARM stopped on it;
  - **with `--sva`, a plain `=>` is an error**: it was evaluated as `->` but printed as `|=>`, another property; `->` keeps its warning;
  - **the permutator** no longer crashes on a template with two equivalence clusters of placeholders, and every `--dump-implications` record of an `equivalent, implied` assertion names the kept assertions it was dropped for.

## New in propositions
- **SystemVerilog syntax:**
  - sized and based literals (`8'd9`, `4'hA`, `'0`, `'1`);
  - concatenation and replication;
  - `?:`, `===`/`!==`;
  - hierarchical names with `.` or `::`.
- **Invariant templates** `G(P0)`, without an implication.
- **`--skip-invalid-props`:** skips a proposition that does not parse, with a warning, instead of stopping.
- **x/z values** follow HARM's documented rule, not SystemVerilog's: README, "x and z values".
- **`origin="…"`** on `<prop>` and `<numeric>`, free text (e.g. `spec`, `rtl`), reported by `--dump-assertion-info` and `--dump-coi-report`.
- **Bitwise operators on CSV `bool` operands**: `a ^ b`, `~a & c`, `a ^ q4`, as in SystemVerilog (v3 stopped with a parse error).
- **Operators bind and convert as in C and SystemVerilog**: `!x == y` is `(!x) == y`; `x & y == y` is `x & (y == y)`; a comparison is a number (`(a < b) + 1`, `x < y < z`, `(x > 0) == y` compares numbers); unary `-` and `+`; `x-1` without blanks; `bool` operands of arithmetic and comparisons. The README has the precedence table.
- **Evaluation as in SystemVerilog**: signed/unsigned rules, context-determined widths, 32-bit decimal literals, `>>>`/`<<<`, shifts and divisions by zero that never stop HARM, 4-state `integer`/`time`, literals that print as they re-parse. The README describes each rule.
- **Hints from the RTL**: `harm-coi --hints FILE` writes signal roles, each proposition's placement and one template per target class (`--hints-use all|placement`); without `--hints` harm-coi's output is unchanged.
- **Signals named after HARM keywords**: a variable named `W`, `X`, `next`, `true`, … no longer stops HARM; write it `\W ` in a formula (a bare keyword keeps its meaning); SVA prints the plain name.
- **Relations from the RTL**: `harm-coi` with `--hints` adds by default (`--no-relations` turns it off) relations from assignments (`x == $past(e)`), the end of reset (`$fell(rst) |-> …`), both polarities of flags and `$stable` for registers held under a condition; in COI `filter` mode a proposition written in the template is no longer filtered.
- **Signed RTL**: `$signed(e)` and `$unsigned(e)` in propositions (SystemVerilog §20.5); harm-coi writes a signed RTL comparison on `$signed` (`$signed(sum) < -13'sd2047`; before: written unsigned, or dropped with a negative constant) and translates sign extensions and signed `>>>` in relations.
- **Constants**: with the relations, a constant assigned outside the reset branch (`acc <= 12'sd2047` under a condition) is a consequent `acc == 12'd2047`; lookup tables (more than 8 distinct constants) are left out.

## New options
| Option | What it does |
|---|---|
| `--reduce syntactic\|equiv\|implies` | remove redundant assertions: identical (default), equivalent propositions (Z3), or implied assertions (Spot plus HARM's finite-trace model) |
| `--keep stronger\|weaker\|ranked` | with `implies`: which side of an implication is kept |
| `--implies-max-pairs <N>` | with `implies`: skip the implication step for a context with more than `N` pairs to check (default `0`: no cap), recorded in `--dump-assertion-info` |
| `--implies-workers <N>` | with `implies`: the processes that check its pairs (default `--max-threads`, from 2,000 pairs per worker); the result does not depend on it |
| `--deadline <S>`, `--mine-deadline <S>` | seconds from HARM's start: the implication step checks pairs until `--deadline` (the rest count as unrelated); mining starts nothing after `--mine-deadline` (default 0.75 of `--deadline`) and what was mined is written; recorded in `--dump-assertion-info` |
| `--atom-premises`, `--atom-premises-max <N>` | with `implies`: also use facts between comparisons (`cnt > 9` ⇒ `cnt > 8`, exclusive FSM states) |
| `--dump-implications <file>` | the dropped assertions and what implies them, as JSON |
| `--dump-assertion-info <file>` | every kept assertion with its metrics, propositions, cycle offsets and origins, as JSON |
| `--trace-end harm\|sva` | how an obligation still pending at the end of a trace is judged: weak (default) or as a SystemVerilog simulator does |
| `--dump-prop-table <file>` | every context's propositions and their value at every cycle (`prop-table` v1), for miners that work on propositions (the portfolio's SAT miner) |
| `--dump-coi-report <file>` | for each consequent, the propositions outside its cone of influence |
| `--skip-invalid-props` | see above |
| `--version` | the version (`git describe`) |

**`--check-dump-eval <dir>` (a v3 option) has a new file format**. v3 named each assertion's CSV after its text with some characters deleted, so different assertions could overwrite each other's file without a warning (`a != b` and `a <= b`), and a name over 255 bytes stopped HARM. v4 names the files `<k>_<text>.csv`, with `k` the order in which the assertions are checked, and writes `index.json`, which maps each file to its context and its exact Spot-LTL and SVA text. Every row now has all five columns; v3 wrote only `t` and `Ant` for an assertion without a shift (`G(a -> b)`).

## Cones of influence (`<coi>`)
- **`<coi file="coi.json" mode="rank"/>`:** new metric variables `coiFrac`, `coiDepthFit` and `coiUnknown`, to sort or filter assertions by structural plausibility. Nothing is pruned.
- **`mode="filter"`:** never tries antecedents outside the consequent's cone, GoldMine-style; `depth="bounded|exact"` also uses the cone's depths. Filter mode assumes the RTL is correct, and says so once.
- **The file format** is `doc/schemas/coi.v1.json`.

## New tool: harm-coi (`tools/harm-coi`)
- **What it does:** reads SystemVerilog RTL (with pyslang) and writes `coi.json`, the cone of every signal, with depths. With `--predicates` it also writes the RTL's own predicates (conditions, case labels, FSM states, comparisons, reset values). `--emit-config` writes a ready-to-run HARM configuration from them.
- **Install:** Python ≥ 3.11, `pip install -e tools/harm-coi`. See `tools/harm-coi/README.md`.

- **Default timescale**: `harm-coi` gives slang `--timescale 1ns/1ps`, the default for a file without a `timescale`, as trivergence and OpenFPV do; a design that mixes files with and without one (AssertLLM2's `i2c_slave`) no longer fails to elaborate.
- **One name per net**: `harm-coi --aliases` (off by default) gives a port-connected net or an `assign a = b` one name in predicates, hints, relations and cones: its shallowest visible name, then a top input, then a top output, then string order. A select of a merged name is rebased to the kept name's declared range. `coi.json` gains `aliases`. On AssertLLM2's `i2c_slave` with traces, harm's assertions went from 4,737 to 3,439 (18 nets merged).
- **Clock domains**: `--domains` writes the clock-domain map (`doc/schemas/domains.v1.json`): clock roots with their registers, derived clocks, crossings, synchronizers, the resets each domain reads and each asynchronous reset's edge (`reset_edges`). `--cut-domains` with `--clock C` keeps C's domain only: other domains' registers, clocks, the inputs only they read and the signals computed only from those are cut (`coi.json`'s `cut`). Without the flags the output is unchanged; on a single-clock design it is byte-identical with them.
- **Larger designs**: harm-coi passes slang `--allow-use-before-declare` (a signal used before its declaration, AssertLLM2's `sdspi`, elaborates); the cone closure runs in linear time (`pci_bridge`'s domain map for `pci_clk_i`: 255 s before, 13.5 s after).
- **Correctness fixes**: a packed array's element select is not a bit; relations keep the context width (`sum <= a + b`); a path past the depth limit is clipped at `max_depth + 1`, not cut; a truncating cast is not its operand's signal, and a signed signal compared with a constant above its range gives no predicate; an `always_ff` with an event control harm-coi cannot read (`@(posedge clk iff en)`) makes its targets unknown (it crashed); a top `inout` port's leaves are unknown; relations walk generate-for blocks and instance arrays.

## Build, platforms and tests
- **Linux and macOS** (arm64): HARM builds and passes the same tests on both, and mines the same assertions.
- **Z3** is a new optional dependency (`third_party/install_z3.sh`, CMake option `HARM_WITH_Z3`, default ON).
- **One compiler for everything**: HARM and the libraries in `third_party` must be built with the same C++ compiler. The install scripts record it, and CMake warns on a mismatch.
- **`-ffp-contract=off`** for everything HARM's CMake builds, so that floating-point scores round the same way on every platform.
- **Profiling is opt-in**: `-DHARM_PROFILE=ON` builds for `gprof`. A default build no longer writes a `gmon.out` on every run.
- **Checked downloads**: every third-party tarball is downloaded over HTTPS with its certificate checked and kept only if its SHA-256 matches (`third_party/fetch.sh`); antlr4's tag `4.13.2` must be its known commit; every install script stops at its first error, and `install_all.sh` at the first failing script, naming it.
- **The tools the tests use** (Verilator 5.052, Icarus Verilog 13.0, yosys 0.69 with `read_slang`) have install scripts in `third_party` (`install_all.sh --no-tools` skips them). Without them, the tests that need them are skipped.
- **The Docker image** (`docker/build.sh [ref]`) includes Z3, harm-coi, Verilator and Icarus, and runs the fast tests while building.
- **The warning and error logs** (`warning.log`, `error.log`) are appended at a constant cost per message: before, every message rewrote the whole file, so a run that emitted many warnings slowed down as the logs grew. The files' format is unchanged.
- **The test suite** has grown from 35 to 284 tests (`ctest`), with independent oracles: brute-force enumeration, iverilog and Verilator simulation, Spot, and hand-labelled fixtures (the report's validation chapter).

## Known limitations
- **The missing operators** `%`, `**`, reduction operators (`&v`, `|v`, …) and `~^` are future work (planned, not scheduled).
- **x/z values:** on cycles where a signal has `x` or `z` bits, HARM's verdicts can differ from a SystemVerilog simulator's (README, "x and z values").
- **Reduction cost:** `--reduce implies` and `--atom-premises` grow with the square of the number of assertions. Only pairs sharing a consequent atom are checked (AssertLLM2's `i2c_slave`, 6,481 assertions: 1.2 M pairs instead of 5.7 M, 71 s instead of 479 s on an M-series Mac, 87 more assertions kept), and `--implies-max-pairs N` skips the step for larger contexts. The pairs are checked in worker processes (`--implies-workers`) and their relations kept per pair, not in an n × n matrix (AssertLLM2's `openmsp430`: 1,163 s before, 384 s after, the same 11,532 assertions in the same order); with `--deadline`, a pair not checked by then counts as unrelated, so a cut run keeps assertions that a full run drops. There is no cap by default: the miner portfolio measured the step at about 1% of the prover time it saves (36 runs: 9 s of reduction against 964 s of proving the 384 dropped assertions), and on `i2c_slave` harm-rel (2.29 M pairs) it takes 139 s and drops 2,550 of 11,041 assertions.
- **Ties in the decision tree** are decided by the last bit of a floating-point score. Platforms agree because they now round the same way; a change of `libm` could still change a choice with `ENT`.
- **Some formulas the grammar accepts cannot be evaluated** (e.g. `F X X (a W c)`), and a trace signal named like an operator (`W`) cannot be loaded. Both predate v4.
- **The `camellia` example's configuration is not valid XML** (a raw `&`); `sub_platform` is the same design and runs.
- **harm-coi and packed structs**: a truncating cast of a packed struct's member is still taken as the member's signal; Verilog designs, which have no structs, are not affected.

## More detail
The technical report (`doc/report/`) explains each change and how it was validated; `doc/MIGRATING_v3_to_v4.md` says what to do when moving from v3.
