# Moving from HARM v3 to v4

For users who run HARM v3 today: what changes when you run v4 with the same configuration, what you may have to change, and what you can now use. The release notes (`doc/RELEASE_NOTES_v4.md`) list everything new; the technical report (`doc/report/`) explains it.

**In short:** your configurations, traces and command lines still work. Every new feature is opt-in. With no new option, the output changes in five ways: the order of the assertions, the SVA text, the Spot-LTL brackets, vector indices on VCD vectors not declared `[n:0]`, and a few bug fixes. If a script parses HARM's output, check the sections "The SVA text" and "The order".

## 1. Building
| | v3 | v4 |
|---|---|---|
| Libraries in `third_party` | antlr4, Spot, Boost | the same, plus **Z3** (optional) |
| `install_all.sh` | the libraries | the libraries and the test tools (Verilator, Icarus, yosys); `--no-tools` for the libraries only |
| Compiler | any | **the same compiler for HARM and every library** (D-010); the scripts take `CC`/`CXX` and record it |
| Platforms | Linux and macOS | the same, now checked: the same tests pass and the same assertions are mined on Linux x86_64 and macOS arm64 (H11b, H12) |

- **Rebuild the libraries** if they were built with another compiler than HARM: mixing C++ runtimes makes HARM crash at start-up. CMake now warns about it.
- **Z3:** `bash third_party/install_z3.sh`, or configure with `-DHARM_WITH_Z3=OFF` to build without it. Without Z3, `--reduce equiv`, `--reduce implies` and `--atom-premises` are not available.
- **No more `gmon.out`:** v3 wrote a 2.6 MB `gmon.out` in the working directory on every run. v4 does so only when built with `-DHARM_PROFILE=ON` (H13).
- **`harm --version`** tells which build you run (`HARM v4` on the release, `HARM v3-<n>-g<commit>` on `dev`).

## 2. What changes in the output
### The order (D-001)
v3's order depended on the number of threads and changed from run to run; with ties at the `--max-ass` cut, so did *which* assertions were kept. v4 sorts by score, then by text, so the same input gives the same output for any `--max-threads`.
- **What to do:** nothing, unless a script relied on v3's order (it could not, since it changed). A diff between a v3 and a v4 output must compare sets, not lines.

### The SVA text (`--sva`, `--sva-assert`; D-002, D-021)
v4 prints valid SystemVerilog, accepted by Verilator. Real lines from the `process` example, v3 then v4:

| v3 | v4 |
|---|---|
| `always (Reject_Application \|-> nexttime Assess_Loan_Risk)` | `always (Reject_Application \|=> Assess_Loan_Risk)` |
| `always (Store_feedback \|-> eventually Assess_Eligibility)` | `always (Store_feedback \|-> s_eventually Assess_Eligibility)` |
| `always (!intf::a ##1 true \|-> DUT::state == 2'b0)` (`fsmSVT`) | `always (!intf.a ##1 1'b1 \|-> DUT.state == 2'b0)` |

- `true`/`false` → `1'b1`/`1'b0`; `::` → `.`; `|-> nexttime q` → `|=> q`; `nexttime[n]` → `##n`; unbounded `eventually` → `s_eventually`.
- **Brackets follow SystemVerilog's precedence:** `(b W c) && F d` is printed `(b until c) and (s_eventually d)`. v3 printed `b until c and s_eventually d`, which SystemVerilog reads as `b until (c and …)`.
- **`->` with a multi-cycle antecedent** (D-021). HARM's `->` starts the consequent together with the antecedent; SVA's `|->` starts it at the antecedent's end. v3 printed `G({a ##1 b} -> X c)` as `a ##1 b |=> c`, one cycle late; v4 prints `a ##1 b |-> c`. Only templates with `->` (not `|->`/`|=>`) and an antecedent longer than one cycle are affected.
- **What to do:** remove any post-processing that rewrote `true`, `::` or `nexttime` (trivergence had one). **`<edit>` rules need no change:** they are still matched against v3's printing.

Check it on the `process` example:
<!-- example -->
```
$ harm --csv-dir examples/process/traces --conf examples/process/processConfig.xml --sva \
    --dont-print-ass --dump-to $OUT/process.txt > /dev/null
$ grep -E 'Reject_Application \|=> Assess_Loan_Risk|Store_feedback \|-> s_eventually' $OUT/process.txt
always (Reject_Application |=> Assess_Loan_Risk)
always (Store_feedback |-> s_eventually Assess_Eligibility)
```

### The Spot-LTL text (the default output; D-021)
v3 dropped brackets that Spot needs: `G({…} |-> X(a && b))` was printed `G({…} |-> Xa && b)`, which Spot reads as `(X a) && b`. v4 prints `X(a && b)`. In the `sub_platform` example, 46 of the 91 assertions change this way, and nothing else does.
- **What to do:** if you parsed the Spot text with Spot (`ltlfilt`, `spot::parse_formula`), v3's text meant something else; v4's means what HARM mined.

### Vector indices (D-028)
On a vector declared in the VCD with a range other than `[n:0]` (e.g. `[1:10]` or `[10:3]`), `x[i]` and `x[a:b]` now use the declared indices, as in SystemVerilog, and an index outside the range is an error. v3 counted bit positions from the right from 0, and stopped on ascending ranges (`[1:10]`) altogether.
- Vectors declared `[n:0]` and CSV variables are unchanged, except that a reversed part-select (`x[0:3]` on `[7:0]`) is now an error.
- `--generate-config --split-logic` writes each bit with its declared index (`asc[1]` … `asc[10]`).
- **What to do:** if a configuration selects bits of such a vector, write the RTL's indices.

### Bug fixes that change results
| Fix | Effect in v3 |
|---|---|
| Bit selections keep their bounds (H1, F10) | a mined `r[7:4]` was printed, and evaluated, as `r[4:7]` |
| Variable names no longer replace text inside literals (H1, F9) | a variable `a` or `x` corrupted `0xa` or `'b1x0` |
| A template with more placeholders than propositions in their domain (H7) | HARM hung |
| macOS arm64 mines the same assertions as Linux x86_64 (H12, F-M2) | among near-equal decision-tree scores, arm64 could keep a different antecedent (a fused multiply-subtract) |
| The log files under concurrent writers (H11f, F-L9) | several HARM processes in one directory could crash |
| `--check-dump-eval` files (H16, D-030) | files named after the assertion's text overwrote each other (`a != b` and `a <= b` both gave `G(a=b->...)`), a name over 255 bytes stopped HARM, and rows of an assertion without a shift had only `t` and `Ant`. v4 writes `<k>_<text>.csv` and `index.json`: **read the index** to find an assertion's file |
| Evaluation (H19, D-035) | C's signed/unsigned rules, also for `logic` (SystemVerilog: unsigned if any operand is unsigned); widths not taken from the context (`ch << am == 0` at 8 bits); 64-bit decimal literals; arithmetic `>>`; shifts by the width or more stopped HARM; a `logic` division by zero aborted it; CSV `integer`/`time` 2-valued; literals printed as different constants (`4'b0x01` as `4'bx01`). v4 evaluates as a SystemVerilog simulator does |
| Operator precedence (H18, D-034) | `!x == y` read `!(x == y)`; `x & y == y` read `(x & y) == y`; `(x > 0) == y` read `(x > 0) == (y != 0)`. v4 reads them as C and SystemVerilog do. **If a configuration meant v3's reading, write the brackets** |
| Printing (H18) | `x - (y - k)` printed `x - y - k` (a different value); `(x + y)[1:0]` printed `x + y[1:0]`; `!(q inside {..})` printed `!q inside {..}` |
| Float `<numeric>` exclusions (H17) | `clustering="...,2E"` on a float compared 2 with the cycle index: it dropped the value at cycle 2 and kept `f == 2` |
| `--vcd-dir`/`--csv-dir` order (H17, D-033) | the files were concatenated in the directory's order, which differs between machines; v4 uses path order |
| Determinism of `--fd` (D-001) | the faulty traces were shuffled with a random seed, so `--find-min-subset` could change between runs |

## 3. What you can now use
All opt-in; see the README for each.
- **Propositions:** `8'd9`, `4'hA`, `'0`, `{a, b}`, `{4{a}}`, `?:`, `===`, `a.b`, bitwise operators on CSV `bool`s (`a ^ b`); invariant templates `G(P0)`; `--skip-invalid-props` to skip a proposition that does not parse.
- **Fewer, non-redundant assertions:** `--reduce equiv` (equivalent propositions, Z3), `--reduce implies` (assertions implied by another one), `--atom-premises`, `--keep`, `--dump-implications`.
- **Simulator semantics at the end of a trace:** `--trace-end sva`, if the mined SVA will be checked by a simulator (`s_eventually` still pending at the end fails).
- **The RTL as a hint:** `harm-coi` computes cones of influence and harvests the RTL's predicates; `<coi mode="rank">` sorts by `coiFrac`/`coiDepthFit`, `<coi mode="filter">` prunes the search, `--dump-coi-report` lists the propositions outside each cone.
- **Machine-readable output:** `--dump-assertion-info` (metrics, propositions, cycle offsets, `origin`); `--dump-prop-table` (every proposition's value at every cycle).

## 4. What stays the same
- The configuration format: every v3 element and attribute keeps its meaning.
- The defaults: `--reduce syntactic` is v3's redundancy filter; `--trace-end harm` is v3's end-of-trace rule; the x/z rule of propositions is v3's, now documented (README, "x and z values"; D-011).
- The command-line options of v3: none was removed or renamed.
- The metrics and the ranking formula; only ties are now broken by text.
