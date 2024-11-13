#!/bin/bash
csvFile=$1
technique=$2
id=$3

#check if $1 exist, if not return error
if [ -z "$1" ]; then
    echo "Error: csv file is not set"
    exit 1
fi

#if technique is not set return error
if [ -z "$technique" ]; then
    echo "Error: technique is not set"
    exit 1
fi

#check if $2 exist, if not set it to 0
if [ -z "$3" ]; then
    id=0
fi

approximation=$(python3 $BENCHMARK_ROOT/support/runDEA.py --csv $csvFile --id $id)

##check program return value
if [ $? -ne 0 ]; then
    echo $approximation
    exit 1
fi

echo $approximation

if [ "$technique" == "cs" ]; then
    #check if script exist
    if [ ! -f $(pwd)/scripts/simulateCS.sh ]; then
        echo "Error: cs technique is not supported"
        exit 1
    fi
bash $(pwd)/scripts/simulateCS.sh "$approximation" "traces/" 1 0
elif [ "$technique" == "br" ]; then
    if [ ! -f $(pwd)/scripts/simulateBR.sh ]; then
        echo "Error: br technique is not supported"
        exit 1
    fi
bash $(pwd)/scripts/simulateBR.sh "$approximation" "traces/" 1 0

elif [ "$technique" == "sr" ]; then
    if [ ! -f $(pwd)/scripts/simulateSR.sh ]; then
        echo "Error: sr technique is not supported"
        exit 1
    fi
bash $(pwd)/scripts/simulateSR.sh "$approximation" "traces/" 1 0
else 
  echo "Error: technique is not supported or not set"
fi


