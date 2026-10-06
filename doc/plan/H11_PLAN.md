# H11 plan: evaluation, documentation and release

*Status: approved 2026-10-06 (D-026, D-027), with the merge into `main` and the tag **deferred** by the user: HARM stays on `dev` for a while; in progress. Branch: `ms/H11-release` (from `dev` @ H3b). Effort: 3–5 d, of which part runs on the Linux machine.*

## Goal
Measure what the extension plan added, and finish the documentation and the Docker image. Run the Linux checks that are still pending for every milestone.

**The release** (merge `dev` into `main` with the tag `v4`, PLAN §0.3) is **deferred** at the user's request (2026-10-06): HARM stays on `dev` for a while. H11 ends on `dev`, and the release becomes a separate step the user starts.

## What can run where
| Part | Here (macOS) | Linux machine (trivergence) |
|---|---|---|
| Evaluation on the H4 fixtures, `constructs` and `examples/` | yes | repeated (the same script) |
| Evaluation on about 10 AssertLLM2 designs | no: no designs or simulation flow here | yes, with trivergence's F4 loaders and Verilator traces |
| GoldMine comparison (Paper A preview) | no | yes, where GoldMine runs |
| Full `ctest` (every milestone's pending "A5 Linux") and harm-coi's pytest | — | yes |
| Docker image build | only if Docker Desktop is started (the daemon is not running) | yes |
| README, Dockerfile, release notes, the merge and the tag | yes | — |

The Linux part is a script plus a checklist (`eval/LINUX.md`) that you run there. Its results come back to be recorded in VALIDATION before the release.

## Decisions to approve
### D-026: the evaluation
- **One script, `eval/run_eval.py`.** It reads a design manifest (RTL files, top, trace(s), scope, recursion, clock, optional faulty traces) and writes a results table as CSV and Markdown.
- **Configurations per design:**

  | # | Configuration | Needs |
  |---|---|---|
  | C0 | vanilla: HARM's `--generate-config` configuration, as users start | trace |
  | C1 | C0 + `--reduce implies` | |
  | C2 | C1 + `--atom-premises` | |
  | C3 | C0 + `<coi mode="rank">`, sorted by `coiDepthFit` | RTL (harm-coi) |
  | C4 / C5 | C0 + `<coi mode="filter">`, `depth="any"` / `"exact"` | RTL |
  | C6 | harm-coi `--emit-config`: RTL predicates | RTL |
  | C7 | C6 + filter `depth="exact"` + `--reduce implies --atom-premises` | RTL |
- **Measures:**
  - assertions out;
  - mining and reduction time;
  - redundancy removed (dropped by each reduction);
  - search space (`coiFilter` statistics);
  - `coiFrac`/`coiDepthFit` of the output;
  - fault coverage with `--fd` where faulty traces exist (`faultCov`, `sobel`; AssertLLM2's mutants on Linux).
- **Designs here:** the 6 H4 fixtures, `constructs`, and the `examples/` that run. The examples have no RTL, so only C0–C2.
- **On Linux:** about 10 AssertLLM2 designs, chosen there by four criteria:
  - pyslang elaborates them;
  - Verilator simulates them;
  - one clock;
  - a trace from trivergence's flow.
- **Not claims:** these are measurements, not acceptance thresholds. The table reports what each configuration does; Paper A interprets it.

### D-027: the release
- **Tag `v4`** (after `v3`): the plan adds features and options, all opt-in, with the defaults unchanged apart from documented printing fixes (D-002, H1d).
- **`--version`** (new, small): prints the tag and commit, so trivergence and users can tell which HARM they run.
- **Release notes:** `doc/RELEASE_NOTES_v4.md`, user-facing: new options, changed defaults (printing), new tool `harm-coi`, how to install it.
- **The Dockerfile:**
  - builds a given ref (`ARG HARM_REF=v4`) instead of whatever `main` is;
  - installs Z3 (already in `install_all.sh`), Python ≥ 3.11 with harm-coi and pyslang, and Verilator and Icarus for the oracles;
  - runs the fast test suite at build time.
- **The merge (deferred):** `dev` into `main`, `--no-ff`, in one reviewed step when the user decides; then the tag `v4`, and pushes. Until then, the Dockerfile's default ref is `dev`, and `--version` reports `git describe` (e.g. `v3-140-g1234abc`).

## Acceptance tests
| # | Test | Where |
|---|---|---|
| A1 | `eval/run_eval.py` reproduces its own results table from the manifests (run twice; the counts are equal; times are reported, not compared) | here and Linux |
| A2 | Full `ctest` green on Linux; harm-coi pytest green on Linux; the macOS full suite green on the release commit | Linux, here |
| A3 | The Docker image builds and its in-image test run passes | Linux (or here with Docker Desktop) |
| A4 | Every command in the README runs: a script extracts the README's command examples and runs them on the shipped examples | here |
| A5 | `--version` prints the tag and commit | here |

## Validation
- **The results table is checked against earlier milestones' numbers** where they overlap: H7/H8's search-space reductions, H3b's `sub_platform1k` 89 → 69, H9/H10 counts. Any difference is explained.
- **Fault coverage** uses HARM's own `--fd`, unchanged by this plan; it is only reported.

## Out of scope
- Writing Paper A. H11 gives its tables.
- New features found useful during the evaluation: they are recorded for after the release.

## Files
- **New:**
  - `eval/run_eval.py`, `eval/manifests/*.json`, `eval/LINUX.md`, `eval/results/` (tables);
  - `doc/RELEASE_NOTES_v4.md`;
  - a README-examples check.
- **Modified:** `docker/Dockerfile`, `docker/build.sh`, README (index of the new sections), `main.cc` (`--version`), `doc/plan/*`.
