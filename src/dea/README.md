  
  
  

## DEA

The official repo of the DEA (Design Exploration for AxC) tool


## Table of contents

[Project info](#project-info)

[Quick start](#quick-start)
1. [Build the project](#build-the-project)

[How to use the miner](#how-to-use-the-miner)

[Optional arguments](#optional-arguments)

## Project info

This tool proposes an automated approach for guiding AxC design exploration. The methodology considers two main approximation techniques, i.e., bit-width reduction and statement reduction, and it employs fault injection to mimic their effect on the design under approximation. 
To guide the designer while assessing the different approximation choices, assertions, which formally capture the behaviours implemented in the design, are dynamically generated from the RTL simulation traces. Then, the impact of fault injections on the truth values of the mined assertions is employed as a proxy for measuring the functional accuracy of the corresponding approximations.
Based on this evaluation, a genetic algorithm is finally used to rank and cluster the approximation targets, thus providing the designer with an efficient and effective way to automatically analyse AxC variants in terms of the trade-off between accuracy and performance.

# Quick start

For now, we support only Linux with gcc (c++17) and cmake 3.14+.

## Dependencies
The same dependencies of HARM

## Build the project

* You must build DEA in "harm/build"

```
cmake -DCMAKE_BUILD_TYPE=Release -DDEA=1 ..
```

```
make dea
```

# How to use DEA


## Minimum input

We report below the minimum input required to run DEA.

dea [--vcd --clk "clk_signal" | --csv] --ass-file "assertions_file.txt" --at-list "listOfAT.txt" --bash "simulateDesign.sh" --fd "traces/" --dump-to "dea_output/"

* \-\-vcd is the type of the generated faulty traces (vcd), "clk signal" is the clock signal to sample time in the vcd trace; csv traces are also supported
* "assertions_file.txt" contains the assertions in HARM format (one per line)
* "listOfAT.txt" contains a list of IDs corresponding to approximation tokens (one per line)
* "simulateDesign.sh" is a bash script capable of simulating the design and generating the faulty traces
* "traces/" is a path to a directory where DEA expects to find the faulty traces
* "dea_output" is a path to a directory where DEA will dump its output


## The input script

DEA requires as input a bash script (--bash option) to simulate the target design.
DEA does not care how the user implements the script as long as the following requirements are satisfied.

The scripts receives four inputs (in this order): 
1. FaultList: a string representing a list of IDs of the form "ID1;ID2;...;IDN" where each IDi is a line of the file provided with the --at-list option
2. Out: a string representing the path to the directory provided with the --dump-to option
3. Mode: a binary value (0 or 1)
4. ThreadID: an ID value used for multi-threading

When executed, the script must behave as follows:
* If Mode is 0, then the script simulates the design with the ONLY fault contained in FaultList and dumps the simulation trace in the Out directory; the trace file name must follow the format "IDi.vcd" (fault id followed by .vcd) for vcd traces, "IDi.csv" (fault id followed by .csv) for csv traces.
```
Example
simulateDesign.sh "s0" "traces/" 0 0
OUTPUT: traces/s0.vcd
```

* If Mode is 1, then the script simulates the design with the list of faults contained in FaultList and dumps the value of the user-defined metric in the Out directory, the file containing the value must follow the format "ThreadID.txt"
```
Example
simulateDesign.sh "s0" "traces/" 1 0
OUTPUT: traces/0.txt, 0.txt contains a float in the range 0-1
```
* If FaultList is equal to "golden" than, the script simulates the design and dumps the golden simulation trace in the Out directory (golden.vcd or golden.csv)
```
Example 1
simulateDesign.sh "s0" "traces/" 0 0
OUTPUT: traces/golden.vcd
```
```
Example 2
simulateDesign.sh "s0" "traces/" 1 0
OUTPUT: No output expected by DEA
````

* WARNING: the ThreadID input should always be set to 0 if the script does not support multi-threading! Use the --max-threads option to set the number of available threads.
* DEA will not use the script to generate the faulty traces (and the golden trace) if their are already present in the Out directory.




	

