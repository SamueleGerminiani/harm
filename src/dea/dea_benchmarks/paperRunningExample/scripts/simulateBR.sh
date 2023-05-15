#!/bin/bash

#parameters
top="adder_tb"
traceLength=1000

#inputs from DEA
faultList=$1
outputDir=$2
mode=$3
threadID=$4

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

#simulate to get the metric value (Err)
$MODELSIM_BIN/vlog -work "work$threadID" +define+OUT_PATH=""$work"/" $compDefine -sv "$BENCHMARK_ROOT/paperRunningExample/rtl/br/*" "$BENCHMARK_ROOT/paperRunningExample/rtl/tb/*"
$MODELSIM_BIN/vsim -L $work "$work.$top" -c -voptargs="+acc" -do "run -all; quit"


if [[ $mode == "1" ]]; then

    if [[ $faultList == "golden" ]]; then
        #no metric value is generated if we are simulating the golden
        cp "$work/output.csv" "sum/golden.csv"
    else
        #get the metric value by comparing the output
        retErr=$("$BENCHMARK_ROOT/paperRunningExample/scripts/getError/getError.x" "$BENCHMARK_ROOT/paperRunningExample/sum/golden.csv" "$work/output.csv" "0")
        #put the metric value where dea expects it
        echo "$retErr" > "$outputDir/$threadID.txt"
    fi
else
    #simply store the trace
    cp "$work/trace.csv" "$outputDir/$faultList.csv"
fi

#clean
rm -rf "$work"


