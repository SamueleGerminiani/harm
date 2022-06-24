#!/bin/bash

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


wget --no-check-certificate https://github.com/Z3Prover/z3/archive/refs/tags/z3-4.8.10.tar.gz
tar -xvf z3-4.8.10.tar.gz && rm z3-4.8.10.tar.gz
cd z3-z3-4.8.10
./configure --staticlib --prefix "$installPrefix"
cd build
make -j"$NThreads"
make install
cd ../../
rm -rf z3-z3-4.8.10


#if [[ "$OSTYPE" == "linux-gnu"* ]]; then
#    wget --no-check-certificate https://github.com/Z3Prover/z3/releases/download/z3-4.8.10/z3-4.8.10-x64-ubuntu-18.04.zip
#    unzip z3-4.8.10-x64-ubuntu-18.04.zip && rm z3-4.8.10-x64-ubuntu-18.04.zip
#    if [ $# -eq 0 ]
#    then
#        mkdir z3
#        mv z3-4.8.10-x64-ubuntu-18.04/bin/ z3/lib
#        mv z3-4.8.10-x64-ubuntu-18.04/include/ z3
#    else
#        installPrefix=$1
#        mkdir "$installPrefix/lib/z3"
#        mkdir "$installPrefix/include/z3"
#        mv z3-4.8.10-x64-ubuntu-18.04/bin/* "$installPrefix/lib/z3"
#        mv z3-4.8.10-x64-ubuntu-18.04/include/* "$installPrefix/include/z3"
#    fi
#    rm -rf z3-4.8.10-x64-ubuntu-18.04/
#
#
#elif [[ "$OSTYPE" == "darwin"* ]]; then
#    wget --no-check-certificate https://github.com/Z3Prover/z3/releases/download/z3-4.8.10/z3-4.8.10-x64-osx-10.15.7.zip
#    unzip z3-4.8.10-x64-osx-10.15.7.zip && rm z3-4.8.10-x64-osx-10.15.7.zip
#
#    if [ $# -eq 0 ]
#    then
#        mkdir z3
#        mkdir z3/lib
#        mv z3-4.8.10-x64-osx-10.15.7/bin/* z3/lib
#        mv z3-4.8.10-x64-osx-10.15.7/include/ z3/
#    else
#        installPrefix=$1
#        mkdir "$installPrefix/lib/z3"
#        mkdir "$installPrefix/include/z3"
#        mv z3-4.8.10-x64-osx-10.15.7/bin/* "$installPrefix/lib/z3"
#        mv z3-4.8.10-x64-osx-10.15.7/include/* "$installPrefix/include/z3"
#    fi
#    rm -rf z3-4.8.10-x64-osx-10.15.7
#fi




