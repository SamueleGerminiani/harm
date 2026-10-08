# H12 plan: the same assertions on macOS arm64 and Linux x86_64 (finding F-M2)

*Status: approved 2026-10-08 by the user (option (a)); done on the Mac (A1–A4 pass, VALIDATION) and on Linux (2026-10-08: `ctest` 229 of 229, fixtures 46 of 46 equal); awaiting the user's review. Branch: `ms/H12-fm2` (from `dev` @ `ecf9ac2`). Effort: 0.5 d, plus a full `ctest` and the fixture table on both machines.*

## The cause (found on the Mac; details: VALIDATION, H11e "macOS checks", F-M2)
- **Where:** the decision-tree scores in `src/miner/modules/src/propertyMiner/TLMiner/supportMethods.cc`:
  - `getCovScore`: `1 - (ATCT/CT) * (1 - ATCF/CF)`, the default (`COVERAGE`);
  - `getConditionalEntropy`: `-p*log2(p) + -q*log2(q)`, with `ENT`.
- **Mechanism:**
  - On arm64, GCC contracts `a - b*c` into one fused instruction (`fmsub`) by default, which skips the rounding of `b*c`. x86_64 without `-mfma` cannot contract, so Linux rounds the product.
  - `AntecedentGenerator` sorts the candidates by gain and, with a negative effort (`-0.1E`, the generated template's), keeps only the first. Among equal or nearly equal scores, the last bit decides which antecedent is kept, so the tree, and the assertions, differ.
- **Evidence:**
  - `-ffp-contract=off` on the Mac gives Linux's counts (`structs` C0 1,839, `constructs` C0 4,215).
  - Turning contraction off in `propertyMiner` alone is enough, and only these two functions in it are fused.
- **The deeper fragility:** even without FMA, the choice among near-ties depends on rounding. Mathematically equal scores often differ in the last bit; with contraction off, the stand-alone entropy formula gives `H(p) != H(1-p)` in 7,266 of 19,900 mirrored pairs. x86_64 and arm64 agree today only because both round the same IEEE operations the same way, and `log2` happened to agree on these inputs.

## Fix options
| | Option | Effect | Cost and risk |
|---|---|---|---|
| **(a) recommended** | `-ffp-contract=off` for everything HARM's CMake builds (HARM's targets, the tests and the sources vendored under `src/`), on every platform and compiler (GCC and Clang) | macOS arm64 gives Linux's counts. Linux x86_64 is unchanged (it never contracted), so every existing Linux table and baseline stays valid | One line in `CMakeLists.txt`. No measurable speed cost expected (a few fused instructions). Does not protect against a future `libm` difference (e.g. `log2` with `ENT`) |
| (b) | Make the selection robust: compare gains with a tolerance (a few ULPs), and break ties by a deterministic key (e.g. the proposition's index) with a stable sort | Removes the rounding dependence on every platform, `libm` included | Changes the mined assertions on **both** platforms: every count, H0 baseline and evaluation table changes and must be re-made on both machines. It is a change to HARM's behaviour, not a portability fix |
| (c) | (a) now, (b) as a later milestone if the user wants rounding-independent mining | | |

**Recommendation: (a), and (b) only if the user asks for it.** (a) is a pure portability fix: no result changes on Linux, and the Mac matches Linux.

## Tests (written first, committed failing on the Mac)
| # | Test | Kind |
|---|---|---|
| A1 | `h12_structs_count`: `structs` C0 (the generated config, `--max-threads 1`) gives **1,839** assertions, Linux's count, on every platform. Fails on the Mac before the fix (1,800); passes on Linux before and after. About 150 s with one thread, label `slow` | ctest |
| A2 | `ScoreTest`: `getCovScore` and `getConditionalEntropy` on fixed counts, compared **bit for bit** with values computed by a version that rounds every operation (written out as `std::fma`-free steps with `volatile` temporaries, so it cannot be contracted). Fails on arm64 before the fix where the fused result differs; must pass on x86_64. The test cases are chosen so that the fused and the rounded results differ (searched once on the Mac and fixed in the test) | gtest |
| A3 | The Mac fixture table re-run, `--check` against `eval/results/linux-fixtures`: **46 of 46 equal** | eval (Mac) |
| A4 | Full `ctest` on the Mac and on Linux; the H0 baselines byte-identical; on Linux, the fixture table with `--check` unchanged (46 of 46) | ctest, eval (both) |

## Not in scope
- Option (b), any change to how candidates are chosen, and any other HARM behaviour.
- The other tools (`dea`, the third-party libraries): only HARM's own targets get the flag.
