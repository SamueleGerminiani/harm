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


wget --no-check-certificate https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.tar.gz
tar -xvf boost_1_83_0.tar.gz
cd boost_1_83_0
bash bootstrap.sh
./b2 --prefix="$installPrefix" install
cd ..
rm -rf boost_1_83_0
rm boost_1_83_0.tar.gz
