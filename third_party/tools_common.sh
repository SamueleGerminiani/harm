#!/bin/bash
# Shared by install_{verilator,iverilog,yosys}.sh (H11d). Sourced, not run.
# Sets NThreads, installPrefix (third_party/<tool>, or $1), CC/CXX, and on macOS puts Homebrew's
# bison and flex first on PATH (macOS's own bison 2.3 is too old for Verilator and yosys).
# Usage: tools_setup <tool> [install prefix]
set -euo pipefail

tools_setup() {
    local tool=$1
    NThreads=1
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        NThreads="$(grep -c ^processor /proc/cpuinfo)"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        NThreads="$(sysctl -n hw.ncpu)"
        if command -v brew >/dev/null; then
            for f in bison flex gperf; do
                if p=$(brew --prefix "$f" 2>/dev/null) && [ -d "$p/bin" ]; then
                    export PATH="$p/bin:$PATH"
                fi
            done
        fi
        if [[ -z "${SDKROOT:-}" ]]; then
            export SDKROOT="$(xcrun --show-sdk-path)"
        fi
    fi
    installPrefix="${2:-$(pwd)/$tool}"
    mkdir -p "$installPrefix"
    installPrefix="$(cd "$installPrefix" && pwd)"
    # The tools are separate programs, not linked into HARM (D-010 does not bind them), but they are
    # built with the same compilers as the other dependencies
    CC="${CC:-cc}"
    CXX="${CXX:-c++}"
    export CC CXX
    echo "Building $tool into $installPrefix with CC=$CC CXX=$CXX ($("$CXX" --version | head -1))${SDKROOT:+ SDKROOT=$SDKROOT}"
}

# tools_require <command>... : stop with the list of missing prerequisites (README, "Dependencies")
tools_require() {
    local missing=()
    for c in "$@"; do
        command -v "$c" >/dev/null || missing+=("$c")
    done
    if [ ${#missing[@]} -gt 0 ]; then
        echo "Missing prerequisites: ${missing[*]} (see README, Dependencies)" >&2
        exit 1
    fi
}

# tools_fetch <url> <archive> : download into the current directory
tools_fetch() {
    if command -v wget >/dev/null; then
        wget -q --no-check-certificate "$1" -O "$2"
    else
        curl -sSL "$1" -o "$2"
    fi
}
