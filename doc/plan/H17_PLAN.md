# H17 plan: the findings left open by H15 and H16

*Status: approved 2026-10-09 by the user (F1 option (a); the ANTLR 4.13.2 download). Branch: `ms/H17-open-findings` (from `dev` @ `886e675`). Effort: 1–1.5 d, plus a full `ctest`. Linux `ctest` stays pending, as the user asked.*

Four findings, each reproduced on the Mac (`dev` @ `886e675`):

| # | Finding | From | Reproduced |
|---|---|---|---|
| F1 | Bitwise `&`, `\|`, `^` (and `~`) reject a `bool` operand: `<prop exp="a ^ b">` and `G(a ^ b -> c)` stop HARM with a parse error | H16 | yes: `a ^ b`, `a & b`, `a \| b`, `a ^ p` (bool with 1-bit logic) fail; `p ^ q` (logic) and `x ^ y == 1` (int) work. `bool` exists only in CSV traces (VCD signals are `logic`) |
| F2 | A float `<numeric>`'s excluded values (`clustering="...,2E"`) are compared with the **cycle index**, not the value (`Clustering.cc`, `gatherElements`) | H15 | yes: with `2E`, `f == 2` is still generated, and the value at cycle 2 is dropped instead. Integers are right (`5E` removes `i == 5`) |
| F3 | `--check-dump-eval`'s `"file": null` path (a file that cannot be opened) has no test | H16 | — (a test gap) |
| F4 | `--vcd-dir`/`--csv-dir` take the files in the directory's order, which is unspecified, so the merged trace's cycle numbering can differ between machines | H15 | yes: `examples/multiTrace` and `examples/process` are read unsorted on the Mac (`counter5, counter4, counter1, …`) |

## F1: bitwise operators on `bool` operands (D-032)
- **The cause:** in `proposition.g4`, `&`, `|`, `^`, `~` are `numeric` rules, and a `bool` variable is only a `boolean`. Letting every `bool` atom be a `numeric` would make many parses that work today ambiguous (`a == b`, `$past(a)`, concatenations), and ANTLR would resolve them differently, changing trees and printing.
- **The fix:** a `bool` atom is accepted as a `numeric` **only as an operand of a bitwise operator** (the token before it is `&`, `|`, `^` or `~`, or the token after it is `&`, `|`, `^`): a semantic predicate in the grammar. No parse that succeeds today changes. Semantics as in SystemVerilog: the `bool` is a 1-bit unsigned value; the result is true where it is non-zero (with x/z as D-011: `a ^ p` with `p = x` is false).
- **Representation and printing:**

  | | Option | Printing of `a ^ b` | Cost |
  |---|---|---|---|
  | **(a) recommended** | a new cast node `BoolToLogic` (bool → 1-bit `logic`), printed as the bare operand | `a ^ b` | the node, plus the printer, copy and Z3 visitors (about 5 files) |
  | (b) | reuse the concatenation's ternary (`b ? 1'b1 : 1'b0`) | `(a ? 1'b1 : 1'b0) ^ (b ? 1'b1 : 1'b0)` | no new node; valid SystemVerilog, unreadable |

  Concatenations keep their current printing (changing it would change existing output).
- **Limits, documented:** the operand must be a variable or constant, not a parenthesised or negated Boolean (`(a && b) ^ c`, `!a ^ b` are still errors; `~a ^ b` works). Inside templates, `&` and `|` keep their temporal meaning (`G(a & b -> c)` is `{a & b}`, as today); `^` has none, so `G(a ^ b -> c)` reaches the proposition parser.
- **The parsers are generated and committed** (`doc/DEVELOPER_GUIDE.md`): they must be regenerated with ANTLR 4.13.2, the runtime's version. This Mac has the 4.10.1 and 4.13.1 tools only, so the 4.13.2 tool jar is fetched from Maven Central (`org.antlr:antlr4:4.13.2:complete`) into a scratch directory, and its SHA-1 is checked against Maven's.

## F2: float exclusions (a bug fix)
- Compare each value with the excluded constants **numerically** (each `<N>E` parsed once as a number), for floats; integers and logic keep their exact string comparison, which is right. `2E` and `2.0E` then exclude the same float value.
- Changes results only for configurations with a float `<numeric>` and an `E` option (none in `examples/` or the tests: the only `E` option there is `0E` on the integer numerics of `examples/nonBoolDT`, which the fix does not touch). Listed under the release notes' bug fixes.

## F3: the `"file": null` test
- A gtest: the dump directory is set to a **regular file** (so opening `<file>/<name>.csv` fails, even as root, unlike a read-only directory), two assertions are checked: no exit, a warning, two index records with `"file": null`, and their contexts and texts.

## F4: sorted trace directories (D-033)
- `--vcd-dir` and `--csv-dir` sort the file list by path (byte order), as `--fd` already does before its fixed shuffle (D-001). Cycle numbering then no longer depends on the machine.
- **Expected:** the mined assertions do not change (the `multiTrace`, `process` and `process_trace_end_sva` baselines pass on the Mac and on Linux today with different directory orders). If a baseline changes anyway, I stop and report it before updating anything.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| A1 | **F1, values:** gtest `BitwiseBoolTest`: on all assignments of `bool a, b, c`, plus `logic p` (0, 1, x) and `logic [3:0] v`, the propositions `a ^ b`, `a & b`, `a \| b`, `~a`, `~a ^ b`, `a ^ b ^ c`, `a & b \| c`, `a ^ p`, `a ^ v`, `a & v` evaluate as a truth table written by hand (SystemVerilog: `a ^ v` with `a = 1, v = 4'b0011` is `4'b0010`, true) | hand |
| A2 | **F1, text:** each prints back as written (`a ^ b`, …) in Spot LTL and SVA, and the printed text re-parses to the same values; `G(a ^ b -> c)` runs in check mode; with `--reduce equiv`, Z3 proves `a ^ b` ≡ `a != b` and `a & b` ≡ `a && b`, and the H2 brute-force enumeration agrees; `(a && b) ^ c` and `!a ^ b` still fail with a parse error, not a crash | hand, brute force |
| A3 | **F2:** a CSV with a float `f` and an int `i`: with `2E`, `--dump-prop-table` lists no `f == 2`; `2E` and `2.0E` give the same propositions; the value at cycle 2 still counts; `5E` on `i` unchanged (hand-written expected proposition sets) | hand |
| A4 | **F3:** gtest `CheckDumpTest` as above | — |
| A5 | **F4:** `--dump-prop-table`'s `traces` are in path order for `examples/multiTrace/csv`, `examples/process/traces`, and a VCD directory with `t1.vcd` written before `t0.vcd`; the H0 baselines byte-identical | — |
| A6 | Full `ctest` on the Mac (background); `h14_doc_coverage` with H17, D-032 and D-033 cited in the release notes and the report | ctest |

## Documents
DECISIONS D-032 (bitwise operators on `bool`), D-033 (sorted trace directories); README (operators table: `bool` operands; `--vcd-dir`/`--csv-dir` order); release notes and migration guide (bug fixes: F2; the trace order); report (reference tables); VALIDATION; PLAN status; TRIVERGENCE_IMPACT (F1 lets trivergence's hints use `^` on CSV `bool`s; F4: cycle numbering of multi-trace runs is now stable).

## Not in scope
- The precedence of `!` against comparisons (`!x == y`), and Boolean operands of `^` that are not atoms.
- Linux `ctest` for H15, H16, H17 (the user's choice: later).
