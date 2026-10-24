"""H34 tests T1-T3 and T5 (`--aliases`, D-042): one HARM name per net that crosses module ports. Every expected class
is written by hand from the RTL in the test or in the fixture:
  - a port connection or `assign a = b` whose other side is a plain reference to one signal of an equivalent type is
    one net; an operator, a select, a constant, a width change or an inout is not;
  - the kept name is the shallowest visible name of the class, ties broken by string order.
T1 the classes on tests/input/h34/aliases; T2 the emitted configuration on it; T3 the output without --aliases, and
the classes of the earlier fixtures; T5 determinism."""
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import pytest

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
SRC = Path(__file__).resolve().parents[1] / "src"
FIXTURE = ROOT / "tests" / "input" / "h34" / "aliases"
EARLIER = {"counter": "coi", "arbiter": "coi", "fsm": "coi", "hier": "coi", "multipath": "coi", "structs": "coi",
           "constructs": "h5"}
PROP = re.compile(r'<prop exp="([^"]*)"')
UNESC = {"&amp;": "&", "&lt;": "<", "&gt;": ">", "&quot;": '"'}

ALIASES = {"x": ["u_mid::a", "u_mid::u_leaf::a"],
           "d": ["u_mid::d", "u_mid::u_leaf::d"],
           "rst": ["u_mid::rst", "u_mid::u_leaf::rst"],
           "q": ["u_mid::q", "u_mid::u_leaf::q"],
           "r": ["u_mid::r", "u_mid::u_leaf::r"],
           "w": ["y"]}  # w = y: both at the top, w first in string order
NOT_MERGED = ["u_or::a", "u_or::rst", "u_or::d", "u_wide::a", "u_wide::rst", "u_wide::d", "io", "u_pad::io",
              "u_mid::clk", "u_mid::u_leaf::clk"]
EARLIER_ALIASES = {"hier": {"dout": ["g[2]::w"]},           # assign dout = g[N-1].w (the stages' ports: invisible)
                   "multipath": {"rb": ["z"]},               # assign z = rb
                   "constructs": {"a": ["bus::valid"], "g": ["k"], "o": ["u::o"]}}  # assign bus.valid = a, g = k, .o(o)


def un(s):
    for k, v in UNESC.items():
        s = s.replace(k, v)
    return s


def args(d, recursion=None):
    meta = next(p for p in (d / "meta.txt", d / "edges.txt") if p.exists()).read_text()
    r = recursion or re.search(r"^vcd_recursion = (\d+)", meta, re.M).group(1)
    top = re.search(r"^top = (\S+)", meta, re.M).group(1)
    return ["--top", top, "--files", *map(str, sorted((d / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
            "--vcd-recursion", str(r), "--vcd", str(d / "trace.vcd"), "--clock", "clk"]


def run(tmp_path, d, *extra, tag="out"):
    out, xml = tmp_path / f"{tag}_coi.json", tmp_path / f"{tag}.xml"
    assert cli.main([*args(d), "--emit-config", str(xml), "--hints", str(tmp_path / f"{tag}_hints.json"),
                     "--relations", "-o", str(out), *extra]) == 0
    return json.loads(out.read_text()), xml.read_text()


# T1: the classes, the kept name, and what is not merged
def test_t1_classes(tmp_path):
    doc, _ = run(tmp_path, FIXTURE, "--aliases")
    assert doc["aliases"] == ALIASES
    merged = {n for ns in doc["aliases"].values() for n in ns}
    for n in NOT_MERGED:
        assert n not in merged and n not in doc["aliases"], n


# T2: the configuration names no merged copy, has no two predicates with one text, and no cone a zero-delay self edge
def test_t2_configuration(tmp_path):
    doc, xml = run(tmp_path, FIXTURE, "--aliases")
    props = [un(p) for p in PROP.findall(xml)]
    assert len(props) == len(set(props))
    copies = {n for ns in ALIASES.values() for n in ns}
    word = re.compile(r"[\w:\[\]]+")
    for p in props:
        assert not copies & set(word.findall(p)), p
        assert not re.fullmatch(r"(\S+) == \1", p), p     # w = y is no relation `w == w`
    for t, v in doc["targets"].items():
        assert t not in copies
        assert not any(s["sig"] == t and 0 in s["depths"] for s in v["sources"]), t
    assert any(p in ("x", "!x") for p in props)            # the leaves' condition `a`, under its kept name


# T3: without --aliases the output is today's (the copies' names, no `aliases`); the earlier fixtures' classes
def test_t3_off_is_unchanged(tmp_path):
    doc, xml = run(tmp_path, FIXTURE)
    assert "aliases" not in doc
    assert any("u_mid::u_leaf::a" in un(p) for p in PROP.findall(xml))


@pytest.mark.parametrize("name", sorted(EARLIER))
def test_t3_earlier_fixtures(tmp_path, name):
    d = ROOT / "tests" / "input" / EARLIER[name] / name
    off, off_xml = run(tmp_path, d, tag="off")
    on, on_xml = run(tmp_path, d, "--aliases", tag="on")
    assert on.pop("aliases", {}) == EARLIER_ALIASES.get(name, {})
    if name not in EARLIER_ALIASES:
        assert on == off and on_xml == off_xml.replace('file="off_coi.json"', 'file="on_coi.json"')


# T5: the same bytes under two hash seeds
def test_t5_deterministic(tmp_path):
    outs = []
    for seed in ("1", "2"):
        d = tmp_path / seed
        d.mkdir()
        cmd = [sys.executable, "-m", "harm_coi", *args(FIXTURE), "--aliases", "--relations", "--emit-config",
               str(d / "c.xml"), "--hints", str(d / "h.json"), "-o", "coi.json"]
        r = subprocess.run(cmd, cwd=d, capture_output=True, text=True,
                           env={**os.environ, "PYTHONHASHSEED": seed, "PYTHONPATH": str(SRC)})
        assert r.returncode == 0, r.stderr
        outs.append([(d / f).read_bytes() for f in ("coi.json", "c.xml", "h.json")])
    assert outs[0] == outs[1]
