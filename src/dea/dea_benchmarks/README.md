# DEA (Design Exploration for Approximate computing) Benchmarks

This repo contains working benchmarks to automatically perform design exploration using the DEA tool.

## Requirements
* Linux
* DEA tool: https://github.com/SamueleGerminiani/harm (DEA is part of HARM)
* Modelsim (vlib,vlog,vsim): https://eda.sw.siemens.com/en-US/ic/modelsim/

## Build

To build DEA, you need to run 

```
make dea
```

inside the HARM repo (harm/build/).

## How to run the experiments

* Initialise the enviroment variables

```
source envSetup.source
```
(you will have to fix the paths according to your system)

* Each benchmark (and technique) has its own script to run DEA.
* The scripts must be run from the root directory of each benchmark. For example, inside dea_benchmarks/sobel/

#### Bit-width reduction
```
bash scripts/runDEA_br.sh
```

#### Statement reduction
```
bash scripts/runDEA_sr.sh
```
