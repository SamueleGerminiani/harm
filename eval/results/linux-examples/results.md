# HARM evaluation (HARM v3-154-gc1735ca)

Manifest: `eval/manifests/examples.json`. Configurations: see `eval/run_eval.py`.

| design | config | assertions | wall_s | dropped | permutations | dt_pairs | coi_frac | coi_depth_fit | coverage |
|---|---|---|---|---|---|---|---|---|---|
| vendingMachine | C0 | 2 | 0.16 |  |  |  |  |  |  |
| vendingMachine | C1 | 2 | 0.2 | 0 |  |  |  |  |  |
| vendingMachine | C2 | 2 | 0.2 | 0 |  |  |  |  |  |
| fsmSVT | C0 | 10 | 1.46 |  |  |  |  |  |  |
| fsmSVT | C1 | 10 | 1.63 | 0 |  |  |  |  |  |
| fsmSVT | C2 | 10 | 1.65 | 0 |  |  |  |  |  |
| multiTrace | C0 | 1 | 0.04 |  |  |  |  |  |  |
| multiTrace | C1 | 1 | 0.05 | 0 |  |  |  |  |  |
| multiTrace | C2 | 1 | 0.05 | 0 |  |  |  |  |  |
| nonBoolDT | C0 | 1 | 0.1 |  |  |  |  |  |  |
| nonBoolDT | C1 | 1 | 0.14 | 0 |  |  |  |  |  |
| nonBoolDT | C2 | 1 | 0.15 | 0 |  |  |  |  |  |
| simpleNonBoolDT | C0 | 1 | 0.04 |  |  |  |  |  |  |
| simpleNonBoolDT | C1 | 1 | 0.05 | 0 |  |  |  |  |  |
| simpleNonBoolDT | C2 | 1 | 0.07 | 0 |  |  |  |  |  |
| paperRE | C0 | 13 | 0.19 |  |  |  |  |  |  |
| paperRE | C1 | 13 | 0.21 | 0 |  |  |  |  |  |
| paperRE | C2 | 13 | 0.22 | 0 |  |  |  |  |  |
| ex3 | C0 | 1 | 0.04 |  |  |  |  |  |  |
| ex3 | C1 | 1 | 0.04 | 0 |  |  |  |  |  |
| ex3 | C2 | 1 | 0.04 | 0 |  |  |  |  |  |
| faultCov | C0 | 1 | 0.04 |  |  |  |  |  | 16.6667 |
| faultCov | C1 | 1 | 0.04 | 0 |  |  |  |  | 16.6667 |
| faultCov | C2 | 1 | 0.04 | 0 |  |  |  |  | 16.6667 |
| csvCheck | C0 | 0 | 0.04 |  |  |  |  |  |  |
| csvCheck | C1 | 0 | 0.04 |  |  |  |  |  |  |
| csvCheck | C2 | 0 | 0.04 |  |  |  |  |  |  |
| sub_platform1k | C0 | 91 | 3.69 |  |  |  |  |  |  |
| sub_platform1k | C1 | 89 | 12.33 | 4 |  |  |  |  |  |
| sub_platform1k | C2 | 69 | 21.57 | 215 |  |  |  |  |  |
| bl_master1h | C0 | 23 | 0.45 |  |  |  |  |  |  |
| bl_master1h | C1 | 23 | 0.66 | 0 |  |  |  |  |  |
| bl_master1h | C2 | 23 | 0.86 | 0 |  |  |  |  |  |
| bl_master1k | C0 | 4 | 3.47 |  |  |  |  |  |  |
| bl_master1k | C1 | 4 | 3.75 | 0 |  |  |  |  |  |
| bl_master1k | C2 | 4 | 4.03 | 0 |  |  |  |  |  |
| sobel | C0 | 30 | 21.97 |  |  |  |  |  | 100 |
| sobel | C1 | 17 | 21.44 | 10 |  |  |  |  | 100 |
| sobel | C2 | 9 | 21.74 | 18 |  |  |  |  | 100 |
| process | C0 | 138 | 0.07 |  |  |  |  |  |  |
| process | C1 | 135 | 0.11 | 3 |  |  |  |  |  |
| process | C2 | 135 | 0.11 | 3 |  |  |  |  |  |
| edit | C0 | 3 | 0.13 |  |  |  |  |  |  |
| edit | C1 | 3 | 0.15 | 0 |  |  |  |  |  |
| edit | C2 | 3 | 0.15 | 0 |  |  |  |  |  |
| svaFunctions | C0 | 112 | 0.16 |  |  |  |  |  |  |
| svaFunctions | C1 | 112 | 6.24 | 0 |  |  |  |  |  |
| svaFunctions | C2 | 112 | 8.67 | 0 |  |  |  |  |  |
| process_trace_end_sva | C0 | 76 | 0.09 |  |  |  |  |  |  |
| process_trace_end_sva | C1 | 73 | 0.12 | 3 |  |  |  |  |  |
| process_trace_end_sva | C2 | 73 | 0.12 | 3 |  |  |  |  |  |
