# H9 plan: out-of-cone report

*Status: approved 2026-10-06 (D-022); in progress. Branch: `ms/H9-coi-report` (from `dev` @ H8). Effort: 1 d.*

## Goal
`--dump-coi-report <file.json>` writes, for each context with a `<coi>`, which antecedent propositions are structurally unable to influence each consequent proposition.
- **Why:** a spec-derived proposition (e.g. `origin="spec"`) outside the cone is trivergence's "spec says A influences B, RTL says it cannot" disagreement (B4 triage, TRIVERGENCE_IMPACT §2).
- **Opt-in, report only:** mining, ranking and filtering are unchanged, whatever the `<coi>` mode. Without the option nothing changes.
- **No mining needed:** the report is computed from the configuration and `coi.json` alone, when the context is loaded.

**Example** (H7's `multipath` configuration, where every proposition can be antecedent and consequent). The cone of `y` is `{a, r1, r2}`.

| Consequent | Antecedents in the cone | Out of the cone (reported) |
|---|---|---|
| `y` | `a`, `r1`, `r2` | `b`, `z`, `rb`, `a && b` (because of `b`), `r1 \|\| rb` (because of `rb`) |

## Decisions to approve
### D-022: what the report pairs
- **Per consequent proposition, not per signal.** The PLAN says "for each target". In a configuration, the unit trivergence reasons about is a proposition with an `origin`, and a consequent proposition can have several signals. The rule is D-017's, exactly the one filter mode prunes with:
  - an antecedent proposition is out of the cone if some variable of it is not a source of any variable of the consequent;
  - the report lists those variables (`outside`).
- **Which propositions are paired:**
  - consequents: propositions in the global `c` domain;
  - antecedents: propositions and numerics in every other domain (`a`, `dt`, local domains);
  - a proposition is not paired with itself.
- **Unknown, never "out":** an antecedent with a variable `coi.json` does not know, or a consequent whose cone is unknown, goes to an `unknown` list for that consequent, not to `outOfCone` (D-017).
- **Signal level only:** no depths in H9. Depths are a possible extension: "in the cone, but not at the delay the spec states".

### Format (`coi-report` v1)
```json
{"version": "1",
 "contexts": [{"name": "default", "coi": "<path>",
   "consequents": [{"text": "y", "origin": "spec", "variables": ["y"], "coneUnknown": false,
     "outOfCone": [{"text": "a && b", "origin": null, "numeric": false,
                    "variables": ["a", "b"], "outside": ["b"]}],
     "unknown": [{"text": "...", "origin": null, "variables": ["..."], "unknownVariables": ["..."]}]}]}]}
```
- Sorted by text, so the output is deterministic.
- `origin` is `null` when not given.
- A context without `<coi>` is listed with `"coi": null` and no consequents, and HARM prints a note.

## Acceptance tests (written first)
| # | Test | Kind |
|---|---|---|
| A1 | **Hand-written expected reports** for `multipath` (H7's configuration, with `origin` added to two propositions) and `structs` (scoped names, `--vcd-r 1`): the full JSON, compared after parsing | regression (python) |
| A2 | **Unknown signals:** a configuration on H5's `constructs` with a proposition on `unnamedblk1::i` (unknown in its `coi.json`), and one on a signal that `coi.json` does not list. Hand-written expected `unknown` entries, which must not appear in `outOfCone` | regression |
| A3 | **Cross-check on every H7/H8 configuration** (5 fixtures + `constructs`): the report equals the pairs computed by a separate Python script from `coi.json` (the cone rule of `restrict_config.py`, written for H7) | regression (python) |
| A4 | **No effect on mining:** with and without `--dump-coi-report`, output identical (`regression` cases re-run with the option on `multipath` rank and filter); without `<coi>` the file has the context with `"coi": null` | regression |

## Validation (independent)
- A1/A2: the lists are written by hand from the fixtures' cones, which were validated by simulation in H4 and H5.
- A3: a separate implementation of the rule, in Python.
- **Mutation test of A1–A3:**
  - "any variable" instead of "every variable";
  - unknown counted as out;
  - pairing a proposition with itself;
  - origins dropped.

## Out of scope
- Depth disagreements (see D-022).
- Ranking or filtering on the report.
- Reporting mined assertions: the report is about the configuration's propositions, before mining.

## Files
- **Modified:** `commandLineParser.cc`, `globals.*` (the option), `ManualDefinition.cc` or a new `CoiReport.cc` (the report, using `CoiInfo::inCone`), README, `doc/plan/*`.
- **New:** `tests/coi/check_coi_report.py`, `tests/input/h9/*` (configurations and expected reports).
