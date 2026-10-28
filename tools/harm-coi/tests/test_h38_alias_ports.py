"""H38 (the miner portfolio's FX1, part H): H34's kept name of a net is its shallowest visible name, and among those a
top input port first, then a top output port, then string order. Before, string order alone decided between a port
and a top-level wire, so on AssertLLM2's pci_bridge32 the reset input `pci_rst_i` was merged into the wire
`pci_resi_pci_rstn_in`, and `--reset pci_rst_i` stopped with "not a visible top input". Expected by hand from
tests/input/h38/ports."""
import json
from pathlib import Path

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
FIX = ROOT / "tests" / "input" / "h38" / "ports"


def _run(tmp, *extra):
    out = tmp / "coi.json"
    args = ["--top", "ports", "--files", str(FIX / "rtl" / "ports.sv"), "--vcd-scope", "tb::dut", "--vcd-recursion",
            "0", "--clock", "clk", "--aliases", "-o", str(out), *extra]
    assert cli.main(args) == 0
    return json.loads(out.read_text())


def test_ports_are_kept(tmp_path):
    assert _run(tmp_path)["aliases"] == {"o": ["aa_q"], "rst_i": ["a_rst"]}


def test_reset_input_is_visible(tmp_path):
    doc = _run(tmp_path, "--hints", str(tmp_path / "hints.json"), "--reset", "rst_i")
    assert "rst_i" in json.dumps(json.loads((tmp_path / "hints.json").read_text()))
    assert doc["aliases"]["rst_i"] == ["a_rst"]
