# HARM evaluation (HARM v4)

Manifest: `eval/manifests/assertllm2.json`. Configurations: see `eval/run_eval.py`.

| design | config | assertions | wall_s | dropped | permutations | dt_pairs | coi_frac | coi_depth_fit | coverage |
|---|---|---|---|---|---|---|---|---|---|
| uart_to_bus | R | 32612 | 151.65 |  |  |  | 0.602 | 0.388 | 60 |
| uart_to_bus | R+F | 12649 | 55.56 |  | 141->141 | 50314->30605 | 1.0 | 1.0 | 60 |
| uart_to_bus | R+F+X | 8837 | 123.74 | 3812 | 141->141 | 50314->30605 | 1.0 | 1.0 | 60 |
| uart_to_bus | RR | 0 | 73.38 |  |  |  |  |  |  |
| uart_to_bus | RR+F+X | 0 | 165.91 | 5222 |  |  |  |  |  |
| ethernet_smii_txrx | R | 326 | 12.77 |  |  |  | 0.483 | 0.465 | 60 |
| ethernet_smii_txrx | R+F | 86 | 3.08 |  | 27->27 | 13379->9989 | 1.0 | 1.0 | 40 |
| ethernet_smii_txrx | R+F+X | 84 | 3.68 | 2 | 27->27 | 13379->9989 | 1.0 | 1.0 | 40 |
| ethernet_smii_txrx | RR | 821 | 24.89 |  |  |  | 0.573 | 0.457 | 100 |
| ethernet_smii_txrx | RR+F+X | 324 | 15.57 | 3 | 69->69 | 37771->35922 | 1.0 | 1.0 | 100 |
| ima_adpcm_encoder | R | 3259 | 46.39 |  |  |  | 0.737 | 0.582 | 80 |
| ima_adpcm_encoder | R+F | 1440 | 22.24 |  | 111->111 | 184148->121429 | 1.0 | 1.0 | 80 |
| ima_adpcm_encoder | R+F+X | 809 | 57.77 | 631 | 111->111 | 184148->121429 | 1.0 | 1.0 | 80 |
| ima_adpcm_encoder | RR | 4026 | 38.37 |  |  |  | 0.761 | 0.589 | 100 |
| ima_adpcm_encoder | RR+F+X | 2004 | 92.73 | 72 | 150->150 | 209683->180464 | 1.0 | 1.0 | 100 |
