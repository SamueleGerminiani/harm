# H47-design-sizes plan: the size of each design in the hint-level study (approved by the user 2026-11-15)

## Why
- The user, 2026-11-15: "add a column to table IV to report the size of the design (number I/O, number of RTL lines)",
  then "add sizes.py to the package". The letter's Table IV now reports, per design, the input/output ports and the
  lines of RTL; this milestone makes those numbers reproducible from the HARM tag the letter cites.

## What is added (`eval/hint-levels/`, evaluation code only; `harm` and `harm-coi` unchanged)
1. **`sizes.py <corpus.json> [--designs ...] [--out sizes.csv]`:** per corpus design, elaborated with `eval/mutants`'
   own `elaborate()` (pyslang) at the corpus's defines: the top's input and output ports (clock and reset included)
   and their bits, and the non-blank, non-comment lines of the PULP files the design compiles (submodules included,
   the corpus wrapper excluded).
2. **`results/sizes.csv`:** the 20 corpus designs.
3. **`reproduce.sh`:** a `sizes` step; **`tables.py`:** prints the sizes when `sizes.csv` is present; **README:** rows.

## Tests (written first, committed failing)
| # | Test |
|---|---|
| T6 | `sizes.py` gives Table IV's values on the 10 base designs (I/O 5/3 … 5/4; LoC 91 … 35, 1,449 in all) and `results/sizes.csv` equals its output on the 20 designs; skipped when common_cells has not been fetched |

T1 (no private path or internal code; standard library, pyslang and local modules only) now also covers `sizes.py`.
ctest stays at 289 tests: T6 runs under `h46_unit`.

## Closing
VALIDATION entry, PLAN.md row, H47 in the report's milestone table (PDF rebuilt); after the user's sign-off, a
`--no-ff` merge into `dev`, `dev` into `main`, tag `v4.1.2`, a GitHub release with neutral notes, no new Docker image.
