# HARM v4 on AssertLLM2 (H44-eval-v4)

HARM v4 (`41d5e96`) on `eval/manifests/assertllm2.json`: the 10 designs, golden traces and 5 single-bug mutants of H11; timeout 600 s, 3 threads per run, 3 runs at a time on the Mac (10 cores). uart_to_bus RR and RR+F+X ran on v4 plus this milestone's parser fix (they failed on the release; see `doc/plan/H44_PLAN.md`, Deviation). Timings are wall clock and only comparable within this table.

Configurations (all from `harm-coi --emit-config`): **R** RTL predicates, cones rank (= H11's C6); **R+F** cones filter at exact depth; **R+F+X** plus `--reduce implies --atom-premises` (= H11's C7); **RR** R plus the relations from the RTL (`--hints`); **RR+F+X** RR filtered and reduced. **C0** is HARM's `--generate-config` template without the RTL.

## Findings

1. **The RTL is still what makes HARM run here.** C0 times out on all 10 designs, as in H11. With the RTL, 9 of 10 complete well inside 600 s. aes_cipher times out in every configuration.
2. **v4 reproduces H11.** R+F+X gives H11's C7 counts exactly on the 8 designs where both ran, with the same coverage. uart_to_bus, which timed out under C7, now completes (8,837 assertions in 124 s). R gives 0-6% fewer assertions than C6 (v3-154 to v4 changes), with the same coverage on every design.
3. **The cone filter makes most of the cut, and causes the coverage loss.** R to R+F cuts 1.5-19x. R+F to R+F+X (the reduction) cuts at most 1.8x (ima_adpcm_encoder) and changes no coverage figure. The two coverage drops of H11's C7 (ethernet_smii_txrx and gaussian_noise_generator, 60% to 40%) already happen at R+F, so they come from the filter.
4. **The relations from the RTL add mutant kills.** RR kills more mutants than R on 7 of the 9 designs that run (+20 to +40 points; ethernet_smii_txrx, ima_adpcm_encoder and ima_adpcm_decoder reach 5 of 5). On uart_to_bus and video_stream_scaler it is unchanged. The cost is 1.2-12x more assertions. RR+F+X keeps RR's coverage on 6 of those 7 (gaussian_noise_generator drops from 80% to 60%) with 2-11x fewer assertions than RR.
5. **One parser bug found and fixed** (uart_to_bus RR and RR+F+X failed on the release; see the plan's Deviation).

Limits: 5 mutants per design (coverage moves in steps of 20 points); one golden trace per design; the Mac only.

## Assertions / wall time / mutants killed (of 5, as %)

| Design | C0 | R | R+F | R+F+X | RR | RR+F+X |
|---|---|---|---|---|---|---|
| aes_cipher | timeout | timeout | timeout | timeout | timeout | timeout |
| uart | timeout | 1,162 / 7 s / 60% | 461 / 3 s / 60% | 410 / 3 s / 60% | 3,946 / 26 s / 80% | 1,127 / 9 s / 80% |
| srdy-drdy-library | timeout | 479 / 4 s / 60% | 316 / 4 s / 60% | 277 / 4 s / 60% | 5,630 / 50 s / 80% | 2,550 / 33 s / 80% |
| sha3 | timeout | 1,496 / 19 s / 60% | 402 / 9 s / 60% | 398 / 9 s / 60% | 6,110 / 40 s / 80% | 2,290 / 25 s / 80% |
| uart_to_bus | timeout | 32,612 / 152 s / 60% | 12,649 / 56 s / 60% | 8,837 / 124 s / 60% | 67,714 / 299 s / 60% | 17,741 / 212 s / 60% |
| ethernet_smii_txrx | timeout | 326 / 13 s / 60% | 86 / 3 s / 40% | 84 / 4 s / 40% | 821 / 25 s / 100% | 324 / 16 s / 100% |
| ima_adpcm_encoder | timeout | 3,259 / 46 s / 80% | 1,440 / 22 s / 80% | 809 / 58 s / 80% | 4,026 / 38 s / 100% | 2,004 / 93 s / 100% |
| ima_adpcm_decoder | timeout | 2,636 / 91 s / 60% | 799 / 37 s / 60% | 790 / 81 s / 60% | 4,603 / 99 s / 100% | 1,397 / 183 s / 100% |
| gaussian_noise_generator | timeout | 17,014 / 305 s / 60% | 904 / 11 s / 40% | 902 / 22 s / 40% | 32,993 / 388 s / 80% | 2,978 / 196 s / 60% |
| video_stream_scaler | timeout | 12,759 / 82 s / 20% | 4,589 / 30 s / 20% | 3,327 / 36 s / 20% | 18,135 / 124 s / 20% | 5,769 / 70 s / 20% |

## Against H11 (HARM v3-154, October)

| Design | H11 C6 | v4 R | H11 C7 | v4 R+F+X |
|---|---|---|---|---|
| aes_cipher | timeout | timeout | timeout | timeout |
| uart | 1,209 / 12 s / 60% | 1,162 / 7 s / 60% | 410 / 6 s / 60% | 410 / 3 s / 60% |
| srdy-drdy-library | 507 / 6 s / 60% | 479 / 4 s / 60% | 277 / 7 s / 60% | 277 / 4 s / 60% |
| sha3 | 1,547 / 24 s / 60% | 1,496 / 19 s / 60% | 398 / 13 s / 60% | 398 / 9 s / 60% |
| uart_to_bus | 34,466 / 278 s / 60% | 32,612 / 152 s / 60% | timeout | 8,837 / 124 s / 60% |
| ethernet_smii_txrx | 344 / 10 s / 60% | 326 / 13 s / 60% | 84 / 4 s / 40% | 84 / 4 s / 40% |
| ima_adpcm_encoder | 3,259 / 57 s / 80% | 3,259 / 46 s / 80% | 809 / 169 s / 80% | 809 / 58 s / 80% |
| ima_adpcm_decoder | 2,670 / 71 s / 60% | 2,636 / 91 s / 60% | 790 / 132 s / 60% | 790 / 81 s / 60% |
| gaussian_noise_generator | 17,096 / 273 s / 60% | 17,014 / 305 s / 60% | 902 / 86 s / 40% | 902 / 22 s / 40% |
| video_stream_scaler | 13,392 / 157 s / 20% | 12,759 / 82 s / 20% | 3,327 / 154 s / 20% | 3,327 / 36 s / 20% |

H11's timings were taken with a different thread count and load; compare counts and coverage, not times.

## Full rows

`results.csv` (all columns: dropped by the reduction, permutations and decision-tree pairs before->after the filter, coiFrac, coiDepthFit, errors). The per-batch outputs are in `part1..3` (C0), `rtl1..3` and `rtlfix`.

