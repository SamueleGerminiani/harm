"""H37 test (D-045): the domain map records each asynchronous reset's edge (`reset_edges`, domains v1), so a domain's
reset polarity is known: a `negedge` control is active low, a `posedge` one active high. The miner portfolio's MC1
(its D2) builds a domain's `disable iff` from it. Expected by hand from tests/input/mc."""
import json
from pathlib import Path

import jsonschema
import pytest

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
MC = ROOT / "tests" / "input" / "mc"
EXPECTED = {"two_counters": {"clk_a": {"rst_a": ["pos"]}, "clk_b": {"rst_b": ["pos"]}},
            "cdc_fifo": {"rclk": {"rrst_n": ["neg"]}, "wclk": {"wrst_n": ["neg"]}},
            "derived": {"clk": {}, "clk_div2": {}, "gclk": {}},          # synchronous resets: no edge
            "raw_cross": {"clk_a": {}, "clk_b": {}}}


@pytest.mark.parametrize("name", sorted(EXPECTED))
def test_reset_edges(tmp_path, name):
    out = tmp_path / "d.json"
    args = ["--top", name, "--files", *map(str, sorted((MC / name / "rtl").glob("*.sv"))), "--vcd-scope", "tb::dut",
            "--vcd-recursion", "2", "--domains", str(out)]
    assert cli.main(args) == 0
    doc = json.loads(out.read_text())
    jsonschema.validate(doc, json.loads((ROOT / "doc" / "schemas" / "domains.v1.json").read_text()))
    assert {c["name"]: c["reset_edges"] for c in doc["clocks"]} == EXPECTED[name]
    for c in doc["clocks"]:
        assert sorted(c["reset_edges"]) == c["resets"]
