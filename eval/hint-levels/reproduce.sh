#!/usr/bin/env bash
# Reproduce the hint-level study's numbers, step by step. Each step calls an existing script; times are those of
# the original runs (Linux, 20-24 cores, 3 runs at a time, 6 HARM threads each). Usage:
#   eval/hint-levels/reproduce.sh <out dir> [step ...]     steps: fetch sizes prepare configs assertllm2 assertllm2-20 arms none depth deep filter tables
# HARM_BIN: the harm binary (default build/harm); PYTHON: a Python with harm-coi's dependencies (default python3);
# NONE_MEM_GIB: none-full's memory limit per HARM process (default 38).
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
OUT=$(mkdir -p "$1" && cd "$1" && pwd); shift
STEPS=${*:-fetch sizes prepare configs assertllm2 assertllm2-20 arms none depth deep filter tables}
HARM_BIN=${HARM_BIN:-$ROOT/build/harm}
PY=${PYTHON:-python3}
M=$ROOT/eval/mutants
H=$ROOT/eval/hint-levels
BASE=spill_register,fall_through_register,fifo_v3,rr_arb_tree,id_queue,lfsr,plru_tree,delta_counter,exp_backoff,credit_counter
DEPTH=exp_backoff_d10,exp_backoff_d14,delta_counter_d10,delta_counter_d14,credit_counter_d16,credit_counter_d64,fifo_v3_d16,fifo_v3_d64
DEEP=lossy_valid_to_stream,stream_delay,id_queue,fall_through_register
SEEDS=(--mining-seeds 1-5 --heldout-seeds 101-103)
link_prepared() {  # link_prepared <dir>: a run directory that reuses the prepared designs (mutants_eval keeps one info.json per dir)
  for d in ${BASE//,/ }; do
    mkdir -p "$1/$d"
    for f in "$OUT/prepared/$d"/*; do [ "$(basename "$f")" = harm ] || ln -sfn "$f" "$1/$d/$(basename "$f")"; done
  done
}
for s in $STEPS; do
  echo "== $s ($(date '+%F %T'))"
  case $s in
    fetch)  # PULP common_cells v1.40.0, pinned
      bash "$M/fetch.sh" "$ROOT" ;;
    sizes)  # each design's ports and lines of RTL (the letter's Table IV): seconds
      $PY "$H/sizes.py" "$M/corpus.json" --out "$OUT/sizes.csv" ;;
    prepare)  # traces (directed tests then 5,000 random cycles), 100 mutants per design, activation: about 2-3 h
      $PY "$M/mutants_eval.py" "$M/corpus.json" "$OUT/prepared" --harm "$HARM_BIN" --python "$PY" \
        --configs prepare-only "${SEEDS[@]}" --jobs 8 ;;
    configs)  # HARM's six configurations on the 10 base designs, 600 s per run: about 1.5 h
      link_prepared "$OUT/configs"
      $PY "$M/mutants_eval.py" "$M/corpus.json" "$OUT/configs" --harm "$HARM_BIN" --python "$PY" \
        --configs C0,R,R+F,R+F+X,RR,RR+F+X --designs $BASE "${SEEDS[@]}" --timeout 600 --threads 6 ;;
    assertllm2)  # the same configurations on AssertLLM2, without fault traces (assertion counts and times only).
      # Needs the AssertLLM2 designs and golden traces under build/assertllm2 (eval/LINUX.md); they are not distributed here.
      $PY - "$ROOT/eval/manifests/assertllm2.json" "$OUT/assertllm2-nofaults.json" <<'EOF'
import json, sys
m = json.load(open(sys.argv[1]))
for e in m:
    e.pop("faults", None)
json.dump(m, open(sys.argv[2], "w"), indent=1)
EOF
      (cd "$ROOT" && $PY eval/run_eval.py "$OUT/assertllm2-nofaults.json" "$OUT/assertllm2" --harm "$HARM_BIN" \
        --python "$PY" --configs C0,R,R+F,R+F+X,RR,RR+F+X --timeout 600 --threads 6) ;;
    assertllm2-20)  # after assertllm2: C0 and RR+F+X again with 20 HARM threads, one run at a time: about 1 h
      (cd "$ROOT" && $PY eval/run_eval.py "$OUT/assertllm2-nofaults.json" "$OUT/assertllm2-20" --harm "$HARM_BIN" \
        --python "$PY" --configs C0,RR+F+X --timeout 600 --threads 20) ;;
    arms)  # the arms L0 to deep on the 10 base designs, deep 3 times, 3,600 s per run: about 5 h
      $PY "$H/run_arms.py" "$M/corpus.json" "$OUT/prepared" "$OUT/arms" --designs $BASE --arms L0,L0+roles,rel,deep --repeats deep=3 \
        --timeout 3600 --threads 6 --jobs 3 --machine "$(uname -s)" --harm "$HARM_BIN" --python "$PY" ;;
    none)  # HARM alone: none, 3,600 s per run, 20 GiB per HARM process (about 4 h); then none-full, one run at a time on
      # every thread, 38 GiB per HARM process (NONE_MEM_GIB): about 6 h for the eight designs that finish; rr_arb_tree
      # reached 38 GiB after 2.2 h and id_queue needs more than 20 GiB (see README). Needs that much RAM free.
      $PY "$H/run_arms.py" "$M/corpus.json" "$OUT/prepared" "$OUT/none" --designs $BASE --arms none \
        --timeout 3600 --threads 6 --jobs 3 --mem-gib 20 --machine "$(uname -s)" --harm "$HARM_BIN" --python "$PY"
      $PY "$H/run_arms.py" "$M/corpus.json" "$OUT/prepared" "$OUT/none-full" --designs $BASE --arms none-full \
        --threads "$(nproc 2>/dev/null || sysctl -n hw.ncpu)" --jobs 1 --mem-gib "${NONE_MEM_GIB:-38}" \
        --machine "$(uname -s)" --harm "$HARM_BIN" --python "$PY" ;;
    depth)  # the depth variants: L0+roles and deep (3 times): about 2.5 h
      $PY "$H/run_arms.py" "$M/corpus.json" "$OUT/prepared" "$OUT/depth" --designs $DEPTH --arms L0+roles,deep \
        --repeats deep=3 --timeout 3600 --threads 6 --jobs 3 --machine "$(uname -s)" --harm "$HARM_BIN" --python "$PY" ;;
    deep)  # the four designs where deep kills more: L0+roles and deep (3 times): about 30 min
      $PY "$H/run_arms.py" "$M/corpus.json" "$OUT/prepared" "$OUT/deep" --designs $DEEP --arms L0+roles,deep \
        --repeats deep=3 --timeout 3600 --threads 6 --jobs 3 --machine "$(uname -s)" --harm "$HARM_BIN" --python "$PY" ;;
    filter)  # the cone filter's lost kills: R and R+F, one info.json per configuration: about 40 min
      for c in R R+F; do
        link_prepared "$OUT/filter-$c"
        $PY "$M/mutants_eval.py" "$M/corpus.json" "$OUT/filter-$c" --harm "$HARM_BIN" --python "$PY" --configs $c \
          --designs $BASE "${SEEDS[@]}" --timeout 600 --threads 6
      done
      $PY "$H/filter_check.py" "$OUT/prepared" "$OUT/filter-R" "$OUT/filter-R+F" --out "$OUT/filter.csv" ;;
    tables)  # the tables, from this run's CSVs where present, else from results/
      T=$OUT/tables; mkdir -p "$T"
      cp "$H/results/"*.csv "$T/"
      [ -f "$OUT/arms/results.csv" ] && cp "$OUT/arms/results.csv" "$T/arms.csv"
      [ -f "$OUT/configs/results.csv" ] && cp "$OUT/configs/results.csv" "$T/configurations-pulp.csv"
      [ -f "$OUT/deep/results.csv" ] && cp "$OUT/deep/results.csv" "$T/rq3.csv"
      [ -f "$OUT/depth/results.csv" ] && cp "$OUT/depth/results.csv" "$T/rq3-depth.csv"
      [ -f "$OUT/filter.csv" ] && cp "$OUT/filter.csv" "$T/filter.csv"
      [ -f "$OUT/sizes.csv" ] && cp "$OUT/sizes.csv" "$T/sizes.csv"
      [ -f "$OUT/assertllm2-20/results.csv" ] && cp "$OUT/assertllm2-20/results.csv" "$T/assertllm2-20-threads.csv"
      if [ -f "$OUT/none/results.csv" ]; then  # none.csv: the none and none-full runs' rows
        { cat "$OUT/none/results.csv"; [ -f "$OUT/none-full/results.csv" ] && tail -n +2 "$OUT/none-full/results.csv"; } \
          > "$T/none.csv"
      fi
      $PY "$H/tables.py" "$T" ;;
    *) echo "unknown step $s" >&2; exit 2 ;;
  esac
done
