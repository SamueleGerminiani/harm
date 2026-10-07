#!/usr/bin/env bash
# Regenerate trace.vcd with Verilator >= 5 (H11c, F-L5). Usage: build.sh <build-dir>
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
out=${1:-$(mktemp -d)}
mkdir -p "$out" && cd "$out"
verilator --binary --timing --trace -Wno-fatal -Wno-lint -Wno-style --top-module tb "$here"/rtl/*.sv "$here"/tb.sv -o sim --Mdir obj >/dev/null
./obj/sim +verilator+seed+3 >/dev/null
cp trace.vcd "$here/trace.vcd"
