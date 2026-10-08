# H14 plan: documentation and a LaTeX report on what is new in HARM v4

*Status: approved 2026-10-08 by the user (technical report, no evaluation section, developer guide added). Branch: `ms/H14-v4-report` (from `dev` @ `55bc66a`). Effort: 3–4 d.*

## Why
- `v3..dev` is 222 commits and about 49,000 added lines across H0–H13. What changed is spread over `README.md`, `doc/RELEASE_NOTES_v4.md`, 25 plan files, `DECISIONS.md` (D-001–D-029) and `VALIDATION.md`.
- Nobody outside this plan can read it in one place, and the release notes are already behind: they cite D-001–D-027 and say nothing about H11b–H13 (Linux build, tools in `third_party`, the same assertions on macOS and Linux, `HARM_PROFILE`).
- The v4 release (`dev` → `main`, tag `v4`) needs user-facing documentation that is complete and checked before it happens.

## Scope
### 1. User documentation (Markdown, in the repository)
- **`doc/RELEASE_NOTES_v4.md`, finished:** every milestone H0–H13, every decision that changes default output, D-028 and D-029, the build changes (`-ffp-contract=off`, `HARM_PROFILE`, tools in `third_party`).
- **`doc/MIGRATING_v3_to_v4.md` (new):** for a v3 user: what output changes with the same configuration and why, how to get the old behaviour where possible, what to change in scripts that parse HARM's output (SVA printing, order, `->`), new dependencies.
- **`README.md` audit:** every new option and XML element has a section with a runnable example; the table of contents is updated; stale text (e.g. the macOS build section after D-010 and H12) is corrected.
- **`tools/harm-coi/README.md` audit:** the same, for `harm-coi`.
- **`doc/DEVELOPER_GUIDE.md` (new, asked by the user):** the purpose of each part of the project, for someone who will change HARM:
  - the repository layout: every top-level directory (`src/`, `tools/`, `tests/`, `eval/`, `examples/`, `third_party/`, `docker/`, `cmake/`, `doc/`) and every module under `src/` (what it does, what depends on it, which modules are vendored third-party code that is not edited);
  - the data flow of one run: command line → XML configuration → trace reading → proposition and template building → mining (decision trees) → metrics and ranking → reduction → printing; with the files where each step happens;
  - the ANTLR grammars (`src/antlr4/`) and how to regenerate them;
  - building (CMake options: `HARM_WITH_Z3`, `HARM_PROFILE`, `HARM_COI_PYTHON`; D-010 same compiler; `-ffp-contract=off`), the tests (ctest labels, the H0 baselines and how a milestone may change them, the oracles), the evaluation scripts;
  - how to: add a CLI option, an XML element, a metric, a template operator, a `harm-coi` feature; with the tests each one needs;
  - the development workflow: milestones, `ms/<ID>-<slug>` branches, `dev`/`main`, DECISIONS and VALIDATION, Mac/Linux hand-offs.

### 2. LaTeX report (`doc/report/`)
- **Style (user's choice):** a technical report, `article` class, about 20–30 pages, with full detail.
- **`doc/report/harm_v4.tex`**, built with `latexmk -pdf`, plus `figures/`, `refs.bib`, a `Makefile`.
- **Outline:**
  1. Introduction: HARM v3 in one page (templates, decision trees, metrics), and the goals of v4.
  2. Changes to default output (D-001, D-002, D-021, D-028), with v3/v4 side-by-side examples.
  3. Proposition language (H1): SystemVerilog syntax, x/z rule (H1b, D-011), end-of-trace strength (H1c, D-015, D-016, `--trace-end`).
  4. Semantic reduction (H2, H3, H3b): Z3 canonicalisation, Spot implication with HARM's finite-trace model, atom premises, `--keep`; algorithms and complexity (bucketing, caching).
  5. Cones of influence (H4–H9): the `coi.json` contract, rank mode and its metrics, filter mode at signal and depth level (the D-007 offset table), the out-of-cone report.
  6. `harm-coi` (H5, H10): pyslang back end (D-006), depth computation, predicate harvesting, `--emit-config`.
  7. Determinism and portability (H0, H11b–H13): thread-independent order, the FMA finding (F-M2) and its fix, the Linux/macOS tool chain, Docker.
  8. Validation: the oracle for each component (brute force, iverilog, Verilator replay, rank-vs-filter equivalence, mutation tests), taken from `VALIDATION.md`.
  9. Limitations and future work (PLAN §5, deferred findings).
  - Appendices: the CLI reference (v3 vs v4), the XML additions, the decision index.
- **No evaluation section (user's choice).** Section 8 describes how each feature was validated, not measured results.
- **Figures:** TikZ (the tool flow HARM + harm-coi, a COI example, the reduction pipeline), so they build without external tools.

## Acceptance (written first; the checks are committed failing)
| # | Check | How |
|---|---|---|
| A1 | The report builds from a clean checkout with `make -C doc/report`: no LaTeX errors, no undefined references or citations, no `??` in the PDF text | `doc/report/check.sh` greps the log and `pdftotext` output |
| A2 | The developer guide describes every top-level directory and every module under `src/` (a directory added later without a description fails the check), and every source path it cites exists | `doc/report/check_coverage.py` |
| A3 | Every runnable example (marked `% harm-example` in the report, and the `bash` blocks of the v4 README sections, the migration guide and the developer guide) runs with the current build and prints what the document shows | `doc/report/run_examples.py --harm <abs path>` |
| A4 | Coverage: every option in `harm --help` that v3 did not have, every new XML element and attribute, and every decision that changes default output appears in the release notes, the README and the report | `doc/report/check_coverage.py` (the v3 option list is taken once from `git show v3:` sources and committed as a fixture) |
| A5 | Every milestone H0–H13 and every finding fixed since v3 (F-L*, F-M*) is cited in the report and in the release notes | `check_coverage.py` |
| A6 | The existing `ctest` is unaffected (documentation only; no code change) | `ctest -L fast` on the Mac |

- The checks run as a ctest with label `doc`, skipped (not failed) when `latexmk` or `pdftotext` is missing, so the Linux and Docker builds are not broken.

## Validation
- The A1–A5 scripts check form, coverage and paths; they cannot check that the text is right. The independent check is **the user's review** of the PDF, the migration guide and the developer guide.
- **Claims cross-check:** each technical claim in sections 2–7 cites the D-xxx or VALIDATION entry it comes from; the review is done against those entries.

## Not in scope
- Any change to HARM's or harm-coi's behaviour. A bug found while writing becomes a finding (F-D*) and a separate milestone.
- An evaluation section, and re-running the evaluation.
- The release itself (`dev` → `main`, tag `v4`): still the user's decision.
- Doxygen and the API documentation.

## Trivergence
- No change to anything trivergence uses. `TRIVERGENCE_IMPACT.md` gets one line pointing to the report and the migration guide.

## Open questions for the user
1. ~~Report style~~: technical report (answered).
2. ~~Evaluation section~~: none (answered).
3. **Author list and affiliation** for the title page. Default: Samuele Germiniani, University of Verona.
