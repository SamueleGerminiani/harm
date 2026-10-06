# H11 on the Linux machine: checks and evaluation

Everything here runs on the Linux machine (trivergence's). The results come back to be recorded in `doc/plan/VALIDATION.md` (H11). The release (merge into `main`, tag `v4`) waits for them and for the user's decision.

Use `dev` (H11 is merged). Write down `build/harm --version`.

## 1. Build (D-010: one compiler for HARM and its libraries)
```
git clone https://github.com/SamueleGerminiani/harm.git && cd harm && git checkout dev
cd third_party && sh ./install_all.sh && cd ..
python3.12 -m venv build/harm-coi-venv
build/harm-coi-venv/bin/pip install -e 'tools/harm-coi[test]'
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DHARM_COI_PYTHON=$PWD/build/harm-coi-venv/bin/python
make -C build -j$(nproc)
build/harm --version
```
- **Optional, the yosys cross-check (H5):** a yosys ≥ 0.67 with `read_slang`, e.g. OSS CAD Suite; add `-DHARM_COI_YOSYS=<path>/yosys`.
- **Verilator and Icarus** are needed by the simulation oracles (H1, H4, H5, H1b).

## 2. The pending Linux checks (A2): every milestone's "A5 Linux"
```
cd build && ctest -j$(nproc) 2>&1 | tee ctest-linux.log | tail -30
```
- All labels, slow included; about 30 minutes on the Mac.
- **Send back:** the last 30 lines (the summary, and any failure with `--output-on-failure`).
- `h5_unit` (harm-coi's pytest) and `h5_*` run only when `HARM_COI_PYTHON` has pyslang, pytest and jsonschema. Check that they are not skipped (`ctest -N -R h5_`).

## 3. The Docker image (A3)
```
docker/build.sh dev
```
- It builds HARM, Z3, harm-coi, Verilator and Icarus, and runs the fast tests inside the image.
- **Send back:** success, or the failing step.

## 4. The evaluation (D-026)
**4a. The local designs, as on the Mac.** HARM is deterministic (H0), so the counts must equal the Mac's; the times may differ:
```
python3 eval/run_eval.py eval/manifests/fixtures.json eval/results/linux-fixtures \
    --python build/harm-coi-venv/bin/python --check eval/results/macos-fixtures/results.csv
python3 eval/run_eval.py eval/manifests/examples.json eval/results/linux-examples \
    --configs C0,C1,C2 --check eval/results/macos-examples/results.csv
```

**4b. About 10 AssertLLM2 designs.**
- **Choose them by four criteria:**
  - pyslang elaborates them (`harm-coi --top … --files …` runs);
  - Verilator simulates them with trivergence's flow (`triad_sim`);
  - one clock;
  - a VCD trace.
- **Write a manifest** from `eval/manifests/assertllm2.template.json`, one entry per design:
  - the golden RTL files and top;
  - the trace and its scope, as trivergence's adapter uses it (`--vcd-r 16`);
  - the clock;
  - `faults`: a directory with traces of the mutants, for fault coverage (`--fd`).
- **Run:**
  ```
  python3 eval/run_eval.py eval/manifests/assertllm2.json eval/results/assertllm2 \
      --python build/harm-coi-venv/bin/python
  ```

**4c. GoldMine (optional, Paper A preview).** On the designs GoldMine supports, note its number of assertions, its time and, if possible, its fault coverage on the same mutants. A row per design is enough; `eval/run_eval.py` does not drive GoldMine.

**Send back:** the `eval/results/*` directories (`results.csv`, `results.md`), and the list of chosen designs with the reasons for the excluded ones.

## 5. What to watch for
- **A `timeout` in the table** (default 30 minutes per run) is a measurement, not a failure.
  - Large outputs make `--reduce implies` and `--atom-premises` slow: their work grows with the square of the number of assertions. On the Mac (`eval/results/macos-fixtures`), `structs` mines 1,526 assertions in 43 s; C1 takes 148 s and C2 1,214 s. `constructs` (4,438 assertions) C2 times out.
- **harm-coi's `unknown` signals** (inout nets, other clocks, latches) make COI configurations keep everything for them: see harm-coi's README.
