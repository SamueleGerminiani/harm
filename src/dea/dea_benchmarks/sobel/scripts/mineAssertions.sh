#!/bin/bash 
$HARM_ROOT/build/harm --vcd traces/golden.vcd --clk sobel_tb::clk --conf scripts/conf.xml --dont-fill-ass --dump-to ass/ --max-ass 1000 --sample-by-con
