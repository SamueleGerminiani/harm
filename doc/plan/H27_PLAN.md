# H27 plan: pinned and checked third-party downloads

*Status: approved by the user 2026-10-15 ("go ahead with harm h27"). Asked by the user (2026-10-15: "OK", on the miner portfolio's question whether HARM's downloads should be pinned) after trivergence's first image build with the portfolio's `scripts/build_miners.sh` (its F7). Branch `ms/H27-pinned-downloads` from `dev` @ `6f736fa`. Effort: about half a day, then one fresh install on Linux and on macOS.*

## Why
trivergence builds HARM into its toolchain image from these scripts. Its first build showed two problems:
- **A failed download goes unnoticed.** `install_spotltl.sh`, `install_boost.sh` and `install_z3.sh` run without errexit, and `install_all.sh` runs the next script whatever the last one did. A missing `wget` surfaced only later, as CMake's "Could NOT find SPOTLTL".
- **Nothing is checked.** Every source is pinned by version or tag, but none is checksummed, and three are fetched with `wget --no-check-certificate`, Spot's over plain `http`:

| Script | Source | Pinned by | Checked |
|---|---|---|---|
| `install_antlr.sh` | `git clone` of antlr4, then tag `4.13.2` | tag | no |
| `install_spotltl.sh` | `http://www.lrde.epita.fr/.../spot-2.9.7.tar.gz` | version | no (`--no-check-certificate`) |
| `install_boost.sh` | `archives.boost.io/.../boost_1_83_0.tar.gz` | version | no (`--no-check-certificate`) |
| `install_z3.sh` | GitHub tag `z3-4.13.4` tarball | version | no (`--no-check-certificate`) |
| `install_verilator.sh`, `install_iverilog.sh`, `install_yosys.sh` (tests only) | GitHub release/tag tarballs (`tools_fetch`) | version | no |

## Parts
| # | Part |
|---|---|
| A | **One fetch helper for every script:** `third_party/fetch.sh`, `fetch <url> <sha256> <file>`. It downloads over HTTPS with certificate checks, using `curl` or else `wget`, and refuses a file whose SHA-256 differs, naming the expected and the actual value. Spot comes over `https` if its server serves it; if not, plain `http` is kept and the checksum is what protects it. |
| B | **Every tarball checksummed:** Spot 2.9.7, Boost 1.83.0, Z3 4.13.4, Verilator 5.052, Icarus 13.0, yosys 0.69, each SHA-256 taken from the release where one is published, else from a download recorded in VALIDATION. **antlr4:** the commit of tag `4.13.2` is pinned and checked after the checkout (`git rev-parse HEAD`), so a moved tag is refused. |
| C | **Failures stop at once:** `set -euo pipefail` in every script; `install_all.sh` stops at the first failing script and names it. |
| D | **Nothing else changes:** the same versions, the same build flags, the same install prefixes. |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `fetch` against a local file served over a `file://` URL: the right checksum is accepted; a wrong one is refused with both values named; a failed download fails | part A |
| T2 | A scan of `third_party/install_*.sh`: no `--no-check-certificate`, no download outside `fetch`, a 64-hex checksum for each tarball, the antlr4 commit pinned, `set -euo pipefail` in each | parts A–C |
| T3 | `install_all.sh` with a stub script that fails: it stops there, exits non-zero and names it | part C |
| T4 | A fresh `install_all.sh` on Linux (the portfolio's Linux machine, or trivergence's image build) and on macOS: HARM builds, and its fast tests pass | part D |
