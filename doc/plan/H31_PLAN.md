# H31 plan: the report brought up to date

*Status: approved by the user 2026-10-16 ("U approve"). Owner: the portfolio's Mac session. Branch `ms/H31-report` from `ms/H30-console-lock` @ `0cdce5a` (both edit the report; H31 merges after H30). Documentation only: HARM's code does not change. Effort: about half a day.*

## Why
The user asked to update HARM's report with what changed since it was written. The committed `harm_v4.pdf` dates from 2026-10-10: it lacks H21 to H30. In the text:
- `harm-coi`'s features since H10 (hints H22, relations H24, signed RTL H25, constants H26, the default timescale H28) are one-line bullets under the portability section's "Smaller changes"; the `harm-coi` section describes only cones (H5) and predicates (H10);
- the introduction's "What is new" names none of them, nor the dumps for other tools (H15's proposition table, H29's implication record);
- the limitations contradict later milestones: a signal named like an operator "cannot be loaded" (fixed by H23), implication reduction "can take tens of minutes" and "a faster implication reduction" as future work (H29);
- the validation section counts 233 tests in 32 minutes (now 277) and omits the oracles added since H14;
- the reference has no table of `harm-coi`'s options.

## Change
1. `06_harm_coi.tex`: subsections for hints, relations, signed RTL, constants and the timescale, moved out of "Smaller changes" and expanded (what is written, why, and its limits), with one example on the `counter` fixture that `h14_doc_examples` runs.
2. `01_introduction.tex`: "What is new" and the flow figure (the hints file next to `--emit-config`).
3. `09_limitations.tex`: the three contradicted items corrected; what stays open (parallel implication checks, which Spot's global BDD dictionary prevents) kept.
4. `08_validation.tex`: the test count and time; the oracles since H14 (H18/H19's operator audits against Icarus, H24/H25's check of every relation by HARM's evaluation).
5. `A_reference.tex`: a table of `harm-coi`'s options.
6. The PDF rebuilt and committed.

## Tests (written first, committed failing; in `doc/report/check_coverage.py`, run by `h14_doc_coverage`)
| # | Test | Oracle |
|---|---|---|
| T1 | Every `harm-coi` option (`tools/harm-coi/src/harm_coi/cli.py`) is in the report's reference | the parser |
| T2 | Every `harm-coi` milestone (H5, H5a, H10, H22, H24, H25, H26, H28) is cited in the `harm-coi` section | the board |
| T3 | The committed PDF cites every milestone on the board (pdftotext; a note when it is missing) | the board |
| T4 | `h14_report_builds`, `h14_doc_examples` pass | H14 |
| T5 | A read-through of the PDF: no statement contradicted by a later milestone | the milestones' VALIDATION entries |
