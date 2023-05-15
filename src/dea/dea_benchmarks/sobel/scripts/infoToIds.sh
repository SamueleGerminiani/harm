#!/bin/bash 
brListFile=$1

#rm info/brIDS.txt

#get list of faults
while IFS=, read -r id size 
do

#remove hidden chars
size=${size//[^[:alnum:]]/}

for ((bit=0;bit<size;bit++)); do
    echo "${id}_${size}_${bit}" >> info/brIDS.txt
done

done < <(tail -n +2 $brListFile)

