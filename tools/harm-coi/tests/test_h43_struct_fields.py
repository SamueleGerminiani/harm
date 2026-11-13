"""H43-struct-fields (doc/plan/H43_PLAN.md; CR1's C9-4, the open case): a packed struct's field that the trace has only
through the struct's vector (Verilator without --trace-structs) is that vector's part-select in predicates and
relations. Before, harm-coi wrote the whole vector (`s == 4'd3` for `s.hi == 4'd3`). Expected by hand from
tests/input/h43: s = {hi[7:4], lo[3:0]}; u = {f[4], in = {g[3], b[2:0]}}."""
import json
from pathlib import Path

from harm_coi import cli

ROOT = Path(__file__).resolve().parents[3]
FIX = ROOT / "tests" / "input" / "h43"


def _run(tmp, vcd):
    xml = tmp / "emitted.xml"
    args = ["--top", "st", "--files", str(FIX / "rtl" / "st.sv"), "--vcd", str(FIX / vcd), "--vcd-scope", "tb::dut",
            "--vcd-recursion", "4", "--clock", "clk", "--reset", "rst", "--relations", "--emit-config", str(xml),
            "--hints", str(tmp / "hints.json"), "--predicates", "-o", str(tmp / "coi.json")]
    assert cli.main(args) == 0
    doc = json.loads((tmp / "coi.json").read_text())
    return xml.read_text().replace("&amp;", "&"), {p["expr"] for p in doc["predicates"]}


# T1: one vector per struct
def test_t1_predicate_is_a_part_select(tmp_path):
    _, preds = _run(tmp_path, "one.vcd")
    assert "s[7:4] == 4'd3" in preds
    assert "s == 4'd3" not in preds


def test_t1_relations_are_part_selects(tmp_path):
    text, _ = _run(tmp_path, "one.vcd")
    assert "s[7:4] == $past(a, 1)" in text
    assert "s[3:0] == ($past(~a, 1) & 4'd15)" in text
    assert "q == $past(s[7:4], 1)" in text
    for wrong in ("s == $past(a, 1)", "q == $past(s, 1)"):
        assert wrong not in text


# T3: a nested struct, and a bit select of a field
def test_t3_nested_offsets(tmp_path):
    text, preds = _run(tmp_path, "one.vcd")
    assert "u[2:0] == 3'd5" in preds
    assert "z == $past(u[1], 1)" in text
    assert "u[2:0] == $past(c, 1)" in text
    assert "u == 3'd5" not in preds and "z == $past(u[1], 1)" in text


# T2: the fields traced one by one (--trace-structs): their own names, as before H43
def test_t2_fields_keep_their_names(tmp_path):
    text, preds = _run(tmp_path, "fields.vcd")
    assert "s::hi == 4'd3" in preds
    assert "s::hi == $past(a, 1)" in text
    assert "u::in::b == 3'd5" in preds
    assert "z == $past(u::in::b[1], 1)" in text
