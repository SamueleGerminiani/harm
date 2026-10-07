#!/bin/bash
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

if [ $# -eq 0 ]
then
    bash install_antlr.sh
    bash install_spotltl.sh
    bash install_boost.sh
    bash install_z3.sh
    if [ $tools -eq 1 ]; then
        bash install_verilator.sh
        bash install_iverilog.sh
        bash install_yosys.sh
    fi
else
    installPrefix="$1"
    bash install_antlr.sh "$installPrefix"
    bash install_spotltl.sh "$installPrefix"
    bash install_boost.sh "$installPrefix"
    bash install_z3.sh "$installPrefix"
    if [ $tools -eq 1 ]; then
        bash install_verilator.sh "$installPrefix"
        bash install_iverilog.sh "$installPrefix"
        bash install_yosys.sh "$installPrefix"
    fi
fi
