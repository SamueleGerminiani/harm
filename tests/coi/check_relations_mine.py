#!/usr/bin/env python3
"""H24 R4, R5, R6, R10: harm-coi --relations on a fixture, then HARM.

- R4 (--oracle): every unconditional relation of the emitted configuration (the propositions of the fixed domains 4
  and 5) holds on the fixture's trace, evaluated by this script (not HARM): at every sampled cycle t whose reset was
  inactive at t-1 (domain 4, registered: `$past` reads t-1) or at t (domain 5, combinational);
- R5, R6, R10 (--expect REGEX, repeatable): HARM, with the emitted configuration (and --extra lines, and the cone's
  mode set by --mode), mines an assertion whose SVA text matches each REGEX.

  check_relations_mine.py FIXTURE_DIR --python PY --harm HARM --out DIR [--oracle] [--expect REGEX ...]
                          [--extra XML_LINE ...] [--mode rank|filter]"""
import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
UNESC = {"&amp;": "&", "&lt;": "<", "&gt;": ">", "&quot;": '"'}


def un(s):
    for k, v in UNESC.items():
        s = s.replace(k, v)
    return s


# ---------------------------------------------------------------- the trace, sampled at each rising clock edge
def samples(vcd: Path, scope: str, clock: str) -> list[dict[str, int]]:
    """the values just before each rising edge of the clock (the changes of the edge's own time step left out), as
    HARM samples them"""
    want = scope.split("::")
    stack, names, cur, out, clk_id, last = [], {}, {}, [], None, None
    lines = vcd.read_text().splitlines()
    i = 0
    for i, line in enumerate(lines):
        t = line.split()
        if not t:
            continue
        if t[0] == "$scope":
            stack.append(t[2])
        elif t[0] == "$upscope":
            stack.pop()
        elif t[0] == "$var" and stack == want:
            names.setdefault(t[3], []).append(t[4])
            if t[4] == clock:
                clk_id = t[3]
        elif t[0] == "$enddefinitions":
            break
    before = {}
    for line in lines[i + 1:]:
        s = line.strip()
        if not s or s[0] == "$":
            continue
        if s[0] == "#":
            before = dict(cur)
            continue
        val, ident = (s[1:].split() if s[0] in "bB" else (s[0], s[1:]))
        v = int(val.replace("x", "0").replace("z", "0").replace("X", "0").replace("Z", "0"), 2)
        if ident == clk_id:
            if last == 0 and v == 1:
                out.append(before)
            last = v
        for n in names.get(ident, []):
            cur[n] = v
    return out


# ---------------------------------------------------------------- HARM's proposition syntax, evaluated
TOK = re.compile(r"\s*(\d+'s?[dbh][0-9a-fA-F_]+|\d+|\$past|\$fell|\$rose|[A-Za-z_][\w$]*|<<|>>|==|!=|<=|>=|&&|\|\||[()\[\]:?,+\-*&|^~!<>])")
BIN = [("||",), ("&&",), ("|",), ("^",), ("&",), ("==", "!="), ("<", "<=", ">", ">="), ("<<", ">>"), ("+", "-"), ("*",)]


class Expr:
    def __init__(self, text):
        self.toks = [m.group(1) for m in TOK.finditer(text)]
        if "".join(self.toks) != re.sub(r"\s+", "", text):
            raise ValueError(f"cannot tokenise {text!r}")
        self.i = 0
        self.tree = self.ternary()
        if self.i != len(self.toks):
            raise ValueError(f"trailing tokens in {text!r}")

    def peek(self):
        return self.toks[self.i] if self.i < len(self.toks) else None

    def eat(self, t=None):
        x = self.toks[self.i]
        if t is not None and x != t:
            raise ValueError(f"expected {t}, got {x}")
        self.i += 1
        return x

    def ternary(self):
        c = self.binary(0)
        if self.peek() == "?":
            self.eat("?")
            a = self.ternary()
            self.eat(":")
            b = self.ternary()
            return ("?", c, a, b)
        return c

    def binary(self, lvl):
        if lvl == len(BIN):
            return self.unary()
        left = self.binary(lvl + 1)
        while self.peek() in BIN[lvl]:
            op = self.eat()
            left = (op, left, self.binary(lvl + 1))
        return left

    def unary(self):
        if self.peek() in ("!", "~", "-"):
            op = self.eat()
            return ("u" + op, self.unary())
        return self.postfix(self.atom())

    def postfix(self, a):
        while self.peek() == "[":
            self.eat("[")
            hi = int(self.eat())
            lo = hi
            if self.peek() == ":":
                self.eat(":")
                lo = int(self.eat())
            self.eat("]")
            a = ("sel", a, hi, lo)
        return a

    def atom(self):
        t = self.eat()
        if t == "(":
            e = self.ternary()
            self.eat(")")
            return e
        if t in ("$past", "$fell", "$rose"):
            self.eat("(")
            e = self.ternary()
            n = 1
            if self.peek() == ",":
                self.eat(",")
                n = int(self.eat())
            self.eat(")")
            return (t, e, n)
        if m := re.fullmatch(r"(\d+)'(s?)([dbh])([0-9a-fA-F_]+)", t):
            return ("const", int(m.group(4).replace("_", ""), {"d": 10, "b": 2, "h": 16}[m.group(3)]))
        if t.isdigit():
            return ("const", int(t))
        return ("sig", t)


def ev(e, tr, t):
    k = e[0]
    if k == "const":
        return e[1]
    if k == "sig":
        return tr[t][e[1]]
    if k == "$past":
        return ev(e[1], tr, t - e[2])
    if k == "$fell":
        return int(ev(e[1], tr, t - 1) != 0 and ev(e[1], tr, t) == 0)
    if k == "$rose":
        return int(ev(e[1], tr, t - 1) == 0 and ev(e[1], tr, t) != 0)
    if k == "sel":
        return (ev(e[1], tr, t) >> e[3]) & ((1 << (e[2] - e[3] + 1)) - 1)
    if k == "?":
        return ev(e[2], tr, t) if ev(e[1], tr, t) else ev(e[3], tr, t)
    if k[0] == "u":
        v = ev(e[1], tr, t)
        return {"u!": int(not v), "u~": ~v, "u-": -v}[k]
    a, b = ev(e[1], tr, t), ev(e[2], tr, t)
    return {"||": int(bool(a or b)), "&&": int(bool(a and b)), "|": a | b, "^": a ^ b, "&": a & b,
            "==": int(a == b), "!=": int(a != b), "<": int(a < b), "<=": int(a <= b), ">": int(a > b),
            ">=": int(a >= b), "<<": a << b, ">>": a >> b, "+": a + b, "-": a - b, "*": a * b}[k]


# ---------------------------------------------------------------- the run
def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("fixture")
    ap.add_argument("--python", required=True)
    ap.add_argument("--harm", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--oracle", action="store_true")
    ap.add_argument("--expect", action="append", default=[])
    ap.add_argument("--extra", action="append", default=[])
    ap.add_argument("--mode", choices=["rank", "filter"], default="rank")
    a = ap.parse_args()
    f = Path(a.fixture).resolve()
    meta = dict(re.findall(r"^(\w+) = (\S+)", (f / "meta.txt").read_text(), re.M))
    name, rst = meta["top"], meta.get("reset")
    out = Path(a.out) / f"h24_{name}"
    out.mkdir(parents=True, exist_ok=True)
    (out / "info.json").unlink(missing_ok=True)
    env = {**os.environ, "PYTHONPATH": str(ROOT / "tools" / "harm-coi" / "src")}
    cmd = [a.python, "-m", "harm_coi", "--top", name, "--files", *map(str, sorted((f / "rtl").glob("*.sv"))),
           "--vcd-scope", meta["vcd_scope"], "--vcd-recursion", meta["vcd_recursion"], "--vcd", str(f / "trace.vcd"),
           "--clock", meta["clock"], "--hints", str(out / "hints.json"), "--relations",
           "--emit-config", str(out / "cfg.xml"), "-o", str(out / "coi.json")]  # fmt: skip
    if rst:
        cmd += ["--reset", rst]
    r = subprocess.run(cmd, capture_output=True, text=True, env=env)
    if r.returncode:
        print(f"{name}: harm-coi failed: {r.stderr[-800:]}")
        return 1
    xml = (out / "cfg.xml").read_text().replace('mode="rank"', f'mode="{a.mode}"')
    xml = xml.replace("    </context>", "".join(f"        {x}\n" for x in a.extra) + "    </context>")
    (out / "cfg.xml").write_text(xml)
    bad = []
    if a.oracle:
        tr = samples(f / "trace.vcd", meta["vcd_scope"], meta["clock"])
        n = 0
        for exp, loc in re.findall(r'<prop exp="([^"]*)" loc="([^"]*)"', xml):
            dom = [x.strip() for x in loc.split(",")]
            if "4" not in dom and "5" not in dom:
                continue
            n += 1
            e = Expr(un(exp))
            lag = 1 if "4" in dom else 0
            for t in range(2, len(tr)):
                if rst and tr[t - lag].get(rst, 0):
                    continue
                if not ev(e.tree, tr, t):
                    bad.append(f"R4: {un(exp)} false at sample {t}")
                    break
        print(f"{name}: R4 checked {n} unconditional relations on {len(tr)} samples")
    if a.expect:
        cmd = [a.harm, "--vcd", str(f / "trace.vcd"), "--clk", meta["clock"], "--vcd-ss", meta["vcd_scope"],
               "--vcd-r", meta["vcd_recursion"], "--conf", str(out / "cfg.xml"), "--max-threads", "2", "--sva",
               "--psilent", "--isilent", "--dump-assertion-info", str(out / "info.json")]  # fmt: skip
        if rst:
            cmd += ["--reset", rst]
        h = subprocess.run(cmd, capture_output=True, text=True, cwd=out)
        (out / "harm.log").write_text(h.stdout + h.stderr)
        if h.returncode or not (out / "info.json").exists():
            print(f"{name}: HARM exit {h.returncode}, see {out / 'harm.log'}")
            return 1
        texts = [x["text"] for x in json.loads((out / "info.json").read_text())["assertions"]]
        for rx in a.expect:
            if not any(re.search(rx, t) for t in texts):
                bad.append(f"no assertion matches {rx!r}")
        print(f"{name}: {len(texts)} assertions")
    for b in bad:
        print(f"{name}: {b}")
    print(f"{name}: {'FAIL' if bad else 'ok'}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
