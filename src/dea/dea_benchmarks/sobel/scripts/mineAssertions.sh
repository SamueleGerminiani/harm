#!/bin/bash 
$HARM_ROOT/build/harm --vcd traces/golden.vcd --clk clk --conf scripts/conf.xml --dont-fill-ass --dump-to ass/ --max-ass 1000 --sample-by-con
