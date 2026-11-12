#!/bin/bash
set -euo pipefail  # H27: a failed step stops the script
# Verilator (the simulation oracles and fixture generators, H1/H4/H5/H11c), from the release
# sources. Usage: install_verilator.sh [install prefix]   (default: third_party/verilator)
here="$(cd "$(dirname "$0")" && pwd)"
source "$here/tools_common.sh"
VERILATOR_VERSION=5.052

tools_setup verilator "${1:-}"
tools_require autoconf make flex bison perl python3 help2man
work="$(mktemp -d)"
cd "$work"
VERILATOR_SHA256=8c8d2e11e6ad32f641dd250742a94195ddecb912e2e2dabe2f42ddbbb99c1092  # H27: from the download of 2026-10-15
tools_fetch "https://github.com/verilator/verilator/archive/refs/tags/v${VERILATOR_VERSION}.tar.gz" "$VERILATOR_SHA256" v.tar.gz
tar -xf v.tar.gz && rm v.tar.gz
cd "verilator-${VERILATOR_VERSION}"
unset VERILATOR_ROOT
autoconf
./configure --prefix "$installPrefix" CC="$CC" CXX="$CXX"
make -j"$NThreads"
make install
cd / && rm -rf "$work"
"$installPrefix/bin/verilator" --version | tee "$installPrefix/.harm_version"
