#!/bin/bash

#parameters
top="sobel_tb"
vcd="$top/*"
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

if [[ $mode == "1" ]]; then
    #simulate to get the metric value (SSIM)
    $MODELSIM_BIN/vlog -work "work$threadID" +define+OUT_PATH=""$work"/" $compDefine +define+IN_PATH="$BENCHMARK_ROOT/sobel/IO/in/" -sv "$BENCHMARK_ROOT/sobel/rtl/sr/*" "$BENCHMARK_ROOT/sobel/rtl/tb/*"
    $MODELSIM_BIN/vsim -L $work "$work.sobel_tb" -c -voptargs="+acc" -do "run -all; quit"
else
    #simulate to get the vcd trace
    $MODELSIM_BIN/vlog -work "work$threadID" +define+TRACE_LENGTH=""$traceLength"" +define+OUT_PATH=""$work"/" $compDefine +define+IN_PATH="$BENCHMARK_ROOT/sobel/IO/in/" -sv "$BENCHMARK_ROOT/sobel/rtl/sr/*" "$BENCHMARK_ROOT/sobel/rtl/tb/*"
    $MODELSIM_BIN/vsim -L $work "$work.sobel_tb" -c -voptargs="+acc" -do "vcd file $outputDir/$faultList.vcd; vcd add $vcd; run -all; quit"
fi


if [[ $mode == "1" ]]; then
    #get the metric value by comparing the output
    python3 "$BENCHMARK_ROOT/sobel/scripts/sobel_IO_to_jpeg.py" "$work/512x512sobel_out_nbits.txt" "$work/img.jpeg"
    if [[ $faultList == "golden" ]]; then
        #no metric value is generated if we are simulating the golden
        cp "$work/img.jpeg" "$BENCHMARK_ROOT/sobel/imgs/golden.jpeg"
    else
        python3 -W ignore "$BENCHMARK_ROOT/sobel/scripts/calc_SSIM_WP.py" "$BENCHMARK_ROOT/sobel/imgs/golden.jpeg" "$work/img.jpeg" "$work/out.txt"
        #move the output where DEA expects it
        cp "$work/out.txt" "$outputDir/$threadID.txt"
    fi
fi

#clean
rm -rf "$work"

