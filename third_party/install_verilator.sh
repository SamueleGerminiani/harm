#!/bin/bash
# Verilator (the simulation oracles and fixture generators, H1/H4/H5/H11c), from the release
# sources. Usage: install_verilator.sh [install prefix]   (default: third_party/verilator)
here="$(cd "$(dirname "$0")" && pwd)"
source "$here/tools_common.sh"
VERILATOR_VERSION=5.052

tools_setup verilator "${1:-}"
tools_require autoconf make flex bison perl python3 help2man
work="$(mktemp -d)"
cd "$work"
tools_fetch "https://github.com/verilator/verilator/archive/refs/tags/v${VERILATOR_VERSION}.tar.gz" v.tar.gz
tar -xf v.tar.gz && rm v.tar.gz
cd "verilator-${VERILATOR_VERSION}"
unset VERILATOR_ROOT
autoconf
./configure --prefix "$installPrefix" CC="$CC" CXX="$CXX"
make -j"$NThreads"
make install
cd / && rm -rf "$work"
"$installPrefix/bin/verilator" --version | tee "$installPrefix/.harm_version"
