"""The size of each design in the hint-level study (the letter's Table IV): ports and lines of RTL.

  sizes.py <corpus.json> [--designs a,b,...] [--out sizes.csv]

Per corpus design (eval/mutants/corpus.json; paths relative to its folder), elaborated with eval/mutants' own
elaborate() (pyslang) at the corpus's defines and include directories:
- inputs, outputs: the top's input and output ports, clock and reset included, and their bits;
- loc: the non-blank, non-comment lines of the PULP files the design compiles (submodules included); the corpus's
  wrapper (corpus/*) is excluded;
- files: those files' names."""

from __future__ import annotations

import argparse
import csv
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "mutants"))
import mutate  # noqa: E402

FIELDS = ["design", "top", "inputs", "input_bits", "outputs", "output_bits", "loc", "files"]


def loc(path: Path) -> int:
    """Lines that are neither blank nor comments (// lines and /* */ blocks)."""
    text = re.sub(r"/\*.*?\*/", "", path.read_text(errors="replace"), flags=re.S)
    return sum(1 for line in text.splitlines() if line.strip() and not line.strip().startswith("//"))


def size(entry: dict, base: Path) -> dict:
    files = [base / f for f in entry["files"]]
    _, inst, _ = mutate.elaborate(entry["top"], [str(f) for f in files], entry.get("defines", []),
                                  [str(base / i) for i in entry.get("includes", [])])  # fmt: skip
    row = {"design": entry["name"], "top": entry["top"], "inputs": 0, "input_bits": 0, "outputs": 0, "output_bits": 0}
    for p in inst.body.portList:
        key = "inputs" if p.direction == mutate.ast.ArgumentDirection.In else "outputs"
        row[key] += 1
        row[key[:-1] + "_bits"] += p.type.bitWidth
    rtl = [f for e, f in zip(entry["files"], files) if not e.startswith("corpus/")]
    row["loc"] = sum(loc(f) for f in rtl)
    row["files"] = " ".join(f.name for f in rtl)
    return row


def main(argv: list[str] | None = None) -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("corpus", type=Path)
    ap.add_argument("--designs", help="comma-separated names (default: every corpus design)")
    ap.add_argument("--out", type=Path, default=Path("sizes.csv"))
    a = ap.parse_args(argv)
    corpus = json.loads(a.corpus.read_text())
    keep = set(a.designs.split(",")) if a.designs else None
    rows = [size(e, a.corpus.resolve().parent) for e in corpus if keep is None or e["name"] in keep]
    with open(a.out, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=FIELDS)
        w.writeheader()
        w.writerows(rows)
    for r in rows:
        print(f"{r['design']:24} I/O {r['inputs']}/{r['outputs']} ({r['input_bits']}/{r['output_bits']} bits)  "
              f"LoC {r['loc']}")


if __name__ == "__main__":
    main()
