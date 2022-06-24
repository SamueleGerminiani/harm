#!/bin/bash

if [ $# -eq 0 ]
then
    bash install_antlr.sh
    bash install_spotltl.sh
    bash install_z3.sh
else
    installPrefix="$1"
    bash install_antlr.sh "$installPrefix"
    bash install_spotltl.sh "$installPrefix"
    bash install_z3.sh "$installPrefix"
fi


