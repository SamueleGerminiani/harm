"""H45-mutant-eval (amendment): Verilator code coverage of a design under its testbench, over a set of seeds.

Plain Verilator coverage (`--coverage`): line, toggle, branch (and expression) points of the design only, i.e. of the
instances under `scope` (the testbench's own points are not counted). A point is hit when some seed's run hits it.
"""

from __future__ import annotations

import subprocess
from pathlib import Path

import traces

KINDS = {"v_line": "line", "v_toggle": "toggle", "v_branch": "branch", "v_expr": "expr"}


def points(dat: Path) -> dict[str, tuple[dict[str, str], int]]:
    """A coverage.dat file: key -> (fields, count)."""
    out = {}
    for line in Path(dat).read_text(encoding="latin-1").splitlines():
        if not line.startswith("C '"):
            continue
        key, cnt = line[3:].rsplit("' ", 1)
        fields = dict(x.split("\x02", 1) for x in key.split("\x01")[1:])
        out[key] = (fields, int(cnt))
    return out


def measure(files: list[Path], tb: Path, scope: str, builddir: Path, seeds: list[int], cycles: int,
            plusargs: list[str] = (), extra: list[str] = ()) -> dict:
    """{"line": (hit, total), "toggle": ..., "branch": ..., "expr": ..., "files": [...]} for the design under scope."""
    exe = traces.build([*files, tb], "tb", builddir, [*extra, "--coverage"])
    merged: dict[str, tuple[dict[str, str], int]] = {}
    for s in seeds:
        dat = builddir / f"cov_s{s}.dat"
        r = subprocess.run([str(exe), f"+seed={s}", f"+cycles={cycles}", f"+vcd={builddir / f'cov_s{s}.vcd'}",
                            f"+verilator+coverage+file+{dat}", *plusargs], capture_output=True, text=True,
                           cwd=builddir)
        if r.returncode != 0 or not dat.exists():
            raise RuntimeError(f"coverage run failed: {(r.stdout + r.stderr)[-1500:]}")
        (builddir / f"cov_s{s}.vcd").unlink(missing_ok=True)
        for k, (f, c) in points(dat).items():
            merged[k] = (f, max(c, merged.get(k, (f, 0))[1]))
    res: dict = {v: [0, 0] for v in KINDS.values()}
    names = set()
    for f, c in merged.values():
        h = f.get("h", "")
        kind = KINDS.get(f.get("page", "").split("/")[0])
        if kind is None or not (h == scope or h.startswith(scope + ".")):
            continue
        res[kind][1] += 1
        res[kind][0] += c > 0
        names.add(f.get("f", ""))
    out = {k: tuple(v) for k, v in res.items()}
    out["files"] = sorted(names)
    return out
