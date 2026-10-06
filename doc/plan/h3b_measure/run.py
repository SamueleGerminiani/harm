import json, os, re, subprocess, sys, tempfile
from pathlib import Path
sys.path.insert(0, os.path.dirname(__file__))
from measure import measure
R = Path("/Users/sam/harm"); HARM = str(R / "build/harm")
V = {"EX": str(R / "examples"), "H1": str(R / "tests/input/h1"), "H3": str(R / "tests/input/h3"),
     "COI": str(R / "tests/input/coi"), "H6": str(R / "tests/input/h6"), "CMAKE_SOURCE_DIR": str(R)}
want = sys.argv[1:]
cases = {}
for line in (R / "tests/regression/cases.cmake").read_text().splitlines():
    m = re.match(r"harm_case\((\w+)[^A]*ARGS (.*)\)\s*$", line)
    if m and (not want or m.group(1) in want):
        args = re.sub(r"\$\{(\w+)\}", lambda k: V[k.group(1)], m.group(2)).split()
        args = [a for a in args if a not in ("--keep-vac-ass",)]
        if "--dump-vac-ass" in args:
            i = args.index("--dump-vac-ass"); del args[i:i + 2]
        cases[m.group(1)] = args
for name, args in cases.items():
    out = {}
    for red in ("syntactic", "implies"):
        with tempfile.TemporaryDirectory() as d:
            info = Path(d) / "i.json"
            a = [x for x in args if x != "--reduce"]
            r = subprocess.run([HARM, *a, "--reduce", red, "--max-threads", "8", "--psilent", "--isilent",
                                "--dump-assertion-info", str(info)], cwd=d, capture_output=True, text=True)
            out[red] = json.loads(info.read_text())["assertions"] if info.exists() else None
    if out["implies"] is None:
        print(f"{name:18} (no dump)"); continue
    dropped, ex = measure(out["implies"], None)
    print(f"{name:18} syntactic {len(out['syntactic'] or []):5}  implies {len(out['implies']):5}  "
          f"+atom facts (lower bound) -{len(dropped)}", flush=True)
    for a, b in ex[:2]:
        print(f"      e.g. {a[:110]}\n        => {b[:110]}")
