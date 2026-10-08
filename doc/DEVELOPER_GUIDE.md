# HARM developer guide

For someone who will change HARM or harm-coi: what each part of the repository is for, how one run flows through the code, how to build and test, where to add things, and how work is organised. User documentation is in `README.md`; what changed in v4 is in `doc/RELEASE_NOTES_v4.md` and in the technical report (`doc/report/`).

## 1. The repository

| Directory | Purpose |
|---|---|
| `src/` | HARM's C++ sources (section 2), including vendored third-party code that is not edited |
| `tools/` | `tools/harm-coi/`, the Python generator of cones of influence and RTL predicates (section 5) |
| `tests/` | unit tests (gtest, one `*Tests.cc` per topic), regression and determinism tests, oracles and fixtures (section 4) |
| `examples/` | example traces and configurations; each one also runs as a ctest (`examples/CMakeLists.txt`) and as a regression case |
| `third_party/` | install scripts for the libraries (antlr4, Spot, Boost, Z3) and for the tools the tests use (Verilator, Icarus, yosys); everything is built from source into this directory, with one compiler (D-010) |
| `cmake/` | CMake modules: finding the libraries (`FindANTLR4.cmake`, `FindSPOTLTL.cmake`, `FindBOOST1_83.cmake`), the test tools (`HarmTools.cmake`, `HarmYosysProbe.cmake`), the version string (`version.cmake`), and installation (`PostInstall.cmake`) |
| `doc/` | user and developer documentation, the `coi.json` schema (`doc/schemas/`), the figures, the report (`doc/report/`) and the development plan (`doc/plan/`, section 7) |
| `docker/` | `docker/Dockerfile` and `docker/build.sh [ref]`: an Ubuntu image with HARM, Z3, harm-coi, Verilator and Icarus, which runs the fast tests while it builds |
| `eval/` | the evaluation of the extension plan (H11) and the Mac/Linux hand-off notes |

`eval/` in detail:
- `eval/run_eval.py` runs HARM's configurations C0–C7 (D-026) on the designs of a manifest (`eval/manifests/`) and writes a table to `eval/results/`. Always pass `--harm` with an absolute path.
- `eval/LINUX.md` and `eval/MACOS.md` are the checklists that were run on the other machine; `eval/HANDOFF_MAC.md`, `eval/HANDOFF_FM2.md` and `eval/HANDOFF_H12.md` are the hand-offs between the Mac and Linux sessions (H11, H12). They are records, not instructions for new work.

## 2. The C++ sources (`src/`)

### HARM's own modules
| Module | What it does | Used by |
|---|---|---|
| `src/main.cc` | `main`: parses the command line, picks the trace reader, handles `--generate-config` and `--dump-trace-as-csv`, then builds and runs the `Miner` | — |
| `src/commandLineParser/` | the command-line options (cxxopts) and their checks; the values go into the `clc` namespace | `src/main.cc`, every module that reads an option |
| `src/globals/` | global state: the options (`clc::`), run statistics (`hs::`), thread limits per level (`l1Constants`, `l2Constants`, `l3Constants`) | everything |
| `src/logging/` | `messageInfo`, `messageWarning`, `messageError` (prints and exits), with the JSON copies in `warning.log`/`error.log` (made safe for concurrent writers in H11f) | everything |
| `src/utils/` | basic types and helpers: `Logic` (4-valued bit vectors up to 511 bits, x/z), `Int`, `Float`, `String`, the output `Language`, string utilities (`misc.hh`) | everything |
| `src/exp/` | the expression tree: atoms (variables, constants), Boolean and arithmetic expressions, bit selection, `inside`, SVA functions (`$past`, `$rose`…), and temporal formulas; the visitors over it (printing, copying, variable extraction, Z3 encoding) | the parsers, the miner |
| `src/antlr4/` | the three ANTLR grammars and their handlers, which build `exp` trees: propositions (`propositionParser/`), temporal templates (`temporalParser/`), variable declarations of CSV traces (`varDeclarationParser/`) | the trace readers, the configuration reader |
| `src/miner/` | the mining pipeline (below) | `src/main.cc` |
| `src/clustering/` | K-means, contiguous and hierarchical clustering, which turn a `<numeric>` into propositions | the configuration reader, the decision trees |
| `src/ddd/` | `--ddd`: a SQLite debug database of contexts, templates, propositions and permutations | the miner |
| `src/ast/` | `ast`, a small tool (not built by default: `make ast`) that prints the syntax tree of a temporal formula | developers |
| `src/dea/` | DEA, a separate tool for approximate-computing design exploration that uses HARM's assertions; built only with `-DDEA=1`, not part of HARM | — |

### Vendored third-party code (not edited)
| Directory | What |
|---|---|
| `src/rapidxml/` | the XML parser of the configuration file (it does not report invalid XML well: a raw `&` silently mangles a template) |
| `src/csv-parser/` | the CSV reader |
| `src/fort/` | libfort, the tables HARM prints |
| `src/progressbar/` | the progress bars |
| `src/paal/` | PAAL's greedy set cover, for `--find-min-subset` |
| `src/SQLiteCpp/` | SQLite for `--ddd` |
| `src/googletest/` | gtest, for the unit tests |

### The miner (`src/miner/`)
| Directory | What |
|---|---|
| `src/miner/interface/` | `Miner`: runs the four modules in order, once per context |
| `src/miner/modules/` | the four modules, each behind an interface, with one implementation each |
| `src/miner/modules/src/traceReader/` | `VCDtraceReader` (a bison/flex VCD parser, `--vcd-ss`, `--vcd-r`, `--clk`; declared ranges, D-028) and `CSVtraceReader`; both produce a `Trace` |
| `src/miner/modules/src/contextMiner/` | `ManualDefinition`: reads the XML configuration into `Context`s (propositions, numerics, templates, metrics, `<edit>`, `<coi>`) |
| `src/miner/modules/src/propertyMiner/` | `TLMiner`: instantiates the templates and mines the assertions; `AntecedentGenerator`, the decision-tree search; `supportMethods.cc`, its scores |
| `src/miner/modules/src/propertyQualification/` | `Qualifier`: everything after mining (below) |
| `src/miner/utils/` | the data structures the modules share: `Trace`, `Context`, `TemplateImplication`, `Assertion`, `Metric`, the evaluators and automata, the decision-tree operators, `Permutator`, `Edit`, and the v4 additions `PropositionCanonicalizer` (H2), `ImplicationReducer` (H3, H3b) and `CoiInfo` (H6–H8) |

## 3. One run, step by step

| Step | What happens | Where |
|---|---|---|
| 1 | The options are parsed into `clc::` | `src/commandLineParser/src/commandLineParser.cc` |
| 2 | The trace is read; values are sampled just before each rising edge of `--clk` (D-005) | `src/miner/modules/src/traceReader/` |
| 3 | The configuration is read: each `<context>` becomes a `Context`. Propositions are parsed (`--skip-invalid-props` skips bad ones), numerics are clustered into propositions, templates are parsed into `TemplateImplication`s, `<coi>` loads a `CoiInfo` | `ManualDefinition.cc`, `src/antlr4/`, `src/clustering/` |
| 4 | **Mining**, per context, on three levels of threads: templates (L3), permutations of each template (L2), and the decision tree of a permutation (L1). A permutation fills the placeholders; a decision-tree operator (`..&&..`, `..##1..`, `..#1&..`) grows the antecedent greedily, keeping candidates that improve the score. Filter mode (`<coi mode="filter">`) removes permutations and candidates outside the cone (H7, H8). Each candidate is evaluated on the trace by a deterministic Spot automaton | `TLMiner.cc`, `AntecedentGenerator.cc`, `src/miner/utils/src/AutomataBasedEvaluator.cc` |
| 5 | **Qualification**: trivial and syntactically redundant assertions are removed (`--reduce syntactic`; with `equiv`, propositions are first grouped by Z3 equivalence), COI metrics are filled, `<filter>` metrics are applied, `<edit>` rules rewrite and remove, `--reduce implies` drops implied assertions, the rest is ranked by `<sort>` metrics (ties by text, D-001), cut by `--min-frank` and `--max-ass` | `Qualifier.cc` (`qualify`), `PropositionCanonicalizer.cc`, `ImplicationReducer.cc` |
| 6 | **Output**: the table (SVA, PSL or Spot LTL), `--dump-to`, `--dump-assertion-info`, `--dump-implications`, `--dump-coi-report`, `--dump-prop-table` (written after step 3, `Miner.cc`), fault coverage with `--fd`, and `check="1"` templates | `Qualifier.cc`, `src/exp/src/visitors/PrinterVisitor.cc` |

The JSON dumps are the easiest way to see what the pipeline produced. For example, the propositions of an assertion, and the cycle at which each is evaluated:
<!-- example -->
```
$ harm --csv examples/ex3/ex3.csv --conf examples/ex3/ex3Config.xml \
    --dump-assertion-info $OUT/info.json > /dev/null
$ python3 -c "import json; a = json.load(open('$OUT/info.json'))['assertions'][0]; print(a['text']); [print(l['text'], l['antecedent'], l['offset']) for l in a['leaves']]"
G({v1 && v2} |-> v4)
v1 && v2 True 0
v4 False 0
```

## 4. Building and testing

### Building
```
cd third_party && CC=gcc-13 CXX=g++-13 bash install_all.sh   # once; the same compiler as HARM
mkdir build && cd build
CC=gcc-13 CXX=g++-13 cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
```
| CMake option | Default | Effect |
|---|---|---|
| `HARM_WITH_Z3` | ON | Z3 for `--reduce equiv`/`implies` and `--atom-premises` |
| `HARM_PROFILE` | OFF | build with `-pg` for `gprof` (H13) |
| `HARM_COI_PYTHON` | `python3` | a Python ≥ 3.11 with pyslang, pytest and jsonschema; enables the harm-coi tests |
| `DEA` | off | also build DEA |

- **Every target is compiled with `-ffp-contract=off`** (H12), so that floating-point scores round the same way on every platform: the decision tree's choice among near-equal scores depends on the last bit. Do not remove it.
- **One compiler (D-010):** the libraries in `third_party` record theirs in `.harm_toolchain`, and CMake warns on a mismatch. On macOS, Homebrew g++-13 with `SDKROOT` set to the Xcode SDK.
- **The version** comes from `git describe` at every build (`cmake/version.cmake`); `harm --version` prints it.

### The ANTLR grammars
The parsers in `src/antlr4/*/grammar*/` are generated and committed. After changing a `.g4` file, regenerate with the ANTLR tool of the runtime's version (4.13.2):
```
cd src/antlr4 && bash regenerateAllParsers.sh /path/to/antlr-4.13.2-complete.jar
```
The VCD parser (`src/miner/modules/src/traceReader/vcdTraceReader/`) is bison/flex output, also committed; it was last regenerated with bison 3.8.2 (H11c).

### The tests
`ctest` runs about 230 tests; the full suite takes about 32 minutes. Labels:

| Label | What |
|---|---|
| (none) | the gtest binaries, one per `tests/*Tests.cc` |
| `regression` | `regression_*`: the examples against frozen baselines (`tests/regression/baseline/`), plus the milestones' end-to-end checks |
| `determinism` | the same cases with 1 and 8 threads and repeated runs: the outputs must be identical |
| `verilator` | simulation oracles: HARM's SVA replayed in Verilator |
| `coi` | the cone fixtures, harm-coi and its oracles |
| `xcheck` | the optional yosys cross-check of harm-coi |
| `report` | measurements that report and do not judge (the depth evidence of the cone fixtures) |
| `slow` | the long ones; `ctest -LE slow` skips them |
| `doc` | the documentation checks (H14) |

| Directory | What |
|---|---|
| `tests/regression/` | the regression and determinism cases (`cases.cmake`), their baselines, and the check scripts. **The baselines change only with approval:** `tests/regression/update_baseline.sh`, recorded in `doc/plan/VALIDATION.md` and, if the output changes, in a decision |
| `tests/input/` | the inputs of the tests: hand-labelled fixtures per milestone (`tests/input/h3/pairs.txt`…), and the RTL fixtures with their testbenches, traces and hand-written cones (`tests/input/coi/`) |
| `tests/oracle/` | independent oracles: the iverilog fixture of the proposition semantics, the Verilator replay of mined SVA, the finite-trace semantics of SVA, Spot equivalence of printed formulas |
| `tests/coi/` | the cone oracles: schema check, closure, simulation non-influence (`perturb.py`), the yosys cross-check, the filter and report checks |

**Tools:** Verilator 5.052, Icarus 13.0 and yosys 0.69 are looked up by `cmake/HarmTools.cmake`: those built in `third_party` first, then those on `PATH`. A Verilator older than 5, or a yosys without `read_slang`, counts as missing. A test whose tool is missing is not registered, and CMake says so at configure time.

## 5. harm-coi (`tools/harm-coi/`)
A Python package (pyslang 12.0.0, D-006), independent of HARM's C++: it communicates with HARM only through `coi.json` (`doc/schemas/coi.v1.json`).

| Module | What |
|---|---|
| `__init__.py` | the version |
| `__main__.py` | `python -m harm_coi` |
| `cli.py` | the command line; writes `coi.json`, `--edges`, `--emit-config` |
| `frontend.py` | elaborates the RTL with pyslang and extracts the direct dependencies (data and control), with their register delays |
| `cone.py` | maps the design's signals to HARM's names, computes the closure up to `--max-depth`, and propagates `unknown` (D-005, D-013, D-019) |
| `vcd.py` | the signal names HARM sees in a VCD under a scope |
| `predicates.py` | harvests the RTL's predicates and writes them as HARM propositions (D-023) |

Tests: `tools/harm-coi/tests/` (pytest), and the `coi` label of `ctest`. The rule for cones is "too large, never too small": what cannot be modelled goes to `unknown`, which HARM treats as in every cone.

## 6. Where to add things
| To add | Change | Tests to add |
|---|---|---|
| a command-line option | `commandLineParser.cc` (declare, check), `globals.hh`/`globals.cc` (the `clc::` variable), the module that uses it; README "Optional Arguments" | a regression case or a gtest; the H14 coverage check then requires it in the release notes, the README and the report |
| an XML element or attribute | `ManualDefinition.cc` (read and check), `Context.hh` (store); README "The configuration file" | error cases (as `tests/input/h6/coi_mode.xml`), and an end-to-end case |
| a metric variable | `Metric.cc` (declare it in the variable table and assign it per assertion), `Assertion.hh` if it is a new feature | hand-computed values (as `tests/coiMetricsTests.cc`) |
| a proposition operator | the grammar (`proposition.g4`), the handler, a node in `src/exp/`, and every visitor (`src/exp/src/visitors/addNewOp.sh` adds stubs); `ExpToZ3Visitor` must encode it exactly or as an opaque atom | the iverilog oracle (`tests/oracle/`) and `tests/propositionLanguageTests.cc` |
| a temporal operator | `temporal.g4`, the temporal handler, the printers (SVA precedence, D-021), the automaton translation; the reducer if it is safety | Spot equivalence of the printed text, the Verilator replay |
| a harm-coi feature | `frontend.py` or `predicates.py`; keep "too large, never too small" | hand-written edges in pytest, the simulation non-influence check |

## 7. How work is organised
- **Plan:** `doc/plan/PLAN.md` lists the milestones (H0–H14) and their status. Each milestone has its own plan (`doc/plan/H*_PLAN.md`), approved before work starts.
- **Tests first:** the acceptance tests are committed failing, then the implementation. A test is never weakened to pass; when an expectation was wrong, the change and the reason are recorded.
- **Independent validation:** every semantic component is checked by something that does not share its code: enumeration, a simulator, Spot, a hand-labelled fixture. Where possible, bugs are planted to check that the oracle catches them (mutation tests).
- **Records:** `doc/plan/DECISIONS.md` (one entry per decision, D-0xx), `doc/plan/VALIDATION.md` (what was run, on which machine, with what result), and `doc/plan/TRIVERGENCE_IMPACT.md` (what trivergence, a downstream user, must change).
- **Branches:** `main` is the released HARM; `dev` integrates; each milestone is `ms/<ID>-<slug>` from `dev`, merged back with `--no-ff` after review. `main` receives `dev` only at a release.
- **Defaults do not change silently:** a new feature is opt-in; a change to default output needs a decision and a baseline update, both recorded.
- **Two machines:** macOS arm64 and Linux x86_64 must give the same results; work that needs the other machine goes through a hand-off file in `eval/`.
