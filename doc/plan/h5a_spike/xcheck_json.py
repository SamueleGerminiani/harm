"""Signal-level cross-check from yosys' JSON netlist: bit-level backward reachability through cells,
all aliases of a net bit are names of it. Struct fields: bit ranges from the struct layout (given)."""
import json, subprocess, sys
from pathlib import Path
Y = "yosys"  # needs read_slang: yosys >= 0.67 (e.g. OSS CAD Suite)
fx = Path(sys.argv[1]); edges_file = sys.argv[2]
FIELDS = {"structs": {"c": {"mode": (3, 4), "val": (0, 2)}}}   # packed struct layout, MSB first
meta, edges, targets = {}, {}, set()
for line in Path(edges_file).read_text().splitlines():
    line = line.split("#")[0].strip()
    if "<-" in line:
        t, rest = [x.strip() for x in line.split("<-")]; edges.setdefault(t, set()).add(rest.split("@")[0].strip()); targets.add(t)
    elif line.startswith("target "): targets.add(line.split()[1])
    elif "=" in line:
        k, v = [x.strip() for x in line.split("=", 1)]; meta[k] = v
top, rec, clk = meta["top"], int(meta["vcd_recursion"]), meta["clock"]
files = " ".join(str(p) for p in sorted((fx / "rtl").glob("*.sv")))
subprocess.run([Y, "-q", "-p", f"read_slang --top {top} {files}; proc; flatten; write_json nl_{top}.json"], check=True, capture_output=True)
m = json.load(open(f"nl_{top}.json"))["modules"][top]
names = {}                                   # bit -> {visible HARM name}
for n, w in m["netnames"].items():
    if n.startswith("$"): continue
    base = n.replace(".", "::")
    for i, b in enumerate(w["bits"]):
        if isinstance(b, str): continue
        nm = base
        for fname, (lo, hi) in FIELDS.get(top, {}).get(n, {}).items():
            if lo <= i <= hi: nm = f"{base}::{fname}"
        if nm.count("::") <= rec and nm != clk:
            names.setdefault(b, set()).add(nm)
drv = {}                                     # bit -> input bits of its driving cell
for c in m["cells"].values():
    ins = [b for p, bs in c["connections"].items() if c["port_directions"][p] == "input" and p not in ("CLK", "C") for b in bs if not isinstance(b, str)]
    for p, bs in c["connections"].items():
        if c["port_directions"][p] == "output":
            for b in bs: drv.setdefault(b, set()).update(ins)
tbits = {}
for b, ns in names.items():
    for n in ns: tbits.setdefault(n, set()).add(b)
def closure(t):
    seen, st = set(), list(edges.get(t, ()))
    while st:
        s = st.pop()
        if s not in seen: seen.add(s); st += edges.get(s, ())
    return seen
ok = True
for t in sorted(targets):
    if t not in tbits: print(f"  {t}: no net (parameter)"); continue
    seen, st = set(), [x for b in tbits[t] for x in drv.get(b, ())]
    while st:
        b = st.pop()
        if b in seen: continue
        seen.add(b); st += drv.get(b, ())
    ys = {n for b in seen for n in names.get(b, ())} - {t}
    mine = closure(t) - {t}
    if ys != mine:
        ok = False; print(f"  {t}: yosys-only {sorted(ys - mine)}  pyslang-only {sorted(mine - ys)}")
print("AGREE" if ok else "DIFFER")
