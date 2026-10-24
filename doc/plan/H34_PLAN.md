# H34 plan: one HARM name per port-connected net (`harm-coi --aliases`)

*Status: approved 2026-10-24 by trivergence's lead, for the user (the user, 2026-10-24: "Do what trivergence tells you to do"), as part of the miner portfolio's AL1. Owner: the portfolio's Mac session. Branch `ms/H34-aliases` from `dev` @ `7020ab7` (H33 merged). Effort: about half a day, plus a Linux run.*

## Why
A net that crosses a module port is dumped once per scope, and harm-coi names each copy by its own path. HARM then mines the copies' equality (`u_i2cSlave.sdaOut |-> u_i2cSlave.u_serialInterface.sdaOut`, on AssertLLM2's `i2c_slave`) and repeats other assertions once per copy. On `i2c_slave` (harm, trivergence's F7 run), collapsing the prefixes leaves 3,854 of 4,737 distinct texts.

## Change (D-042)
| # | Part |
|---|---|
| A | The front end records an alias edge only when a port connection or `assign a = b` (or `wire a = b`) is the whole signal: the other side is a plain reference to one signal (no select, concatenation, operator, constant or implicit conversion), of an equivalent type; struct leaves pair field by field. The driven side has no other source, and neither side is unknown (inout ports stay unknown) or on the clock's path. The classes are the connected components. Nothing is merged on trace values. |
| B | With `--aliases`, every visible name of a class is replaced by its shallowest visible name (fewest scope levels), ties broken by string order. Predicates, hints, relations and cones then use it, so duplicates collapse; the zero-delay self edge a merge makes is dropped from the cones, and an `assign a = b` gives no relation `a == a`. |
| C | `coi.json` gains `"aliases": {kept: [merged names, sorted]}` (only classes with two or more visible names, only with `--aliases`); `--edges` lists them. Without `--aliases` the output is unchanged (HARM v4's features are opt-in). |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| T1 | `tests/input/h34/aliases`: copies through input ports, output ports and `assign`, a chain of three names; not merged: an operator, a part-select, a constant, a width change, an inout, the clock's copies | the classes, by hand from the RTL |
| T2 | Its configuration names no copy, has no two predicates with one text, no relation `a == a`, and no cone a zero-delay self edge | part B |
| T3 | Without `--aliases`: the copies' names, no `aliases`. The earlier fixtures with `--aliases`: `hier`, `multipath` and `constructs` give their classes (by hand), the others output identical to that without the flag | part C, no other change |
| T5 | Two hash seeds give the same bytes | determinism |
| T6 | ctest and harm-coi's pytest on the Mac and on Linux | no other change |
