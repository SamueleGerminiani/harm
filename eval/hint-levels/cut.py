"""Idle stretches cut from a trace, for
stutter-invariant templates only.

A cycle is the VCD text from one active clock edge's timestamp up to the next one's. A cycle in which no atom (a
signal the templates read) changes repeats the previous cycle's atom state; of each state, the first `keep` cycles
are kept and the rest dropped, the later timestamps moving back by the time dropped. A signal that is not an atom and
changed in a dropped stretch is written, with its last value, at the next kept cycle's timestamp. With nothing to
drop the output is the input, byte for byte. The cut is recorded beside the output (`<out>.cut.json`).

A property is unchanged by the cut (stutter-invariant) when it never looks forward by an exact number of cycles and
looks back at most one cycle, which keep >= 2 preserves: `stutter_invariant`. A candidate mined on a cut trace is
proved and checked on the real design like any other, so a cut can cost candidates, never give a wrong verdict."""

from __future__ import annotations

import json
import re
from collections.abc import Iterator
from pathlib import Path
from typing import Any

_FORWARD = re.compile(r"##|\|=>|\[\*|\[=|\[->|\bnexttime\b|\bs_nexttime\b|\$past\b|eventually\s*\[|\balways\s*\[")


def stutter_invariant(sva: str) -> bool:
    """`sva` reads a cut trace as it reads the full one: no `##`, `|=>`, repetition, `nexttime`, ranged eventually or
    ranged always (exact forward counts), no `$past` (`$rose`, `$fell`, `$stable`, `$changed` look back one cycle)."""
    return not _FORWARD.search(sva)


def _header(lines: list[str]) -> tuple[int, dict[tuple[str, ...], dict[str, str]]]:
    """(index of the line after $enddefinitions, {scope path: {name: id}})."""
    scopes: dict[tuple[str, ...], dict[str, str]] = {}
    stack: list[str] = []
    for i, ln in enumerate(lines):
        t = ln.split()
        if not t:
            continue
        if t[0] == "$scope":
            stack.append(t[2])
        elif t[0] == "$upscope":
            stack.pop()
        elif t[0] == "$var":
            scopes.setdefault(tuple(stack), {})[t[4]] = t[3]
        elif t[0] == "$enddefinitions":
            return i + 1, scopes
    raise ValueError("no $enddefinitions in the VCD")


def _kinds(lines: list[str]) -> dict[str, str]:
    """each id's VCD kind from the header, "real", "vector" (wider than 1 bit) or "scalar", so a value
    is written back in its own form (`b0 !` for a vector, which Icarus shortens, not `0!`; `r1.5 !` for a real)."""
    out: dict[str, str] = {}
    for ln in lines:
        t = ln.split()
        if t and t[0] == "$var" and len(t) >= 4:
            out[t[3]] = "real" if t[1] in ("real", "realtime") else ("vector" if t[2] != "1" else "scalar")
        elif t and t[0] == "$enddefinitions":
            break
    return out


def _write(i: str, v: str, kind: str | None) -> str:
    """A value-change line for id `i` (value `v` as `_change` reads it)."""
    if kind == "real":
        return f"r{v} {i}\n"
    if kind == "vector" or (kind is None and len(v) != 1):
        return f"b{v} {i}\n"
    return f"{v}{i}\n"


def _id(scopes: dict[tuple[str, ...], dict[str, str]], scope: str, name: str) -> str:
    parts = name.split(".")
    path = tuple(scope.split("::")) + tuple(parts[:-1])
    try:
        return scopes[path][parts[-1]]
    except KeyError:
        raise KeyError(f"{name!r} is not a signal of {scope} in the VCD") from None


def _change(ln: str) -> tuple[str, str] | None:
    """(id, value) of a value-change line, None for anything else."""
    if not ln or ln[0] in "#$":
        return None
    if ln[0] in "bBrR":
        v, i = ln[1:].split()
        return i, v
    return ln[1:].strip(), ln[0]


def _blocks(lines: list[str], start: int) -> Iterator[list[str]]:
    """The VCD body as timestamp blocks: a `#t` line and the lines up to the next one (the first block may have none)."""
    block: list[str] = []
    for ln in lines[start:]:
        if ln.startswith("#") and block:
            yield block
            block = []
        block.append(ln)
    if block:
        yield block


def _rises(block: list[str], clk: str) -> bool:
    return any(c == (clk, "1") for c in map(_change, (x.rstrip("\n") for x in block)))


def sample(vcd: Path, scope: str, clock: str, names: list[str]) -> list[dict[str, Any]]:
    """`names`' values at each rising edge of `clock`, after that timestamp's changes (as the miners sample): an int
    for a binary value, the text otherwise (x, z)."""
    lines = Path(vcd).read_text().splitlines()
    start, scopes = _header(lines)
    clk = _id(scopes, scope, clock)
    ids = {n: _id(scopes, scope, n) for n in names}
    cur: dict[str, str] = {}
    out = []
    for block in _blocks(lines, start):
        rose = False
        for ln in block:
            c = _change(ln)
            if c:
                cur[c[0]] = c[1]
                rose = rose or c == (clk, "1")
        if rose:
            out.append({n: int(cur[i], 2) if re.fullmatch(r"[01]+", cur.get(i, "x")) else cur.get(i, "x")
                        for n, i in ids.items()})  # fmt: skip
    return out


def cut(src: Path, out: Path, scope: str, clock: str, atoms: list[str], keep: int = 2) -> dict[str, Any]:
    """Writes `out`, `src` with each atom state's cycles after the first `keep` dropped; returns (and writes to
    `<out>.cut.json`) {source, atoms, keep, cycles_in, cycles_out, stretches: [{cycle, dropped}]}, `cycle` the first
    dropped cycle's index (0: the first active edge)."""
    if keep < 2:
        raise ValueError("keep must be >= 2: one-cycle look-back ($rose, $stable, ...) needs two copies of a state")
    lines = Path(src).read_text().splitlines(keepends=True)
    start, scopes = _header([x.rstrip("\n") for x in lines])
    kinds = _kinds([x.rstrip("\n") for x in lines[:start]])
    clk = _id(scopes, scope, clock)
    atom_ids = {_id(scopes, scope, a) for a in atoms}
    true: dict[str, str] = {}  # every signal's value in the source
    seen: dict[str, str] = {}  # what a reader of the output has
    res: list[str] = lines[:start]
    cycles, kept, run, offset = 0, 0, 0, 0
    drop_from: int | None = None  # the time the current dropped stretch starts at
    stretches: list[dict[str, int]] = []
    chunk: list[list[str]] = []

    def stamp(ln: str) -> str:
        return f"#{int(ln[1:]) - offset}\n" if offset else ln

    def flush(chunk: list[list[str]]) -> None:
        nonlocal cycles, kept, run, offset, drop_from
        if not chunk:
            return
        is_cycle = _rises(chunk[0], clk)
        changes = [c for b in chunk for c in map(_change, (x.rstrip("\n") for x in b)) if c]
        moved = any(i in atom_ids and true.get(i) != v for i, v in changes)
        if is_cycle:
            run = 1 if (cycles == 0 or moved) else run + 1
            cycles += 1
        catch_up = {i: v for i, v in true.items() if seen.get(i, v) != v}  # what a dropped stretch changed
        for i, v in changes:
            true[i] = v
        if is_cycle and run > keep:  # dropped
            if drop_from is None:
                drop_from = int(chunk[0][0][1:])
                stretches.append({"cycle": cycles - 1, "dropped": 0})
            stretches[-1]["dropped"] += 1
            return
        if drop_from is not None:  # the first kept cycle after a dropped stretch
            offset += int(chunk[0][0][1:]) - drop_from
            drop_from = None
        if is_cycle:
            kept += 1
        for k, b in enumerate(chunk):
            res.append(stamp(b[0]) if b[0].startswith("#") else b[0])
            if k == 0:  # the values a dropped stretch changed, first at this cycle's timestamp (its own lines follow)
                res.extend(_write(i, v, kinds.get(i)) for i, v in catch_up.items())
            res.extend(b[1:])
        for i, v in true.items():
            seen[i] = v

    for block in _blocks(lines, start):
        if _rises(block, clk) and chunk:
            flush(chunk)
            chunk = []
        chunk.append(block)
    flush(chunk)
    Path(out).write_text("".join(res))
    info = {"source": Path(src).name, "atoms": list(atoms), "keep": keep, "cycles_in": cycles, "cycles_out": kept,
            "stretches": stretches}  # fmt: skip
    Path(f"{out}.cut.json").write_text(json.dumps(info, indent=1))
    return info
