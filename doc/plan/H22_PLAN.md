# H22 plan: HARM's hints from the RTL (`harm-coi --hints`)

*Status: approved by the user (2026-10-11, Q1–Q5 as recommended). Branch `ms/H22-coi-hints` from `dev` @ `0663902`. Asked by the user from the miner portfolio's P1 pilot: "can we start by generating hints for harm using the coi? Then we will decide if it worth merging with LLM hints". Effort: about 3 d (harm-coi 2 d; the portfolio's switch and the measurement 1 d). The portfolio's full P1 runs wait for it.*

## Why
In trivergence, HARM's hints (propositions, templates, signal roles) come from an LLM reading the spec (trivergence `docs/PROJECT_OVERVIEW.md` §3.1). Without a spec (the miner portfolio, GoldMine-style use), harm-coi gives today:
- **propositions:** the RTL's predicates (D-023), each allowed everywhere (`loc="a, c, dt"`);
- **one template for every target:** `G({..#1&..}|-> P0)`, `dtLimits="5D,3W,15A,-0.1E,U"`;
- **the cone**, in rank or filter mode (H5–H8).

The P1 pilot (portfolio `doc/plan/VALIDATION.md`, P1a) shows HARM's precision depends on these: on sha3 the first round's precision falls from 45% (cone filter) to 21% (no cone). H22 derives the other two kinds of hint, **signal roles** and **templates**, from the RTL, in the same form an LLM would give them, so the two sources can later be compared and merged.

**Ground rule (the user, from the pilot discussion):** the hints use the RTL's **roles and timing shape** only, never *which* signal may explain which. A bug that cuts or adds a connection then cannot hide an assertion, as the cone filter can (portfolio P1: 7 of 50 measurable mutants change input-to-output connectivity). Every rule below is fixed in this plan, before any measurement; none is tuned on AssertLLM2 designs.

## What `--hints FILE` writes (`hints` v1, a new versioned contract, D-036)
1. **Roles**, per visible signal, from `coi.json` and the elaborated top:
   - `input`: a top input port (not the clock), and its depth-0 copies (as the portfolio's `runner/structure.py` defines them);
   - `reset`: the reset input (harm-coi's asynchronous-control detection, or `--reset NAME`);
   - `state`: a register (a source of itself at depth 1, or every source at depth ≥ 1);
   - `comb`: every other driven signal (a source at depth 0);
   - plus the flag `control`: the signal appears in a harvested condition or case label (D-023 kinds *Condition*, *Case label*).
2. **Proposition placement**, per predicate: antecedent and decision tree always (`a, dt`); **consequent (`c`) only if one of its signals is not an `input` or `reset`**. An assertion whose consequent constrains only inputs fails any formal check unless it is a tautology (inputs are free), so it can only cost a proof.
3. **Templates per timing class** of the consequent's signals:
   - `comb` targets: `G({..#1&..}|-> P0(k_comb))` (the consequent may follow the antecedent's last cycle combinationally, as today);
   - `state` targets: `G({..#1&..}|=> P0(k_state))` (a register shows its inputs one cycle later);
   - `dtLimits` unchanged (`5D,3W,15A,-0.1E,U`), the same for both classes (Q2).
   A predicate over signals of both classes gets both domains.
4. **Provenance:** every hint has `origin: "rtl"` and the rule that produced it, so a merge with LLM hints (`origin: "llm"`) can keep both.

`--emit-config` with `--hints` writes the config from the hints file: the predicates with their placement and class domains, the two templates. **Without `--hints`, harm-coi's output is byte-identical** (rule 5).

## Decisions to approve
| | Question | Options | Recommended |
|---|---|---|---|
| Q1 | Which hints | (a) roles, placement and per-class templates (b) roles and placement only (the safe part: no input consequents) | **(a)**: the templates are the hint the pilot points at; (b) is measured as well (Q4), at no extra cost |
| Q2 | Template limits per class | (a) unchanged for both classes; only the implication differs (b) the depth `D` from each class's cone depths | **(a)**: one knob fewer; (b) is a rule I would have to choose, and the pilot is too small to choose it on |
| Q3 | Format | (a) a separate `hints.json` (schema `doc/schemas/hints.v1.json`), read by `--emit-config` (b) only inside the emitted XML | **(a)**: a file the LLM side can also write; the merge is then a union of two files |
| Q4 | Measurement (reported, not acceptance) | (a) the portfolio's HARM, `--hints none | placement | all`, on the 8 RTL fixtures and the two pilot designs (sha3, ima_adpcm_decoder), in `filter` and `io`, 2 rounds as the pilot (about 1.5 h) (b) the whole corpus (about 6 h) | **(a)**: the decision is whether H22 is worth keeping; P1's full runs then cover the corpus |
| Q5 | Where | (a) harm-coi, in HARM (this plan; branch pushed to `origin` as every HARM milestone, rule 0.3) (b) the portfolio only | **(a)**: hints are HARM's input, and trivergence uses harm-coi |

## Tests (written first, committed failing)
| # | Test | Oracle |
|---|---|---|
| B1 | Roles on the H4 fixtures (`tests/input/coi/*`: counter, fsm, arbiter, multipath, structs, hier; `h5/constructs`) | hand-written expected roles, one file per fixture |
| B2 | Placement and classes on the same fixtures: no consequent domain on an input-only predicate; the class of each target | hand-written |
| B3 | `hints.json` validates against `hints.v1.json`; `--emit-config` without `--hints` byte-identical to `dev` on every fixture | jsonschema; diff |
| B4 | An independent recomputation of roles and classes from `coi.json` alone (`tests/coi/hints_oracle.py`, written without reading harm-coi's code) agrees on the fixtures and on every corpus design's `coi.json` (20 designs) | the script |
| B5 | The emitted configuration parses and mines on every fixture (`ctest -L coi`); the H0 regression baselines byte-identical (HARM itself unchanged) | ctest |
| B6 | Portfolio: `portfolio refine --miner harm --hints {none,placement,all}`; the hint mode is in the record and in each candidate's provenance; the default (`none`) gives the configuration of today, byte for byte | pytest, diff |

## Documents
DECISIONS D-036 (the `hints` v1 contract, Q1–Q5); harm-coi README (`--hints`, roles, placement, classes); VALIDATION (B1–B6, and the measurement table); PLAN status; TRIVERGENCE_IMPACT (an RTL source for the three kinds of hint the LLM writes, in a file it can merge with); portfolio `PLAN.md` and `P1_PLAN.md` (H22 before the full runs).

## Not in scope
- Merging with LLM hints: decided after the measurement (the user).
- Ordering candidates by cone score (discussed in the pilot): a separate decision.
- Any change to HARM's miner (C++): H22 changes only what harm-coi writes.
- Hints for satminer or GoldMine: satminer reads HARM's proposition table (the placement applies to it only if Q4 shows it helps; a later choice).
