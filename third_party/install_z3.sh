#!/bin/bash
# Z3 SMT solver (used by HARM for proposition equivalence, H2). Built from source with the same
# compiler as HARM: a system or Homebrew Z3 may use another C++ runtime (D-010).

NThreads=1

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NThreads="`grep -c ^processor /proc/cpuinfo`"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NThreads="`sysctl -n hw.ncpu`"
fi

if [ $# -eq 0 ]
then
    installPrefix="$(pwd)/z3"
    mkdir z3
else
    installPrefix="$1"
fi

# Use the same C/C++ compiler for every dependency and for HARM (mixing C++ runtimes crashes HARM)
CC="${CC:-cc}"
CXX="${CXX:-c++}"
# On macOS, Homebrew gcc defaults to the newest Command Line Tools SDK, which it may not be able
# to parse: use the SDK CMake uses for HARM (the active developer directory's), unless SDKROOT is set
if [[ "$OSTYPE" == "darwin"* && -z "${SDKROOT:-}" ]]; then
    export SDKROOT="$(xcrun --show-sdk-path)"
fi
echo "Building with CC=$CC CXX=$CXX ($("$CXX" --version | head -1))${SDKROOT:+ SDKROOT=$SDKROOT}"

Z3_VERSION=4.13.4
wget --no-check-certificate https://github.com/Z3Prover/z3/archive/refs/tags/z3-${Z3_VERSION}.tar.gz
tar -xf z3-${Z3_VERSION}.tar.gz && rm z3-${Z3_VERSION}.tar.gz
cd z3-z3-${Z3_VERSION}
mkdir build && cd build
cmake -DCMAKE_C_COMPILER="$CC" -DCMAKE_CXX_COMPILER="$CXX" -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX="$installPrefix" -DZ3_BUILD_LIBZ3_SHARED=ON \
      -DZ3_BUILD_TEST_EXECUTABLES=OFF -DZ3_BUILD_PYTHON_BINDINGS=OFF ..
make -j"$NThreads"
make install
cd ../..
rm -rf z3-z3-${Z3_VERSION}
echo "$("$CXX" --version | head -1)" > "$installPrefix/.harm_toolchain"
