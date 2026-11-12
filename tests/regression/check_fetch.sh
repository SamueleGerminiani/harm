#!/bin/bash
# H27 T1: third_party/fetch.sh's `fetch <url> <sha256> <file>` keeps a download whose SHA-256 is the expected one,
# refuses another (naming both values) and fails on a failed download. A local file:// URL, so no network.
# Usage: check_fetch.sh <repository root>
set -euo pipefail
src=$1
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT
printf 'harm h27\n' > "$work/payload"
good=$( (command -v sha256sum >/dev/null && sha256sum "$work/payload" || shasum -a 256 "$work/payload") | cut -d' ' -f1)
source "$src/third_party/fetch.sh"
cd "$work"
fetch "file://$work/payload" "$good" ok.bin
cmp -s ok.bin payload || { echo "FAIL: the kept file differs"; exit 1; }
if err=$(fetch "file://$work/payload" "$(printf '0%.0s' {1..64})" bad.bin 2>&1); then
    echo "FAIL: a wrong checksum was accepted"; exit 1
fi
[[ "$err" == *"$good"* && "$err" == *"0000000000000000"* ]] || { echo "FAIL: the refusal does not name both values: $err"; exit 1; }
[ ! -e bad.bin ] || { echo "FAIL: a refused file was kept"; exit 1; }
if fetch "file://$work/missing" "$good" none.bin 2>/dev/null; then
    echo "FAIL: a failed download passed"; exit 1
fi
echo "h27 fetch: ok"
