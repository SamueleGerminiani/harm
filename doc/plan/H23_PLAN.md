# H23 plan: signals whose names are HARM keywords

*Status: draft, for the user's approval. Branch `ms/H23-reserved-names` from `dev` @ `b14c03b`. Asked by the user (2026-10-12) after H22's measurement: the fixture `hier` mines nothing because of a parameter named `W`; "Should we change the W parameter to something else like _W?" Answer: no, the fixture shows a general defect, fixed here. Effort: about 2 d.*

## Why
HARM refuses any trace whose variables include one of its keywords (`propositionParsingUtils.cc`, `checkReservedKeywords`: `X`, `W`, `G`, `next`, `until`, `always`, `and`, `or`, `not`, `true`, `false`, `inside`, `eventually`, `s_eventually`, `nexttime`, `substr`, `first_match`):

- **`hier`** (H4 fixture): Verilator dumps the parameter `W` as a variable; no proposition reads it, yet HARM stops: "The keyword W is reserved (in variable declaration): W". The whole design mines nothing (H22's VALIDATION; the portfolio's P1 measurement).
- **Real RTL:** `X`, `W`, `G`, `next`, `true`, `false`, `substr` are legal SystemVerilog names; `next` is common (an FSM's next state). One such signal anywhere in the dumped scope stops HARM on the whole design. Of the 21 designs of the miner portfolio's corpus, only `hier` has one today (`W`).
- **Keywords not in the list:** the temporal grammar also has `F`, `R` and `intersect` (`temporal.g4`). A variable with one of these names is not refused; whether formulas that use it are read correctly is not known (step 1 finds out).

## What changes
1. **Declaring** a variable with a keyword's name is no longer an error.
2. **Writing** it in a formula (a proposition, a template, `--dump`ed text read back): as a SystemVerilog escaped identifier, `\W ` (backslash, the name, a blank). A bare keyword keeps its meaning (`W` is the weak until), so no formula changes meaning; `\W ` is always the variable. Every other name is written as today.
3. **Printing**: SVA output prints the plain name (`W`: a legal SystemVerilog identifier, which is what the RTL calls it); HARM's own formula syntax prints the escaped form wherever HARM may read the text again.
4. **harm-coi** writes the escaped form for such signals in the propositions and hints it emits (H22's `hints` v1 unchanged otherwise).
5. **The list** is checked against the three grammars (`temporal.g4`, `proposition.g4`, `varDeclaration.g4`): every word token that can end where an identifier can (`F`, `R`, `intersect` and any others found) is handled the same way, or shown harmless by a test.

## Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Approach | (a) escaped references (above) (b) declare such variables but never use them: harm-coi drops predicates reading them, with a warning (fixes `hier`, loses `next`-like signals) (c) rename at trace load (`W` → `W_`), map back on output (collisions with real `W_`, two names for one signal in every log) | **(a)**: nothing is lost and no formula changes meaning |
| Q2 | Escape syntax | (a) SystemVerilog's escaped identifier `\W ` (b) a HARM-only form (`{W}`) | **(a)**: standard; slang and Yosys read it, so an LLM or a user can write it without learning HARM syntax |
| Q3 | Keywords missing from the list (`F`, `R`, `intersect`, …) | (a) test each; handle like the others where a test shows a misreading (b) add them to the list without testing | **(a)**: the list then follows the grammar, by test, not by guess |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| R1 | A new fixture `tests/input/coi/keywords/` (SystemVerilog, simulated as the H4 fixtures): signals and a parameter named `X`, `W`, `G`, `F`, `R`, `next`, `true`, `false`, `substr`, and an ordinary signal, related by known logic | hand-written expected assertions |
| R2 | HARM mines on it, with propositions over those signals **and** templates that use the operators `X`, `W`, `G`, `F`, `R`, `until`, `next` in the same formulas; every expected assertion is found, none has a keyword read as a variable or the reverse | R1's expectations |
| R3 | The parser on hand-written formulas: `\W ` is the variable, `W` the operator, in propositions and templates; a bare keyword-named variable in a formula is an error that names the escape | expected parse trees |
| R4 | SVA output prints plain names; HARM's own syntax prints `\W `, and reading it back gives the same assertion | round trip |
| R5 | harm-coi on `keywords` and `hier`: the escaped form in the emitted propositions and `hints.json`; `hier` now mines (`h22_mine_hier` expects assertions instead of the failure shared with `dev`) | hand-written; ctest |
| R6 | `ctest -L "coi|regression"`: the H0 baselines byte-identical (no design in them has such a name) | ctest |
| R7 | Portfolio: HARM on `hier` through `portfolio refine` yields candidates; their SVA passes the portfolio's subset check and OpenFPV's trace check | pytest (container) |

## Documents
DECISIONS D-037 (escaped references, Q1–Q3); README (writing such names in configurations); harm-coi README; VALIDATION H23; PLAN row; TRIVERGENCE_IMPACT (facts: a hint naming such a signal is written `\W `; traces with such names no longer stop HARM).

## Not in scope
- Names that are SystemVerilog keywords (`always`, `until`, `and`, …): RTL can only declare them as escaped identifiers; tested only if Verilator dumps them (R1 notes it either way).
- Any other change to HARM's grammar.
