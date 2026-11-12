# H37 plan: reset edges in the domain map

*Status: part of the miner portfolio's MC1b (`doc/plan/MC1_PLAN.md`, D2, approved by the user 2026-10-26; "go ahead" 2026-10-27). Owner: the portfolio's Mac session. Branch `ms/H37-reset-edges` from `dev` @ `a2f4986`. Effort: an hour.*

## Why
MC1's D2 takes a domain's reset from H35's map when it finds exactly one. To build that domain's `disable iff`, the portfolio needs the reset's polarity, which the map does not record.

## Change (D-045)
Each domain of `--domains` gains `reset_edges`: `{reset root: [edges]}` for its asynchronous controls, the edge of the event control (`negedge rst_n`: `neg`, active low; `posedge rst`: `pos`, active high). Its keys are the domain's `resets`. Schema `domains.v1.json` updated (a new required property of a clock; the file is H35's, not yet used outside the portfolio).

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/input/mc`'s four fixtures: `reset_edges` as written by hand (two_counters `pos`, cdc_fifo `neg`, synchronous resets none); valid against the schema; keys equal `resets` | the change |
| T2 | H35's tests updated for the new field; ctest and harm-coi's pytest on the Mac and on Linux | no other change |
