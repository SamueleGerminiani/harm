# H18 plan: `!` binds as in C and SystemVerilog

*Status: planned 2026-10-09, awaiting approval (the user chose option A: SystemVerilog precedence). Branch: `ms/H18-not-precedence` (from `dev` @ `b05dcc7`, with H17). Effort: 1.5–2 d (2–3 d with Q2 (a)), plus a full `ctest`. Linux `ctest` stays pending.*

## The problem (found in H17, reproduced on `dev`)
In C, C++, Java, Verilog and SystemVerilog, `!` is a unary operator that binds tighter than every binary operator. HARM gets it right on Boolean operands (`!a && b` is `(!a) && b`, `!a == b` is `(!a) == b`), but on a **numeric** operand (`int`, `logic`) `!` takes the whole comparison or arithmetic expression after it:

| Written | HARM reads (prints) | SystemVerilog reads |
|---|---|---|
| `!x == y` | `!(x == y)` | `(!x) == y` |
| `!x < y` | `!(x < y)` | `(!x) < y` |
| `!p ^ q` | `!(p ^ q)` | `(!p) ^ q` |
| `!v + 1 == 1` | `!(v + 1 == 1)` | `(!v) + 1 == 1` |

- HARM **prints** the brackets, so its output is valid SystemVerilog with HARM's meaning; only hand-written input is misread. With `x = 0, y = 2`: SystemVerilog `(!0) == 2` is false, HARM `!(0 == 2)` is true.
- **The cause:** in `proposition.g4`, `!` takes a `boolean`, and `numeric relop numeric` is a primary `boolean` alternative, so `NOT boolean` swallows the whole comparison; there is no `!` on numerics.
- **Who is affected:** hand-written `<prop>`, `<numeric>` and templates (LLM-written hints included). Nothing in `examples/` or `tests/` writes it, and `harm-coi` brackets every negated predicate other than a single signal or bit (`predicates.py`), so its configurations are unaffected.

## The fix (D-034)
- **Grammar:**
  - a numeric logical not, `numeric: NOT numeric`, with the precedence of `~` (the highest), giving a 1-bit unsigned value;
  - the Boolean `!` takes a restricted operand (an atom, a select, a function, a bracketed expression or another `!`), so it can no longer swallow a comparison, an arithmetic or a bitwise expression;
  - where both readings remain possible (`!x` alone), the Boolean `!` is preferred, so a standalone `!v` keeps its value.
  - The lesson of H17 applies: no predicates; every new ambiguity is listed and resolved by alternative order, and tested.
- **Values** (the x/z question):

  | | Option | `!v` with `v = 4'b00x0` | `(!v) == 1'b1` |
  |---|---|---|---|
  | **(a) recommended** | SystemVerilog inside numeric expressions: `!v` is `1'bx` when `v` has x/z bits and no known 1. A standalone proposition `!v` keeps HARM's 2-valued rule (D-011) | true (unchanged) | false (a comparison with x, D-011), as a simulator |
  | (b) | 2-valued everywhere: numeric `!v` is 1 when `v` has no known 1 | true | true (a simulator says x, so false) |

  (a) matches SystemVerilog and the H1 oracle's model (comparisons with x/z are false); D-011's rule that a proposition and its negation are complementary still holds for propositions.
- **`!` on a `bool` before a bitwise operator** (H17 made `!a ^ b` an error because of this bug): with `!` binding tightly, `!a ^ b` becomes `(!a) ^ b`, as in SystemVerilog; the H17 exclusion in `addTypeToExp` is removed.
- **Printing:** the numeric `!` prints `!x`; the printer brackets where SystemVerilog precedence needs it, so every printed proposition re-parses to the same value. Propositions that print today print the same (`!(x == y)` stays `!(x == y)`).
- **Z3:** the new node is encoded 4-valued, like the other logic operators.

## Related findings (measured while planning) and a question for you
- **F2: a Boolean compared with a number.** `(x > 0) == y` is read as a Boolean equality, `(x > 0) == (y != 0)`; SystemVerilog compares the 1-bit result with `y` (with `x = 1, y = 2`: HARM true, SystemVerilog false). It predates v4.
- **F3: a printing bug.** `(!x) == y` (Boolean equality today) prints `!x == y`, which HARM itself re-reads as `!(x == y)`: on `x = 1, y = 2` the printed text is false where the proposition was true. After the fix, `!x == y` reads as SystemVerilog does, so the printed text would mean `(!x) == y` numerically, still not the Boolean equality it was printed from.

| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | x/z of a numeric `!` | (a) or (b) above | **(a)** |
| Q2 | F2 and F3 | (a) in H18: a comparison (`==`, `!=`, relational) with a numeric operand on either side compares numerically, the Boolean side as a 1-bit value, as in SystemVerilog; the printer brackets so that text re-parses to the same value. A Boolean-only comparison (`a == b` on `bool`s) is unchanged. (b) only record them; H18 fixes `!` alone | **(a)**: after H18, `(!x) == y` would otherwise be numeric and `(x > 0) == y` Boolean, two readings of the same shape |

With Q2 (a), A2 adds `(x > 0) == y`, `(!x) == y`, `(a && b) != q4` on hand values, A4 covers F3 (every printed proposition re-parses to the same values), and A1's generator also produces Boolean-versus-number comparisons.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| A1 | **Icarus Verilog, random expressions:** a new fixture `tests/oracle/fixture_h18/` (the H1 fixture is golden and stays as is), generated by `gen_iverilog_fixture.py --not-precedence`: about 500 expressions with an unbracketed `!` before numeric operands of comparisons, arithmetic, bitwise operators, selects, `!!`, `~!`, on the H1 trace pool (4-valued, widths 1–70). A proposition holds exactly where the H1 HARM model (SystemVerilog with comparisons on x/z false) is 1 | iverilog 12 |
| A2 | **Hand cases** (gtest `NotPrecedenceTest`): the four rows above on hand-chosen values (`x = 0, y = 2` and so on); `!v` with `v = 4'b00x0` true, `(!v) == 1'b1` false; `!a ^ b` is `(!a) ^ b` on all `bool` assignments | hand |
| A3 | **Unchanged readings:** `!a && b`, `!a \|\| b`, `!a == b`, `!(x == y)`, `!x`, `!v`, `!(a)`, `!$past(a)`, `!x && y`, `!q4[1]` keep their values and printing; the existing H1 oracle fixture (1,000 expressions) passes unchanged | hand, iverilog |
| A4 | **Printing:** each A1 and A2 proposition prints to text that re-parses to the same values; `--sva` output of templates using them is accepted by Verilator lint (as H1 did) | re-parse, Verilator |
| A5 | **Z3:** `!x == 1'b1` ≡ `x == 0`, `(!p) ^ q` ≡ `p == q` (1-bit), and a few non-equivalences, against brute-force enumeration (H2) | brute force |
| A6 | Full `ctest` on the Mac; the H0 baselines byte-identical (they contain no such text); `h14_doc_coverage` with H18 and D-034 | ctest |

## Documents
DECISIONS D-034; README (the operators section: precedence, x/z of numeric `!`); release notes and migration guide (a change of meaning for hand-written `!x == y`: **write `!(x == y)` if that is what you mean**); report (reference tables, the language chapter); D-032 updated (`!a ^ b` now accepted); VALIDATION; PLAN status; TRIVERGENCE_IMPACT (hints written with C/SystemVerilog precedence are now read as written).

## Not in scope
- F2 and F3, if you choose Q2 (b).
- Linux `ctest` (the user's choice: later).
