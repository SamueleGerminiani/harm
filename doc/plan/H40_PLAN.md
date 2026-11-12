# H40 plan: harm-coi's cones in linear time

*Status: part of the miner portfolio's BR1 (`doc/plan/BR1_PLAN.md`, part A: every arm within its budget, approved by the user 2026-10-29). Owner: the portfolio's Mac session. Branch `ms/H40-coi-closure` from `dev` @ `798fe28`. Effort: a day.*

## Why
The portfolio's Daikon and GoldMine adapters run harm-coi's domain map (`--domains --clock C --cut-domains`) before they mine. On AssertLLM2's `pci_bridge` (clock `pci_clk_i`) it takes 308 s of a 340 s domain budget, and Daikon is then left about 1 s. A profile (511 s under cProfile): 474 s in `cone.closure`, nearly all in two generator expressions that, for every source of a target's cone, scan the whole reachable set again (`sorted(d for x, d in reach if x == s ...)` and `any(x == s and d > max_depth ...)`): 2,625,175,093 calls.

## Change
`closure` groups each target's reachable (source, depth) pairs by source once, and builds each source's depths and its `saturated` flag from its own group. The output is unchanged: the same targets, the same sources in the same order, the same depths and flags, the same unknown set.

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `closure` equals the H39 version (kept in the test as the reference) on random graphs (depths, cycles, unknown names, several max depths) and on harm-coi's fixtures | the same output |
| T2 | (measurement) `pci_bridge`'s domain map for `pci_clk_i`: at least 10x faster, the same `domains.json` and `domains_coi.json` | speed, same files |
| T3 | harm-coi's suite and HARM's ctest | no other change |
