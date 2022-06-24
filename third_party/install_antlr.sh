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


mkdir antlr4_tmp
cd antlr4_tmp
wget --no-check-certificate https://www.antlr.org/download/antlr4-cpp-runtime-4.9.3-source.zip
unzip antlr4-cpp-runtime-4.9.3-source.zip
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX="$installPrefix" -DCMAKE_CXX_STANDARD=17 ..
make -j"$NThreads"
make install
cd ../../
rm -rf antlr4_tmp
