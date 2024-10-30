#!/bin/bash 
$HARM_ROOT/build/harm --vcd traces/golden.vcd --clk sobel_tb::clk --conf scripts/conf.xml --dump-to ass/axc_ass.txt
