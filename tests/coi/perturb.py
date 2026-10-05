#!/usr/bin/env python3
"""Simulation checks of a COI fixture's hand-written cones (H4, acceptance tests A3-A5).

  reproduce  A3: building the fixture again gives its committed trace.vcd (header lines aside)
  influence  A4: forcing a visible signal S to pseudo-random values never changes a target whose
             cone does not contain S (non-influence claims are sound); exit 1 otherwise
  depths     A5: for each claimed (S, T, d), a one-cycle pulse on S changes T d cycles later in at
             least one run; claims never observed are only reported (exit 0)

Values are compared at every rising clock edge, as HARM samples them: the values in effect just
before the edge.

Usage: perturb.py <reproduce|influence|depths> <fixture dir> [--harm <bin>] [--work <dir>]
"""
import argparse
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

PULSE_CYCLES = [20, 60, 100, 140]
SEEDS = [1, 2, 3, 4, 5]


# ---------------------------------------------------------------- VCD
def read_vcd(path, scope, clock):
    """{harm name: [value at each rising clock edge]} for the signals under 'scope' ('::' path)"""
    names, stack, values, current = {}, [], {}, {}
    samples = {}
    scope_parts = scope.split("::") if scope else []
    clock_id, clock_val, in_defs = None, None, True
    lines = Path(path).read_text().split("\n")
    i = 0
    time_events = []
    for line in lines:
        tok = line.split()
        if not tok:
            continue
        if in_defs:
            if tok[0] == "$scope":
                stack.append(tok[2])
            elif tok[0] == "$upscope":
                stack.pop()
            elif tok[0] == "$var":
                ident, name = tok[3], tok[4]
                if stack[:len(scope_parts)] == scope_parts:
                    rel = stack[len(scope_parts):] + [name]
                    harm = "::".join(rel)
                    names.setdefault(ident, []).append(harm)
                    if harm == clock and len(rel) == 1:
                        clock_id = ident
            elif tok[0] == "$enddefinitions":
                in_defs = False
            continue
        time_events.append(tok)
    if clock_id is None:
        sys.exit(f"clock '{clock}' not found under scope '{scope}' in {path}")
    # HARM's convention: the values in effect just before each rising clock edge. SVA concurrent
    # assertions sample in the Preponed region, while VCD dumps record the end of the time step
    # (after nonblocking assignments): sampling before the edge gives what an assertion sees, so
    # a register updated at an edge shows its new value at the next edge
    def sample():
        for ident, hs in names.items():
            for h in hs:
                samples.setdefault(h, []).append(current.get(ident, "x"))

    block = []

    def flush():
        nonlocal clock_val
        rising = any(ident == clock_id and val == "1" for val, ident in block) and clock_val == "0"
        if rising:
            sample()
        for val, ident in block:
            if ident == clock_id:
                clock_val = val
            current[ident] = val
        block.clear()

    for tok in time_events:
        t = tok[0]
        if t.startswith("#"):
            flush()
            continue
        if t.startswith("$"):
            continue
        if t[0] in "bBrR":
            block.append((t[1:], tok[1]))
        else:
            block.append((t[0], t[1:]))
    flush()
    return samples


# ---------------------------------------------------------------- builds
def build(fixture, work, name, perturb=None, extra=()):
    out = work / name
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    args = []
    if perturb is not None:
        (out / "perturb.svh").write_text(perturb)
        args = ["+define+PERTURB"]
    r = subprocess.run(["bash", str(fixture / "build.sh"), str(out), "trace.vcd"] + args + list(extra),
                       capture_output=True, text=True)
    return out if r.returncode == 0 else None


def run(build_dir, plusargs, vcd):
    r = subprocess.run([str(build_dir / "obj" / "sim"), f"+vcd={vcd}"] + plusargs, cwd=build_dir,
                       capture_output=True, text=True)
    return r.returncode == 0


def force_code(path, width):
    # cast to the signal's own type (enums do not accept a plain vector)
    w = f"type({path})'"
    return f'''  int unsigned p_mode = 0, p_from = 0, p_until = 0;
  initial begin
    int unsigned c = 0;
    void'($value$plusargs("pmode=%d", p_mode));
    void'($value$plusargs("pfrom=%d", p_from));
    void'($value$plusargs("puntil=%d", p_until));
    if (p_mode != 0)
      forever begin
        @(negedge clk);
        c++;
        if (c >= p_from && c < p_until)
          case (p_mode)
            1: force {path} = {w}((c * 32'h9E3779B9) >> 5);
            2: force {path} = {w}('0);
            default: force {path} = {w}({{{width}{{1'b1}}}});
          endcase
        else release {path};
      end
  end
'''


def sv_path(harm_name):
    return "dut." + harm_name.replace("::", ".")


def widths(fixture, coi):
    """bit width of every signal visible to HARM (under the scope, within the recursion depth)"""
    w = {}
    scope = coi["meta"]["vcd_scope"].split("::")
    stack = []
    for line in (fixture / "trace.vcd").read_text().split("\n"):
        tok = line.split()
        if not tok:
            continue
        if tok[0] == "$scope":
            stack.append(tok[2])
        elif tok[0] == "$upscope":
            stack.pop()
        elif (tok[0] == "$var" and stack[:len(scope)] == scope
              and len(stack) - len(scope) <= coi["meta"]["vcd_recursion"]):
            # only the signals HARM sees at the recorded --vcd-r depth
            w["::".join(stack[len(scope):] + [tok[4]])] = int(tok[2])
        elif tok[0] == "$enddefinitions":
            break
    return w


# ---------------------------------------------------------------- checks
def reproduce(fixture, work):
    b = build(fixture, work, "base")
    if b is None:
        print("build failed")
        return False

    def body(p):
        lines = Path(p).read_text().split("\n")
        skip, out = False, []
        for l in lines:  # drop the $date/$version/$comment blocks
            if l.strip().startswith(("$date", "$version", "$comment")):
                skip = True
            if not skip:
                out.append(l)
            if skip and l.strip().endswith("$end"):
                skip = False
        return out
    same = body(b / "trace.vcd") == body(fixture / "trace.vcd")
    print("reproduced" if same else "DIFFERENT from the committed trace.vcd")
    return same


def cones(coi):
    return {t: {s["sig"]: s for s in c["sources"]} for t, c in coi["targets"].items()}


def influence(fixture, work, coi):
    meta = coi["meta"]
    cone = cones(coi)
    w = widths(fixture, coi)
    # every visible signal is a target: a signal coi.json does not list has an empty cone
    for name in w:
        if name != meta["clock"] and name not in cone:
            print(f"  note: '{name}' is not a target in coi.json: checked as having an empty cone")
            cone[name] = {}
    base = build(fixture, work, "base")
    run(base, [], "base.vcd")
    ref = read_vcd(base / "base.vcd", meta["vcd_scope"], meta["clock"])
    ok, skipped, checked = True, [], 0
    for s in sorted(cone):
        excluded = [t for t in cone if t != s and s not in cone[t]]
        if not excluded:
            continue
        b = build(fixture, work, "p_" + re.sub(r"\W", "_", s), force_code(sv_path(s), w[s]))
        if b is None:
            skipped.append(s)
            continue
        run(b, ["+pmode=1", "+pfrom=10", "+puntil=100000"], "p.vcd")
        got = read_vcd(b / "p.vcd", meta["vcd_scope"], meta["clock"])
        if got[s] == ref[s]:
            print(f"  note: forcing {s} did not change it (nothing tested)")
        for t in excluded:
            checked += 1
            if got[t] != ref[t]:
                ok = False
                first = next(i for i, (a, b2) in enumerate(zip(ref[t], got[t])) if a != b2)
                print(f"  INFLUENCE: forcing {s} changed {t} (cycle {first}), but {s} is not in its cone")
    if skipped:
        print(f"  not forceable (e.g. parameters), skipped: {', '.join(skipped)}")
    print(f"non-influence: {'ok' if ok else 'FAIL'} ({checked} (source, excluded target) pairs checked)")
    return ok


def depths(fixture, work, coi):
    meta = coi["meta"]
    cone = cones(coi)
    w = widths(fixture, coi)
    base = build(fixture, work, "base")
    refs = {}
    for seed in SEEDS:
        run(base, [f"+seed={seed}"], f"base{seed}.vcd")
        refs[seed] = read_vcd(base / f"base{seed}.vcd", meta["vcd_scope"], meta["clock"])
    claims = {(s, t, d) for t in cone for s in cone[t] for d in cone[t][s]["depths"] if s != t}
    seen = set()
    sources = sorted({s for s, _, _ in claims})
    for s in sources:
        b = build(fixture, work, "d_" + re.sub(r"\W", "_", s), force_code(sv_path(s), w[s]))
        if b is None:
            print(f"  not forceable, skipped: {s}")
            continue
        for seed in SEEDS:
            ref = refs[seed]
            for c in PULSE_CYCLES:
                for mode in (2, 3):
                    run(b, [f"+seed={seed}", f"+pmode={mode}", f"+pfrom={c}", f"+puntil={c + 1}"], "d.vcd")
                    got = read_vcd(b / "d.vcd", meta["vcd_scope"], meta["clock"])
                    diff = [i for i, (a, b2) in enumerate(zip(ref[s], got[s])) if a != b2]
                    if not diff:
                        continue
                    t0 = diff[0]
                    for (s2, t, d) in claims:
                        if s2 == s and t0 + d < len(ref[t]) and ref[t][t0 + d] != got[t][t0 + d]:
                            seen.add((s, t, d))
    missing = sorted(claims - seen)
    print(f"depth evidence: {len(claims) - len(missing)}/{len(claims)} claimed (source, target, depth) "
          f"observed")
    for s, t, d in missing:
        print(f"  not observed: {t} <- {s} @{d}")
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", choices=["reproduce", "influence", "depths"])
    ap.add_argument("fixture")
    ap.add_argument("--work")
    a = ap.parse_args()
    fixture = Path(a.fixture).resolve()
    coi = json.loads((fixture / "expected_coi.json").read_text())
    work = Path(a.work) if a.work else Path(tempfile.mkdtemp())
    work.mkdir(parents=True, exist_ok=True)
    print(f"[{fixture.name}] {a.mode}")
    ok = {"reproduce": lambda: reproduce(fixture, work),
          "influence": lambda: influence(fixture, work, coi),
          "depths": lambda: depths(fixture, work, coi)}[a.mode]()
    if not a.work:
        shutil.rmtree(work, ignore_errors=True)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
