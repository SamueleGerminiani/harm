#!/bin/bash
# stop at the first failure: a broken clone (network) used to go on and install a wrong tree (H11d)
set -euo pipefail

NThreads=1

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NThreads="`grep -c ^processor /proc/cpuinfo`"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NThreads="`sysctl -n hw.ncpu`"
fi


if [ $# -eq 0 ]
then
    installPrefix="$(pwd)/antlr4"
    mkdir -p antlr4
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

echo "Installing ANTLR4 C++ runtime to: $installPrefix"

rm -rf antlr4_tmp   # left by an interrupted run
git clone https://github.com/antlr/antlr4 --depth 1 antlr4_tmp
cd antlr4_tmp/runtime/Cpp
mkdir build && cd build
git fetch --all --tags --prune
git checkout 4.13.2
cmake -DCMAKE_C_COMPILER="$CC" -DCMAKE_CXX_COMPILER="$CXX" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$installPrefix" -DCMAKE_CXX_STANDARD=17 ..
make -j"$NThreads"
make install
cd ../../../../
rm -rf antlr4_tmp
echo "$("$CXX" --version | head -1)" > "$installPrefix/.harm_toolchain"
