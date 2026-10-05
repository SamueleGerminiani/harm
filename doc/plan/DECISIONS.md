# Decisions

One entry per decision: context, decision, alternatives, consequences. Numbering follows `PLAN.md` §3; IDs above D-009 are added as they come up.

## D-010: one C++ toolchain for HARM and all third-party libraries (2026-10-05, H0)
- **Context:** on the development Mac, `harm` aborted at start-up (`malloc: pointer being freed was not allocated`), even for `--help`. The dependencies had been built against three C++ runtimes, all loaded into one process:
  - Spot: gcc-12 `libstdc++`;
  - ANTLR and HARM: gcc-13 `libstdc++`;
  - Boost: Apple `libc++`, because `b2` ignores `CC`/`CXX`.

  The install scripts did not pin a compiler.
- **Decision:**
  - Build every dependency and HARM with **Homebrew g++-13**, chosen by the user.
  - `third_party/install_*.sh` honour `CC`/`CXX` (Boost through an explicit `b2` toolset) and record the compiler in `<prefix>/.harm_toolchain`.
  - CMake warns at configure time when a recorded compiler differs from HARM's, or when the record is missing.
  - Boost is built `--with-regex` only: it is the only compiled Boost library HARM links; the rest is header-only.
- **macOS SDK finding:**
  - Homebrew gcc-13 (13.3.0) cannot compile a hello-world against its default sysroot, the newest Command Line Tools SDK (15.4). It fails with errors in `_stdio.h` and `_Alignof`, and `configure` reports "cannot run C compiled programs".
  - It works with the Xcode 15.2 SDK, which is the one CMake passes for HARM.
  - So on macOS the scripts set `SDKROOT=$(xcrun --show-sdk-path)` unless `SDKROOT` is already set.
- **Alternatives considered:**
  - Apple clang with `libc++` for everything. It avoids the SDK issue, but the user chose g++-13.
  - Developing in Docker (Linux only). It leaves macOS broken.
- **Consequences:** anyone building on macOS with Homebrew gcc needs an SDK their gcc supports. The README says so.

## D-001: deterministic output (2026-10-05, H0)
- **Context:** with identical inputs, HARM's output order changed with the number of threads and from run to run. Before the fix, 8 of 17 determinism tests failed. The `--max-ass` cut and the fault-coverage minimum subset could also change *which* assertions are reported (trivergence M0 #31). Five sources were found:
  1. `TLMiner` appended each permutation's assertions in thread-completion order;
  2. `extractUniqueAssertionsFast` iterated a pointer-hashed `unordered_set`, which is address-dependent even with one thread;
  3. ranking sorted on the score only, so ties were in arbitrary order;
  4. the fault-coverage code iterated id-keyed maps, and assertion ids come from a global counter incremented as threads create assertions;
  5. `--fd` faulty traces came in the directory order, which is unspecified, and VCD traces were then shuffled with a **random seed** (for an early outlook on coverage in the progress bar). Fault ids changed on every run, and with them the greedy set cover's tie-breaking, even with one thread.
- **Decision:**
  1. Collect per `(template index, permutation index)` in a `std::map`, and concatenate in key order.
  2. Deduplicate in input order; the first occurrence of a key is kept.
  3. Ranking order: `final score desc`, then `toString() asc`.
  4. The fault loop follows the order of `selected`. The set cover receives its candidate sets sorted by assertion text.
  5. Sort the faulty-trace list, then shuffle VCD traces with a fixed seed (`std::mt19937{0}`). This keeps the early-outlook intent and makes it reproducible.
- **Consequences:**
  - Output is identical across runs and thread counts on all 19 regression cases, including the `--max-ass 10` ones.
  - The ordered baseline is frozen after this change. Set changes against the pre-fix baseline are listed in `VALIDATION.md` (H0).
  - Fault ids in logs are now stable, but they differ from those of earlier HARM versions.

## D-002: SVA printing (2026-10-05, H1, approved)
- **Context:** HARM's `--sva` output contained `true` (not SystemVerilog), `::` (package scope, not a hierarchical reference), and `always`/`nexttime`. The last two are valid IEEE 1800-2009 but rejected by Verilator and EBMC. Trivergence rewrites all of these in an adapter (M0 #9).
- **Decision (both `--sva` and `--sva-assert`):**
  - `true`/`false` → `1'b1`/`1'b0`;
  - `p |-> nexttime q` → `p |=> q` and `nexttime[n]` → `##n`, when `q` is boolean;
  - `a::b` → `a.b`.
- **The outer `always (…)`:** kept in `--sva` (valid, and backward compatible). Dropped in `--sva-assert`, which prints `assert property (@(posedge <clk>) …);`.
- **Validation:** Verilator replay of printed assertions against HARM's own evaluation. Verilator is installed on the development Mac with Homebrew.

## D-011: x/z semantics of propositions (2026-10-05, H1). **Decided: option (b), milestone H1b**
- **Finding (H1 oracle, A2):** HARM's propositions do not follow SystemVerilog when values contain x/z.
  - **HARM's rule:** a relational or equality comparison (`== != < <= > >=`) is **false** if either operand contains an x or z bit. Boolean operators (`! && ||`) then work on 2-valued results.
  - **SV's rule:** the comparison yields x, or a known 0/1 when known bits already decide it (e.g. `!=` with a known differing bit is 1). `!`, `&&`, `||` propagate x (Kleene logic). An assertion treats a final x as false.
  - **Consequences:**
    - `!(a == b)` is **true** in HARM but x (false) in SV when `a` has x bits;
    - `4'bx10x != q4` is always false in HARM, but 1 in SV when a known bit differs.
  - **Evidence:** iverilog oracle over 32 random 4-valued rows. Of 300 random pre-H1 expressions, 78 differ from SV on at least one row. All 300 match the rule above exactly, which confirms it describes HARM's behaviour precisely.
- **Impact:** a HARM-mined assertion with a negated proposition can hold on a trace in HARM but fail in an SV simulator on the same trace when x/z values are present. This explains HARM/Verilator disagreements like trivergence M0 #33.
- **Status:** H1 keeps the current semantics, as its plan states. The oracle checks new operators against HARM's rule (the "HARM model" column) and reports the SV gap.
- **Options:**
  - (a) keep it and document it in the README;
  - (b) add SV-faithful three-valued semantics as an option (e.g. `--sv-xsemantics`);
  - (c) make SV semantics the default. This changes mining results on traces with x/z.

  Proposed: (b), as a new milestone after H1. The oracle fixture already contains the SV column needed to validate it.
- **Additions found during implementation (H1):**
  - **Unbounded `F` is printed as `s_eventually` in SVA.** `eventually` without a range is not SystemVerilog, and `F` is the strong, unbounded form. The parser accepts `s_eventually` as input.
  - **Edit rules keep matching the pre-D-002 printing.** `<edit>` rules are matched against the printed SVA text, with spaces removed. With `1'b1`, a rule such as `##@(N,b) @(P,c)` with `c=="true"` would silently stop matching: `##2 1'b1` becomes `##21'b1`. While edit rules are matched and applied, HARM prints SVA as before (`clc::legacySvaPrinting`), so existing users' edit rules keep working. The output still follows D-002.
  - **Updated test expectations:** `svaParserPrinterTests` (parse_print3, parse_print7, parse_print8) now expect `|=>`, `##9` and `s_eventually`.
  - **Regression:** the `process` baseline was re-captured. Its new output equals the old one with the D-002 rewrites applied mechanically (checked as sets; same count, 138 assertions in 4 contexts). `edit` is unchanged.

## D-012: fixes stay on `dev` until the final merge (2026-10-05)
- **Context:** H1 found bugs that also affect the stable `main` used by other people, notably F10 (bit selections evaluated and printed with swapped bounds) and F9 (variable names corrupting literals).
- **Decision (user):** no hotfix on `main`. All fixes stay on `dev` and reach `main` with the final merge after H11.
- **Consequence:** until then, `main` users keep these bugs. Trivergence must pin `dev` commits (TRIVERGENCE_IMPACT.md).

## D-003: Z3 equivalence of propositions (2026-10-05, H2, approved; revised from PLAN.md §3)
- **Context:** the original proposal ("never merge propositions with x/z constants or `===`; 2-valued otherwise") is unsound. Variables can hold x/z at run time, and under HARM's rule (D-011) `a == c` and `!(a != c)` then differ.
- **Decision:**
  - Encode HARM's evaluator exactly: each logic signal is a value bit-vector plus an x-mask and a z-mask, and each operator follows `Logic`'s implementation.
  - Constructs not encoded exactly become opaque atoms, keyed by their text. This is sound but incomplete.
  - A timeout or unknown result means "not equivalent".
- **Z3:** built from source in `third_party/` with HARM's compiler (D-010), behind the CMake option `HARM_WITH_Z3` (default ON).
