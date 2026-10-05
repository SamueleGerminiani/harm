#!/usr/bin/env bash
# Rewrite the regression baselines. Use only with explicit approval, and record every use in
# doc/plan/VALIDATION.md.
#
# Usage: update_baseline.sh <build-dir> <set|ordered> [ctest -R regex, default: all cases]
set -euo pipefail

build=$1
mode=$2
filter=${3:-.*}

[[ "$mode" == "set" || "$mode" == "ordered" ]] || { echo "mode must be set or ordered" >&2; exit 2; }

HARM_REGRESSION_CAPTURE=$mode ctest --test-dir "$build" -R "^regression_($filter)\$" --output-on-failure
