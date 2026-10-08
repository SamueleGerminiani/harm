#!/bin/bash
# yosys with read_slang (the H5 cross-check), from the release tarball, which includes slang and
# sv-elab (built in since yosys 0.67). Needs C++20: GCC >= 11, Clang >= 17 or Xcode >= 16.4.
# Usage: install_yosys.sh [install prefix]   (default: third_party/yosys)
here="$(cd "$(dirname "$0")" && pwd)"
source "$here/tools_common.sh"
YOSYS_VERSION=0.69

tools_setup yosys "${1:-}"
tools_require cmake make flex bison gawk pkg-config python3
# slang's code generators need Python >= 3.9; pass it explicitly, so that CMake does not pick an
# older pythonX.Y found first on PATH
PY="$(command -v "${PYTHON:-python3}" || true)"   # an absolute path: CMake ignores a bare name
[ -n "$PY" ] || { echo "yosys (slang) needs Python >= 3.9: ${PYTHON:-python3} not found" >&2; exit 1; }
"$PY" -c 'import sys; sys.exit(sys.version_info < (3, 9))' || {
    echo "yosys (slang) needs Python >= 3.9; $PY is $("$PY" --version 2>&1). Set PYTHON=<python3.9+>" >&2
    exit 1
}
work="$(mktemp -d)"
cd "$work"
tools_fetch "https://github.com/YosysHQ/yosys/releases/download/v${YOSYS_VERSION}/yosys.tar.gz" y.tar.gz
mkdir yosys && tar -xf y.tar.gz -C yosys && rm y.tar.gz
cd yosys
cmake -B build . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$installPrefix" \
      -DCMAKE_C_COMPILER="$CC" -DCMAKE_CXX_COMPILER="$CXX" \
      -DYOSYS_ENABLE_UNIT_TESTS=OFF -DYOSYS_USE_BUNDLED_LIBS=ON \
      -DPython_EXECUTABLE="$PY" -DPython3_EXECUTABLE="$PY"
cmake --build build -j"$NThreads"
cmake --install build
cd / && rm -rf "$work"
"$installPrefix/bin/yosys" -V | tee "$installPrefix/.harm_version"
# the probe HARM's build uses (cmake/HarmYosysProbe.cmake)
probe="$(mktemp -d)"
echo "module harm_yosys_probe(input logic a, output logic y); assign y = a; endmodule" > "$probe/p.sv"
"$installPrefix/bin/yosys" -q -p "read_slang $probe/p.sv" && echo "read_slang: ok"
rm -rf "$probe"
