#!/bin/bash

approximation=$(python3 scripts/daToDea.py --csv $1 --txt $2)

echo $approximation
bash scripts/simulateCS.sh "$approximation" "traces/" 1 0 >> /dev/null



