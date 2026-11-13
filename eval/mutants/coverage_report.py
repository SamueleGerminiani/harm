"""H45-mutant-eval (amendment): the corpus's Verilator coverage (line, toggle, branch, expression) per design, over
the mining seeds. Usage: coverage_report.py <corpus.json> <work dir> [--seeds 1-5] [--designs a,b] [--jobs 4]"""

from __future__ import annotations

import argparse
import json
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import vcov  # noqa: E402
from mutants_eval import seeds_arg  # noqa: E402


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("corpus", type=Path)
    ap.add_argument("work", type=Path)
    ap.add_argument("--seeds", default="1-5")
    ap.add_argument("--designs")
    ap.add_argument("--jobs", type=int, default=4)
    a = ap.parse_args()
    corpus = json.loads(a.corpus.read_text())
    base = a.corpus.resolve().parent
    if a.designs:
        corpus = [d for d in corpus if d["name"] in a.designs.split(",")]

    def one(d):
        extra = [f"+define+{x}" for x in d.get("defines", [])] + [f"-I{base / i}" for i in d.get("includes", [])]
        return d["name"], vcov.measure([base / f for f in d["files"]], base / d["tb"], "tb.dut",
                                       (a.work / d["name"]).resolve(), seeds_arg(a.seeds), d.get("cycles", 5000),
                                       extra=extra)

    rows = {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for name, r in ex.map(one, corpus):
            rows[name] = r
            print(f"{name:22} " + "  ".join(f"{k} {r[k][0]}/{r[k][1]} ({100 * r[k][0] / r[k][1]:.0f}%)" if r[k][1]
                                             else f"{k} -" for k in ("line", "branch", "toggle", "expr")), flush=True)
    (a.work / "coverage.json").write_text(json.dumps(rows, indent=1))


if __name__ == "__main__":
    main()
