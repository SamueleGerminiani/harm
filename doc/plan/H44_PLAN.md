# H44-eval-v4 plan: H11's AssertLLM2 evaluation on v4, with each effect measured apart

*Status: done, signed off by the user 2026-11-13; approved by the user 2026-11-13 ("Approve"). Asked by the user (2026-11-13: "yes, rerun the H11 evaluation on v4"), for a
possible tool paper on HARM v4. Owner: the portfolio's Mac session. Branch `ms/H44-eval-v4` from `dev` (`8cfc422`).*

## Why
H11 (`eval/results/assertllm2/results.md`, HARM v3-154, October) is the only measurement of what the RTL-derived
configuration and the cones do. Three things limit it for a paper:
- C7 = the cone filter **and** `--reduce implies --atom-premises`: its 3-19x fewer assertions mix two effects;
- it predates relations from the RTL (H24-H26), clock domains, aliases, H39's deadline and every CR1 fix;
- C0-C5 (HARM's `--generate-config` template) timed out on every design tried, so only C6/C7 ran.

## The run
`eval/run_eval.py` on `eval/manifests/assertllm2.json` (the same 10 designs, traces and 5 single-bug mutants as H11),
HARM v4 (`41d5e96`, the release; the Mac's `build-mac`), timeout 600 s as in H11. Configurations, all from
`harm-coi --emit-config`:

| Name | Propositions | Cones | Reduction | H11 equivalent |
|---|---|---|---|---|
| R | RTL predicates | rank | syntactic (default) | C6 |
| R+F | RTL predicates | filter, exact depth | syntactic | (new) |
| R+F+X | RTL predicates | filter, exact depth | implies, atom premises | C7 |
| RR | RTL predicates + relations (`--hints`, H24-H26) | rank | syntactic | (new) |
| RR+F+X | RTL predicates + relations | filter, exact depth | implies, atom premises | (new) |

C0 (the template without the RTL) is run once per design as the baseline, to confirm it still times out on v4.
Measured as in H11: assertions, wall time, permutations and decision-tree pairs, `coiFrac`, `coiDepthFit`,
mutation coverage (`--fd`, 5 mutants), errors.

## Change
`run_eval.py`: the five configurations above (named as here; H11's names stay in its old table) and `--configs` to
pick some. No HARM or harm-coi change.

## Tests
`tests/regression` keeps `eval_smoke` (if present) passing; the new configurations are run on one fixture first
(`eval/manifests/fixtures.json`), and their XML checked to differ only as the table says.

## Output
`eval/results/assertllm2-v4/results.md` (and `.csv`), with a comparison to H11's C6/C7 rows; a VALIDATION entry.
Nothing from it goes to trivergence or a paper without the user.

## Cost
On the Mac, 3 designs at a time with 3 threads each: 10 designs x 6 runs, at most 600 s each, so 1-3 hours. The Mac
runs nothing else meanwhile.

## Deviation (2026-11-13): one HARM fix
The run found a parser bug, so the milestone also changes HARM (the plan said no change; for the user at sign-off).
On uart_to_bus, RR and RR+F+X failed: harm-coi's relation
`bin_last_byte == ((bin_byte_count == 8'd1) ? 1'd1 : 1'd0)` mined fine, but the fault-based qualification parses
each printed assertion again, and a proposition inside a template reached the proposition parser as ANTLR's
`getText()`, without its spaces: `c==8'b1?1'b1:1'b0`, where the lexer reads `8'b1?1` as one based literal (`?` is a
z digit). Fix: the template handler parses the proposition's source text (spaces kept); the space-free text stays
the cache key. Test first: `tests/h44Tests.cc` (H44Test, label `parser`). The two uart_to_bus runs were repeated
with the fixed HARM; every other run is the release (`41d5e96`).
