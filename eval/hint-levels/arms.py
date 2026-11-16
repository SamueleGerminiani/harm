"""The hint-level arms of the HARM v4 letter: none, L0, L0+roles, rel and deep, as harm-coi and HARM command lines.

These are evaluation scripts, not HARM features: they drive `harm-coi --emit-config` and `harm` from outside. They
were extracted from the wrapper the letter's runs used, with the same behaviour (tests/test_arms.py, T2-T4). Only the
Python standard library and pyslang (harm-coi's own dependency) are used.

An arm's run: harm-coi writes the configuration (RTL predicates, cones; with hints, roles, placement and per-class
templates; with relations, the RTL relations); its cone element is set to mode="filter" depth="exact"; HARM mines the
golden traces with --reduce implies --atom-premises --sva --reset and a deadline, and checks every kept assertion on
the fault traces (--fd --find-min-subset). Assertions whose antecedent needs the reset active are dropped (vacuous
under `disable iff` of the reset), and so are trivially true long-range forms. Each kept assertion is labelled L0,
L1 or L2 (`level`). The deep arm adds a second pass of long-range templates over the design's 1-bit flags and state
encodings, mined on traces with their long stable stretches cut (cut.py)."""

from __future__ import annotations

import csv
import json
import os
import re
import shlex
import shutil
import signal
import subprocess
import threading
import time
from dataclasses import dataclass, field
from functools import cache
from pathlib import Path
from typing import Any

import pyslang  # harm-coi's own dependency: the top module's ports, for the deep arm

import cut as _cut  # this directory's cut.py


LR_DOMAIN = 7
_FLAG = re.compile(r"!?([A-Za-z_][\w:]*)")
_PROP = re.compile(r'(?P<pre>[ \t]*<prop exp=")(?P<exp>[^"]*)(?P<mid>" loc=")(?P<loc>[^"]*)(?P<post>"[^>]*/>\n)')
LR_POSITIVE = 8  # the flags that are not negations: events (trigger, release, eventuality)
LR_STATE = 9  # the positive state encodings (`x == c`), the state of an event-in-state trigger
LR_EVENT_FLAG = 10  # the positive 1-bit flags, the event of that trigger (disjoint from LR_STATE)
EVENT_IN_STATE = f"G({{{{P0({LR_EVENT_FLAG}) & P1({LR_STATE})}}}} {{a}} !P1({LR_STATE}) W P2({LR_POSITIVE}))"
_CMP = re.compile(r"([A-Za-z_][\w:]*) (==|!=) (\d+)'[bdh][0-9a-fA-F]+")
STATE_MAX_BITS = 4  # a wider state register compared with a constant is data
DEADLINE_FRACTION = 0.2  # HARM's --deadline: the budget left at its start, less this fraction and DEADLINE_MARGIN_S
DEADLINE_MARGIN_S = 5.0
MEM_GIB = 16.0  # the hard limit's resident memory per process
POLL_S = 0.5


def normalise(text: str) -> str:
    """HARM's --sva text without the outer `always (...)`; hierarchy `::` as `.`."""
    m = re.fullmatch(r"always \((.*)\)", text.strip())
    body = m.group(1) if m else text.strip()
    return body.replace("::", ".")


def one_cycle_and(sva: str) -> str:
    """HARM prints a template trigger `{p & s}` as `p and s`, SVA's sequence and (outside the subset); of
    two one-cycle Boolean terms it equals `p && s`. A trigger with a delay or any other sequence operator is left."""
    m = re.fullmatch(r"(.*?) (\|->|\|=>) (.*)", sva)
    if not m or m.group(1).count(" and ") != 1 or re.search(r"##|\[\*|\b(or|intersect|throughout|within)\b", m.group(1)):
        return sva
    # `and` binds more loosely than `||` and `?:`, `&&` more tightly: an operand with either at its
    # top level (outside brackets) is bracketed, so `a || b and c` becomes `(a || b) && c`, not `a || (b && c)`
    terms = [t.strip() for t in m.group(1).split(" and ")]
    if any(_depth0(t, ("(", ")")) is None for t in terms):
        return sva
    terms = [f"({t})" if _top_level(t) else t for t in terms]
    return f"{' && '.join(terms)} {m.group(2)} {m.group(3)}"


def _depth0(t: str, pair: tuple[str, str]) -> str | None:
    """t with every bracketed part blanked (None if the brackets do not balance)"""
    out, depth = [], 0
    for ch in t:
        depth += (ch == pair[0]) - (ch == pair[1])
        if depth < 0:
            return None
        out.append(ch if depth == 0 and ch != pair[1] else " ")
    return "".join(out) if depth == 0 else None


def _top_level(t: str) -> bool:
    """t has `||` or `?` outside brackets"""
    flat = _depth0(t, ("(", ")")) or ""
    return "||" in flat or "?" in flat


def needs_reset_active(leaves: list[dict[str, Any]], reset: str, *, active_low: bool) -> bool:
    """An assertion is vacuous under `disable iff` of the reset if a leaf reads the reset other than as its end
    (`$fell(rst)`, `$rose(rst_n)`) or its inactive value (`!rst`, `rst_n`)."""
    ok = {reset, f"$rose({reset})"} if active_low else {f"!{reset}", f"$fell({reset})"}
    word = re.compile(rf"(?<![\w$]){re.escape(reset)}(?![\w])")
    for leaf in leaves:
        if reset not in leaf["variables"]:
            continue
        # HARM's leaf is one cycle's conjunction (`!rst && !start`): each conjunct that reads the reset must be ok
        if "||" in leaf["text"] and word.search(leaf["text"]):
            return True
        for part in leaf["text"].split("&&"):
            if word.search(part) and part.strip().replace(" ", "") not in ok:
                return True
    return False


def level(a: dict[str, Any], reset: str | None, *, active_low: bool) -> str:
    """How much of an assertion the RTL fixed: L2 the whole of it (a fixed template's antecedent: the reset's
    inactive value or its end, padding aside), L1 its consequent (a proposition of origin rtl-relation under a mined
    antecedent), L0 the vocabulary and shape only."""
    ant = [x for x in a["leaves"] if x["antecedent"]]
    con = [x for x in a["leaves"] if not x["antecedent"]]
    if reset:
        fixed = {reset, f"$rose({reset})", "1'b1"} if active_low else {f"!{reset}", f"$fell({reset})", "1'b1"}
        if ant and all(x["text"].replace(" ", "") in fixed for x in ant):
            return "L2"
    return "L1" if any(x.get("origin") == "rtl-relation" for x in con) else "L0"


def state_encodings(work: Path) -> set[str]:
    """The signals harm-coi's roles (hints.json, written when hints are on) mark state and control."""
    f = work / "hints.json"
    roles = json.loads(f.read_text()).get("roles", {}) if f.exists() else {}
    return {n for n, r in roles.items() if r.get("role") == "state" and r.get("control")}


def _atom(exp: str, states: set[str] | frozenset[str]) -> tuple[str, bool] | None:
    """(signal, positive) of a flag (`x`, `!x`) or of a state encoding (`x == c` positive, `x != c` not) of
    a signal in `states` at most STATE_MAX_BITS wide; None for any other proposition."""
    if f := _FLAG.fullmatch(exp):
        return f.group(1), not exp.startswith("!")
    if (c := _CMP.fullmatch(exp.replace("&#39;", "'"))) and c.group(1) in states and int(c.group(3)) <= STATE_MAX_BITS:
        return c.group(1), c.group(2) == "=="
    return None


def _positive(exp: str) -> str:
    return exp[1:] if exp.startswith("!") else exp.replace(" != ", " == ")


def flags(xml: str, *, reset: str | None, exclude: set[str] | frozenset[str] = frozenset(),
          states: set[str] | frozenset[str] = frozenset()) -> list[str]:  # fmt: skip
    """The configuration's 1-bit flag propositions (a bare signal or its negation) and the state encodings
    of `states` (`_atom`); the reset and `exclude` left out"""
    out = []
    for m in _PROP.finditer(xml):
        a = _atom(m.group("exp"), states)
        if a and a[0] != reset and a[0].replace("::", ".") not in exclude:
            out.append(m.group("exp"))
    return out


def _attr(v: str) -> str:
    return v.replace("&", "&amp;").replace('"', "&quot;").replace("<", "&lt;").replace(">", "&gt;")


def _lr_templates(arrow: str) -> str:
    a = _attr(arrow)
    d, pos = LR_DOMAIN, LR_POSITIVE
    return "".join(f'        <template exp="{t}"/>\n' for t in (
        f"G({{P0({pos})}} {a} P1({d}) W P2({pos}))",    # after event p, q holds until event r
        f"G({{P0({pos})}} {a} !P1({pos}) W P2({pos}))",  # after event p, b does not happen before a
    ))  # fmt: skip
    # no liveness template `F P1`: false on golden traces whenever the wait depends on an input, and its true
    # candidates are implied by bounded ones


def long_range(xml: str, *, reset: str | None, arrow: str = "|=>", only: bool = False,
               exclude: set[str] | frozenset[str] = frozenset(), states: set[str] | frozenset[str] = frozenset(),
               a6_only: bool = False) -> str:  # fmt: skip
    """The configuration with its flags (`flags`) in LR_DOMAIN (the positive ones in LR_POSITIVE too) and the three
    long-range templates written with `arrow` after its templates. `only` (the cut pass): only the flags and the two templates are kept."""
    keep = set(flags(xml, reset=reset, exclude=exclude, states=states))
    in_state = {9: 0, 10: 0}  # the full pass only: how many propositions each of its domains holds

    def extra(exp: str) -> str:
        if only:
            return ""
        d = LR_EVENT_FLAG if _FLAG.fullmatch(exp) else LR_STATE
        in_state[d] += 1
        return f", {d}"

    def mark(m: re.Match[str]) -> str:
        if m.group("exp") not in keep:
            return "" if only else m.group(0)
        positive = _atom(m.group("exp"), states)[1]  # type: ignore[index]
        dom = f", {LR_DOMAIN}" + (f", {LR_POSITIVE}" + extra(m.group("exp")) if positive else "")
        return m.group("pre") + m.group("exp") + m.group("mid") + m.group("loc") + dom + m.group("post")

    xml = _PROP.sub(mark, xml)
    have = {m.group("exp") for m in _PROP.finditer(xml)}
    pos = sorted({_positive(k) for k in keep} - have)  # events need the positive form of a flag written negated only
    if pos:
        last_prop = list(_PROP.finditer(xml))[-1].end()
        lead = "" if a6_only else "a, c, "  # a6_only: kept out of the usual templates' domains
        xml = xml[:last_prop] + "".join(f'        <prop exp="{_attr(p)}" loc="{lead}{LR_DOMAIN}, {LR_POSITIVE}{extra(p)}" '
                                        f'origin="positive"/>\n' for p in pos) + xml[last_prop:]  # fmt: skip
    if only:
        xml = re.sub(r"[ \t]*<template [^>]*/>\n", "", xml)
    last = list(re.finditer(r"[ \t]*<template [^>]*/>\n", xml))
    at = last[-1].end() if last else (re.search(r"[ \t]*<sort ", xml) or re.search(r"    </context>", xml)).start()
    a6 = f'        <template exp="{_attr(EVENT_IN_STATE.format(a=arrow))}"/>\n' if all(in_state.values()) else ""
    return xml[:at] + ("" if a6_only else _lr_templates(arrow)) + a6 + xml[at:]  # a6_only: the cut recipe's full pass


def _encloses(x: str) -> bool:
    """x's first bracket closes at its last character (, finding 6: `(!x) until (x)` is not one bracketed term)"""
    depth = 0
    for i, ch in enumerate(x):
        depth += (ch == "(") - (ch == ")")
        if depth == 0:
            return i == len(x) - 1
    return False


def _strip(x: str) -> str:
    x = x.strip()
    while x.startswith("(") and x.endswith(")") and _encloses(x):
        x = x[1:-1].strip()
    return x


def _negates(q: str, r: str) -> bool:
    """q is `!r`, `!(r)` or, for a comparison r `x == c`, `x != c` """
    return q in (f"!{r}", f"!({r})") or (" == " in r and q == r.replace(" == ", " != "))


def trivial_long_range(sva: str) -> bool:
    """A long-range candidate true on every trace: `q until q`, `!r until r`; with |-> (same cycle), a release or an
    eventuality equal to the trigger."""
    m = re.fullmatch(r"(.+?) \|(->|=>) (.+)", sva.strip())
    if not m:
        return False
    p, arrow, cons = _strip(m.group(1)), m.group(2), _strip(m.group(3))
    if u := re.fullmatch(r"(!?)(.+?) until (.+)", cons):
        q, r = _strip(u.group(1) + u.group(2)), _strip(u.group(3))
        return q == r or _negates(q, r) or (arrow == "->" and p == r)
    if e := re.fullmatch(r"s_eventually (.+)", cons):
        return arrow == "->" and p == _strip(e.group(1))
    return False


# ----------------------------------------------------------- the hard limit

def hard_limit_s(budget_s: float) -> float:
    """The wall time after which an arm's process is killed: its own deadline is one it can overrun."""
    return budget_s * 1.5 + 60


class HardLimit(Exception):
    """The process tree was killed at the hard limit; `kind` "wall" or "memory"; its output up to the kill."""

    def __init__(self, kind: str, limit: float, peak_gib: float, stdout: str, stderr: str) -> None:
        what = f"{round(limit)} s" if kind == "wall" else f"{limit} GiB per process (peak {round(peak_gib, 2)} GiB)"
        super().__init__(f"killed at the hard limit: {what}")
        self.kind, self.limit, self.peak_gib, self.stdout, self.stderr = kind, limit, peak_gib, stdout, stderr


def _tree(root: int) -> list[tuple[int, float]]:
    """(pid, resident GiB) of `root` and its descendants."""
    out = subprocess.run(["ps", "-axo", "pid=,ppid=,rss="], capture_output=True, text=True).stdout
    kids: dict[int, list[tuple[int, float]]] = {}
    rss: dict[int, float] = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3:
            pid, ppid = int(p[0]), int(p[1])
            kids.setdefault(ppid, []).append((pid, int(p[2]) / 2**20))
            rss[pid] = int(p[2]) / 2**20
    todo, seen = [root], [(root, rss.get(root, 0.0))]
    while todo:
        for pid, g in kids.get(todo.pop(), []):
            seen.append((pid, g))
            todo.append(pid)
    return seen


def _kill(proc: subprocess.Popen[str]) -> None:
    try:
        os.killpg(proc.pid, signal.SIGKILL)
    except (ProcessLookupError, PermissionError):
        proc.kill()


def run(cmd: list[str], *, wall_s: float, mem_gib: float = MEM_GIB, cwd: Path | str | None = None,
        env: dict[str, str] | None = None, stop: threading.Event | None = None) -> subprocess.CompletedProcess[str]:  # fmt: skip
    """subprocess.run(cmd, capture_output=True, text=True), in its own process group, killed past `wall_s` or when a
    process of its tree holds more than `mem_gib` resident; then HardLimit with the output so far. `stop`: the caller
    no longer needs the run (HardLimit kind "stopped")."""
    proc = subprocess.Popen(cmd, cwd=cwd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
                            start_new_session=True)  # fmt: skip
    out: dict[str, Any] = {}
    readers = [threading.Thread(target=lambda k, f: out.__setitem__(k, f.read()), args=(k, f), daemon=True)
               for k, f in (("stdout", proc.stdout), ("stderr", proc.stderr))]  # fmt: skip
    for t in readers:
        t.start()
    t0, kind, peak = time.time(), None, 0.0
    while proc.poll() is None:
        if stop is not None and stop.is_set():
            kind = "stopped"
        elif time.time() - t0 > wall_s:
            kind = "wall"
        else:
            peak = max([peak, *(g for _, g in _tree(proc.pid))])
            if peak > mem_gib:
                kind = "memory"
        if kind:
            _kill(proc)
            proc.wait()
            break
        time.sleep(POLL_S)
    for t in readers:
        t.join(timeout=10)
    if kind:
        raise HardLimit(kind, wall_s if kind == "wall" else mem_gib, peak, out.get("stdout", ""), out.get("stderr", ""))
    cp = subprocess.CompletedProcess(cmd, proc.returncode, out.get("stdout", ""), out.get("stderr", ""))
    cp.peak_gib = round(peak, 3)  # type: ignore[attr-defined]  # the tree's peak resident memory, sampled
    return cp


@cache
def _ports(files: tuple[str, ...], top: str, includes: tuple[str, ...], defines: tuple[str, ...]
           ) -> tuple[frozenset[str], frozenset[str]]:  # fmt: skip
    d = pyslang.driver.Driver()
    d.addStandardArgs()
    args = ["ports", "--top", top, *(f"-D{x}" for x in defines), *(f"-I{x}" for x in includes), *files]
    if not d.parseCommandLine(shlex.join(args), pyslang.driver.CommandLineOptions()) or not d.processOptions():
        raise ValueError(f"{top}: invalid front-end options")
    if not d.parseAllSources():
        raise ValueError(f"{top}: cannot parse the sources")
    comp = d.createCompilation()
    inst = next((i for i in comp.getRoot().topInstances if i.name == top), None)
    if inst is None:
        raise ValueError(f"top module {top!r} not found")
    ins, outs = set(), set()
    for p in inst.body.portList:
        d_ = str(p.direction).split(".")[-1]
        if d_ in ("In", "InOut"):
            ins.add(p.name)
        if d_ in ("Out", "InOut"):
            outs.add(p.name)
    return frozenset(ins), frozenset(outs)



# ------------------------------------------------------------------------------------------------- the arms

ARMS: dict[str, dict[str, Any] | None] = {
    "none": None,  # HARM alone on its --generate-config configuration, the arms' deadline
    "none-full": None,  # the same, no deadline and no time limit: mining and what follows it timed apart
    "L0": {"hints": "none", "knobs": {}},
    "L0+roles": {"hints": "all", "knobs": {}},
    "rel": {"hints": "relations", "knobs": {}},
    "deep": {"hints": "all", "knobs": {"long_range": True, "cut": True}},
}
HINTS = ("none", "placement", "all", "relations")


@dataclass
class Tools:
    """Where HARM and harm-coi are: the harm binary, the Python with harm-coi's dependencies, and HARM's repository
    (for tools/harm-coi/src)."""

    harm: Path
    python: Path
    repo: Path


@dataclass
class Result:
    candidates: list[dict[str, Any]]
    status: str  # ok, timeout or error
    stats: dict[str, Any] = field(default_factory=dict)
    dropped: list[dict[str, Any]] = field(default_factory=list)
    error: str | None = None


def entry_for(d: dict[str, Any], base: Path, prep: dict[str, Any]) -> tuple[dict[str, Any], list[dict[str, Any]]]:
    """A design and its golden traces from eval/mutants: `d` its corpus.json item, `base` that file's folder, `prep`
    its prepared.json."""
    rst = d.get("reset", "")
    design = {"id": d["name"], "root": str(base), "rtl_files": d["files"], "top": d["top"],
              "clock": {"name": d["clk"], "edge": "posedge"},
              "reset": {"name": rst.lstrip("!"), "active_low": rst.startswith("!")} if rst else None,
              "include_dirs": d.get("includes", []), "defines": {x: None for x in d.get("defines", [])}}  # fmt: skip
    entry = {"id": d["name"], "vcd_recursion": 16, "design": design}
    vcds = sorted(str(p) for p in Path(prep["mining_dir"]).glob("*.vcd"))
    return entry, [{"vcd_paths": vcds, "scope": "tb::dut"}]


def coi_name(name: str) -> str:
    """A signal's name in HARM's and harm-coi's notation (`u_div::q`) from SVA's (`u_div.q`)."""
    return name.replace(".", "::")


def ports_of(entry: dict[str, Any]) -> tuple[set[str], set[str]]:
    """The top module's (inputs, outputs)."""
    b = entry["design"]
    root = Path(b["root"])
    ins, outs = _ports(tuple(str(root / f) for f in b["rtl_files"]), b["top"],
                       tuple(str(root / i) for i in b["include_dirs"]),
                       tuple(k if v is None else f"{k}={v}" for k, v in sorted(b.get("defines", {}).items())))  # fmt: skip
    return set(ins), set(outs)


def trace_args(entry: dict[str, Any], traces: list[dict[str, Any]], work: Path) -> list[str]:
    """HARM's trace arguments: several VCD files go to --vcd-dir as links named in their order (HARM concatenates a
    directory's files in path order)."""
    vcds = [Path(p) for t in traces for p in t["vcd_paths"]]
    if len(vcds) == 1:
        a = ["--vcd", str(vcds[0])]
    else:
        d = work / "vcd"
        if d.exists():
            shutil.rmtree(d)
        d.mkdir(parents=True)
        for i, v in enumerate(vcds):
            (d / f"{i:04d}_{v.name}").symlink_to(v)
        a = ["--vcd-dir", str(d)]
    a += ["--clk", coi_name(entry["design"]["clock"]["name"]), "--vcd-ss", traces[0]["scope"]]
    return a + ([f"--vcd-r={entry['vcd_recursion']}"] if entry["vcd_recursion"] else [])


def config(entry: dict[str, Any], traces: list[dict[str, Any]], work: Path, tools: Tools, hints: str = "none") -> str:
    """harm-coi's configuration for `hints` (none, placement, all or relations), its cone element in filter mode with
    exact depths."""
    if hints not in HINTS:
        raise ValueError(f"hints {hints!r}: expected one of {', '.join(HINTS)}")
    b = entry["design"]
    root = Path(b["root"])
    cmd = [str(tools.python), "-m", "harm_coi", "--top", b["top"], "--files", *[str(root / f) for f in b["rtl_files"]],
           "--vcd-scope", traces[0]["scope"], "--vcd-recursion", str(entry["vcd_recursion"]),
           "--vcd", traces[0]["vcd_paths"][0], "--clock", coi_name(b["clock"]["name"]),
           "--emit-config", str(work / "emitted.xml"), "-o", str(work / "coi.json"), "--aliases",
           "--domains", str(work / "domains.json"), "--cut-domains"]  # fmt: skip  # the clock's own domain only
    for i in b["include_dirs"]:
        cmd += ["--include", str(root / i)]
    for k, v in b.get("defines", {}).items():
        cmd += ["--define", k if v is None else f"{k}={v}"]
    if hints != "none":
        cmd += ["--hints", str(work / "hints.json"), "--hints-use", "all" if hints == "relations" else hints]
        cmd.append("--relations" if hints == "relations" else "--no-relations")
        if (rst := b.get("reset")) is not None:
            cmd += ["--reset", f"!{rst['name']}" if hints == "relations" and rst["active_low"] else rst["name"]]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=work,
                       env={**os.environ, "PYTHONPATH": str(tools.repo / "tools" / "harm-coi" / "src")})  # fmt: skip
    (work / "harm-coi.log").write_text(r.stdout + r.stderr)
    if r.returncode != 0:
        raise RuntimeError(f"harm-coi failed: {r.stderr.strip()[-300:]}")
    xml = (work / "emitted.xml").read_text()
    xml = xml.replace('file="coi.json"', f'file="{work / "coi.json"}"')
    return xml.replace('mode="rank"', 'mode="filter" depth="exact"')


_ESC = re.compile(r"\x1b\[[0-9;]*m")


def mine(entry: dict[str, Any], traces: list[dict[str, Any]], work: Path, tools: Tools, *, timeout_s: float = 600,
         threads: int = 8, hints: str = "none", knobs: dict[str, Any] | None = None) -> Result:  # fmt: skip
    """One HARM run of an arm (`hints`, `knobs`: ARMS), its kept assertions as candidates with their provenance:
    HARM's text, the pass (full or cut), the level. Knobs: `long_range` and `cut` (the deep recipe), `harm_args`
    (more HARM arguments, e.g. --fd), `reduce` (default true)."""
    knobs = knobs or {}
    if knobs.get("cut"):
        if not knobs.get("long_range"):
            raise ValueError("knob cut needs long_range")
        return _mine_with_cut(entry, traces, work, tools, timeout_s=timeout_s, knobs=knobs, threads=threads,
                              hints=hints)  # fmt: skip
    start = time.time()  # the budget counts from here (harm-coi's time included)
    work.mkdir(parents=True, exist_ok=True)
    b = entry["design"]
    xml = config(entry, traces, work, tools, hints)
    lr_only = bool(knobs.get("_lr_only"))  # the cut pass
    forms = "t34" if knobs.get("long_range") or lr_only or knobs.get("_a6") else "a7"
    rst_name = (b.get("reset") or {}).get("name")
    if lr_only:
        xml = long_range(xml, reset=rst_name, arrow="|->", only=True, exclude=ports_of(entry)[0],
                         states=state_encodings(work))  # fmt: skip
    elif knobs.get("long_range"):
        xml = long_range(xml, reset=rst_name, arrow="|=>", states=state_encodings(work))
    elif knobs.get("_a6"):  # the deep recipe's full pass: the event-in-state template only
        xml = long_range(xml, reset=rst_name, arrow="|=>", states=state_encodings(work), a6_only=True)
    (work / "config.xml").write_text(xml)
    args = (["--reduce", "implies", "--atom-premises"] if knobs.get("reduce", True) else []) + [
        "--sva", "--max-threads", str(threads)]
    if (r := b.get("reset")) is not None:
        args += ["--reset", f"!{r['name']}" if r["active_low"] else r["name"]]
    if "<prop " not in xml:
        return Result([], "ok", stats={"note": "harm-coi found no predicates; HARM not run"})
    left = timeout_s - (time.time() - start)
    deadline = max(0.0, left * (1 - DEADLINE_FRACTION) - DEADLINE_MARGIN_S)
    cmd = [str(tools.harm), *trace_args(entry, traces, work), "--conf", str(work / "config.xml"), *args,
           "--psilent", "--isilent", "--dont-print-ass", "--dump-assertion-info", str(work / "info.json"),
           "--deadline", f"{deadline:.1f}", *knobs.get("harm_args", [])]  # fmt: skip
    t0 = time.time()
    try:  # the hard limit, from the run's start
        p = run(cmd, wall_s=max(1.0, hard_limit_s(timeout_s) - (t0 - start)), cwd=work)
    except HardLimit as e:
        (work / "harm.log").write_text(_ESC.sub("", e.stdout + e.stderr))
        return Result([], "timeout", stats={"wall_s": round(time.time() - t0, 2), "command": cmd},
                      error=f"HARM {e} (its deadline {deadline:.1f} s; see {work / 'harm.log'})")  # fmt: skip
    wall = round(time.time() - t0, 2)
    (work / "harm.log").write_text(_ESC.sub("", p.stdout + p.stderr))
    if p.returncode != 0:
        return Result([], "error", stats={"wall_s": wall, "command": cmd},
                      error=f"HARM exit {p.returncode} (see {work / 'harm.log'})")  # fmt: skip
    info = work / "info.json"  # with --deadline HARM writes it even when it keeps no assertion
    dump = json.loads(info.read_text()) if info.exists() else {}
    cut = dump.get("deadline") or {}
    cands, dropped = [], []
    reset = (b.get("reset") or {}).get("name")
    low = bool((b.get("reset") or {}).get("active_low"))
    for i, a in enumerate(dump.get("assertions", [])):
        sva = one_cycle_and(normalise(a["text"]))
        if reset and needs_reset_active(a["leaves"], reset, active_low=low):
            dropped.append({"harm_text": a["text"], "reasons": f"reads the reset {reset} (vacuous under disable iff)"})
            continue
        if forms == "t34" and trivial_long_range(sva):
            dropped.append({"harm_text": a["text"], "reasons": "trivially true long-range relation"})
            continue
        cands.append({"sva": sva, "provenance": {"harm_text": a["text"], "context": a["context"], "rank": str(i),
                                                 "hints": hints, "form": "bounded",
                                                 "rtl_level": level(a, reset, active_low=low)}})  # fmt: skip
    stats = {"wall_s": wall, "harm_assertions": len(dump.get("assertions", [])), "command": cmd, "deadline": cut}
    status = "timeout" if cut.get("mineCut") else "ok"  # HARM stopped mining at its deadline: the run is partial
    return Result(cands, status, stats=stats, dropped=dropped)


def _mine_with_cut(entry: dict[str, Any], traces: list[dict[str, Any]], work: Path, tools: Tools, *, timeout_s: float,
                   knobs: dict[str, Any], threads: int, hints: str) -> Result:  # fmt: skip
    """The deep recipe: the usual templates (and the event-in-state one) on the full traces with two thirds of the
    budget, then the long-range templates (|->) on the traces cut over the flags that are not top inputs; the
    candidates of both, `provenance.pass` full or cut."""
    start = time.time()
    base = {k: v for k, v in knobs.items() if k not in ("long_range", "cut")}
    r1 = mine(entry, traces, work / "full", tools, timeout_s=timeout_s * 2 / 3, knobs={**base, "_a6": True},
              threads=threads, hints=hints)  # fmt: skip
    if r1.status == "error":
        return r1
    b = entry["design"]
    reset = (b.get("reset") or {}).get("name")
    inputs = ports_of(entry)[0]
    cfg = work / "full" / "config.xml"
    st = state_encodings(work / "full")
    atoms = sorted({_atom(f, st)[0].replace("::", ".")  # type: ignore[index]
                    for f in flags(cfg.read_text(), reset=reset, exclude=inputs, states=st)} if cfg.exists() else set())  # fmt: skip
    for c in r1.candidates:
        c["provenance"]["pass"] = "full"
    if not atoms:
        return Result(r1.candidates, r1.status, stats={**r1.stats, "cut_pass": "no flag that is not a top input"},
                      dropped=r1.dropped, error=r1.error)  # fmt: skip
    cdir = work / "cut" / "traces"
    cdir.mkdir(parents=True, exist_ok=True)
    cut_traces, infos = [], []
    try:
        for t in traces:
            paths = []
            for v in t["vcd_paths"]:
                out = cdir / f"{len(infos):04d}_{Path(v).name}"
                infos.append(_cut.cut(Path(v), out, t["scope"], b["clock"]["name"], atoms))
                paths.append(str(out))
            cut_traces.append({**t, "vcd_paths": paths})
    except Exception as e:  # a failed cut ends the cut pass only; the full pass's candidates stay
        msg = f"cut pass: {type(e).__name__}: {e}"
        return Result(r1.candidates, r1.status, stats={**r1.stats, "cut_pass": {"status": "error", "error": msg}},
                      dropped=r1.dropped, error="; ".join(x for x in (r1.error, msg) if x))  # fmt: skip
    left = max(1.0, timeout_s - (time.time() - start))
    r2 = mine(entry, cut_traces, work / "cut", tools, timeout_s=left, knobs={**base, "_lr_only": True},
              threads=threads, hints=hints)  # fmt: skip
    for c in r2.candidates:
        c["provenance"]["pass"] = "cut"
    status = "timeout" if "timeout" in (r1.status, r2.status) else r1.status
    stats = {**r1.stats, "cut_pass": {**r2.stats, "atoms": atoms, "status": r2.status}}
    err = "; ".join(e for e in (r1.error, r2.error and f"cut pass: {r2.error}") if e) or None
    return Result(r1.candidates + r2.candidates, status, stats=stats, dropped=r1.dropped + r2.dropped, error=err)


_CONST_ENTRY = re.compile(r'^\s*<(?:prop|numeric)\s.*\sexp="([^"]*)".*/>\s*$')  # clustering holds "><"
_TIME_TO_MINE = re.compile(r"Time to mine: ([0-9.]+)s")


def constant_signals(csv_path: Path) -> list[str]:
    """The signals of HARM's --dump-trace-as-csv file whose value never changes (header cells "<type> <name>")."""
    with open(csv_path, newline="") as f:
        rows = csv.reader(f)
        names = [c.strip().rsplit(" ", 1)[-1] for c in next(rows)]
        first = next(rows, None)
        if first is None:
            return []
        const = set(range(len(names)))
        for r in rows:
            const -= {i for i in const if r[i] != first[i]}
            if not const:
                break
    return sorted(names[i] for i in const)


def drop_entries(xml: str, names: set[str]) -> str:
    """The configuration without the <prop>/<numeric> entries whose exp is one of `names`."""
    return "".join(line for line in xml.splitlines(keepends=True)
                   if not ((m := _CONST_ENTRY.match(line)) and m.group(1) in names))  # fmt: skip


def run_none(entry: dict[str, Any], traces: list[dict[str, Any]], work: Path, tools: Tools, *, timeout_s: float,
             threads: int, harm_args: list[str] = (), full: bool = False, mem_gib: float = MEM_GIB) -> Result:  # fmt: skip
    """HARM alone: its --generate-config configuration over every trace signal less those constant over the mining
    traces (parameters), the arms' arguments. `full` False: the arms' deadline and hard limit; True: neither, mining
    and what follows it (reduction, ranking, fault check, output) timed apart (HARM's "Time to mine" and the rest)."""
    start = time.time()
    work.mkdir(parents=True, exist_ok=True)
    ta = trace_args(entry, traces, work)
    conf = work / "config.xml"
    run([str(tools.harm), *ta, "--conf", str(work / "generated.xml"), "--generate-config", "--psilent", "--isilent"],
        wall_s=600, cwd=work)  # fmt: skip
    run([str(tools.harm), *ta, "--dump-trace-as-csv", str(work / "trace.csv"), "--psilent", "--isilent"], wall_s=600,
        cwd=work)  # fmt: skip
    const = constant_signals(work / "trace.csv")
    (work / "trace.csv").unlink()
    conf.write_text(drop_entries((work / "generated.xml").read_text(), set(const)))
    b = entry["design"]
    r = b.get("reset")
    args = ["--reduce", "implies", "--atom-premises", "--sva", "--max-threads", str(threads)]
    if r is not None:
        args += ["--reset", f"!{r['name']}" if r["active_low"] else r["name"]]
    cmd = [str(tools.harm), *ta, "--conf", str(conf), *args, "--psilent", "--isilent", "--dont-print-ass",
           "--dump-assertion-info", str(work / "info.json")]  # fmt: skip
    if not full:
        left = timeout_s - (time.time() - start)
        cmd += ["--deadline", f"{max(0.0, left * (1 - DEADLINE_FRACTION) - DEADLINE_MARGIN_S):.1f}"]
    cmd += list(harm_args)
    stats: dict[str, Any] = {"command": cmd, "dropped_constant": const, "mine_s": None, "post_s": None,
                             "permutations_done": None, "permutations_total": None, "peak_gib": None}  # fmt: skip
    t0 = time.time()
    try:
        p = run(cmd, wall_s=float("inf") if full else max(1.0, hard_limit_s(timeout_s) - (t0 - start)),
                mem_gib=mem_gib, cwd=work)  # fmt: skip
    except HardLimit as e:
        (work / "harm.log").write_text(_ESC.sub("", e.stdout + e.stderr))
        stats.update(wall_s=round(time.time() - t0, 2), peak_gib=round(e.peak_gib, 3))
        return Result([], "timeout", stats=stats, error=str(e))
    log = _ESC.sub("", p.stdout + p.stderr)
    (work / "harm.log").write_text(log)
    wall = round(time.time() - t0, 2)
    stats.update(wall_s=wall, peak_gib=p.peak_gib)  # type: ignore[attr-defined]
    if (m := _TIME_TO_MINE.search(log)) is not None:
        stats.update(mine_s=float(m.group(1)), post_s=round(wall - float(m.group(1)), 2))
    if p.returncode != 0 or not (work / "info.json").exists():
        return Result([], "error", stats=stats, error=f"HARM exit {p.returncode}")
    dump = json.loads((work / "info.json").read_text())
    cut = dump.get("deadline") or {}
    stats.update(permutations_done=cut.get("permutationsDone"), permutations_total=cut.get("permutationsTotal"))
    reset, low = (r or {}).get("name"), bool((r or {}).get("active_low"))
    cands = []
    for a in dump["assertions"]:
        if reset and needs_reset_active(a["leaves"], reset, active_low=low):
            continue
        cands.append({"provenance": {"harm_text": a["text"], "rtl_level": level(a, reset, active_low=low),
                                     "pass": "full"}})  # fmt: skip
    return Result(cands, "timeout" if cut.get("mineCut") else "ok", stats=stats)


def run_arm(arm: str, entry: dict[str, Any], traces: list[dict[str, Any]], work: Path, tools: Tools, faults: str, *,
            timeout_s: float, threads: int, mem_gib: float = MEM_GIB) -> tuple[list[dict[str, Any]], dict[str, Any]]:  # fmt: skip
    """One arm on one design, scored on `faults` (the fault traces directory): candidates and the run's status."""
    spec = ARMS[arm]
    fd = ["--fd", faults, "--find-min-subset"]
    t0 = time.time()
    if spec is None:
        res = run_none(entry, traces, work, tools, timeout_s=timeout_s, threads=threads, harm_args=fd,
                       full=arm == "none-full", mem_gib=mem_gib)  # fmt: skip
    else:
        res = mine(entry, traces, work, tools, timeout_s=timeout_s, threads=threads, hints=spec["hints"],
                   knobs={**spec["knobs"], "harm_args": fd})  # fmt: skip
    wall = res.stats.get("wall_s", 0) if spec is None else round(time.time() - t0, 2)  # none: HARM's own run
    st = {"status": res.status, "wall_s": wall, "error": res.error or ""}
    if spec is None:
        st.update({k: res.stats.get(k) for k in NONE_STATS})
        st["dropped_constant"] = len(res.stats.get("dropped_constant") or [])
    return res.candidates, st


NONE_STATS = ("mine_s", "post_s", "permutations_done", "permutations_total", "peak_gib")
