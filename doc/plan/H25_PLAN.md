# H25 plan: signed RTL conditions and relations (harm-coi, HARM)

*Status: approved by the user (2026-10-13: "approved as recommended, go ahead with H25": Q1–Q3 as recommended). Asked by the user (2026-10-13: "yes, plan it") after the finding recorded in D-038: harm-coi turns a signed RTL comparison into an unsigned one. Branch `ms/H25-signed` from `dev` @ `e4c4169`. Effort: about 1.5 d with Q1 (a) (HARM 1 d, harm-coi and the measurement 0.5 d).*

## Why
A trace carries no signedness: HARM reads every VCD vector as an unsigned `logic` (`VCDtraceReader.cc`), and harm-coi writes its propositions with unsigned literals. For an RTL signal declared `signed` this changes what a proposition means, or drops it. Checked on HARM's fixture `tests/input/h24/satacc` (a copy of the miner portfolio's D1 design: `logic signed [12:0] sum = acc + x`; `if (sum > 13'sd2047) … else if (sum < -13'sd2047) …`), `dev` @ `e4c4169`:

| # | RTL | harm-coi writes | Effect |
|---|---|---|---|
| 1 | `sum > 13'sd2047` (a signed comparison) | `sum > 13'd2047` (unsigned) | true for every negative `sum` (its top bit set), where the RTL's condition is false |
| 2 | `sum < -13'sd2047` (a negative constant) | nothing, and no `-v` message | the condition of the negative saturation has no proposition (`cmp` drops a constant outside `0 … 2^w − 1`) |
| 3 | `assign sum = acc + x` (signed operands extended to 13 bits) | nothing (`-v`: "relation: sign extension") | the relation that D1's `satacc/B01` breaks (`x` added unsigned) is not offered |

Nothing false gets through: every mined assertion is checked on the traces and, in the portfolio, proved. The cost is the alphabet: HARM with relations (H24) still misses `satacc/B01` (3 above) and `satacc/B04` (negative saturation at −2048: 2 above, and its consequent `acc == -12'sd2047` is a negative constant too). Whether H25 catches them is measured (S7), not assumed.

## What changes
1. **HARM reads signedness** (Q1): the propositions harm-coi writes for a signed comparison, a negative constant or a sign extension mean what the RTL means, in HARM's evaluation and in the printed SVA.
2. **harm-coi, predicates:** a comparison whose two operands are signed (SystemVerilog §11.8.1: signed only if both are) is written signed (Q1); a constant outside the unsigned range of the signal is kept when the comparison is signed (`sum < -13'sd2047`); a comparison that is always true or false for the signal's range is still dropped. A comparison with an unsigned operand is written as today.
3. **harm-coi, relations (H24):** sign extension and signed comparisons, today "not translated", are translated (Q2); arithmetic right shift (`>>>`) stays out unless Q1 (a) makes it free (HARM has `>>>` on signed values since D-035).
4. **Unchanged:** designs with no signed signal give byte-identical output (S5); harm-coi's other rules; HARM's mining.

## Decisions (as recommended, unless the user changes them)
| # | Question | Options | Recommended |
|---|---|---|---|
| Q1 | How HARM learns that an operand is signed | (a) `$signed(e)` / `$unsigned(e)` in HARM's proposition language (SystemVerilog's system functions: same width, signedness changed), parsed, evaluated with H19's rules and printed as written in SVA and HARM's syntax; harm-coi writes `$signed(sum) > 13'sd2047`. (b) Signal types from the RTL: harm-coi declares `sum` as `logic signed [12:0]` in the configuration and HARM types the VCD variable so (a new configuration element); propositions then read as the RTL (`sum > 13'sd2047`). (c) harm-coi only, no HARM change: an unsigned rewrite with the same meaning (`!sum[12] && sum > 13'd2047`; `sum[12] && sum < 13'd6145`; sign extension as `((x[7] ? 13'd7936 : 13'd0) \| x)`) | **(a)**: the SVA reads as SystemVerilog would write it and holds in any context (the binding module's types do not matter); local to the expression; HARM's evaluator already has signed types and SystemVerilog's conversion rules (H19, D-035). (b) changes how HARM reads traces for every proposition over the signal, and its printed SVA depends on the bound module's declarations. (c) needs no HARM change but the assertions are hard to read and to review |
| Q2 | Scope | (a) predicates and relations (1–3 above) (b) predicates only | **(a)**: B01's relation needs the sign extension |
| Q3 | `$signed` in the miner portfolio's SVA subset | (a) check with the portfolio's subset check and OpenFPV (trace check and proof on `satacc`) before the measurement; if refused, record it and stop for the user (b) assume | **(a)** |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| S1 | harm-coi on hand-written RTL: `s > 13'sd2047` with `s` signed gives `$signed(s) > 13'sd2047`; `s < -13'sd2047` gives `$signed(s) < -13'sd2047`; a signed `s` against an unsigned operand stays unsigned (as SystemVerilog); always-true or always-false comparisons still dropped; an unsigned design's output unchanged | hand-written expected propositions |
| S2 | HARM (Q1 a): `$signed(e)` and `$unsigned(e)` parse; their value, width and signedness, alone and in comparisons, arithmetic, shifts (`>>>`) and with x/z bits, equal Icarus Verilog's on generated cases (as H19's `h19_evaluation_fixture`); printed SVA and HARM's syntax read back to the same proposition | Icarus Verilog; round trip |
| S3 | Relations (Q2): `assign sum = acc + x` with signed operands gives a relation with the sign extension; it holds at every cycle of `satacc`'s golden trace (H24's independent evaluator, extended to `$signed`) | the trace oracle |
| S4 | HARM mines on `satacc` (fixture of H24): an assertion whose antecedent reads `$signed(sum) < -13'sd2047` and whose consequent is the saturated value, and one with the relation `sum == …` | hand-written expectations; ctest |
| S5 | Without signed signals, harm-coi's output and the H0 baselines are byte-identical (`ctest`) | ctest |
| S6 | (portfolio, container) the propositions of S1/S3 pass the SVA subset check; OpenFPV's trace check agrees with HARM on `satacc`'s golden trace; a proof of one mined `$signed` assertion on `satacc` | pytest |
| S7 | (portfolio, measured) D1 with `harm-rel` on `satacc` (4 bugs) and the whole corpus with `--against` H24's run (`runs/d1/h24-final3-20261013`): no bug lost; whether `satacc/B01`, `B04` are caught; D1b likewise | VALIDATION |

## Documents
DECISIONS D-039; README (signed propositions, `$signed`); harm-coi README; VALIDATION H25; PLAN row; RELEASE_NOTES_v4; the report's reference section; DEVELOPER_GUIDE; TRIVERGENCE_IMPACT (facts: propositions may contain `$signed`).

## Not in scope
- Signedness of HARM's own mined numerics and ranges (HARM's ranges over a signed variable print unsigned literals; OpenFPV reads them the same, checked in H24).
- Signed types read from the VCD (Q1 b), real and `integer` handling (unchanged, D-035).
