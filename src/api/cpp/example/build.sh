#!/bin/bash
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    $CXX example.cpp -I../include/ ../../../../install/harm/lib/libantlr4-runtime.so ../../../../install/harm/lib/libdevharm.so ../../../../install/harm/lib/libspot.so ../../../../install/harm/lib/libz3.so -o harm_example
elif [[ "$OSTYPE" == "darwin"* ]]; then
    $CXX example.cpp -I../include/ ../../../../install/harm/lib/libantlr4-runtime.dylib ../../../../install/harm/lib/libdevharm.dylib ../../../../install/harm/lib/libspot.dylib ../../../../install/harm/lib/libz3.dylib -o harm_example
fi


