# HARM evaluation (HARM v3-131-g917e103 (dirty))

Manifest: `eval/manifests/examples.json`. Configurations: see `eval/run_eval.py`.

| design | config | assertions | wall_s | dropped | permutations | dt_pairs | coi_frac | coi_depth_fit | coverage |
|---|---|---|---|---|---|---|---|---|---|
| vendingMachine | C0 | 2 | 0.19 |  |  |  |  |  |  |
| vendingMachine | C1 | 2 | 0.19 | 0 |  |  |  |  |  |
| vendingMachine | C2 | 2 | 0.19 | 0 |  |  |  |  |  |
| fsmSVT | C0 | 10 | 0.96 |  |  |  |  |  |  |
| fsmSVT | C1 | 10 | 1.04 | 0 |  |  |  |  |  |
| fsmSVT | C2 | 10 | 1.07 | 0 |  |  |  |  |  |
| multiTrace | C0 | 1 | 0.07 |  |  |  |  |  |  |
| multiTrace | C1 | 1 | 0.07 | 0 |  |  |  |  |  |
| multiTrace | C2 | 1 | 0.07 | 0 |  |  |  |  |  |
| nonBoolDT | C0 | 1 | 0.11 |  |  |  |  |  |  |
| nonBoolDT | C1 | 1 | 0.11 | 0 |  |  |  |  |  |
| nonBoolDT | C2 | 1 | 0.13 | 0 |  |  |  |  |  |
| simpleNonBoolDT | C0 | 1 | 0.07 |  |  |  |  |  |  |
| simpleNonBoolDT | C1 | 1 | 0.07 | 0 |  |  |  |  |  |
| simpleNonBoolDT | C2 | 1 | 0.07 | 0 |  |  |  |  |  |
| paperRE | C0 | 13 | 0.16 |  |  |  |  |  |  |
| paperRE | C1 | 13 | 0.18 | 0 |  |  |  |  |  |
| paperRE | C2 | 13 | 0.17 | 0 |  |  |  |  |  |
| ex3 | C0 | 1 | 0.07 |  |  |  |  |  |  |
| ex3 | C1 | 1 | 0.06 | 0 |  |  |  |  |  |
| ex3 | C2 | 1 | 0.09 | 0 |  |  |  |  |  |
| faultCov | C0 | 1 | 0.07 |  |  |  |  |  | 16.6667 |
| faultCov | C1 | 1 | 0.07 | 0 |  |  |  |  | 16.6667 |
| faultCov | C2 | 1 | 0.07 | 0 |  |  |  |  | 16.6667 |
| csvCheck | C0 | 0 | 0.07 |  |  |  |  |  |  |
| csvCheck | C1 | 0 | 0.07 |  |  |  |  |  |  |
| csvCheck | C2 | 0 | 0.06 |  |  |  |  |  |  |
| sub_platform1k | C0 | 91 | 2.99 |  |  |  |  |  |  |
| sub_platform1k | C1 | 89 | 4.77 | 4 |  |  |  |  |  |
| sub_platform1k | C2 | 69 | 9.41 | 215 |  |  |  |  |  |
| bl_master1h | C0 | 23 | 0.4 |  |  |  |  |  |  |
| bl_master1h | C1 | 23 | 0.46 | 0 |  |  |  |  |  |
| bl_master1h | C2 | 23 | 0.5 | 0 |  |  |  |  |  |
| bl_master1k | C0 | 4 | 2.7 |  |  |  |  |  |  |
| bl_master1k | C1 | 4 | 2.77 | 0 |  |  |  |  |  |
| bl_master1k | C2 | 4 | 2.81 | 0 |  |  |  |  |  |
| sobel | C0 | 30 | 16.05 |  |  |  |  |  | 100 |
| sobel | C1 | 17 | 16.25 | 10 |  |  |  |  | 100 |
| sobel | C2 | 9 | 15.78 | 18 |  |  |  |  | 100 |
| process | C0 | 138 | 0.09 |  |  |  |  |  |  |
| process | C1 | 135 | 0.11 | 3 |  |  |  |  |  |
| process | C2 | 135 | 0.11 | 3 |  |  |  |  |  |
| edit | C0 | 3 | 0.11 |  |  |  |  |  |  |
| edit | C1 | 3 | 0.12 | 0 |  |  |  |  |  |
| edit | C2 | 3 | 0.12 | 0 |  |  |  |  |  |
| svaFunctions | C0 | 112 | 0.18 |  |  |  |  |  |  |
| svaFunctions | C1 | 112 | 2.64 | 0 |  |  |  |  |  |
| svaFunctions | C2 | 112 | 2.98 | 0 |  |  |  |  |  |
| process_trace_end_sva | C0 | 76 | 0.09 |  |  |  |  |  |  |
| process_trace_end_sva | C1 | 73 | 0.12 | 3 |  |  |  |  |  |
| process_trace_end_sva | C2 | 73 | 0.12 | 3 |  |  |  |  |  |
