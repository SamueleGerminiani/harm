#!/bin/bash

#check if $3 is not defined and set row to 1

if [ -z "$3" ]; then
    row=0
else
    row=$3
fi


approximation=$(python3 $BENCHMARK_ROOT/support/daToDea.py --csv $1 --txt $2 --row $row)

##check program return value
if [ $? -ne 0 ]; then
    echo $approximation
    exit 1
fi

echo $approximation
bash $(pwd)/scripts/simulateCS.sh "$approximation" "traces/" 1 0



