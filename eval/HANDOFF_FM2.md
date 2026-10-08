# F-M2 on the Mac: find the cause of the macOS/Linux count difference (hand-off, 2026-10-08)

**Done (2026-10-08):** the cause is FMA contraction in the decision-tree scores, fixed in H12 (`ms/H12-fm2`). See VALIDATION (F-M2, H12) and `eval/HANDOFF_H12.md` for the Linux part.

For the Mac session (or the user). The goal of this file is to **find the cause**, not to fix it. The fix is a milestone (H12) with the usual workflow: plan, the user's approval, failing tests first.

**Never modify trivergence.** `main` is not touched: the user decides the release.

## What is known (details: `doc/plan/VALIDATION.md`, H11e "macOS checks", F-M2)
- **The difference:** `structs` and `constructs` give different assertion counts on macOS and Linux in C0/C1/C3 (no COI filter). For example, `structs` C0 gives 1,800 on the Mac and 1,839 on Linux. The other 40 of 46 fixture runs are equal.
- **The same configuration:** `--generate-config` gives the same `gen.xml` on both, SHA-1 `820b2a29ab651bc8dd4f6391c8744c387102030d`.
- **Deterministic on each system:**

  | System | Compiler | `structs` C0 |
  |---|---|---|
  | macOS 15.3.2, arm64 | g++-13 13.3 | 1,800 (8 threads and 1) |
  | Ubuntu 22.04, x86_64 | g++ 11.4 | 1,839 (8 threads and 1) |
  | Ubuntu 24.04, x86_64 (Docker) | g++ 13.3 | 1,839 |

- **So not the compiler version.** It is the platform: the architecture (arm64 vs x86_64) or macOS's libraries (libm, libc++/libstdc++).
- **Lead:** on arm64, GCC contracts `a*b+c` into FMA instructions by default (`-ffp-contract=fast`), which rounds differently from x86_64 SSE. Floating-point code at mining time, e.g. K-means clustering of `<numeric>` (the generated config clusters every numeric), may then cut differently.

## Experiments on the Mac (from `dev` @ `23a9bb0` or later, on a branch `ms/H12-fm2` from `dev`)
The reference command, for `structs` C0 (run from any scratch directory; `R` = the repository):
```
H=$R/build-mac/harm
T="--vcd $R/tests/input/coi/structs/trace.vcd --clk clk --vcd-ss tb::dut --vcd-r 1"
$H $T --conf gen.xml --generate-config --psilent --isilent && shasum gen.xml
$H $T --conf gen.xml --max-threads 1 --psilent --dump-assertion-info info.json
python3 -c "import json;print(len(json.load(open('info.json'))['assertions']))"
```

1. **Architecture or macOS:** an arm64 *Linux* build on the Mac.
   - `docker/build.sh` pins `linux/amd64`, so call Docker directly and leave the script unchanged:
     ```
     docker build --platform linux/arm64 --build-arg HARM_REF=dev -t harm:arm64 docker
     docker run --rm --platform linux/arm64 -w /tmp harm:arm64 bash -c '<the reference command, R=/harm, H=/harm/build/harm>'
     ```
   - **1,800:** the architecture (go to 2).
   - **1,839:** macOS's libraries (go to 3).
   - This builds the tools too, so it is long. If that is too slow, building only HARM in an arm64 Ubuntu container is enough for this question.
2. **If the architecture: FMA.**
   - Rebuild HARM on the Mac with contraction off, in a separate build directory:
     ```
     mkdir build-nofma && cd build-nofma
     CC=gcc-13 CXX=g++-13 cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-ffp-contract=off ..
     make -j"$(sysctl -n hw.ncpu)" harm
     ```
   - Run the reference command with this `harm`. **1,839** confirms FMA.
   - Also try `-ffp-contract=off` in the arm64 container, if step 1 used one.
3. **If macOS's libraries:** compare where the two systems first diverge.
   - Run with `--dump-assertion-info` on both (Linux reference: ask the Linux session, or use the Docker image there), and diff the assertion lists. The first assertions present on one side only show which `<numeric>` or template differs.
   - Then look at the clustering's inputs and outputs for that numeric (its cluster bounds).
   - Suspects: `std::` math functions (`log`, `sqrt`, `pow`) and `<random>` distributions, whose results are implementation-defined across standard libraries.

## Recording
- On `ms/H12-fm2`: one bullet per experiment under F-M2 in `doc/plan/VALIDATION.md` (system, build flags, count). Push the branch; don't merge.
- **If the cause is found, write the H12 plan** (`doc/plan/H12_PLAN.md`): the cause, the fix options, and the acceptance test. For example, `structs` C0 gives the same count on macOS and Linux, plus a unit test of the clustering on fixed inputs with its expected cut points. Then stop for the user's approval.
- **Possible fixes to weigh in the plan, not to apply yet:**
  - `-ffp-contract=off` for HARM's own targets, on all platforms;
  - making the clustering independent of the last rounding bit (e.g. no exact floating-point comparisons);
  - a platform-independent implementation of any library function involved.
- **Then:** tell the user, and the Linux session if a Linux run is needed.
