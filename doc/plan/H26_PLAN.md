# H26 plan: constants assigned outside a reset branch (harm-coi)

*Status: draft, for the user's approval. Asked by the user (2026-10-13: "yes, plan the constant-assignment follow-up for satacc/B04") after H25's measurement. Branch `ms/H26-constants` from `dev` @ `213d50c`. Effort: about 1 d (harm-coi 0.5 d, the measurement 0.5 d).*

## Why
harm-coi makes a proposition of a register's constant value only in the reset branch (H10's reset values, D-023). A constant assigned anywhere else gives none: H24's relations skip an assignment whose right side is a constant, assuming "a reset value or a constant comparison already" (`relations.py`), which is true only in the reset branch. On D1's `satacc`:

```
if (sum > 13'sd2047)       begin acc <= 12'sd2047;  sat <= 1'b1; end
else if (sum < -13'sd2047) begin acc <= -12'sd2047; sat <= 1'b1; end
```

`acc == 12'sd2047` and `acc == -12'sd2047` are no proposition, so HARM cannot state the saturated values, and `satacc/B04` (negative saturation at −2048) is missed by every HARM arm (H25: 46 of 49, B04 among the 3 missed). `sat`'s values are covered (1-bit flags have both polarities since H24).

Counted on 2026-10-13 (harm-coi `dev` @ `213d50c`; assignments of a constant to a whole visible signal outside the reset branch; distinct target and value):

| Designs | Distinct constants | Predicates today |
|---|---|---|
| D1 (12 designs) | 0–6 per design (27 in total, 1-bit flags included; 6 designs have none) | 4–16 per design |
| P1, small (versatile_counter, sha3, uart, gost, ethernet, present, srdy-drdy, video) | 4–22 | 10–276 |
| P1, tables (ima encoder/decoder 108/104, uart_to_bus 91, gaussian 265, aes_cipher 5,121) | mostly case-statement lookup tables (an S-box: `8'h00: out <= 8'h63; …`) | 110–5,129 |

## What changes
1. **Constant propositions** (harm-coi, with relations): for a constant `c` assigned to a whole visible signal `x` outside the reset branch, the proposition `x == c` (with H25's rule for a signed target and a negative `c`: `$signed(x) == -w'sdN`), placed as a consequent like a relation (Q2): a registered assignment in the single-cycle `|=>` tree (domain 7), a combinational one in the `|->` tree (domain 6). An unconditional constant assignment (`assign x = 4'd3`) is skipped (a constant signal). A proposition harm-coi already writes (a reset value, a case label) is not duplicated; it gains the placement.
2. **Lookup tables** (Q1): a target with more than 8 distinct assigned constants gets none of them (counted as dropped, `-v` says why).
3. **1-bit targets:** unchanged (both polarities since H24).
4. **Switch:** part of the relations (on by default with `--hints` and `--emit-config`; `--no-relations` restores the output before H24). Designs with no constant assigned outside a reset branch give the output of before.

## Decisions (as recommended, unless the user changes them)
| # | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Lookup tables | (a) a target with more than 8 distinct constants gets none (b) the first 8 in source order (c) no cap | **(a)**: a table's values are data, and any 8 of 256 would be an arbitrary subset; without a cap aes_cipher would get 5,121 propositions, gaussian 265 |
| Q2 | Placement | (a) consequent only, in the single-cycle trees of the relations (domains 6, 7) (b) also as antecedent propositions (`a`, `dt`) | **(a)**: B04 needs a consequent; as antecedents they would grow every decision tree's alphabet (the cost H24 cut by moving conditional relations to their own trees) |
| Q3 | Where the switch lives | (a) with the relations (b) its own option | **(a)**: the constant is the relation of a constant right-hand side, the case H24 meant to cover |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| C1 | harm-coi on hand-written RTL: `acc <= 12'sd2047` under a condition gives `acc == 12'd2047` in domain 7; `acc <= -12'sd2047` gives `$signed(acc) == -12'sd2047`; a combinational constant under a condition goes to domain 6; `assign x = 4'd3` gives nothing; a reset value assigned again outside the reset branch is not duplicated; a target with 9 distinct constants gets none (dropped, with its reason); `--no-relations` and designs without such constants unchanged | hand-written expected propositions |
| C2 | HARM mines on H24's `satacc` fixture an assertion whose consequent is `$signed(acc) == -12'sd2047` (and one with `acc == 12'b11111111111`) | ctest |
| C3 | The H0 baselines and every earlier test unchanged | ctest |
| C4 | (portfolio, measured) D1 and D1b with `harm-rel` against H25's runs (`runs/d1/h25-20261013`, `h25-hunt-20261013`): no bug lost; whether `satacc/B04` is caught; the cost on P1's designs (sha3, ima_adpcm_encoder, uart; against `runs/p1-h24-cost4`): mining time, candidates, proofs | VALIDATION |

## Documents
DECISIONS D-040; harm-coi README; README (relations section); VALIDATION H26; PLAN row; RELEASE_NOTES_v4; the report's reference section; TRIVERGENCE_IMPACT.

## Not in scope
- Constants of a part of a signal (`x[3:0] <= 4'd0`), and memories.
- Lookup tables as relations (a table as a function of its index).
