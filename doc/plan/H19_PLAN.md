# H19 plan: evaluation and conversions as in SystemVerilog (H18 audit findings E1–E6, R4)

*Status: approved 2026-10-09 by the user: Q1 (a) SystemVerilog's rules for every operation, Q2 (a), Q3 (a), Q4 (a), Q5 (a). Implemented, awaiting review (VALIDATION, H19). Branch: `ms/H19-evaluation` (from `dev` @ `d1be73b`, with H18). Effort: 2–3 d, plus `ctest -L parser` while iterating and one full `ctest`. Linux `ctest` stays pending.*

## Why SystemVerilog is the reference
HARM prints SVA, and that SVA is checked by SystemVerilog simulators and formal tools (trivergence's OpenFPV, Verilator). Wherever HARM evaluates a proposition differently from SystemVerilog, it can mine an assertion that fails in simulation, or miss one that holds. C only matters where SystemVerilog and C agree, or where C leaves the case undefined (§6.5.5, §6.5.7: division by zero, shift amounts).

## Findings (from H18's audit, re-measured on `dev` @ `d1be73b`)
| # | Finding | Today | SystemVerilog (IEEE 1800-2017) |
|---|---|---|---|
| E1 | A shift amount ≥ the operand's width, or negative | **HARM stops** (`x >> 33`: "right side of right bit shift is greater than left side size") | 0 (§11.4.10: the amount is unsigned, vacated bits are zero) |
| E2 | The shift amount is read at the left operand's width | `t << 4` on a 2-bit `t` shifts by 0 | the amount is self-determined (§11.6.1, Table 11-21) |
| E3 | Signed with unsigned | C's rules (`applyCStandardConversion`), also for `logic`: `x < q`, `s < w`, `q - r < 0`, `u - s` differ on 18–20 of 40 rows | "if any operand is unsigned, the result is unsigned" (§11.8.1); the narrower operand is zero-extended (§11.4.4) |
| E4 | `>>` on a signed value | arithmetic (C, GCC) | logical; `>>>` is arithmetic (§11.4.10) |
| E5 | Division by zero | `int`: 0 on arm64, a crash (SIGFPE) on x86_64; `logic`: **HARM aborts** | x (§11.4.2), so false in a comparison or as a condition (D-011) |
| E6 | Conversions and types | `LogicToInt` and `FloatToInt` test the operand's type wrongly (always unsigned; `FloatToInt` of a negative value is undefined); a signed `logic` wider than 32 bits is sign-tested with an `int` shift (undefined); signed based literals (`8'sb1111_1111`) are not sign-extended; CSV `int unsigned` is accepted but has no mapping ("Unknown type"); CSV `integer` and `time` are read as binary, like `logic`, but stored as 2-valued integers | `integer` is 4-state 32-bit signed, `time` 4-state 64-bit unsigned (Table 6-8); `int unsigned` is legal |
| E7 | Arithmetic with an x/z operand gives a **1-bit** x, zero-extended (`Logic.cc`) | `(q + 4'bx) ^ 4'b1000` is `100x`, true | the whole result is x (§11.4.2): `xxxx`, false |
| R4 | Literal printing that re-parses differently | `4'b0x01` prints `4'bx01` (re-parsed `4'bxx01`); `8'sd5` loses its `s`; unsigned C constants (`0x10`, `0b101`, `…ull`) print as decimals (re-parsed signed) or with the C suffix `ull` (not SystemVerilog); `2.0` prints `2` | §5.7.1: a literal is padded with x when its leftmost digit is x |

## Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Signedness (E3) | (a) SystemVerilog's rules for every operation: unsigned if any operand is unsigned, the narrower operand zero- or sign-extended accordingly (b) SystemVerilog's rules when any operand is `logic` (including a `bool` and a comparison result, both 1-bit unsigned), C's otherwise (c) keep C's | **(a)**: the argument above; C and SystemVerilog differ only on promotions of narrow unsigned C types (`unsigned char` is promoted to a signed `int` in C) |
| Q2 | `>>` on a signed value (E4) | (a) logical, as SystemVerilog; add `>>>` (arithmetic on a signed result) and `<<<` (as `<<`), moved here from H20 (b) keep arithmetic for C integer types | **(a)** |
| Q3 | Division by zero (E5) | (a) `logic`: x (SystemVerilog); `int` (2-valued, it has no x): 0, the same on every platform, documented as a difference (b) `int` too behaves as x: a comparison or condition containing it is false at that cycle; needs an "unknown" flag through integer evaluation | **(a)** (no crash on any platform; (b) costs a change to every integer operator) |
| Q4 | CSV `integer` and `time` (E6) | (a) 4-state, as SystemVerilog: `logic signed [31:0]` and `logic [63:0]` (b) keep 2-valued integers, reading decimal values | **(a)**: they are already written in binary |
| Q5 | Literal printing (R4) | (a) every literal prints as text that re-parses to the same value **and type**: based literals keep a leading `0` before an x/z digit and their `s`; unsigned C constants print as SystemVerilog based literals (`0x10` → `8'h10`, `…ull` → `64'd…`); floats keep a decimal point (b) fix only the value-changing cases (`4'b0x01`, the lost `s`) | **(a)**: with Q1 (a), signedness changes values, so a constant must not change type when printed and re-parsed |

**No decision needed** (bugs, or behaviour C leaves undefined): E1 (0, as SystemVerilog), E2, the cast bugs of E6, `int unsigned`, E7 (the whole result x).

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| A1 | `h18_operators_fixture` with the H19 exemptions removed: its 351 `H19:` cases (shifts; signed with unsigned) become `ok` and must agree with Icarus (regenerating the fixture changes only its `expect` column; Icarus's values are unchanged) | iverilog |
| A2 | A new fixture `tests/oracle/fixture_h19/` (generator `gen_h19_fixture.py`, same checker): shifts by 0 … width + 3 and by negative amounts on widths 1, 2, 4, 8, 32, 64 (`<<`, `>>`, `<<<`, `>>>`, signed and unsigned); every operator on every pair of signedness and width; signed based literals; `integer` and `time` columns; arithmetic with x/z followed by bitwise operators (4-valued rows); `logic` division by zero. Every case must agree, except `int` division by zero, checked against Q3's rule by hand | iverilog, hand (Q3) |
| A3 | Round trip of literals (the H18 checker re-parses every printed proposition): `4'b0x01`, `4'bz101`, `8'sd5`, `-8'sd3`, `8'sb1111_1111`, `0x1F`, `0b101`, `18446744073709551615ull`, `2.0`, `-1.5` print to text that re-parses to the same values and the same text | HARM itself |
| A4 | gtest `ConversionTest`: `LogicToInt` of a negative signed `logic`, `FloatToInt` of `-2.5`, a 40-bit signed `logic` variable's sign, a CSV `int unsigned` column, `integer` with x/z values; no crash: `int` and `logic` division by zero, shifts by 100 and by −1 | hand |
| A5 | `ctest -L parser` while iterating; one full `ctest` before review; the H0 baselines byte-identical, **or each change listed and explained** (Q1, Q2 and Q5 can change values or texts of mined assertions on examples with negative integers, `>>` or hex constants; if any baseline changes, I stop and report before updating it) | ctest |

## Documents
DECISIONS D-035 (Q1–Q5); README (conversions, `>>>`/`<<<`, division by zero, CSV types); release notes and migration guide (changes of meaning); report; VALIDATION; PLAN status; TRIVERGENCE_IMPACT (HARM now evaluates as the simulators trivergence uses); H20 shrinks (`<<<`, `>>>` move here with Q2 (a)).

## Not in scope
- `%`, `**`, reduction operators, `~^` (H20).
- Linux `ctest` (the user's choice: later).
