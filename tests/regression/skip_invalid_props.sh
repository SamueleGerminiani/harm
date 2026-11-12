#!/usr/bin/env bash
# H1, acceptance test A7: --skip-invalid-props
#   with the flag, a config with invalid propositions mines exactly what the config without them
#   mines, and warns once per invalid proposition; without the flag, HARM exits with an error.
#
# Usage: skip_invalid_props.sh <harm> <csv> <config-with-invalid> <reference-config> <n-invalid>
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
harm=$1 csv=$2 bad=$3 ref=$4 nInvalid=$5

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

bash "$here/run_case.sh" print "$harm" /dev/null --csv "$csv" --conf "$ref" >"$tmp/ref"

# keep warnings visible for this run (run_case.sh does not silence them)
bash "$here/run_case.sh" print "$harm" /dev/null --csv "$csv" --conf "$bad" --skip-invalid-props \
    >"$tmp/skip"
diff -u "$tmp/ref" "$tmp/skip"

(cd "$tmp" && "$harm" --csv "$csv" --conf "$bad" --skip-invalid-props --psilent --max-threads 1) \
    >"$tmp/log" 2>&1
n=$(grep -c "Invalid proposition skipped" "$tmp/log" || true)
if [[ "$n" != "$nInvalid" ]]; then
    echo "expected $nInvalid 'Invalid proposition skipped' warnings, got $n"
    cat "$tmp/log"
    exit 1
fi

if (cd "$tmp" && "$harm" --csv "$csv" --conf "$bad" --psilent --max-threads 1) >"$tmp/log2" 2>&1; then
    echo "without --skip-invalid-props HARM must fail on an invalid proposition"
    exit 1
fi
echo "ok"
