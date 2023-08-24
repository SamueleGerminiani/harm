#!/bin/bash

# Check if the correct number of arguments are provided
if [ $# -lt 2 ]; then
    echo "Usage: $0 <input_path> <original_new_pairs>"
    exit 1
fi

input_path="$1"
shift

# Iterate over the provided original-new pairs
while [ $# -gt 0 ]; do
    pair="$1"
    IFS=', ' read -ra values <<< "$pair"
    if [ ${#values[@]} -ne 2 ]; then
        echo "Invalid pair: $pair. Skipping."
        shift
        continue
    fi

    original="${values[0]}"
    new="${values[1]}"
    
    # Find and replace occurrences of original with new in all files within input path
    grep -rl "$original" "$input_path" | xargs sed -i "s/$original/$new/g"

    shift
done

echo "Replacement completed."

