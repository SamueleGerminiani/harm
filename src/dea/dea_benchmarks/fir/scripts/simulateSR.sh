#!/bin/bash

#parameters
top="tb_FIR"
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
        compDefine="$compDefine +define+$fault"
    done
fi


echo "$compDefine"

work="work$threadID"

$MODELSIM_BIN/vlib "$work"

#simulate to get the metric value (Err)
$MODELSIM_BIN/vlog -work "work$threadID" +define+OUT_PATH=""$work"/" $compDefine -sv "$BENCHMARK_ROOT/fir/rtl/sr/*" "$BENCHMARK_ROOT/fir/rtl/tb/*"
$MODELSIM_BIN/vsim -L $work "$work.$top" -c -voptargs="+acc" -do "run -all; quit"


if [[ $mode == "1" ]]; then

    if [[ $faultList == "golden" ]]; then
        #no metric value is generated if we are simulating the golden
        cp "$work/output.csv" "filtered/golden.csv"
    else
        #get the metric value by comparing the output
        retErr=$("$BENCHMARK_ROOT/fir/scripts/getError/getError.x" "$BENCHMARK_ROOT/fir/filtered/golden.csv" "$work/output.csv" "0")
        #put the metric value where dea expects it
        echo "$retErr" > "$outputDir/$threadID.txt"
    fi
else
    #simply store the trace
    cp "$work/trace.csv" "$outputDir/$faultList.csv"
fi

#clean
rm -rf "$work"


