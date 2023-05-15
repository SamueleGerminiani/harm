  
  
  

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


We report below the minimum input required to run DEA

Usage:
 evaluator [--vcd --clk <string> | --csv]
 --ass-file <ASSERTIONS FILE>
 --at-list <AT FILE>
 --bash <BASH SCRIPT>
 --fd <FAULTY TRACES DIRECTORY>
 --dump-to <DEA OUTPUT DIRECTORY>




	

