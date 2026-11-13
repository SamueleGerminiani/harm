# HARM evaluation (HARM v4-19-g9818e10 (dirty))

Manifest: `eval/manifests/assertllm2.json`. Configurations: see `eval/run_eval.py`.

| design | config | assertions | wall_s | dropped | permutations | dt_pairs | coi_frac | coi_depth_fit | coverage |
|---|---|---|---|---|---|---|---|---|---|
| uart_to_bus | RR | 67714 | 298.92 |  |  |  | 0.573 | 0.339 | 60 |
| uart_to_bus | RR+F+X | 17741 | 211.69 | 5222 | 281->281 | 126991->73748 | 1.0 | 1.0 | 60 |
