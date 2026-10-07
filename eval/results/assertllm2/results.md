# HARM evaluation (HARM v3-154-gc1735ca)

Manifest: `eval/manifests/assertllm2.json`. Configurations: see `eval/run_eval.py`. Linux, `--timeout 600` (10 min, the user's choice; the default is 30 min).

Only C6/C7 ran on every design (the user's choice): with HARM's `--generate-config` template, C0 timed out on every design tried. The C0-C5 rows are those timeouts, taken from the run logs. `ethernet_smii_txrx` is not in the table: HARM rejects its trace (finding F-L4). Coverage is the % of the 5 AssertLLM2 single-bug mutants detected (`--fd`). The runs were split into 4 parallel `run_eval.py` processes (8 threads each).

| design | config | assertions | wall_s | dropped | permutations | dt_pairs | coi_frac | coi_depth_fit | coverage | error |
|---|---|---|---|---|---|---|---|---|---|---|
| aes_cipher | C0 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| aes_cipher | C1 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| aes_cipher | C2 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| aes_cipher | C3 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| aes_cipher | C4 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| aes_cipher | C6 |  | 600 |  |  |  |  |  |  | timeout (600 s) |
| aes_cipher | C7 |  | 600 |  |  |  |  |  |  | timeout (600 s) |
| uart | C0 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| uart | C6 | 1209 | 12.15 |  |  |  | 0.51 | 0.421 | 60 |  |
| uart | C7 | 410 | 5.98 | 51 | 23->23 | 7683->5604 | 1.0 | 1.0 | 60 |  |
| uart_to_bus | C6 | 34466 | 277.55 |  |  |  | 0.574 | 0.375 | 60 |  |
| uart_to_bus | C7 |  | 600 |  |  |  |  |  |  | timeout (600 s) |
| srdy-drdy-library | C6 | 507 | 5.92 |  |  |  | 0.811 | 0.591 | 60 |  |
| srdy-drdy-library | C7 | 277 | 6.77 | 39 | 19->19 | 12104->9582 | 1.0 | 1.0 | 60 |  |
| ima_adpcm_encoder | C6 | 3259 | 57.06 |  |  |  | 0.737 | 0.582 | 80 |  |
| ima_adpcm_encoder | C7 | 809 | 169.38 | 631 | 111->111 | 184148->121429 | 1.0 | 1.0 | 80 |  |
| ima_adpcm_decoder | C6 | 2670 | 70.93 |  |  |  | 0.551 | 0.386 | 60 |  |
| ima_adpcm_decoder | C7 | 790 | 131.92 | 9 | 110->110 | 488253->350870 | 1.0 | 1.0 | 60 |  |
| sha3 | C0 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| sha3 | C6 | 0 | 0.8 |  |  |  |  |  |  | Message: Constant ''d0' is wider than 511 bits |
| sha3 | C7 | 0 | 0.8 |  |  |  |  |  |  | Message: Constant ''d0' is wider than 511 bits |
| gaussian_noise_generator | C6 | 17096 | 272.77 |  |  |  | 0.195 | 0.089 | 60 |  |
| gaussian_noise_generator | C7 | 902 | 85.59 | 2 | 313->313 | 124167->27728 | 1.0 | 1.0 | 40 |  |
| video_stream_scaler | C0 |  | 600 |  |  |  |  |  |  | timeout (600 s); from the run log (run stopped before writing its tabl |
| video_stream_scaler | C6 | 13392 | 157.48 |  |  |  | 0.683 | 0.359 | 20 |  |
| video_stream_scaler | C7 | 3327 | 154.44 | 1262 | 69->69 | 52667->23102 | 1.0 | 1.0 | 20 |  |
