#!/bin/bash

NThreads=1

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NThreads="`grep -c ^processor /proc/cpuinfo`"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NThreads="`sysctl -n hw.ncpu`"
fi

if [ $# -eq 0 ]
then
    installPrefix="$(pwd)/spot"
    mkdir spot
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

wget --no-check-certificate http://www.lrde.epita.fr/dload/spot/spot-2.9.7.tar.gz
tar -xvf spot-2.9.7.tar.gz && rm spot-2.9.7.tar.gz
cd spot-2.9.7
./configure CC="$CC" CXX="$CXX" --disable-python --prefix "$installPrefix"

make -j"$NThreads"
make install
cd ../
rm -rf spot-2.9.7
echo "$("$CXX" --version | head -1)" > "$installPrefix/.harm_toolchain"
