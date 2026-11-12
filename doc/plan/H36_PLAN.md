# H36 plan: mine one clock domain (`harm-coi --cut-domains`)

*Status: part D of the miner portfolio's MC1 (`doc/plan/MC1_PLAN.md` there, approved by the user 2026-10-26, D1: a domain reads no other domain's register). Moved from stage MC1b to MC1a on 2026-10-26, after measuring (below) that "unknown" does not keep another domain out. Owner: the portfolio's Mac session. Branch `ms/H35-clock-domains` (with H35). Effort: about half a day.*

## Why
With `--clock X`, a register on another clock is `unknown`, and HARM treats unknown signals as in every cone (D-017, D-019: a cone may be too large, never too small). So its propositions are mined on X's ticks. On `tests/input/mc/two_counters` (clk_a, clk_b) mined on clk_a, `harm` gave `cnt_b == 4'b1111 ##3 cnt_a == 4'b1111 |=> cnt_a == 4'b1111` and `... ##1 en_a |-> cnt_b == 4'b0`: assertions over two clocks, true only for the trace's clock ratio. The other clock, `clk_b`, was a target. Every arm of the portfolio did the same (MC1a T2: 14 of 14 runs).

## Change (D-044)
| # | Part |
|---|---|
| A | `--cut-domains` (with the sampling clock, `--clock` or inferred): every signal of another domain is cut. That is the other domains' registers (H35's map), the other clock roots and their paths, the top inputs read only by other domains' registers, and the signals computed only from those, through wires and logic. A cut signal is no visible name: no target, no source, no predicate, no hint and no relation. |
| B | The cones stop at a cut signal; it makes nothing unknown. A domain's register fed by another domain (a synchronizer's first stage, an asynchronous FIFO's read data) is mined from its own domain's sources. |
| C | `coi.json` gains `"cut": [names]` (the visible names cut, sorted; only when not empty). Schema updated. |
| D | Without the flag the output is unchanged; on a single-clock design the flag changes nothing. Docs: D-044, README, the report. |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `two_counters` on clk_a: `cut` is exactly clk_b's domain (`clk_b`, `cnt_b`, `wrap_b`, `en_b`, `rst_b`); no target, source, unknown, proposition or hint names one; `cnt_a`, `wrap_a`, `neg_a` are targets and nothing is unknown | parts A-C |
| T2 | `cdc_fifo` on rclk (with `--aliases`): the write side is cut (its registers, `wclk`, `winc`, `wdata`, `wrst_n`, `wbin_next`, `wq2_rptr`, the synchronizer's input `u_w2r::d`); the read side is not, and its registers, the synchronizer `u_w2r::q1`/`q` included, are targets (today all unknown) | parts A, B |
| T3 | Without the flag: today's output (`cnt_b`, `wrap_b` unknown, no `cut`). The 7 single-clock fixtures: identical bytes with and without the flag | part D |
| T4 | Two hash seeds give the same bytes | determinism |
| T5 | ctest and harm-coi's pytest on the Mac and on Linux | no other change |
