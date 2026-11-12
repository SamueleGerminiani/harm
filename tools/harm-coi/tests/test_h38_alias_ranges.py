"""H38 (the miner portfolio's FX1): a net whose names are declared with different ranges (`[19:19]` at the top,
`[31:31]` in a submodule) is one variable under its kept name (H34), so a bit or range select the submodule writes is
rebased to the kept name's range. Before, `m[31]` became `am[31]`, outside `am`'s `[19:19]`, and HARM stopped on
AssertLLM2's pci_bridge32 ("Index 31 is outside the declared range [19:19] of 'conf_wb_am1_out'"). Expected by hand
from tests/input/h38/ranges."""
import json
from pathlib import Path

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
FIX = ROOT / "tests" / "input" / "h38" / "ranges"


def _props(tmp):
    xml = tmp / "emitted.xml"
    args = ["--top", "ranges", "--files", str(FIX / "rtl" / "ranges.sv"), "--vcd-scope", "tb::dut",
            "--vcd-recursion", "1", "--clock", "clk", "--aliases", "--relations", "--emit-config", str(xml),
            "--hints", str(tmp / "hints.json"),
            "-o", str(tmp / "coi.json")]
    assert cli.main(args) == 0
    return xml.read_text(), json.loads((tmp / "coi.json").read_text())


def test_aliases_merged(tmp_path):
    _, doc = _props(tmp_path)
    assert doc["aliases"]["am"] == ["u::m"]
    assert doc["aliases"]["aw"] == ["u::w"]


def test_bit_select_rebased(tmp_path):
    text, _ = _props(tmp_path)
    assert "am[19]" in text
    assert "am[31]" not in text


def test_range_select_rebased(tmp_path):
    text, _ = _props(tmp_path)
    assert "aw[2:1]" in text
    assert "aw[6:5]" not in text
