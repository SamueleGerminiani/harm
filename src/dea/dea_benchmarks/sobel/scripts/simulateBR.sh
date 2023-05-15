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

declare -A idToName
declare -A idToSize
declare -A idToBit

#Split the list into an array using the semicolon as a delimiter
IFS=';' read -r -a faults <<< "$faultList"

compDefine=""
declare -A nameToMask
declare -A nameToSize

if [[ ! $faultList == "golden" ]]; then
    
    #retrieve the masks to inject the faults
    for fault in "${faults[@]}"
    do
        
        IFS='_' read -r -a split <<< "$fault"
        
        # Store the values into variables
        name="${split[0]}"
        size="${split[1]}"
        bit="${split[2]}"
        
        #check if the key $name is contained in the dictionary 'nameToMask'
        if [ ! -v 'nameToMask[$name]' ]; then
            #populate the mask with 1s if token was unkown until now
            nameToMask[$name]=$(head -c "$size" < /dev/zero | tr '\0' '1')
        fi
        
        #set the ith bit to 0
        let index="$((size - bit))"
        nameToMask[$name]=$(echo ${nameToMask[$name]} | sed s/./0/$index)
        nameToSize[$name]=$size
        
    done
fi

#generate the compile options required to inject the faults into the design
for name in "${!nameToMask[@]}"
do
    compDefine="$compDefine +define+$name +define+MASK_$name=${nameToSize[$name]}'b${nameToMask[$name]}"
done

echo "$compDefine"

work="work$threadID"

$MODELSIM_BIN/vlib "$work"

if [[ $mode == "1" ]]; then
    #simulate to get the metric value (SSIM)
    $MODELSIM_BIN/vlog -work "work$threadID" +define+OUT_PATH=""$work"/" $compDefine +define+IN_PATH="$BENCHMARK_ROOT/sobel/IO/in/" -sv "$BENCHMARK_ROOT/sobel/rtl/br/*" "$BENCHMARK_ROOT/sobel/rtl/tb/*"
    $MODELSIM_BIN/vsim -L $work "$work.sobel_tb" -c -voptargs="+acc" -do "run -all; quit"
else
    #simulate to get the vcd trace
    $MODELSIM_BIN/vlog -work "work$threadID" +define+TRACE_LENGTH=""$traceLength"" +define+OUT_PATH=""$work"/" $compDefine +define+IN_PATH="$BENCHMARK_ROOT/sobel/IO/in/" -sv "$BENCHMARK_ROOT/sobel/rtl/br/*" "$BENCHMARK_ROOT/sobel/rtl/tb/*"
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

