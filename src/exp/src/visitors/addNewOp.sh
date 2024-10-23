#!/bin/bash

# Function to append text to the second-to-last line of a file
append_to_second_to_last_line() {
  local file="$1"
  local text="$2"
  local nRows=$(wc -l < "$file")

  # Check if the file exists
  if [ ! -e "$file" ]; then
    echo "Error: File '$file' does not exist."
    return 1
  fi

  # Check if the system is macOS
  if [ "$(uname)" == "Darwin" ]; then
    gsed -i "${nRows}i\\${toInsert}" "$file"
  else
    sed -i "${nRows}i\\${toInsert}" "$file"
  fi

  echo "Text appended to the second-to-last line of '$file'."
}

ope=$1

files=(ExpVisitor.cc CopyVisitor.cc PrinterVisitor.cc)

for i in "${files[@]}"
do
  #retrieve name without .cc suffix
  class=${i%.cc}
  echo "Processing $i file..."
  toInsert="void ${class}::visit($ope &o) {\n \t messageError(\"${class}::visit($ope &o) not implemented\"); \n }"
  append_to_second_to_last_line "$i" "$toInsert"
done

