"""The hint-level study's driver: each arm on eval/mutants' prepared designs, scored on their fault traces.

  run_arms.py <corpus.json> <prepared dir> <out> --harm <harm> --python <harm-coi python> --machine <name>
              [--designs a,b] [--arms none,L0,L0+roles,rel,deep] [--repeats deep=3] [--timeout 3600] [--threads 6]
              [--jobs 3]

<prepared dir> holds `mutants_eval.py --configs prepare-only`'s output (<design>/prepared.json). A kill: a candidate
that fails on none of the held-out golden traces (else it is a false positive and kills nothing) fails on one of a
mutant's traces; only activated mutants count. Writes <out>/results.csv: per design, arm and repeat, the status, time,
assertions, false positives, kills (all, on outputs), kills by level (L0, L1, L2), kills only by long-range candidates,
kills per operator, and the killed mutants' ids."""

from __future__ import annotations

import json
import statistics
import sys
from pathlib import Path
from typing import Any

sys.path.insert(0, str(Path(__file__).resolve().parent))
import arms  # noqa: E402

LEVELS = ("L0", "L1", "L2")

def infos_of(work: Path) -> dict[str, list[dict[str, Any]]]:
    """HARM's --dump-assertion-info records of an arm's run, by pass: `full` (work/info.json, or work/full/info.json
    for the deep arm) and `cut`."""
    out = {}
    for name, p in (("full", work / "info.json"), ("full", work / "full" / "info.json"), ("cut", work / "cut" / "info.json")):
        if p.exists():
            out[name] = json.loads(p.read_text()).get("assertions", [])
    return out


def score(cands: list[dict[str, Any]], infos: dict[str, list[dict[str, Any]]], goldens: list[str],
          mutants: dict[str, tuple[str, str, list[str]]]) -> dict[str, Any]:  # fmt: skip
    """Kills of an arm's candidates. infos: HARM's records by pass; goldens: the held-out golden traces; mutants: id
    -> (activation, operator, fault traces), as eval/mutants' prepared.json."""
    faults: dict[tuple[str, str], list[str]] = {}
    for p, recs in infos.items():
        for r in recs:
            if r.get("faultsComplete") is not True:
                raise ValueError("the fault lists are not complete: run HARM with --fd and --find-min-subset")
            faults[(p, r["text"])] = r["faults"]
    gold = set(goldens)
    trace_to_m = {f: m for m, (_, _, fs) in mutants.items() for f in fs}
    act = {m for m, (a, _, _) in mutants.items() if a != "none"}
    per = []  # (level, false positive, mutants killed)
    lr = []  # long-range (RQ3 amendment): per candidate, True when its form is not bounded or it is from the cut pass
    for c in cands:
        pv = c["provenance"]
        fs = set(faults.get((pv.get("pass", "full"), pv["harm_text"]), []))
        fp = bool(fs & gold)
        per.append((pv.get("rtl_level", "L0"), fp, set() if fp else {trace_to_m[f] for f in fs if f in trace_to_m} & act))
        lr.append(pv.get("form", "bounded") != "bounded" or pv.get("pass") == "cut")
    killed = set().union(*[k for _, _, k in per]) if per else set()
    by_level = {}
    for lv in LEVELS:
        mine = [(fp, k) for l, fp, k in per if l == lv]
        lk = set().union(*[k for _, k in mine]) if mine else set()
        others = set().union(*[k for l, _, k in per if l != lv]) if per else set()
        by_level[lv] = {"assertions": len(mine), "false_positives": sum(fp for fp, _ in mine), "killed": len(lk),
                        "killed_only": len(lk - others)}  # fmt: skip
    lk = set().union(*[k for (_, _, k), x in zip(per, lr) if x]) if per else set()
    bk = set().union(*[k for (_, _, k), x in zip(per, lr) if not x]) if per else set()
    long_range = {"assertions": sum(lr), "false_positives": sum(fp for (_, fp, _), x in zip(per, lr) if x),
                  "killed": len(lk), "killed_only": len(lk - bk)}  # fmt: skip
    out_act = {m for m in act if mutants[m][0] == "output"}
    by_op: dict[str, dict[str, int]] = {}
    for m, (a, op, _) in mutants.items():
        d = by_op.setdefault(op, {"activated": 0, "killed": 0})
        if a != "none":
            d["activated"] += 1
            d["killed"] += m in killed
    return {"assertions": len(cands), "false_positives": sum(fp for _, fp, _ in per), "activated": len(act),
            "killed": len(killed), "killed_ids": sorted(killed), "score": len(killed) / len(act) if act else None,
            "activated_output": len(out_act), "killed_output": len(killed & out_act), "by_level": by_level,
            "long_range": long_range, "by_op": by_op}  # fmt: skip


def summarise_repeats(rows: list[dict[str, Any]]) -> dict[tuple[str, str], dict[str, Any]]:
    """Repeated runs of an arm (the deep arm's cut is wall-clock based): (min, median, max) of each number, and the
    machines."""
    groups: dict[tuple[str, str], list[dict[str, Any]]] = {}
    for r in rows:
        groups.setdefault((r["design"], r["arm"]), []).append(r)
    out = {}
    for k, rs in groups.items():
        s: dict[str, Any] = {"repeats": len(rs), "machines": sorted({r["machine"] for r in rs})}
        for f in ("wall_s", "assertions", "killed", "score"):
            v = sorted(r[f] for r in rs)
            s[f] = (v[0], statistics.median(v), v[-1])
        out[k] = s
    return out


def rq3_table(rows: list[dict[str, Any]]) -> dict[str, dict[str, Any]]:
    """RQ3 (amendment 2), per design from results.csv rows: L0+roles (one run) and deep (its repeats: min, median,
    max) kills, the mutants deep kills that L0+roles does not, kills only by long-range assertions, wall time; `gain`
    when every deep repeat kills a mutant that L0+roles does not."""
    def mm(v: list[float]) -> tuple[Any, Any, Any]:
        v = sorted(v)
        return (v[0], statistics.median(v), v[-1])

    out: dict[str, dict[str, Any]] = {}
    for d in sorted({r["design"] for r in rows}):
        base = [r for r in rows if r["design"] == d and r["arm"] == "L0+roles" and r["status"] == "ok"]
        deep = [r for r in rows if r["design"] == d and r["arm"] == "deep" and r["status"] == "ok"]
        if len(base) != 1 or not deep:
            continue
        b = base[0]
        bk = set(json.loads(b["killed_ids"]))
        only = [len(set(json.loads(r["killed_ids"])) - bk) for r in deep]
        out[d] = {"l0roles_killed": int(b["killed"]), "l0roles_wall_s": float(b["wall_s"]),
                  "l0roles_assertions": int(b["assertions"]), "l0roles_fp": int(b["false_positives"]),
                  "activated": int(b["activated"]), "repeats": len(deep),
                  "deep_killed": mm([int(r["killed"]) for r in deep]), "deep_only": mm(only),
                  "long_range_only": mm([json.loads(r["long_range"])["killed_only"] for r in deep]),
                  "deep_wall_s": mm([float(r["wall_s"]) for r in deep]),
                  "deep_assertions": mm([int(r["assertions"]) for r in deep]),
                  "deep_fp": mm([int(r["false_positives"]) for r in deep]), "gain": all(n > 0 for n in only)}
    return out


def main(argv: list[str] | None = None) -> None:
    import argparse
    import csv
    from concurrent.futures import ThreadPoolExecutor

    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("corpus", type=Path, help="eval/mutants/corpus.json")
    ap.add_argument("prepared", type=Path, help="eval/mutants' prepared directory (<design>/prepared.json)")
    ap.add_argument("out", type=Path)
    ap.add_argument("--arms", default=",".join(arms.ARMS))
    ap.add_argument("--designs")
    ap.add_argument("--repeats", default="deep=3", help="arm=n,...")
    ap.add_argument("--timeout", type=float, default=3600)
    ap.add_argument("--threads", type=int, default=6)
    ap.add_argument("--jobs", type=int, default=2, help="runs at once")
    ap.add_argument("--mem-gib", type=float, default=arms.MEM_GIB, help="the none arms' resident memory limit")
    ap.add_argument("--machine", required=True, help="a name for the machine, recorded with each row")
    ap.add_argument("--harm", type=Path, required=True, help="the harm binary")
    ap.add_argument("--python", type=Path, required=True, help="a Python with harm-coi's dependencies (pyslang)")
    a = ap.parse_args(argv)
    machine = a.machine
    tools = arms.Tools(a.harm.resolve(), a.python, Path(__file__).resolve().parents[2])
    base = a.corpus.resolve().parent
    corpus_ = json.loads(a.corpus.read_text())
    if a.designs:
        corpus_ = [d for d in corpus_ if d["name"] in a.designs.split(",")]
    reps = {k: int(v) for k, v in (x.split("=") for x in a.repeats.split(",") if x)}
    jobs = [(d, arm, i) for d in corpus_ for arm in a.arms.split(",") for i in range(reps.get(arm, 1))]

    def one(job):  # type: ignore[no-untyped-def]
        d, arm, i = job
        work = (a.out / d["name"] / arm / f"r{i}").resolve()
        try:  # a design that was not prepared, or one failing run, is reported; the others go on
            prep = json.loads((a.prepared / d["name"] / "prepared.json").read_text())
            entry, traces = arms.entry_for(d, base, prep)
            cands, st = arms.run_arm(arm, entry, traces, work, tools, prep["faults"], timeout_s=a.timeout,
                                     threads=a.threads, mem_gib=a.mem_gib)  # fmt: skip
        except Exception as e:
            cands, st = [], {"status": "error", "wall_s": 0, "error": " ".join(str(e).split())[:300] or type(e).__name__}
        row = {"design": d["name"], "arm": arm, "repeat": i, "machine": machine, **st}
        if st["status"] in ("ok", "timeout") and (infos := infos_of(work)):
            mut = {k: tuple(v) for k, v in prep["mutants"].items()}
            s = score(cands, infos, prep["goldens"], mut)
            row.update({k: v for k, v in s.items() if k not in ("by_level", "long_range", "by_op", "killed_ids")},
                       killed_ids=json.dumps(s["killed_ids"]),
                       by_level=json.dumps(s["by_level"], sort_keys=True), by_op=json.dumps(s["by_op"], sort_keys=True),
                       long_range=json.dumps(s["long_range"], sort_keys=True))
        print(f"{d['name']:22} {arm:9} r{i} {row['status']:8} {row['wall_s']:>8}s "
              f"killed {row.get('killed', '-')}/{row.get('activated', '-')} fp {row.get('false_positives', '-')} "
              f"assertions {row.get('assertions', '-')}", flush=True)
        return row

    a.out.mkdir(parents=True, exist_ok=True)
    with ThreadPoolExecutor(a.jobs) as ex:
        rows = list(ex.map(one, jobs))
    cols = ["design", "arm", "repeat", "machine", "status", "wall_s", "assertions", "false_positives", "activated",
            "killed", "score", "activated_output", "killed_output", "by_level", "long_range", "by_op", "killed_ids",
            *arms.NONE_STATS, "dropped_constant", "error"]
    with open(a.out / "results.csv", "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=cols, extrasaction="ignore")
        w.writeheader()
        w.writerows(rows)
    print(f"written {a.out / 'results.csv'} ({len(rows)} runs)")


if __name__ == "__main__":
    main()
