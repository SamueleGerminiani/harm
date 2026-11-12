#!/usr/bin/env bash
# Build and run the 'structs' fixture with Verilator; writes trace.vcd (or $2) in the build directory.
# Usage: build.sh <build-dir> [vcd-name] [extra verilator arguments...]
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
out=$1; vcd=${2:-trace.vcd}; shift; shift || true
mkdir -p "$out"
cd "$out"
verilator --binary --timing --trace --trace-structs -Wno-fatal -Wno-lint -Wno-style --top-module tb \
  +define+VCD=\"$vcd\" -I"$out" -I"$here/../.." "$@" "$here"/rtl/*.sv "$here"/tb.sv -o sim --Mdir obj >/dev/null
./obj/sim >/dev/null
