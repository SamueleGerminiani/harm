#!/usr/bin/env bash
# Run one regression case and compare its mined assertions with a stored baseline.
#
# Usage: run_case.sh <print|check|capture> <harm-binary> <baseline-file> [harm args...]
#   print   : print the normalised output (ordered) to stdout
#   check   : compare with the baseline; the baseline header says whether order matters
#   capture : (re)write the baseline; the mode is taken from $HARM_REGRESSION_CAPTURE (set|ordered)
#
# If $HARM_REGRESSION_CAPTURE is set, `check` behaves like `capture` (used by update_baseline.sh).
# The number of threads is $HARM_THREADS (default 1).
set -euo pipefail

action=$1
harm=$2
baseline=$3
shift 3

if [[ -n "${HARM_REGRESSION_CAPTURE:-}" && "$action" == "check" ]]; then
    action=capture
fi

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
mkdir "$tmp/dump"

# Run in a scratch directory: some cases write files into the working directory
if ! (cd "$tmp" && "$harm" "$@" --max-threads "${HARM_THREADS:-1}" --psilent --isilent \
    --dump-to "$tmp/dump/") >"$tmp/log" 2>&1; then
    echo "harm failed; output:" >&2
    cat "$tmp/log" >&2
    exit 1
fi

# One section per dumped file (one file per context, plus fault-coverage files), in file-name order.
# $1: set|ordered
normalise() {
    local f
    for f in $(cd "$tmp/dump" && LC_ALL=C ls); do
        echo "### $f"
        sed -e $'s/\x1b\\[[0-9;]*m//g' -e 's/[[:space:]]*$//' "$tmp/dump/$f" |
            if [[ "$1" == "set" ]]; then LC_ALL=C sort; else cat; fi
    done
}

case "$action" in
print)
    normalise ordered
    ;;
capture)
    mode=${HARM_REGRESSION_CAPTURE:-ordered}
    [[ "$mode" == "set" || "$mode" == "ordered" ]] || { echo "bad capture mode '$mode'" >&2; exit 2; }
    mkdir -p "$(dirname "$baseline")"
    { echo "# mode: $mode"; normalise "$mode"; } >"$baseline"
    echo "captured $baseline ($mode)"
    ;;
check)
    [[ -f "$baseline" ]] || { echo "missing baseline $baseline" >&2; exit 1; }
    mode=$(head -1 "$baseline" | sed -nE 's/^# mode: (set|ordered)$/\1/p')
    [[ -n "$mode" ]] || { echo "baseline $baseline has no '# mode:' header" >&2; exit 1; }
    { echo "# mode: $mode"; normalise "$mode"; } >"$tmp/result"
    diff -u "$baseline" "$tmp/result"
    ;;
*)
    echo "unknown action '$action'" >&2
    exit 2
    ;;
esac
