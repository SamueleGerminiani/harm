#!/bin/bash

NThreads=1

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NThreads="`grep -c ^processor /proc/cpuinfo`"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NThreads="`sysctl -n hw.ncpu`"
fi


if [ $# -eq 0 ]
then
    installPrefix="$(pwd)/antlr4"
    mkdir antlr4
else
    installPrefix="$1"
fi


git clone https://github.com/antlr/antlr4 --depth 1 antlr4_tmp
cd antlr4_tmp/runtime/Cpp
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$installPrefix" -DCMAKE_CXX_STANDARD=17 ..
make -j"$NThreads"
make install
cd ../../../../
rm -rf antlr4_tmp
