# H5a spike (throwaway code, kept for the record)

Not part of the tool. See `../H5_PLAN.md`, section "H5a results".

- `spike_pyslang.py <fixture-dir>`: direct COI edges from the pyslang 12.0 elaborated AST, printed in `edges.txt` format. It covers the constructs of the H4 fixtures and `probe.sv`.
- `xcheck_json.py <fixture-dir> <edges.txt>`: a signal-level cross-check (no depths) from yosys' JSON netlist (`read_slang; proc; flatten`), with backward reachability over net bits and all aliases of a bit. The cell model is coarse (each output bit depends on every input bit of its cell), so it over-approximates. Struct field bit ranges are hard-coded.
- `probe.sv`: constructs outside the fixtures (`case` with default, `?:`, function call, blocking temporary, bit select, partial register write).

Reproduce (`python3` ≥ 3.11 with `pyslang==12.0.0`):
```
for d in counter arbiter fsm hier structs multipath; do
  python3 spike_pyslang.py ../../../tests/input/coi/$d > $d.edges
  python3 ../../../tests/coi/closure.py $d.edges > $d.json   # compare with expected_coi.json
done
```
