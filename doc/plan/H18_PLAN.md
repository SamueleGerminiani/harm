# H18 plan: operator precedence, conversions and printing, audited against C and SystemVerilog

*Status: planned 2026-10-09. Approved so far by the user: `!` binds as in C/SystemVerilog (option A); a numeric `!` is 2-valued (no new 4-valued logic, Q1 (b)); a Boolean compared with a number compares numerically, as C, C++, Python and SystemVerilog do (Q2 (a)). The user then asked for an audit of the precedence and conversions of every operator. The audit's findings and the proposed split into milestones below await approval. Branch: `ms/H18-not-precedence` (from `dev` @ `b05dcc7`). Linux `ctest` stays pending.*

## How the audit was done
- **Differential test** (`doc/plan/h18_audit/audit.py`, measured on `dev` @ `b05dcc7`): 1,154 expressions evaluated by HARM (`--dump-prop-table`, one HARM run per expression) and by Icarus Verilog 12 (SystemVerilog) on 40 rows of random 2-valued values (`bool`, `int`, `unsigned int`, `logic [3:0]`, `logic [7:0]`, `logic signed [3:0]`, `float`/`real`):
  - every ordered pair of the 17 binary operators (`A op1 B op2 C`);
  - `!`, `~`, unary `-` before each binary operator;
  - each operator on each pair of operand types;
  - Boolean-versus-number comparisons, context widths, ternaries.
  
  **387 differ or are rejected** (summary: `h18_audit/summary_dev_b05dcc7.txt`).
- **Code reading** (grammar `proposition.g4`, `implicitConversion.hh`, `GenericExpression.cc`, `Logic.cc`, `TypeCast.cc`, `PrinterVisitor.cc`). Every claim used below was then **checked on HARM**; one claim from the reading (`q + q == 5'd16` wrong) proved false and is dropped.
- C and C++ were checked with Apple clang where C and SystemVerilog could differ (they agree on every precedence question; `(x > 0) == y` is false in C, C++, Python and SystemVerilog, true in HARM).

## Findings

### P: precedence (the parser)
| # | Finding | Example: HARM reads / C and SV read |
|---|---|---|
| P1 | `!` on a numeric operand takes the whole expression after it (approved fix) | `!x == y`: `!(x == y)` / `(!x) == y` |
| P2 | `&`, `^`, `\|` bind **tighter** than comparisons; C and SystemVerilog put them **below** `==` | `x & y == y`: `(x & y) == y` / `x & (y == y)`; `x < y & y`: `x < (y & y)` / `(x < y) & y` |
| P3 | Comparisons are not operators of the numeric expression: they do not chain and their result is not a number (approved part: Q2) | `(x > 0) == y`: Boolean equality / numeric; `x < y == y`: same; `a < b < c`, `(a < b) + 1`: parse errors / legal |
| P4 | `<<` and `>>` are on two levels; Boolean `==` and `!=` too | `x >> y << k`: `x >> (y << k)` / `(x >> y) << k` |

### L: lexing and missing operators
| # | Finding |
|---|---|
| L1 | `x-1` (no spaces) is a parse error: the lexer reads `-1` as a negative literal. `x - 1` works |
| L2 | Unary minus and plus do not exist: `-x`, `-q + r` are parse errors |
| L3 | A `bool` in arithmetic or a relational comparison (`a + a`, `a < y`) is a parse error (H17 covered bitwise operators only) |
| L4 | Not supported (parse or lexer errors): `%`, `**`, reduction `&v \|v ^v ~&v ~\|v ~^v`, `<<<`, `>>>`, binary `~^`; `0xaB` (mixed-case hex) |

### E: evaluation and conversions
| # | Finding |
|---|---|
| E1 | **A shift amount ≥ the operand's width, or negative, stops HARM** with an error (SystemVerilog: 0). Common: `q << r` with `r ≥ 4` on a 4-bit `q` |
| E2 | The shift amount is read at the left operand's width: `t << 4` on a 2-bit `t` shifts by 0 |
| E3 | Signed with unsigned: HARM applies C's integer rules (`applyCStandardConversion`) to `logic` too; SystemVerilog makes the operation unsigned when any operand is unsigned, so `x < q` (`int` vs `logic`), `s < w` (signed vs unsigned `logic`), `q - r < 0`, `logic / int` differ (18–20 rows of 40) |
| E4 | `>>` on a signed operand is arithmetic (C); in SystemVerilog `>>` is always logical (`>>>` is arithmetic) |
| E5 | Integer division by zero is undefined behaviour (a crash is possible); SystemVerilog gives x (false, D-011) |
| E6 | Cast bugs: `LogicToInt` and `FloatToInt` test the wrong type for signedness (always unsigned); a signed `logic` wider than 32 bits is sign-tested with an `int` shift (undefined); signed based constants (`8'sb1111_1111`) are not sign-extended; the CSV type `int unsigned` is accepted by the grammar but has no mapping ("Unknown type") |

### R: printing that re-parses differently (HARM writes these texts into assertions)
| # | Finding | Checked |
|---|---|---|
| R1 | A right operand at the same level loses its brackets | `x - (y - k) == 3` prints `x - y - k == 3` (different values); `x / (y * k)` prints `x / y * k` |
| R2 | A select on an expression loses its brackets | `(x + y)[1:0]` prints `x + y[1:0]` |
| R3 | `!` over a comparison or `inside` | `(!x) == y` prints `!x == y`; `!(q inside {1, 5})` prints `!q inside {5,1}`, which SystemVerilog reads `(!q) inside` (wrong SVA today) |
| R4 | Literals | `4'b0x01` prints `4'bx01`, which re-parses as `4'bxx01` (a different constant); signed based constants lose their `s`; unsigned 64-bit constants print with a C suffix `ull` (not SystemVerilog); `2.0` prints `2` (same value) |

## Proposed split
| Milestone | Scope | Why together | Effort |
|---|---|---|---|
| **H18** (now) | P1–P4, L1–L3, R1–R3: the grammar follows C/SystemVerilog precedence (comparisons become numeric operators with a 1-bit result, `&`/`^`/`\|` below them, one level each for shifts and for `==`/`!=`, a numeric `!`, unary `-`/`+`, `bool` as a 1-bit number wherever a number is expected), and the printer brackets by the **same** table, so every printed proposition re-parses to itself | The printer must follow the parser; the precedence changes and the printer fixes cannot be tested apart | 3–4 d |
| **H19** | E1–E6, R4: shifts never stop HARM (≥ width gives 0, as in SV), shift amount at its own width, signedness rules, division by zero, the cast bugs, literal printing | Evaluation, not parsing; each changes values and needs its own decision | 2–3 d |
| H20 (optional) | L4: `%`, `**`, reduction operators, `<<<`, `>>>`, `~^` | New features | 1–2 d |

## H18 in detail

### Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q3 | P2 changes the meaning of text like `x & mask == 0` (HARM reads `(x & mask) == 0`, C and SV read `x & (mask == 0)`). Nothing in the repository writes it, and HARM's own output always brackets it (`(x & y) == y`), so mined output is unaffected | (a) follow C/SV (b) keep HARM's reading and document it | **(a)**, consistent with P1 and Q2 |
| Q4 | Signedness and `>>` (E3, E4) differ between C (HARM's `int`, `unsigned`) and SystemVerilog (`logic`). Decided in H19, not H18 | — | proposal for H19: C rules when every operand is a C type, SystemVerilog rules when any operand is `logic` |

### How (grammar)
- **Comparisons become numeric operators** with a 1-bit unsigned result, at their C/SV levels: `* /`, `+ -`, `<< >>`, `< <= > >= inside`, `== != === !==`, `&`, `^`, `|`. `&&`, `||` and `?:` stay Boolean. A numeric expression used as a condition is true where it has a known 1 bit (D-011, unchanged).
- **Prefix operators** `!`, `~`, `-`, `+` bind tightest. A standalone `!v` keeps today's value (2-valued, true where `v` has no known 1).
- **`bool` operands** become 1-bit numbers wherever a number is expected (generalising H17's `«x,bit»` marking, or by the grammar now that comparisons are numeric; the choice is made by the tests).
- **No new ambiguity is left to chance**: every ambiguity ANTLR reports (`-diagnostic` run on the A1 corpus) is listed and resolved by alternative order, with a test. H17's lesson: no semantic predicates.
- **x/z:** a comparison with an x/z operand is false (D-011), so its 1-bit result is 0; everything else is unchanged.

### Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| A1 | `h18_operators`: the audit made a test. The 1,154 expressions (and the bracketed SystemVerilog readings) against Icarus Verilog, on 2-valued values. Must agree, except expressions listed as H19 or H20 findings (E1–E6, L4), each listed with its finding id in the test, so that H19 shrinks the list | iverilog |
| A2 | The H1 oracle fixture (1,000 expressions, 4-valued) unchanged | iverilog (H1) |
| A3 | **Round trip:** every A1 and A2 proposition, and every proposition of every `examples/` and `tests/input/` configuration, prints to text that re-parses to the same values (and to the same text) | HARM itself |
| A4 | Hand cases (gtest): the table rows above; `!v` with `v = 4'b00x0` true; `a ^ b`, `!a ^ b` (now `(!a) ^ b`), `(a) == b`, `!(a)`, `c && !(a)` (H17's list) | hand |
| A5 | Z3 against brute-force enumeration on the new forms (`(x > 0) == y`, `x & (y == y)`, `!x + 1`) | brute force |
| A6 | Full `ctest`; the H0 baselines byte-identical, or each change explained (none expected: no example writes the changed forms) | ctest |

### Documents
DECISIONS D-034 (precedence and the Boolean/number rule), README (an operator table with precedence), release notes and migration guide (the changes of meaning: `!x == y`, `x & y == y`, `(x > 0) == y`: write brackets for HARM's old reading), report, VALIDATION, PLAN, TRIVERGENCE_IMPACT (hints are now read as C/SystemVerilog read them).
