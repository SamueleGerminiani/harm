#!/bin/bash

#parameters
top="fft_tb"
traceLength=1000

#inputs from DEA
faultList=$1
outputDir=$2
mode=$3
threadID=$4

#Split the list into an array using the semicolon as a delimiter
IFS=';' read -r -a faults <<< "$faultList"

compDefine=""

#generate the compile options required to inject the faults into the design
if [[ ! $faultList == "golden" ]]; then
    for fault in "${faults[@]}"
    do
        IFS='#' read -r -a split <<< "$fault"
        name="${split[0]}"
        sub="${split[2]}"
        compDefine="$compDefine +define+$name +define+SUB_$name=$sub"
    done
fi

if [[ $mode == "1" ]]; then
traceLength=10000
fi

echo "$compDefine"

work="work$threadID"

$MODELSIM_BIN/vlib "$work"

#simulate to get the metric value (Err)
$MODELSIM_BIN/vlog -work "work$threadID" +define+TRACE_LENGTH=""$traceLength"" +define+OUT_PATH=""$work"/" $compDefine -sv "$BENCHMARK_ROOT/fft/rtl/cs/*" "$BENCHMARK_ROOT/fft/rtl/tb/*"
$MODELSIM_BIN/vsim -L $work "$work.$top" -c -voptargs="+acc" -do "run -all; quit"


if [[ $mode == "1" ]]; then

    if [[ $faultList == "golden" ]]; then
        #no metric value is generated if we are simulating the golden
        cp "$work/trace.csv" "traces/golden.csv"
    else
        cp "$work/err.txt" "$outputDir/$threadID.txt"
        #cat "$outputDir/$threadID.txt"
    fi
else
    #simply store the trace
    cp "$work/trace.csv" "$outputDir/$faultList.csv"
fi

#clean
rm -rf "$work"


