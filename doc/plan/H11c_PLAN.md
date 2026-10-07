# H11c plan: the Linux checklist's findings F-L3, F-L4, F-L5

*Status: approved 2026-10-07, with F-L4 extended by the user: vector indexing follows SystemVerilog (D-028); in progress. Branch: `ms/H11c-linux-findings` (from `dev` @ `3b0a9ee`). Effort: 2–3 d.*

The findings are in H11's VALIDATION entry ("Linux evaluation", branch `ms/H11-linux`).

## F-L3: the yosys probe accepts any yosys (test infrastructure only)
- **Bug:** `tests/regression/CMakeLists.txt` registers the H5 yosys cross-check when `yosys -p "help read_slang"` exits with 0. But yosys exits with 0 even for an unknown command. With yosys 0.47 on `PATH`, the 7 `h5_xcheck_yosys_*` tests are registered and fail with "No such command: read_slang".
- **Fix:** the probe really runs `read_slang` on a one-line SystemVerilog module (written to the build directory at configure time). The cross-check is registered only if that succeeds. Otherwise the existing "skipped" message is printed.
- HARM is unchanged.

## F-L4: HARM rejects ascending vector ranges in a VCD
- **Bug:** the VCD parser (`VCDParser.ypp:197`, and its generated `VCDParser.cpp`) stops on `$var … [1:10]`: "Reverse bit direction not supported". `ethernet_smii_txrx` declares `input [1:10] state`.
- **What a VCD says (checked with Verilator 5.031 and Icarus 11; IEEE 1364/1800 §21.7):**
  - The `$var` line keeps the declared range as written: `[1:10]`, `[10:3]`.
  - The value string starts with the left declared index. For `[l:r]`, SystemVerilog index `i` sits `|i − r|` bits from the right end:

    ```
    $var wire 10 # asc [1:10] $end        after asc[2] = 1:      b1100000001
    $var wire 8 $ dsc_off [10:3] $end     after dsc_off[5] = 1:  b10000111
    ```
  - **What the VCD cannot say:**
    - A packed multi-dimensional vector is flattened (`logic [1:0][3:0] p2` → `p2 [7:0]`).
    - A bit-blasted vector (`sig [3]`, one `$var` per bit) gives each bit's index but not the declared direction.
    - Verilator dumps unpacked arrays as one `$var` per element (`mem[0] [7:0]`), which looks like a split vector.
- **HARM today:**
  - `VarDeclaration` keeps the name, type and size, not the range.
  - So `x[i]` is "bit i from the right", which matches SystemVerilog only for `[n:0]`. For `[10:3]`, HARM's `x[3]` is SystemVerilog's `x[6]`.
  - The parser refuses `l < r` outright.

### D-028 (to be written in DECISIONS when approved with the code): vector indexing follows SystemVerilog
- **Ranges:** HARM keeps each vector's declared range `[l:r]` from the VCD. Ascending and offset ranges are accepted. CSV traces, which have no range, are `[size−1:0]` as now.
- **Bit and part selects:** `x[i]` and `x[a:b]` use SystemVerilog indices, mapped to the bit `|i − r|` from the right.
  - An index outside the range is an error.
  - So is a part-select whose direction is opposite to the declaration (`x[a:b]` needs `a ≥ b` when `l ≥ r`, and `a ≤ b` when `l < r`).
- **Output:** printed assertions (SVA, PSL, Spot) keep the SystemVerilog indices the user or harm-coi wrote.
- **Unchanged:** for `[n:0]` vectors, which covers every existing test, example and the H0 baselines, behaviour is identical.
- **Limits (documented, not fixed):**
  - Packed multi-dimensional vectors are seen flattened: only single-dimension indices.
  - Bit-blasted vectors keep the current assumption, highest index = MSB (as synthesized netlists are `[n:0]`).

- **Steps:**
  1. **Investigate** with hand-written VCDs and record the results here:
     - how HARM reads `[1:10]`, `[10:3]`, `[0:0]` and the bit-blasted form;
     - whether Verilator's `mem[0] [7:0]` elements are wrongly joined into one vector;
     - every place an index is turned into a bit position: the proposition parser, `BitSelector`, the Z3 back end (H2), the printers, harm-coi's emitted predicates.
  2. **Fix:**
     - the range is stored per variable;
     - selects are mapped at parse time;
     - printers keep the source index;
     - unpacked-array elements are not joined (if step 1 confirms the problem).
  - **Step 1 results (2026-10-07, hand-written VCD `t [10:3]`, `mem[0] [7:0]`, bit-blasted `bb [0..2]`):**
    - **Selects are positional.** On `dsc_off [10:3] = 10000011`:
      - `dsc_off[3] == 1` is false (SystemVerilog: true);
      - `dsc_off[0] == 1` is true (SystemVerilog: out of range);
      - `dsc_off[10]` is an error, "Range is wider than the size of the variable" (SystemVerilog: true);
      - `dsc_off[4:3] == 2'b11` is false (SystemVerilog: true).
    - **The mapping point:** a select is turned into bit positions in one place, `PropositionParserHandler.cc:1164`, which also normalizes `[a:b]` to min..max and ignores direction. Evaluation and Z3 (`ExpToZ3Visitor`) see only positions.
    - **Printers:** `PrinterVisitor` (`EXP_OPE_BIT_SELECTION`) prints positions as `[upper:lower]`.
    - **harm-coi (H10):** emits the source index (`("bit", atom, i)`, with `i` the RTL constant). So HARM currently misreads its bit-select predicates on vectors not declared `[n:0]`.
    - **Verilator's unpacked-array elements are not joined:** `mem[0]` and `mem[1]` stay separate variables, named with the brackets, and `mem[0] == 8'd15` resolves to that variable. No change needed.
    - **Bit-blasted `bb [0..2]`** is joined into `bb`, LSB = index 0, as assumed.
    - **Consequence for the fix:** `VarDeclaration` and the variables carry the declared range. The parser maps SystemVerilog indices to positions for a select whose operand is a variable (a select on any other expression keeps positions, as now). `BitSelector` keeps the source indices for printing.
  3. **The parser is generated by bison:** `third_party_parser/make.sh` regenerates `VCDParser.cpp` from `VCDParser.ypp`. Both are committed, as now.

## F-L5: harm-coi emits predicates that HARM cannot use
- **Bug:** on `sha3`, harm-coi (H10) emits `f_permutation_::out == 1600'd0`. HARM rejects the configuration: "Constant ''d0' is wider than 511 bits".
- **Why dropping, not trimming:** HARM already truncates any logic signal wider than 511 bits to its low 511 bits when reading the trace (`minerUtils.cc:266`, `VCDtraceReader.cc:366`). A predicate on such a signal would compare a truncated value, and trimming the predicate (e.g. to its low 511 bits) would change its meaning without saying so.
- **Fix (harm-coi only):** a predicate is dropped when any operand or constant is wider than 511 bits. It goes to the existing dropped list with the reason `wider than HARM's 511-bit limit`, printed by `-v`. The limit is a named constant in harm-coi, with a comment pointing to HARM's.

## Tests (written first, committed failing)
| # | Test | Kind |
|---|---|---|
| A1 | F-L3: configuring with a yosys that lacks `read_slang` registers no `h5_xcheck_*` test (`ctest -N`), and prints the skip message | regression (CMake script, with a fake `yosys` that exits 0 for anything) |
| A2 | F-L4: a VCD with `[1:10]` gives the same mined assertions as the same trace with `[9:0]` (whole vectors), hand-written, for `--generate-config` and a fixed template | regression |
| A3 | F-L4/D-028: `x[i]`, `x[a:b]` on `[1:10]`, `[10:3]`, `[7:0]`: values equal to the hand-written expectations from IEEE 1800. Out-of-range and wrong-direction selects are errors | gtest |
| A3b | F-L4/D-028: an independent simulation check. A Verilator testbench prints `x[i]`, `x[a:b]` for the same declarations each cycle; HARM evaluates the same propositions on its VCD, and the two must match | regression (python + Verilator) |
| A3c | F-L4/D-028: printed SVA keeps the source indices (`x[2]` on `[1:10]` prints `x[2]`) | gtest (`PrintingTest`) |
| A4 | F-L4: bit-blasted vectors keep today's order (highest index = MSB). Verilator's unpacked-array elements (`mem[0] [7:0]`) stay separate variables (if step 1 confirms the problem) | gtest |
| A5 | F-L5: a module with a 1600-bit register `r` and `if (r == 0)` drops that predicate with the reason, and keeps a ≤ 511-bit one | pytest (`test_predicates.py`) |
| A6 | F-L5: `--emit-config` on the same module gives a configuration HARM accepts | regression (`h10_emit_config`-style) |
| A7 | No regression: Linux `ctest` green (with Verilator 5), H0 baselines byte-identical | ctest |

## Validation
- **A2:** two traces of the same signal behaviour in two declarations; the expected output is the descending one's, which HARM already handles.
- **A3:** expected values written by hand from IEEE 1800 bit-select semantics.
- **Real designs:** `ethernet_smii_txrx` and `sha3` are re-run on Linux with the AssertLLM2 manifest (C6/C7), and the results are added to the H11 table.
