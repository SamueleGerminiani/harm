# H35 plan: the clock-domain map (`harm-coi --domains`)

*Status: approved by the user 2026-10-26, as part A of the miner portfolio's MC1 (`doc/plan/MC1_PLAN.md` there, stage MC1a). Owner: the portfolio's Mac session. Branch `ms/H35-clock-domains` from `dev` @ `0532211` (H34 merged). Effort: about a day, plus a Linux run. Cutting the cones at a domain boundary (MC1's part D) is H36, in stage MC1b.*

## Why
harm-coi samples one clock. With several clocks and no `--clock` it refuses ("several clocks"). With `--clock`, the registers on the other clocks are `unknown`, and so is everything they feed. To mine each domain on its own clock, the portfolio first needs to know the domains: which registers each clock drives, which clocks are derived, where signals cross, which crossings are synchronized, and each domain's resets. 23 of AssertLLM2's 83 designs list more than one clock.

## Change (D-043)
| # | Part |
|---|---|
| A | `--domains FILE` writes a domain map (`domains.v1`). `-o` becomes optional when `--domains` is given; a design with several clocks is then mapped, not refused. With `-o` too, `coi.json` and every other output are unchanged. |
| B | **Domains:** one per clock root, found by following a process's clock back through single-source wires and ports (`clock_root`, as today). Per domain: `edges` (the edges its registers use), `registers` (the targets of its processes), `resets` (the roots of its registers' asynchronous controls). A root driven by logic or by a register is `derived`. `from` lists the domains it is made from: the domain of the register that drives it, or the domains among the roots of its sources. |
| C | **Crossings:** a register of another domain that reaches a domain's register through wires and combinational logic, listed as `{signal, from, to, into}`. |
| D | **Synchronizers:** in a domain, a register whose sources, other than itself and its asynchronous controls, lead only through wires to one foreign register, followed by a register whose only such source is the first (the 2-flop pattern): `{clock, from, first, second}`. |
| E | **`--reset NAME`** (the existing option) adds `reads_resets` per domain: the given resets that the domain's registers read, asynchronously or through their logic. MC1's D2 uses this. |
| F | `unclocked`: the registers of processes whose clock cannot be told from their asynchronous controls (they stay unknown, as today). |
| G | Docs: D-043, README, the report (harm-coi section, options, decisions and milestones), the schema `doc/schemas/domains.v1.json`. |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/input/mc`:<br>`two_counters`: two independent domains, a falling-edge register on `clk_a`, async resets.<br>`cdc_fifo`: an asynchronous FIFO, gray pointers through `sync2` instances, the data crossing unsynchronized.<br>`derived`: a divide-by-2 and a gated clock.<br>`raw_cross`: a single-flop crossing and one through logic.<br>The whole map equals the one written by hand. | parts B-D, F |
| T2 | The 7 single-clock fixtures (`coi/*`, `h5/constructs`): one domain `clk`, no crossing, and `coi.json` byte-identical with and without `--domains` | part A, no other change |
| T3 | `--reset`: `two_counters`, `derived` and `cdc_fifo` give the resets each domain reads | part E |
| T4 | Two hash seeds give the same bytes | determinism |
| T5 | ctest and harm-coi's pytest on the Mac and on Linux | no other change |
