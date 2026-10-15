#!/bin/bash
set -euo pipefail  # H27
# HARM's libraries (antlr4, Spot, Boost, Z3) and, unless --no-tools, the tools its tests use
# (Verilator, Icarus, yosys with read_slang; H11d). Everything is built from source into
# third_party (or into the given prefix).
# Usage: install_all.sh [--no-tools] [install prefix]
tools=1
if [ "${1:-}" = "--no-tools" ]; then
    tools=0
    shift
fi
here="$(cd "$(dirname "$0")" && pwd)"
cd "$here"

# H27: stop at the first script that fails, and name it
run() {
    local s=$1
    shift
    bash "$s" "$@" || { echo "install_all.sh: $s failed (exit $?)" >&2; exit 1; }
}

if [ $# -eq 0 ]
then
    run install_antlr.sh
    run install_spotltl.sh
    run install_boost.sh
    run install_z3.sh
    if [ $tools -eq 1 ]; then
        run install_verilator.sh
        run install_iverilog.sh
        run install_yosys.sh
    fi
else
    installPrefix="$1"
    run install_antlr.sh "$installPrefix"
    run install_spotltl.sh "$installPrefix"
    run install_boost.sh "$installPrefix"
    run install_z3.sh "$installPrefix"
    if [ $tools -eq 1 ]; then
        run install_verilator.sh "$installPrefix"
        run install_iverilog.sh "$installPrefix"
        run install_yosys.sh "$installPrefix"
    fi
fi
