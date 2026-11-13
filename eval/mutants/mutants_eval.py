"""H45-mutant-eval driver (doc/plan/H45_PLAN.md): mutation score of HARM's configurations on a corpus of designs.

Per design: sample the mutants (mutate.py), simulate golden (seed 1: mining; seed 2: the false-positive check) and
every mutant (seed 2) with Verilator, classify activation (traces.py), then run each configuration of run_eval.py
(H44's C0, R, R+F, R+F+X, RR, RR+F+X) on the seed-1 trace with --fd over golden seed 2 and the activated mutants,
--find-min-subset, and score it (score.py).

Corpus (JSON list; paths relative to the corpus file's folder): {"name", "top", "files": [...], "tb": path,
"clk", "cycles", "defines": [...], "includes": [...]}; the testbench instantiates the design as tb.dut.

Usage: mutants_eval.py <corpus.json> <out-dir> --harm H --python PY [--configs ...] [--designs ...]
                       [--mutants 100] [--seed 1] [--jobs 4] [--threads 3] [--timeout 600]
"""

from __future__ import annotations

import argparse
import csv
import json
import random
import shutil
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent))
import mutate  # noqa: E402
import run_eval  # noqa: E402
import score  # noqa: E402
import traces  # noqa: E402

CONFIGS = ["C0", "R", "R+F", "R+F+X", "RR", "RR+F+X"]
configs_for = run_eval.configs_for
COLUMNS = ["design", "config", "assertions", "wall_s", "ok", "false_positives", "mutants", "activated",
           "not_activated", "killed", "score", "activated_output", "killed_output", "by_op", "error"]


def outputs_of(files, top, defines, includes) -> set[str]:
    _, inst, _ = mutate.elaborate(top, [str(f) for f in files], defines, includes)
    return {p.name for p in inst.body.portList if getattr(p, "direction", None) == mutate.ast.ArgumentDirection.Out}


def prepare(d: dict, base: Path, work: Path, n: int, seed: int, jobs: int) -> dict:
    """Mutants, traces and activation of one design; reused if work/prepared.json exists."""
    done = work / "prepared.json"
    if done.exists():
        return json.loads(done.read_text())
    if work.exists():
        shutil.rmtree(work)
    work.mkdir(parents=True)
    files = [base / f for f in d["files"]]
    tb = base / d["tb"]
    defs, incs = d.get("defines", []), [str(base / i) for i in d.get("includes", [])]
    extra = [f"+define+{x}" for x in defs] + [f"-I{i}" for i in incs]
    cycles = d.get("cycles", 5000)
    gold = traces.build(files + [tb], "tb", work / "build" / "golden", extra)
    g1 = traces.run(gold, 1, cycles, work / "golden1.vcd")
    faults = work / "faults"
    g2 = traces.run(gold, 2, cycles, faults / "golden2.vcd")
    outs = outputs_of(files, d["top"], defs, incs)
    all_sites = mutate.sites(files, d["top"], defs, incs)
    chosen = mutate.sample(all_sites, n, seed)
    taken = {s.id for s in chosen}
    rng = random.Random(seed)
    spare: dict[str, list] = {}
    for g in mutate.PROPORTIONS:  # replacements for mutants that do not compile: the same group, seeded order
        rest = [s for s in all_sites if mutate.GROUP[s.op] == g and s.id not in taken]
        rng.shuffle(rest)
        spare[g] = rest

    def one(s):
        src = mutate.apply(s, files, work / "src" / s.id)
        try:
            exe = traces.build(src + [tb], "tb", work / "build" / s.id, extra)
        except RuntimeError:
            return s, None
        vcd = traces.run(exe, 2, cycles, work / "mutants" / f"{s.id}.vcd")
        shutil.rmtree(work / "build" / s.id, ignore_errors=True)
        return s, traces.activation(g2, vcd, "tb.dut", d["clk"], outs)

    results: dict[str, tuple[str, str]] = {}
    uncompiled: list[str] = []
    queue = list(chosen)
    with ThreadPoolExecutor(jobs) as ex:
        while queue:
            nxt = []
            for s, act in ex.map(one, queue):
                if act is None:
                    uncompiled.append(s.id)
                    if spare[mutate.GROUP[s.op]]:
                        nxt.append(spare[mutate.GROUP[s.op]].pop(0))
                else:
                    results[s.id] = (act, s.op)
            queue = nxt
    for sid, (act, _) in results.items():  # HARM reads every file of --fd: keep only the activated mutants
        if act != "none":
            shutil.copy(work / "mutants" / f"{sid}.vcd", faults / f"{sid}.vcd")
    prep = {"sites": len(all_sites), "outputs": sorted(outs), "golden1": str(g1), "faults": str(faults),
            "golden2": str(g2), "mutants": {str(faults / f"{sid}.vcd"): list(v) for sid, v in sorted(results.items())},
            "uncompiled": sorted(uncompiled)}
    done.write_text(json.dumps(prep, indent=1))
    return prep


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("corpus", type=Path)
    ap.add_argument("out", type=Path)
    ap.add_argument("--harm", required=True)
    ap.add_argument("--python", required=True, help="a Python with harm-coi's dependencies (pyslang)")
    ap.add_argument("--configs", default=",".join(CONFIGS))
    ap.add_argument("--designs")
    ap.add_argument("--mutants", type=int, default=100)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--jobs", type=int, default=4, help="parallel Verilator builds")
    ap.add_argument("--threads", type=int, default=3, help="HARM's --max-threads")
    ap.add_argument("--timeout", type=int, default=600)
    a = ap.parse_args()
    run_eval.THREADS = a.threads
    corpus = json.loads(a.corpus.read_text())
    base = a.corpus.resolve().parent
    if a.designs:
        corpus = [d for d in corpus if d["name"] in a.designs.split(",")]
    rows = []
    a.out.mkdir(parents=True, exist_ok=True)
    for d in corpus:
        work = (a.out / d["name"]).resolve()
        try:
            prep = prepare(d, base, work, a.mutants, a.seed, a.jobs)
        except Exception as e:  # a design that does not build or elaborate: reported, the others go on
            msg = " ".join(str(e).split())[:300]
            rows.append({"design": d["name"], "config": "-", "ok": False, "error": f"prepare: {msg}"})
            print(f"{d['name']:22} prepare failed: {msg}", flush=True)
            continue
        entry = {"name": d["name"], "trace": {"vcd": prep["golden1"], "clk": d["clk"], "scope": "tb::dut",
                                              "recursion": 16},
                 "rtl": {"files": [str(base / f) for f in d["files"]], "top": d["top"],
                         "defines": d.get("defines", []), "includes": [str(base / i) for i in d.get("includes", [])]}}
        hd = work / "harm"
        hd.mkdir(exist_ok=True)
        base_args, cfg = configs_for(entry, a.harm, a.python, str(hd))
        mutants = {k: tuple(v) for k, v in prep["mutants"].items()}
        for name in a.configs.split(","):
            if name not in cfg:
                continue
            xml, extra = cfg[name]
            conf = hd / f"{name}.xml"
            conf.write_text(xml)
            args = base_args + ["--conf", str(conf)] + extra + ["--fd", prep["faults"], "--find-min-subset"]
            r = run_eval.run_harm(a.harm, args, str(hd), a.timeout)
            row = {"design": d["name"], "config": name, "assertions": r.get("assertions", ""), "wall_s": r["wall_s"],
                   "ok": r["ok"], "mutants": len(mutants), "error": r.get("error", "")}
            if r["ok"]:
                s = score.score(hd / "info.json", prep["golden2"], mutants)
                row.update({k: s[k] for k in COLUMNS if k in s})
                row["by_op"] = json.dumps(s["by_op"], sort_keys=True)
                row["score"] = round(s["score"], 3) if s["score"] is not None else ""
            rows.append(row)
            print(f"{d['name']:22} {name:7} {row['assertions']!s:>6} assertions {row['wall_s']:>7}s "
                  f"killed {row.get('killed', '-')}/{row.get('activated', '-')} fp {row.get('false_positives', '-')}"
                  + ("" if r["ok"] else f"  {row['error']}"), flush=True)
    with open(a.out / "results.csv", "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=COLUMNS, extrasaction="ignore")
        w.writeheader()
        w.writerows(rows)
    print(f"written {a.out / 'results.csv'} ({len(rows)} runs)")


if __name__ == "__main__":
    main()
