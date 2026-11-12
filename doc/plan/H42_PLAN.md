# H42-v4-release plan: HARM v4 released

*Status: approved by the user 2026-11-12 ("yes, approved"). Asked by the user: "a good time to finally complete harm v4
release" (trivergence's first wave of experiments is about to start). Branch: `ms/H42-v4-release` (from `dev` @
5a96497, H41). This is the release that H11's D-027 deferred "until the user says so".*

## Goal
Merge `dev` into `main` with the tag `v4` (D-027), with the documentation complete through H41. No behaviour change:
the release commit's tree is `dev`'s plus documentation and the Dockerfile's default ref.

## Where things stand
- `main` (8a26182, 2026-10-05) is behind `dev` by 437 commits, and has no commit that `dev` lacks, so the merge has no
  conflicts.
- The release notes, the report and the status board in PLAN.md stop at H33. H34-H41 are merged into `dev` but are not
  on the board, so `h14_doc_coverage` passes without checking them. H39 alone has entries, for its options only.
- The Dockerfile builds `ARG HARM_REF=dev`. `--version` prints `git describe`, so it prints `HARM v4` once the tag
  exists (test h11_version).
- Last full checks: jupiter `ctest` 284/284 at bc40724 (2026-11-09, trivergence's A7f), the same tree as `dev`'s
  head. The Mac's full suite and the Docker image (A3) were not run at this commit.

## Part A: documentation through H41 (tests first)
1. **Test first:** PLAN.md's status board gets rows H34-H41, and H42 as in-progress. `h14_doc_coverage` then fails,
   since none of them is cited in the release notes or the report. Committed failing.
2. **Release notes**:
   - **Changes to default output:**
     - H38, a net's kept name: a top port is preferred, and selects are rebased to that name's range;
     - H41, `!(x == c)` printed with its brackets;
     - any other output change that H34-H40 recorded in their VALIDATION entries (checked one by one).
   - **New options and tools:**
     - H34 `harm-coi --aliases`;
     - H35/H36 `--domains`, `--cut-domains`;
     - H37 `reset_edges` in the domain map;
     - H39 `--deadline`, `--mine-deadline`, `--implies-workers`;
     - H40, the cone closure in linear time.
   - **Bug fixes:**
     - H38, 1-bit `[k:k]` VCD variables;
     - CR1's HARM fixes on `dev`: C7a, C7b, C9-4.
   - **Where each change comes from:** the table gets the new rows.
3. **Migration guide:** the default-output changes above, each with what to do.
4. **Report:**
   - a section for each feature;
   - H34-H41's findings and decisions (D-042 to D-045 and later), which A5 requires;
   - the validation section brought to H41;
   - the PDF rebuilt (`make -C doc/report`; LaTeX is on the Mac).
5. **README:** an audit of the new options and of harm-coi's new modes, with `--version`'s example kept.
6. **Developer guide:** whatever A2 reports missing (new modules or tests since H33).

## Part B: the release's own files
- Dockerfile: `ARG HARM_REF=v4` (D-027), and the comment that says "dev until the release" updated.
- Release notes header: "The release is deferred..." becomes the release date.
- PLAN.md: H11's row records the release; H42 is done at the sign-off.

## Part C: checks on the release candidate (`ms/H42-v4-release` after A and B)
| # | Check | Where |
|---|---|---|
| C1 | full `ctest`, `h14_doc_coverage` and `h14_doc_examples` included | Mac (`-j4`; never with the container tests) |
| C2 | full `ctest` and harm-coi's pytest | Linux: jupiter, or saturn if jupiter is busy with the wave; trivergence told before it is queued; under 1 h |
| C3 | the Docker image builds with `HARM_REF=ms/H42-v4-release` and its in-image test run passes (H11 A3) | Linux (Docker on the Mac is not running) |
| C4 | every README command runs (H11 A4) | Mac |

The C2 and C3 results go into VALIDATION's H42 entry.

## Part D: the release (after the user's sign-off)
1. `ms/H42-v4-release` merged into `dev` with `--no-ff`.
2. `dev` merged into `main` with `--no-ff`: "Merge H42-v4-release: HARM v4".
3. The annotated tag `v4` on that merge.
3b. `dev` fast-forwarded to `main`, so a later build of `dev` describes itself as `v4-<n>-g<commit>` (README, `--version`). This was added while writing the documentation.
4. `main`, `dev` and `v4` pushed to origin (SamueleGerminiani/harm; never upstream).
5. Then: a build from `main` prints `HARM v4`, and the Docker image's default ref is `v4`.
6. The Docker Hub image (added by the user, 2026-11-12: "yes, push the docker after the release"): `docker/build.sh v4`
   builds `samger/harm:v4`, which is tagged `latest` too, and both are pushed (the README's `docker pull samger/harm:latest`).
   It is built where Docker runs on x86_64, and the push needs the user's `docker login` there. No credentials are
   put in an image or a file.

`main` is the branch other people use. **The push is the step that cannot be taken back**, so it waits for the
sign-off.

## Part E: what does not change
- **The miner portfolio** keeps HARM pinned at `dev` 5a96497 (the same tree). Moving the pin to the `v4` commit
  changes `harm --version`, which the portfolio records, during trivergence's wave. So it moves at the portfolio's
  next milestone, and trivergence is told first.
- **trivergence's image t7** builds HARM from the portfolio's pin, so it is unaffected.

## Out of scope
- Any behaviour change.
- H20, the missing SystemVerilog operators, which stays future work.
- A new evaluation (H11's tables stand).
- USM-T.

## Effort
About 1 day for the documentation. C2 and C3 take under 1 h each on Linux, at a gap in trivergence's wave.
