"""H45-mutant-eval: simulation with Verilator and the activation check (doc/plan/H45_PLAN.md).

The testbench takes +seed=, +cycles= and +vcd=. A mutant is activated when some signal of the design differs from the
golden run at some rising edge of the clock (same stimulus); "output" if a top-level output differs, else "internal".
"""

from __future__ import annotations

import os
import subprocess
from pathlib import Path

WATCHDOG_MARGIN = 10000  # corpus/tb_common.svh stops a run after +cycles plus this many cycles (H45 amendment, T12)
RUN_TIMEOUT_S = 600  # the wall-clock backstop of one simulation


class SimTimeout(RuntimeError):
    """A simulation that did not end within its wall-clock limit (prepare() sets such a mutant aside as hung)."""


VERILATOR_ARGS = ["--binary", "--timing", "--trace", "-Wno-fatal", "-Wno-lint", "-Wno-style", "-O0"]


def build(files: list[Path], top: str, builddir: Path, extra: list[str] = ()) -> Path:
    builddir.mkdir(parents=True, exist_ok=True)
    exe = builddir / f"V{top}"
    r = subprocess.run([os.environ.get("VERILATOR", "verilator"), *VERILATOR_ARGS, *extra, "--top-module", top,
                        "-Mdir", str(builddir), *map(str, files)], capture_output=True, text=True)
    if r.returncode != 0 or not exe.exists():
        raise RuntimeError(f"verilator failed for {top}: {(r.stdout + r.stderr)[-1500:]}")
    return exe


def run(exe: Path, seed: int, cycles: int, vcd: Path, timeout_s: float = RUN_TIMEOUT_S, plusargs=()) -> Path:
    """plusargs: more of the testbench's plusargs (e.g. +watchdog=, HL1 RQ3 amendment)."""
    vcd.parent.mkdir(parents=True, exist_ok=True)
    try:
        r = subprocess.run([str(exe), f"+seed={seed}", f"+cycles={cycles}", f"+vcd={vcd}", *plusargs], capture_output=True,
                           text=True, cwd=vcd.parent, timeout=timeout_s)
    except subprocess.TimeoutExpired:
        vcd.unlink(missing_ok=True)
        raise SimTimeout(f"simulation did not end in {timeout_s} s: {exe} +seed={seed}") from None
    if r.returncode != 0 or not vcd.exists():
        raise RuntimeError(f"simulation failed: {(r.stdout + r.stderr)[-1500:]}")
    return vcd


def simulate(files: list[Path], top: str, builddir: Path, seed: int, cycles: int, vcd: Path) -> Path:
    return run(build(files, top, builddir), seed, cycles, vcd)


def sample(vcd: Path, scope: str, clk: str) -> dict[str, list[str]]:
    """Values (binary, MSB first, padded to the width) of every signal under scope (names relative to it, sub-scopes
    as a.b), taken just before each rising edge of scope's clk."""
    want = scope.split(".")
    path: list[str] = []
    ids: dict[str, list[tuple[str, int]]] = {}
    clk_id = None
    lines = iter(Path(vcd).read_text().split("\n"))
    for line in lines:
        tok = line.split()
        if not tok:
            continue
        if tok[0] == "$scope":
            path.append(tok[2])
        elif tok[0] == "$upscope":
            path.pop()
        elif tok[0] == "$var" and path[:len(want)] == want:
            width, code, name = int(tok[2]), tok[3], tok[4]
            rel = ".".join(path[len(want):] + [name])
            ids.setdefault(code, []).append((rel, width))
            if rel == clk:
                clk_id = code
        elif tok[0] == "$enddefinitions":
            break
    if clk_id is None:
        raise ValueError(f"no clock {clk} under {scope} in {vcd}")
    widths = {rel: w for v in ids.values() for rel, w in v}
    cur: dict[str, str] = {rel: "x" * w for rel, w in widths.items()}
    out: dict[str, list[str]] = {rel: [] for rel in widths}
    pending: list[tuple[str, str]] = []

    def flush():
        clk_rise = False
        for code, val in pending:
            for rel, w in ids.get(code, ()):
                v = val[-w:].rjust(w, "0" if val[0] in "01" else val[0])
                if code == clk_id and cur[rel] != "1" and v == "1":
                    clk_rise = True
        if clk_rise:
            for rel in out:
                out[rel].append(cur[rel])
        for code, val in pending:
            for rel, w in ids.get(code, ()):
                cur[rel] = val[-w:].rjust(w, "0" if val[0] in "01" else val[0])
        pending.clear()

    for line in lines:
        if not line or line[0] == "$":
            continue
        if line[0] == "#":
            flush()
        elif line[0] in "bB":
            val, code = line[1:].split()
            pending.append((code, val.lower()))
        elif line[0] in "rR":
            val, code = line[1:].split()
            pending.append((code, val))
        else:
            pending.append((line[1:], line[0].lower()))
    flush()
    return out


def classify(golden: dict[str, list[str]], mutant: dict[str, list[str]], outputs: set[str]) -> str:
    diff = {n for n in golden.keys() & mutant.keys() if golden[n] != mutant[n]}
    if diff & outputs:
        return "output"
    return "internal" if diff else "none"


RANK = {"none": 0, "internal": 1, "output": 2}


def combine(acts: list[str]) -> str:
    """The activation of a mutant over several stimulus seeds: the strongest one."""
    return max(acts, key=RANK.__getitem__, default="none")


def activation(golden_vcd: Path, mutant_vcd: Path, scope: str, clk: str, outputs: set[str]) -> str:
    return classify(sample(golden_vcd, scope, clk), sample(mutant_vcd, scope, clk), outputs)
