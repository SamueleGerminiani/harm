#!/usr/bin/env bash
# Regenerate ranges.vcd and expected.txt with Verilator >= 5 (H11c, D-028).
# Usage: tests/input/h11c/gen.sh   (from anywhere)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
work=$(mktemp -d)
cd "$work"
verilator --binary --timing --trace -Wno-fatal -Wno-lint -Wno-style --top-module tb "$here/tb.sv" -o sim --Mdir obj >/dev/null
./obj/sim +verilator+seed+7 +verilator+rand+reset+2 | grep '^CYC' > "$here/expected.txt"
cp ranges.vcd "$here/ranges.vcd"
verilator --version > "$here/generated_with.txt"
rm -rf "$work"
