#!/bin/bash 
$HARM_ROOT/build/harm --csv traces/golden.csv --conf scripts/conf.xml --dont-fill-ass --dump-to ass/ --max-ass 1000 --sample-by-con
