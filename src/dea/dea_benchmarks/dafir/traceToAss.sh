#!/bin/bash

# Check if the input file is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <filename.csv>"
  exit 1
fi

input_file="$1"

# Read the CSV file into an array, skipping the header row
mapfile -t lines < <(tail -n +2 "$input_file")

# Loop through each line and generate the required string
for ((i = 0; i < ${#lines[@]} - 17; i++)); do
  # Split each line into `in` and `out` based on comma delimiter
  in_value=$(echo "${lines[i]}" | cut -d',' -f1)
  out_future=$(echo "${lines[i + 17]}" | cut -d',' -f2)

  # Generate the string for each `in` value
  echo "G(in==$in_value -> Xout==$out_future)"
done

