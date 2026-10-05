# H2 plan: Z3 back end and proposition canonicalisation

*Status: proposed 2026-10-05, awaiting approval. Branch: `ms/H2-z3` (from `dev` @ H1). Effort: **4–5 d**, revised up from 3–4 d in PLAN.md (see F1).*

## Goal
Decide with Z3 when two propositions are **equivalent under HARM's semantics**, and give equivalent propositions one canonical token. H3 uses the tokens to abstract assertions for Spot. In H2 they let the existing redundancy filter merge assertions that differ only in how a proposition is written. Examples:
- `cnt == 4'd9` vs `cnt == 4'b1001` (H1 lets both spellings into a config);
- `!(a < b)` vs `a >= b` (only when no x/z is possible, see F2);
- the same predicate harvested from RTL (H10) and written by an LLM (trivergence).

## Findings from the investigation (2026-10-05)
- **F1. USM-T's `ExpToZ3Visitor` has no `Logic` support.** It handles bool, int and float (43 visits), but VCD signals in HARM are 4-valued `Logic`, the main type. The logic part is new work; the bool/int/float parts and `Z3ExpWrapper` are ported.
- **F2. The 2-valued assumption in PLAN.md's D-003 is unsound.** It said: "propositions with x/z constants or `===` are never merged; the rest use 2-valued semantics". But *variables* can hold x/z at run time. Under HARM's rule (D-011), `a == 4'd1` and `!(a != 4'd1)` are both false when `a` has an x bit, so they differ. Merging them would change the meaning of mined assertions on traces with x/z.
- **F3. HARM's `Logic` evaluator, which the encoding must mirror exactly:**
  - **Comparisons** (`== != < <= > >=`): false if either operand has an x/z bit.
  - **Bitwise** (`& | ^ ~`): per-bit x propagation, e.g. `0 & x = 0`, `1 | x = 1`.
  - **Arithmetic** (`+ - * /`, shifts): if any operand bit is x/z, the result is a **1-bit x**.
  - **`===`/`!==`:** exact bitwise identity, including x and z.
  - **Concatenation and ternary:** as implemented in H1.
- **F4. The redundancy filter's key** (`extractUniqueAssertionsFast`) is the contingency table plus the assertion text. Canonical tokens replace only the text part, so two assertions are still merged only if their contingency tables are identical too. That's a second, behavioural safety net.
- **F5. No Z3 in `third_party/`.** It must be built with the same compiler as HARM (D-010): g++-13 on this Mac, the default `c++` on Linux. A Homebrew Z3 would bring in `libc++` and recreate the H0 crash.

## Decision D-003 (revised from PLAN.md; approval needed)
- **Encode HARM's semantics exactly.** Each logic variable becomes three Z3 bit-vectors of its width: value `v`, x-mask `xm`, z-mask `zm`, with `xm & zm = 0` and `v & (xm | zm) = 0`, as in `Logic`. Each operator is encoded as HARM evaluates it (F3).
- **Anything not encoded exactly becomes an opaque atom:** a fresh boolean, or a fresh 4-valued value, keyed by its printed text. This covers floats in non-linear arithmetic, strings, `$past`/`$stable`/`$rose`/`$fell`, and signed arithmetic corner cases if they prove hard. It is sound, because a proof that holds for every value of a free atom also holds for its real values, but incomplete (fewer merges).
- **A solver timeout (1 s default) or an unknown result means "not equivalent".**
- Int variables are 64-bit 2-valued bit-vectors (signed or unsigned per type). Bool variables are 2-valued.

## Scope
1. **`third_party/install_z3.sh`:** Z3 4.13.x from the release tarball, CMake build with `CC`/`CXX` (D-010), recorded in `.harm_toolchain`. The CMake option `HARM_WITH_Z3` (default ON) uses `find_package(Z3)` under `third_party/z3`. With `HARM_WITH_Z3=OFF`, canonicalisation is disabled and `--reduce equiv` stops with a clear error. Docker and README are updated.
2. **`src/exp`:**
   - `Z3ExpWrapper` (ported);
   - `ExpToZ3Visitor` (bool/int/float ported from USM-T, logic new, H1 nodes new, opaque fallback);
   - `expression::z3::areEquivalent(p1, p2, timeoutMs) -> Equivalent | NotEquivalent | Unknown`.
3. **Canonicalisation** (`src/miner/utils`): a `PropositionCanonicalizer` that assigns one token per equivalence class. To keep the number of solver calls down, propositions are bucketed by their variable set (USM-T's `getNumberOfCommonVariables` idea), and identical printed text is merged without a solver call. Results are cached by text pair.
4. **CLI `--reduce syntactic|equiv`** (`implies` is added in H3). The default `syntactic` is today's behaviour, byte-identical. With `equiv`, the redundancy key uses canonical tokens instead of proposition text (F4). The kept representative is the first in the deterministic order (D-001).

## Out of scope
Temporal reasoning (H3); implication between atoms (H3b); changing HARM's x/z semantics (H1b).

## Acceptance tests (written first)

| # | Test | Kind |
|---|---|---|
| A1 | `install_z3.sh` builds Z3 with the configured compiler. `otool -L`/`ldd` shows a single C++ runtime for HARM. CMake finds Z3 | build check + ctest that runs `harm --help` |
| A2 | **Hand-labelled pairs** (`tests/input/h2/pairs.txt`, about 60, written before the implementation): equivalent / not equivalent, mixed widths and signedness, x/z-sensitive pairs (`a == c` vs `!(a != c)`: **not** equivalent), `===` pairs, concatenation and ternary, `inside`, bit selection, `$past` (opaque) | gtest |
| A3 | **Brute-force oracle:** for every pair in A2 plus about 2,000 generated pairs (random expressions from the H1 oracle generator, paired with variants: De Morgan, comparison flips, literal re-spellings, random other expressions), Z3's verdict agrees with exhaustive evaluation by **HARM's own evaluator** over all 4-valued assignments when the total input is ≤ 8 logic bits (4^8 = 65,536 rows), and with 100,000 random 4-valued assignments otherwise. Z3 "equivalent" with any counterexample row is a **failure (unsound)**. Z3 "not equivalent" when exhaustive evaluation finds none is counted and reported as incompleteness, not a failure | gtest |
| A4 | A timeout or unknown result never merges: forced with a 1 ms timeout on a hard pair | gtest |
| A5 | `--reduce equiv` on a new regression case whose config spells the same predicates in different ways gives the hand-checked reduced output. Without `--reduce`, every H0/H1 baseline is byte-identical | regression |
| A6 | Determinism: `--reduce equiv` output is identical across thread counts and runs (H0 harness) | determinism |

## Validation (independent)
- **The evaluator brute force (A3)** is independent of the Z3 encoding: it runs HARM's `evaluate()` on concrete 4-valued values. That is exactly the semantics canonicalisation must preserve.
- **Cross-check with USM-T** on the bool/int subset: the same pairs through USM-T's `check_equivalence` must agree wherever both have an answer.

## Files
- **New:**
  - `third_party/install_z3.sh`, `cmake/FindZ3.cmake`;
  - `src/exp/include/expUtils/Z3ExpWrapper.hh`;
  - `src/exp/{include,src}/visitors/ExpToZ3Visitor.*`;
  - `src/miner/utils/{include,src}/PropositionCanonicalizer.*`;
  - `tests/z3EquivalenceTests.cc`, `tests/input/h2/*`, regression case `h2_reduce_equiv`.
- **Modified:**
  - `CMakeLists.txt` (Z3 option), `src/exp/CMakeLists.txt`;
  - `Qualifier.cc` (key with canonical tokens), `commandLineParser.cc`, `globals`, `main.cc`;
  - `install_all.sh`, `docker/Dockerfile`, `README.md`;
  - `doc/plan/*`, including `TRIVERGENCE_IMPACT.md` (Z3 in the trivergence image).

## Decisions needed before starting
1. **D-003 revised:** encode HARM's 4-valued semantics exactly, with opaque atoms as a sound fallback, instead of the unsound 2-valued shortcut.
2. **Z3 built from source in `third_party/`** with the same compiler as HARM, about 15–20 min once. The alternative is a system or Homebrew Z3, which risks the mixed-runtime crash again.
