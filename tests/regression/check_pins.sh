#!/bin/bash
# H27 T2: every third-party install script downloads through `fetch` with a SHA-256, never with an unchecked
# certificate, runs with errexit, and antlr4's checkout is pinned to a commit.
# Usage: check_pins.sh <repository root>
set -euo pipefail
tp="$1/third_party"
fail=0
for s in "$tp"/install_*.sh "$tp"/tools_common.sh; do
    n=$(basename "$s")
    grep -q -- "--no-check-certificate" "$s" && { echo "FAIL: $n: --no-check-certificate"; fail=1; }
    grep -Eq '^[^#]*\b(wget|curl)\b' "$s" && { echo "FAIL: $n: downloads outside fetch"; fail=1; }
    grep -q '^set -euo pipefail' "$s" || { echo "FAIL: $n: no set -euo pipefail"; fail=1; }
done
for s in install_spotltl.sh install_boost.sh install_z3.sh install_verilator.sh install_iverilog.sh install_yosys.sh; do
    grep -Eq '(fetch|tools_fetch) .*[0-9a-f]{64}' "$tp/$s" || grep -Eq '_SHA256=[0-9a-f]{64}' "$tp/$s" \
        || { echo "FAIL: $s: no SHA-256"; fail=1; }
done
grep -Eq 'ANTLR_COMMIT=[0-9a-f]{40}' "$tp/install_antlr.sh" && grep -q 'rev-parse HEAD' "$tp/install_antlr.sh" \
    || { echo "FAIL: install_antlr.sh: the commit of its tag is not pinned and checked"; fail=1; }
[ "$fail" = 0 ] && echo "h27 pins: ok"
exit "$fail"
