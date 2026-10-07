#!/bin/bash
# Icarus Verilog (the 4-state fixture generator, H1), from the release sources.
# Usage: install_iverilog.sh [install prefix]   (default: third_party/iverilog)
here="$(cd "$(dirname "$0")" && pwd)"
source "$here/tools_common.sh"
IVERILOG_TAG=v13_0

tools_setup iverilog "${1:-}"
tools_require autoconf make flex bison gperf
work="$(mktemp -d)"
cd "$work"
tools_fetch "https://github.com/steveicarus/iverilog/archive/refs/tags/${IVERILOG_TAG}.tar.gz" i.tar.gz
tar -xf i.tar.gz && rm i.tar.gz
cd "iverilog-${IVERILOG_TAG#v}"
sh autoconf.sh
./configure --prefix "$installPrefix" CC="$CC" CXX="$CXX"
make -j"$NThreads"
make install
cd / && rm -rf "$work"
# not 'iverilog -V | head -1': with pipefail, iverilog killed by SIGPIPE would fail the script
version="$("$installPrefix/bin/iverilog" -V 2>&1 || true)"
echo "${version%%$'\n'*}" | tee "$installPrefix/.harm_version"
