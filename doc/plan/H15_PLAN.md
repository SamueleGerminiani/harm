# H15 plan: the proposition table (`--dump-prop-table`), for the miner portfolio's SAT miner

*Status: planned 2026-10-08, awaiting approval of this plan (the milestone itself was approved 2026-10-08). Branch: `ms/H15-prop-table` (rebased on `dev` @ `b8fb8dd`, with H16). Effort: 2–3 d, plus a full `ctest`.*

## What the SAT miner needs
`~/miner-portfolio` S1 mines `antecedent |-> ##d c` over **windows** of cycles. From HARM it needs, for every proposition of a context and every sampled cycle, the value HARM's evaluator gives, plus where each input trace (and each reset segment) begins and ends, so that no window spans two traces. It then needs neither a VCD reader nor a proposition evaluator, and inherits D-011 (x/z), D-028 (vector indices) and HARM's sampling.

## Facts that shape the design (read in the code)
- **Traces:** several input files are concatenated into one trace; `Trace::getCuts()` holds the last cycle of each sub-trace, and `--reset` adds a cut after each reset interval (`TraceReader.cc`). The trace keeps no file names, and a file that reads as empty (a VCD without a rising clock edge) is skipped silently, so file *i* is not always sub-trace *i*.
- **Sampling:** a VCD is sampled at each rising edge of `--clk`, with the values just before the edge (the Preponed view, D-005). A CSV row is a cycle.
- **Values:** a proposition evaluates to `bool` only. x/z follow D-011: a condition is true only on a known 1. (`--sv-xsemantics` does not exist; D-024 withdrew it.)
- **Which propositions a context has:**
  - `<prop>` elements: one proposition each, in the domains of its `loc`.
  - `<numeric>` with plain domains (`loc="a, c, dt"` or a domain id): expanded **when the configuration is loaded**, by clustering over the whole trace, into ordinary propositions (`cnt >= 3 && cnt <= 7`, …). Deterministic (fixed seeds). D-022: they get no `origin`.
  - `<numeric>` with **bracketed** domains (`[dt]`, `[n]`): never expanded at load time. The decision tree clusters them during mining, per template, permutation, tree depth and partial tree. These propositions are transient and are not one set per context.
  - Propositions written inline in templates belong to no domain.
- **Where:** all of a context's domain propositions exist right after `mineContexts` (`Miner.cc`), before any mining. The table is written there, read-only.

## The format: `prop-table` v1 (D-031)
One JSON file:
```json
{
  "format": "prop-table", "version": "1", "harm": "<git describe>",
  "sampling": {"input": "vcd", "clock": "clk", "edge": "posedge", "values": "preponed"},
  "length": 404,
  "traces":   [{"file": "<path as given>", "first": 0, "last": 201}, {"file": "...", "first": 202, "last": 403}],
  "segments": [[0, 1], [2, 201], [202, 203], [204, 403]],
  "contexts": [{
    "name": "default",
    "propositions": [
      {"id": 0, "text": "en", "domains": ["a", "dt"], "source": "prop", "origin": "rtl", "values": "0110…"},
      {"id": 1, "text": "cnt >= 3 && cnt <= 7", "domains": ["a"], "source": "numeric", "numeric": "cnt", "origin": null, "values": "…"}
    ],
    "unexpanded_numerics": [{"text": "cnt", "domains": ["dt"]}]
  }]
}
```
- `values` holds one character per cycle of the whole trace (`length` characters, `0` or `1`); `traces` and `segments` give the cycle ranges, inclusive. `sampling` is `{"input": "csv"}` for CSV.
- `text` is HARM's Spot-LTL printing of the proposition (`prop2String`), the same text as in `--dump-assertion-info`.
- **Deduplication:** a proposition is listed once per context, by text, with the union of its domains. The same text twice (two `<prop>`, or a `<prop>` and a numeric's expansion) has the same values by construction; the first source wins, and its origin, if any.
- Order: `<prop>`s in configuration order, then each numeric's expansion in configuration order.
- `traces` needs a small change in `TraceReader`: remember the names of the files that were actually read, in order (no change to what is read).

## Choices for you
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Bracketed numerics (`[dt]`) | (a) listed in `unexpanded_numerics` only, not in the table. A configuration that wants their propositions in the table writes them with a plain domain (`loc="dt"`), which HARM expands over the whole trace. (b) expand them for the table only, as `loc="dt"` would; mining unchanged. The table then has propositions mining never uses | **(a)** (the table equals what HARM mines from) |
| Q2 | After writing the table | (a) HARM continues as usual (`--dump-prop-table` adds a file, nothing else changes). For the table alone, a context without templates runs in a moment (checked: exit 0, a warning). (b) HARM exits after the table, like `--dump-trace-as-csv` | **(a)** |
| Q3 | Body | (a) `values` strings in the JSON (1 byte per cycle and proposition: 50 MB for 500 propositions × 100k cycles). (b) a JSON header plus a binary or bit-packed body | **(a)** for v1; a packed body can be v2 if sizes call for it |

## Tests (written first, committed failing)
Fixtures in `tests/input/h15/`; checker `tests/regression/check_prop_table.py`; ctests `h15_prop_table_*` (label `regression`).

| # | Test | Oracle |
|---|---|---|
| A1 | **x/z, CSV:** the 23 propositions of `tests/input/h1b/x_values.xml`: every cell of the table equals (i) `--check-dump-eval`'s `Ant` column for `G(p -> k)`, generated by the checker for every listed `text` (H16's index maps each back), and (ii) the HARM column written by hand in `check_x_semantics.py` | HARM's check mode; hand values |
| A2 | **VCD, sampling, two traces, reset:** `tests/input/coi/counter/trace.vcd` copied twice into a directory read with `--vcd-dir` (`--vcd` takes one file; the checker follows the order the table records), `--clk clk`, `--reset rst`, a config with `<prop>`s (one with `origin="rtl"`), `<numeric exp="cnt" loc="a"/>` and `<numeric exp="cnt" loc="[dt]"/>`. Every cell equals `--check-dump-eval`; and every cell of the `<prop>`s and of the numeric expansions equals a **Python VCD reader written for the test** (its own parser, sampling the values before each rising edge of `clk`, evaluating `rst`, `en`, `wrap` and the expansions' ranges on `cnt`): it shares no code with HARM's VCD reader or evaluator | check mode; independent VCD reader |
| A3 | **Header:** `format`, `version`, `length`; `traces` (the two files, `[0, n-1]`, `[n, 2n-1]`); `segments` equal the reset intervals the Python reader finds; `sampling`; per proposition `text`, `domains`, `source`, `numeric`, `origin` as hand-written in the checker; a duplicated `<prop>` listed once with both domains; the `[dt]` numeric in `unexpanded_numerics` only | hand-written |
| A4 | **Behaviour unchanged:** on the A2 configuration with templates, HARM's stdout with and without `--dump-prop-table` is identical (after removing the timing line); the H0 baselines byte-identical | diff |
| A5 | Full `ctest` on the Mac (background, ~32 min); `h14_doc_coverage` passes with the new option in the README, the release notes and the report (its A4 rule) | ctest |

## Documents
- `doc/plan/DECISIONS.md` **D-031** (the format v1 and the choices above); README (the option and the format), release notes, the report (`--dump-prop-table` in the reference and a paragraph), `doc/plan/VALIDATION.md`, `doc/plan/PLAN.md` status.
- `doc/plan/TRIVERGENCE_IMPACT.md`: an H15 entry (trivergence could read propositions and values the same way; no change it needs).
- The portfolio's own plan and status (`~/miner-portfolio`) are not edited from this milestone.

## Not in scope, recorded
- **`--vcd-dir`/`--csv-dir` order:** the files are taken in `directory_iterator` order, which is unspecified, so the merged trace's cycle numbering can differ between machines (the faulty-trace lists are sorted; these are not). The table records the order used, so it stays self-consistent. Sorting them would change HARM's behaviour: a separate decision.
- A float `<numeric>`'s excluded values are compared against the cycle index instead of the value (`Clustering.cc`, `gatherElements`; found by reading, not reproduced).
- The propositions inside templates, and the decision tree's transient numeric propositions (Q1).
