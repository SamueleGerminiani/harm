# H43-struct-fields plan: a packed struct's field, when the trace has only the struct

*Status: approved by the user 2026-11-13 ("Approve"). The open case of CR1's C9-4 (the portfolio's CR1_FINDINGS.md: "the
struct-field case open, latent"). Owner: the portfolio's Mac session. Branch `ms/H43-struct-fields` from `dev`
(`46d610d`).*

## Why
Verilator dumps a packed struct as one vector unless it runs with `--trace-structs`. harm-coi's `--vcd` then maps a
field's atom (`s.hi`) to the vector's name (`s`), as cones need (cone.visible_names). Predicates and relations use the
same names, so they state something the RTL does not say. Reproduced (scratch: `pair_t s` = {hi[3:0], lo[3:0]}, a VCD
with `s [7:0]` only):

| RTL | harm-coi today | right |
|---|---|---|
| `y <= (s.hi == 4'd3)` | predicate `s == 4'd3` | `s[7:4] == 4'd3` |
| `s.hi <= a` | relation `s == $past(a, 1)` | `s[7:4] == $past(a, 1)` |
| `s.lo <= ~a` | relation `s == ($past(~a, 1) & 4'd15)` | `s[3:0] == ($past(~a, 1) & 4'd15)` |
| `q <= s.hi` | relation `q == $past(s, 1)` | `q == $past(s[7:4], 1)` |

These are false propositions given to the miners as the RTL's own (origin `rtl`). Without `--vcd`, or with a VCD that
has the fields, the names are right. Verilog designs have no structs, so AssertLLM2 is not affected; SystemVerilog
designs traced by Verilator's default are.

## Change
- A struct field's atom that is visible only through its enclosing vector is written as that vector's part-select,
  `s[msb:lsb]`, from the field's bit offset in the packed struct (slang's field offsets, nested structs summed); a
  bit select of the field is the vector's bit at offset + i.
- If the offset cannot be computed (an unpacked struct, an array of structs), the predicate or relation is dropped
  with a reason, as other untranslatable ones are.
- The cones are unchanged (a field's cone is the vector's, as today).

## Tests (written first, committed failing)
| # | Test |
|---|---|
| T1 | `tests/test_h43_struct_fields.py`: the four rows above, with a one-vector VCD: the right texts |
| T2 | the same design with a VCD that has the fields (`s.hi`, `s.lo`, as `--trace-structs` writes): the field names, as today |
| T3 | a nested struct and a bit select of a field: the summed offset |
| T4 | the full harm-coi pytest and `ctest -j4` on the Mac: no other output changes |

## Release
Merged into `dev` after the user's sign-off; HARM `main` and a `v4.1` release only when the user says so. The
portfolio's pin is unchanged until a portfolio milestone takes it.

## Effort
About 2 hours.
