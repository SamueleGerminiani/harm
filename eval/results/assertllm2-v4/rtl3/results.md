# HARM evaluation (HARM v4)

Manifest: `eval/manifests/assertllm2.json`. Configurations: see `eval/run_eval.py`.

| design | config | assertions | wall_s | dropped | permutations | dt_pairs | coi_frac | coi_depth_fit | coverage |
|---|---|---|---|---|---|---|---|---|---|
| ima_adpcm_decoder | R | 2636 | 91.09 |  |  |  | 0.552 | 0.386 | 60 |
| ima_adpcm_decoder | R+F | 799 | 36.86 |  | 110->110 | 488253->350870 | 1.0 | 1.0 | 60 |
| ima_adpcm_decoder | R+F+X | 790 | 81.42 | 9 | 110->110 | 488253->350870 | 1.0 | 1.0 | 60 |
| ima_adpcm_decoder | RR | 4603 | 98.6 |  |  |  | 0.656 | 0.38 | 100 |
| ima_adpcm_decoder | RR+F+X | 1397 | 182.73 | 34 | 133->133 | 537871->519941 | 1.0 | 1.0 | 100 |
| gaussian_noise_generator | R | 17014 | 305.39 |  |  |  | 0.196 | 0.087 | 60 |
| gaussian_noise_generator | R+F | 904 | 10.56 |  | 313->313 | 130147->28932 | 1.0 | 1.0 | 40 |
| gaussian_noise_generator | R+F+X | 902 | 22.03 | 2 | 313->313 | 130147->28932 | 1.0 | 1.0 | 40 |
| gaussian_noise_generator | RR | 32993 | 388.36 |  |  |  | 0.387 | 0.112 | 80 |
| gaussian_noise_generator | RR+F+X | 2978 | 196.06 | 192 | 372->372 | 143489->34724 | 1.0 | 1.0 | 60 |
| video_stream_scaler | R | 12759 | 81.56 |  |  |  | 0.68 | 0.358 | 20 |
| video_stream_scaler | R+F | 4589 | 29.86 |  | 69->69 | 52667->23102 | 1.0 | 1.0 | 20 |
| video_stream_scaler | R+F+X | 3327 | 35.91 | 1262 | 69->69 | 52667->23102 | 1.0 | 1.0 | 20 |
| video_stream_scaler | RR | 18135 | 123.67 |  |  |  | 0.702 | 0.413 | 20 |
| video_stream_scaler | RR+F+X | 5769 | 70.18 | 1764 | 164->164 | 84483->49478 | 1.0 | 1.0 | 20 |
