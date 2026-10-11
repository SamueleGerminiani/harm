"""H22 (D-036): HARM's hints from the RTL, `hints` v1 (doc/schemas/hints.v1.json).

Only roles and timing shape, never which signal may explain which (a bug that cuts or adds a connection cannot
hide an assertion):
  - roles: `input` (a top input port), `reset` (an input named by --reset, or an asynchronous control of a
    register), `const` (a parameter, or another signal without sources), `clock` (an alias of the clock), `unknown`
    (coi.json's), `comb` (a source at depth 0, resets aside), `state` (every source at depth >= 1); `control` when a
    harvested condition, case label or loop condition reads the signal;
  - placement: a predicate may be a consequent only if it reads a comb, state or unknown signal (a consequent on
    inputs alone fails any formal check unless it is a tautology); its classes are those signals' classes;
  - classes: comb (and unknown) targets get `G({..#1&..}|-> P0(1))`, state targets `G({..#1&..}|=> P0(2))`, with
    the dtLimits of today's template."""

DT_LIMITS = "5D,3W,15A,-0.1E,U"
TEMPLATE = "G({..#1&..}|-> P0)"
CLASSES = {"comb": (1, "G({..#1&..}|-> P0(1))", "comb or unknown targets: the consequent may follow at once"),
           "state": (2, "G({..#1&..}|=> P0(2))", "state targets: a register shows its inputs one cycle later")}
CLASS_OF = {"comb": "comb", "unknown": "comb", "state": "state"}
CONTROL = {"condition", "case label", "loop condition"}


def _role(k, v, unknown, clock, resets, inputs, params):
    if k in unknown:
        return "unknown", "unknown in coi.json"
    if not v["sources"]:
        if k.split("::")[-1] == clock:
            return "clock", "an alias of the clock"
        if k in resets:
            return "reset", "a reset input (--reset or an asynchronous control)"
        if k in inputs:
            return "input", "a top input port"
        return "const", "a parameter" if k in params else "no sources"
    if any(0 in s["depths"] and s["sig"] not in resets for s in v["sources"]):
        return "comb", "a source at depth 0 (resets aside)"
    return "state", "every source at depth >= 1 (resets aside)"


def build(doc, design, vis, extra, resets=()):
    """the hints of a coi.json document (`doc`), from the design's ports, parameters and asynchronous controls and
    the predicates' signals and kinds (`extra`, from predicates.harvest)"""
    names = lambda atoms: {vis[a] for a in atoms if a in vis}  # noqa: E731
    inputs, params = names(design.top_inputs), names(design.params)
    for r in resets:
        if r not in inputs:
            raise ValueError(f"--reset {r}: not a visible top input")
    rs = (set(resets) | names(design.asyncs)) & inputs
    t, unknown = doc["targets"], set(doc["unknown"])
    clock = doc["meta"]["clock"]
    control = {s for e in extra.values() if e["kinds"] & CONTROL for s in e["signals"]}
    roles = {}
    for k in sorted(set(t) | unknown):
        role, rule = _role(k, t.get(k, {"sources": []}), unknown, clock, rs, inputs, params)
        roles[k] = {"role": role, "control": k in control, "origin": "rtl", "rule": rule}
    classes = {c: {"domain": d, "template": tpl, "dtLimits": DT_LIMITS,
                   "targets": sorted(k for k, v in roles.items() if CLASS_OF.get(v["role"]) == c),
                   "origin": "rtl", "rule": rule} for c, (d, tpl, rule) in CLASSES.items()}
    props = []
    for p in doc["predicates"]:
        sig = sorted(extra[p["expr"]]["signals"])
        cls = sorted({CLASS_OF[roles[s]["role"]] for s in sig if roles[s]["role"] in CLASS_OF})
        loc = ["a", "c", "dt"] + sorted(str(CLASSES[c][0]) for c in cls) if cls else ["a", "dt"]
        props.append({"expr": p["expr"], "signals": sig, "consequent": cls, "loc": loc, "origin": "rtl",
                      "rule": "reads a comb, state or unknown signal" if cls else "reads only inputs, resets or constants"})
    meta = {k: doc["meta"][k] for k in ("design", "top", "clock", "generator")}
    return {"version": "1", "meta": {**meta, "reset": sorted(rs)}, "roles": roles, "classes": classes,
            "propositions": props}
