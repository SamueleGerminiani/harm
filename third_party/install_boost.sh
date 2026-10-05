#!/bin/bash

NThreads=1

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NThreads="`grep -c ^processor /proc/cpuinfo`"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NThreads="`sysctl -n hw.ncpu`"
fi


if [ $# -eq 0 ]
then
    installPrefix="$(pwd)/boost"
    mkdir boost
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

wget --no-check-certificate https://archives.boost.io/release/1.83.0/source/boost_1_83_0.tar.gz
tar -xvf boost_1_83_0.tar.gz
cd boost_1_83_0
bash bootstrap.sh
# b2 ignores CC/CXX: select the toolset explicitly; only regex is a compiled library used by HARM
if "$CXX" --version | grep -qi clang; then
    toolset=clang
else
    toolset=gcc
fi
echo "using $toolset : : $CXX ;" > user-config.jam
./b2 --user-config=user-config.jam toolset="$toolset" --with-regex -j"$NThreads" --prefix="$installPrefix" install
cd ..
rm -rf boost_1_83_0
rm boost_1_83_0.tar.gz
echo "$("$CXX" --version | head -1)" > "$installPrefix/.harm_toolchain"
