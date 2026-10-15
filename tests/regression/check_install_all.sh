#!/bin/bash
# H27 T3: install_all.sh stops at the first install script that fails, exits non-zero and names it.
# Stub scripts in a copy of third_party: install_spotltl.sh fails, the others leave a marker.
# Usage: check_install_all.sh <repository root>
set -euo pipefail
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT
cp "$1/third_party/install_all.sh" "$work/"
for t in antlr spotltl boost z3 verilator iverilog yosys; do
    printf '#!/bin/bash\ntouch "%s/ran_%s"\n' "$work" "$t" > "$work/install_$t.sh"
done
printf '#!/bin/bash\necho broken >&2\nexit 7\n' > "$work/install_spotltl.sh"
if out=$(bash "$work/install_all.sh" --no-tools 2>&1); then
    echo "FAIL: install_all.sh succeeded after a failing script"; exit 1
fi
[[ "$out" == *install_spotltl.sh* ]] || { echo "FAIL: the failing script is not named: $out"; exit 1; }
[ -e "$work/ran_antlr" ] || { echo "FAIL: install_antlr.sh did not run"; exit 1; }
[ ! -e "$work/ran_boost" ] || { echo "FAIL: install_boost.sh ran after the failure"; exit 1; }
echo "h27 install_all: ok"
