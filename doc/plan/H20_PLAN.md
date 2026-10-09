# H20 plan: the missing SystemVerilog operators (H18 audit finding L4)

*Status: planned, awaiting approval. Branch: `ms/H20-missing-operators` (from `dev` @ `1f10fa0`, with H18 and H19). Effort: 2 d, plus `ctest -L parser` while iterating and one full `ctest`. Linux `ctest`: in Docker, as for H19; the real machine stays pending.*

## Why
Hints, `--check` assertions and trivergence's LLM-written SVA use SystemVerilog's operators. Today HARM rejects some of them with a parse error: a hint or a checked assertion that uses one cannot be read. Reductions (`|req`, `^data`) are common in SVA.

## Findings (H18's audit, L4; `<<<` and `>>>` were done in H19)
| # | Not supported today | SystemVerilog (IEEE 1800-2017) |
|---|---|---|
| L4a | `a % b` | §11.4.3: the remainder takes the sign of the first operand; `b == 0` gives x. Not legal on `real` (Table 11-1). Precedence and widths as `*` and `/` (Table 11-2, Table 11-21) |
| L4b | `a ** b` | §11.4.3, Table 11-4: `0 ** negative` is x; `x ** 0` is 1; any other negative exponent gives 0, except for a base of 1 or −1. The exponent is self-determined; the result has the base's width and signedness (§11.6.1, §11.8.1). With a `real` operand the result is `real`. Binds tighter than `*` and looser than the unary operators (`-2**2` is 4), **left-associative** (`2**3**2` is 64; checked with Icarus 12) |
| L4c | Reductions `&v`, `\|v`, `^v`, `~&v`, `~\|v`, `~^v`, `^~v` | §11.4.9, Tables 11-16 to 11-18: a 1-bit unsigned result, the operand self-determined, 4-valued (`&4'b10x1` is 0, `\|4'b00x0` is x). Unary, so at the highest precedence. Not legal on `real` |
| L4d | Binary `a ~^ b`, `a ^~ b` (XNOR) | §11.4.8: at the level of `^`. Today `a ^~ b` parses as `a ^ (~b)`, which has the same value, so nothing changes except its printing (`a ~^ b`) |
| L4e | `0xaB` (mixed-case C hex constant) | not SystemVerilog, a lexer bug: the `HEX` token accepts all-lower or all-upper digits only |

## Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | `%` by zero and `0 ** negative` on the 2-valued C integer types (no x) | (a) 0, the same rule as D-035 Q3 for `/` (b) something else | **(a)** |
| Q2 | `%` on `float` | (a) a parse error, as for `===` and the bitwise operators on floats (SystemVerilog does not allow it) (b) C's `fmod` | **(a)**: HARM's printed SVA must remain legal SystemVerilog |
| Q3 | System functions also missing in hints and `--check`: `$onehot`, `$onehot0`, `$countones`, `$isunknown` (common in SVA) | (a) not in H20, recorded as a candidate milestone (they are functions, not operators, and go through `nonTemporalFunction`) (b) add them to H20 (+1 d) | **(a)** |

**No decision needed:** reductions and XNOR follow the standard (4-valued); the precedence and associativity of Table 11-2; `0xaB`.

## How (for the reviewer)
- **Grammar** (`proposition.g4`): tokens `MOD '%'`, `POW '**'`, `RNAND '~&'`, `RNOR '~|'`, `XNOR '~^' | '^~'`; `**` as its own level between the unary operators and `* / %`; `BAND | BOR | BXOR | RNAND | RNOR | XNOR` added to the unary operators; `XNOR` at the level of `^`. The temporal grammar uses `&` and `|` between SEREs and formulas (`{a} & {b}`, `p | q`): tests A3 cover these and every template shape.
- **Nodes:** `IntMod`, `LogicMod`, `IntPow`, `LogicPow`, `FloatPow`, `IntBXnor`, `LogicBXnor`, and the six reductions on `logic` (an `int` operand is cast to `logic`; a `bool` is marked as a 1-bit operand as for D-032). Evaluation follows D-035 (`valueAt`, whole-x arithmetic, context widths); the printer gets the new precedence levels, so printed text re-parses to itself.
- **Z3:** reductions and XNOR exact; `%` and `**` opaque, as `/` is today.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| A1 | A new fixture `tests/oracle/fixture_h20/` (generator `gen_h20_fixture.py`, the H18/H19 checker, mode `fixture20`): `%` and `**` on every pair of the H19 types (signed and unsigned, C types and `logic`, `integer`, `time`), with zero divisors, negative and zero exponents, bases 0, 1, −1, −2; the seven reductions on every integral type and width, with x/z rows; XNOR; precedence and associativity (`-2**2`, `2*3**2`, `2**3**2`, `a % b * c`, `&q == 0`, `^a ^ b`, `a ~^ b ^ c`, `~&q \| r`); `float ** float`. Every case must agree, except the C-integer cases of Q1, checked by hand | iverilog, hand (Q1) |
| A2 | Round trip: every fixture expression, printed by HARM, re-parses to the same text (the H18 checker) | HARM itself |
| A3 | gtest `OperatorH20Test`: `%` on floats is a parse error (Q2); `0xaB == 171`; a reduction of a `bool` and of an `int`; temporal formulas that mix the new unary `&`/`\|` with SERE `&` and formula `\|` (`G({a} & {b} \|-> \|w)`, `G(a \|-> b \| \|w)`), and every template of `tests/input` still parses | hand |
| A4 | `Z3EquivalenceTest`: new pairs `a ~^ b` ≡ `~(a ^ b)`, `~&q` ≡ `!(&q)`, `\|q` ≡ `q != 0` (2-valued variables); `%` and `**` give "Unknown", never "equivalent" | Z3 |
| A5 | `ctest -L parser` while iterating; one full `ctest` before review; the H0 baselines byte-identical (H20 only adds syntax; if any baseline changes, I stop and report) | ctest |

## Documents
DECISIONS D-036 (Q1–Q3); README (operator table); release notes; report; VALIDATION; PLAN status; TRIVERGENCE_IMPACT (hints and `--check` accept SystemVerilog's reductions, `%`, `**` and XNOR; the adapter's rewrites can go).

## Not in scope
- `$onehot`, `$onehot0`, `$countones`, `$isunknown` (Q3).
- `==?`, `!=?`, `dist`, `++`, `--`, assignment operators: not used in assertion propositions (H18 audit).
- The real Linux machine.
