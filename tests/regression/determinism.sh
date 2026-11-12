#!/usr/bin/env bash
# Check that HARM's ordered output does not depend on the number of threads or on the run.
#
# Usage: determinism.sh <harm-binary> [harm args...]
#   A2: --max-threads 1 vs --max-threads 8
#   A3: three runs with --max-threads 8
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
harm=$1
shift

run() { HARM_THREADS=$1 bash "$here/run_case.sh" print "$harm" /dev/null "${@:2}"; }

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

run 1 "$@" >"$tmp/t1"
for i in 1 2 3; do
    run 8 "$@" >"$tmp/t8_$i"
done

status=0
if ! diff -u "$tmp/t1" "$tmp/t8_1" >"$tmp/d"; then
    echo "FAIL: output with 1 thread differs from output with 8 threads"
    head -40 "$tmp/d"
    status=1
fi
for i in 2 3; do
    if ! diff -u "$tmp/t8_1" "$tmp/t8_$i" >"$tmp/d"; then
        echo "FAIL: run $i with 8 threads differs from run 1"
        head -40 "$tmp/d"
        status=1
    fi
done
exit $status
