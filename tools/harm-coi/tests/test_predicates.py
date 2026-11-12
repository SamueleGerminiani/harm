"""H10 acceptance test A3: translation of RTL predicates into HARM propositions (D-023).

Each expected predicate (expr -> targets) is written by hand from the RTL in the test:
  - signal names as HARM sees them; constants as sized decimal literals with the width of the
    signal they are compared with; the signal on the left;
  - a 1-bit comparison as the signal or its negation;
  - a compound condition, and each of its atoms (comparisons and 1-bit signals, without '!');
  - predicates on signals that are not visible are dropped; elaboration-time conditions are not
    harvested.
"""
import json
import textwrap

from harm_coi import cli


def harvest(tmp_path, sv, recursion=0):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(sv))
    out = tmp_path / "coi.json"
    rc = cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut",
                   "--vcd-recursion", str(recursion), "--clock", "clk", "--predicates", "-o", str(out)])
    assert rc == 0
    preds = json.loads(out.read_text())["predicates"]
    for p in preds:
        assert p["origin"] == "rtl" and p["src"].startswith("m.sv:")
    return {p["expr"]: sorted(p.get("targets", [])) for p in preds}


def test_enum_constants_and_reset(tmp_path):
    # every enum value of s, the reset value, the conditions
    assert harvest(tmp_path, """
        typedef enum logic [1:0] {A = 2'd0, B = 2'd2} e_t;
        module m(input logic clk, rst, go);
          e_t s;
          always_ff @(posedge clk)
            if (rst) s <= A;
            else if (go) s <= B;
        endmodule
    """) == {"rst": ["s"], "go": ["s"], "s == 2'd0": ["s"], "s == 2'd2": ["s"]}


def test_parameter_and_constant_on_the_left(tmp_path):
    assert harvest(tmp_path, """
        module m #(parameter int LIM = 5) (input logic clk, input logic [3:0] cnt, output logic y, z, w);
          assign y = cnt > LIM;
          assign z = (4'd9 == cnt);
          assign w = (4'd3 < cnt);
        endmodule
    """) == {"cnt > 4'd5": ["y"], "cnt == 4'd9": ["z"], "cnt > 4'd3": ["w"]}


def test_unsized_literal_takes_the_signal_width(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, input logic [3:0] v, output logic z);
          assign z = (v == '0);
        endmodule
    """) == {"v == 4'd0": ["z"]}


def test_not_equal_and_less_than(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, input logic [2:0] a, input logic [3:0] b, output logic y, z);
          assign y = (a != 3'd2);
          assign z = (b < 4'd7);
        endmodule
    """) == {"a != 3'd2": ["y"], "b < 4'd7": ["z"]}


def test_one_bit_comparisons(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, e, output logic y, z);
          assign y = (e == 1'b0);
          assign z = (e != 1'b0);
        endmodule
    """) == {"!e": ["y"], "e": ["z"]}


def test_bit_select_condition(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, d, input logic [1:0] gnt, output logic p);
          always_ff @(posedge clk)
            if (gnt[0]) p <= d;
        endmodule
    """) == {"gnt[0]": ["p"]}


def test_async_reset_value(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, rst, input logic [3:0] d, output logic [3:0] q);
          always_ff @(posedge clk or posedge rst)
            if (rst) q <= 4'd3; else q <= d;
        endmodule
    """) == {"rst": ["q"], "q == 4'd3": ["q"]}


def test_compound_condition_and_atoms(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, a, b, c, d, output logic r);
          always_ff @(posedge clk)
            if (a && (b || !c)) r <= d;
        endmodule
    """) == {"a && (b || !c)": ["r"], "a": ["r"], "b": ["r"], "c": ["r"]}


def test_case_labels_without_default(tmp_path):
    assert harvest(tmp_path, """
        module m(input logic clk, a, b, input logic [1:0] sel, output logic y);
          always_comb begin
            y = 1'b0;
            case (sel)
              2'd1: y = a;
              2'd3: y = b;
            endcase
          end
        endmodule
    """) == {"sel == 2'd1": ["y"], "sel == 2'd3": ["y"]}


def test_struct_field_and_interface(tmp_path):
    assert harvest(tmp_path, """
        typedef struct packed { logic [1:0] mode; logic [2:0] val; } cfg_t;
        interface bif; logic valid; endinterface
        module m(input logic clk, input cfg_t c, input logic a, d, output logic y, z);
          bif bus ();
          assign bus.valid = a;
          always_ff @(posedge clk) if (c.mode == 2'd1) y <= d;
          always_ff @(posedge clk) if (bus.valid) z <= d;
        endmodule
    """, recursion=1) == {"c::mode == 2'd1": ["y"], "bus::valid": ["z"]}


def test_invisible_signal_is_dropped(tmp_path):
    # the condition inside u is on u::en, not visible at recursion 0
    assert harvest(tmp_path, """
        module sub(input logic clk, en, d, output logic q);
          always_ff @(posedge clk) if (en) q <= d;
        endmodule
        module m(input logic clk, en, d, output logic q);
          sub u (.clk(clk), .en(en), .d(d), .q(q));
        endmodule
    """) == {}


def test_elaboration_time_conditions_and_loop_variables(tmp_path):
    # generate if is constant in the trace; the loop condition is on a local variable
    assert harvest(tmp_path, """
        module m #(parameter int P = 1) (input logic clk, a, input logic [3:0] v, output logic y, w);
          if (P == 1) begin : g
            assign y = a;
          end
          always_comb begin
            w = 1'b0;
            for (int i = 0; i < 4; i++) w = w | v[i];
          end
        endmodule
    """) == {}


def test_reset_rule_on_a_non_reset_condition(tmp_path):
    # D-023's reset rule is structural: the first if of an always_ff whose branch assigns only
    # constants. A data condition of that shape also gives the register's value as a predicate
    assert harvest(tmp_path, """
        module m(input logic clk, x, output logic y);
          always_ff @(posedge clk)
            if (x) y <= 1'b1; else y <= 1'b0;
        endmodule
    """) == {"x": ["y"], "y": ["y"]}


def test_predicates_wider_than_harm_are_dropped(tmp_path, capsys):
    # H11c, F-L5: HARM keeps at most 511 bits of a logic signal (it truncates wider ones), so a
    # predicate with an operand or constant wider than that is dropped, with the reason
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent("""
        module m(input logic clk, input logic [1599:0] wide, input logic [510:0] edge511,
                 input logic [511:0] edge512, input logic [7:0] narrow, output logic a, b, c, d);
          assign a = (wide == 0);
          assign b = (edge511 == 0);
          assign c = (edge512 == 0);
          assign d = (narrow == 8'd3);
        endmodule
    """))
    out = tmp_path / "coi.json"
    rc = cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut", "--vcd-recursion", "0",
                   "--clock", "clk", "--predicates", "-v", "-o", str(out)])
    assert rc == 0
    exprs = {p["expr"] for p in json.loads(out.read_text())["predicates"]}
    assert exprs == {"edge511 == 511'd0", "narrow == 8'd3"}
    err = capsys.readouterr().err
    assert err.count("wider than HARM's 511-bit limit") == 2
