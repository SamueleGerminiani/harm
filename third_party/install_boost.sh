#!/bin/bash
set -euo pipefail  # H27: a failed step stops the script

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

here="$(cd "$(dirname "$0")" && pwd)"
source "$here/fetch.sh"
BOOST_SHA256=c0685b68dd44cc46574cce86c4e17c0f611b15e195be9848dfd0769a0a207628  # H27: boost.io's published value
fetch https://archives.boost.io/release/1.83.0/source/boost_1_83_0.tar.gz "$BOOST_SHA256" boost_1_83_0.tar.gz
tar -xvf boost_1_83_0.tar.gz
cd boost_1_83_0
bash bootstrap.sh
# b2 ignores CC/CXX: select the toolset explicitly; only regex is a compiled library used by HARM
if "$CXX" --version 2>/dev/null | grep -i clang >/dev/null; then  # no -q: under pipefail an early exit fails the pipe
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
