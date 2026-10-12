"""H22 acceptance tests B1-B4 (harm-coi --hints, hints v1, D-036).

B1 roles and B2 placement are compared with the hand-written `expected_hints.txt` of each fixture; B3 checks the
schema and that harm-coi without --hints writes what it wrote before H22 (`data/h22_default`, from `dev` @ 0663902);
B4 runs the independent oracle `tests/coi/hints_oracle.py` on each fixture."""
import importlib.util
import json
import re
from pathlib import Path

import jsonschema
import pytest

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
DATA = Path(__file__).resolve().parent / "data" / "h22_default"
FIXTURES = ["counter", "arbiter", "fsm", "hier", "multipath", "structs", "constructs"]
_spec = importlib.util.spec_from_file_location("hints_oracle", ROOT / "tests" / "coi" / "hints_oracle.py")
oracle = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(oracle)


def fixture(name):
    d = ROOT / "tests" / "input" / ("h5" if name == "constructs" else "coi") / name
    meta = (d / ("meta.txt" if name == "constructs" else "edges.txt")).read_text()
    r = re.search(r"^vcd_recursion = (\d+)", meta, re.M).group(1)
    return d, ["--top", name, "--files", *map(str, sorted((d / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
               "--vcd-recursion", r, "--vcd", str(d / "trace.vcd")]


def run(tmp_path, name, *extra, hints=True):
    _, args = fixture(name)
    out = tmp_path / f"{name}_coi.json"
    argv = [*args, "--emit-config", str(tmp_path / f"{name}.xml"), "-o", str(out), *extra]
    if hints:
        argv += ["--hints", str(tmp_path / f"{name}_hints.json")]
    assert cli.main(argv) == 0
    h = json.loads((tmp_path / f"{name}_hints.json").read_text()) if hints else None
    return json.loads(out.read_text()), h


def expected(name):
    d, _ = fixture(name)
    roles, props = {}, {}
    for line in (d / "expected_hints.txt").read_text().splitlines():
        if line.startswith("role "):
            w = line.split()
            roles[w[1]] = (w[2], "control" in w[3:])
        elif line.startswith("prop "):
            expr, cls = line[5:].rsplit(" -> ", 1)
            props[expr] = [] if cls == "-" else cls.split(",")
    return roles, props


@pytest.mark.parametrize("name", FIXTURES)
def test_b1_roles(tmp_path, name):
    _, h = run(tmp_path, name)
    roles, _ = expected(name)
    assert {k: (v["role"], v["control"]) for k, v in h["roles"].items()} == roles
    assert all(v["origin"] == "rtl" and v["rule"] for v in h["roles"].values())


@pytest.mark.parametrize("name", FIXTURES)
def test_b2_placement_and_classes(tmp_path, name):
    _, h = run(tmp_path, name)
    roles, props = expected(name)
    assert {p["expr"]: p["consequent"] for p in h["propositions"]} == props
    cls = {"comb": "comb", "unknown": "comb", "state": "state"}
    for c, d in h["classes"].items():
        assert sorted(d["targets"]) == sorted(k for k, (r, _) in roles.items() if cls.get(r) == c)
    assert h["classes"]["comb"]["template"] == "G({..#1&..}|-> P0(1))"
    assert h["classes"]["state"]["template"] == "G({..#1&..}|=> P0(2))"
    assert {d["dtLimits"] for d in h["classes"].values()} == {"5D,3W,15A,-0.1E,U"}  # Q2 (a): unchanged


def test_b2_reset_option(tmp_path):
    # counter's synchronous reset is an input unless named with --reset
    _, h = run(tmp_path, "counter", "--reset", "rst")
    assert h["roles"]["rst"]["role"] == "reset" and h["meta"]["reset"] == ["rst"]
    assert {p["expr"]: p["consequent"] for p in h["propositions"]}["rst"] == []


def test_b2_emitted_config(tmp_path):
    run(tmp_path, "arbiter")
    xml = (tmp_path / "arbiter.xml").read_text()
    assert '<prop exp="req == 2\'d3" loc="a, dt" origin="rtl"/>' in xml
    assert '<prop exp="gnt[0]" loc="a, c, dt, 1" origin="rtl"/>' in xml
    assert '<prop exp="!prio" loc="a, c, dt, 2" origin="rtl"/>' in xml
    assert 'exp="G({..#1&amp;..}|-&gt; P0(1))"' in xml and 'exp="G({..#1&amp;..}|=&gt; P0(2))"' in xml
    run(tmp_path, "arbiter", "--hints-use", "placement")
    xml = (tmp_path / "arbiter.xml").read_text()
    assert '<prop exp="req == 2\'d3" loc="a, dt" origin="rtl"/>' in xml
    assert '<prop exp="gnt[0]" loc="a, c, dt" origin="rtl"/>' in xml
    assert xml.count("<template ") == 1 and 'exp="G({..#1&amp;..}|-&gt; P0)"' in xml


@pytest.mark.parametrize("name", FIXTURES)
def test_b3_schema_and_default_unchanged(tmp_path, name):
    _, h = run(tmp_path, name)
    schema = json.loads((ROOT / "doc" / "schemas" / "hints.v1.json").read_text())
    jsonschema.validate(h, schema)
    with_hints = (tmp_path / f"{name}_coi.json").read_text()
    plain = tmp_path / "plain"
    plain.mkdir()
    run(plain, name, hints=False)
    assert (plain / f"{name}_coi.json").read_text() == with_hints == (DATA / f"{name}_coi.json").read_text()
    assert (plain / f"{name}.xml").read_text() == (DATA / f"{name}.xml").read_text()


@pytest.mark.parametrize("name", FIXTURES)
def test_b4_oracle(tmp_path, name):
    coi, h = run(tmp_path, name)
    assert oracle.check(coi, h) == []
