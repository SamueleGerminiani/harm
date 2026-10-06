"""H5 acceptance test A4: constructs that the H4 fixtures do not cover.

Every expected edge below is written by hand from the RTL in the test, as in the fixtures' edges.txt:
`target <- source @delay` lists the direct dependencies between visible signals, `target x` a visible
signal without sources, and `unknown x` a visible signal whose cone harm-coi cannot compute.
Depth follows HARM's sampling (D-005): a register is one cycle behind its inputs.
"""
import textwrap

import pytest

from harm_coi import cli


def edges(tmp_path, sv, *extra, vcd=None, recursion=0):
    src = tmp_path / "m.sv"
    src.write_text(textwrap.dedent(sv))
    out = tmp_path / "edges.txt"
    argv = ["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut",
            "--vcd-recursion", str(recursion), "--clock", "clk", "--max-depth", "3",
            "--edges", str(out), "-o", str(tmp_path / "coi.json"), *extra]
    if vcd is not None:
        (tmp_path / "t.vcd").write_text(textwrap.dedent(vcd))
        argv += ["--vcd", str(tmp_path / "t.vcd")]
    assert cli.main(argv) == 0
    lines = set()
    for line in out.read_text().splitlines():
        line = line.split("#")[0].strip()
        if line and "=" not in line:
            lines.add(" ".join(line.split()))
    return lines


def E(text):
    return {" ".join(x.split()) for x in textwrap.dedent(text).strip().splitlines()}


def test_case_with_default(tmp_path):
    # the selector is a control dependency of every branch
    assert edges(tmp_path, """
        module m(input logic clk, a, b, input logic [1:0] sel, output logic y);
          always_comb
            case (sel)
              2'd0: y = a;
              2'd1: y = b;
              default: y = 1'b0;
            endcase
        endmodule
    """) == E("""
        target a
        target b
        target sel
        y <- a @0
        y <- b @0
        y <- sel @0
    """)


def test_nested_if_in_register(tmp_path):
    # both conditions control r; r holds its value when !a
    assert edges(tmp_path, """
        module m(input logic clk, a, b, c, d, output logic r);
          always_ff @(posedge clk)
            if (a) begin
              if (b) r <= c;
              else   r <= d;
            end
        endmodule
    """) == E("""
        target a
        target b
        target c
        target d
        r <- a @1
        r <- b @1
        r <- c @1
        r <- d @1
        r <- r @1
    """)


def test_conditional_operator(tmp_path):
    assert edges(tmp_path, """
        module m(input logic clk, s, a, b, output logic y);
          assign y = s ? a : b;
        endmodule
    """) == E("""
        target s
        target a
        target b
        y <- s @0
        y <- a @0
        y <- b @0
    """)


def test_function_reads_arguments_and_module_signals(tmp_path):
    # f reads its argument and the module-level g; its local t is not a signal
    assert edges(tmp_path, """
        module m(input logic clk, a, k, output logic y);
          logic g;
          function automatic logic f(input logic p);
            logic t;
            t = p ^ g;
            return t;
          endfunction
          assign g = k;
          assign y = f(a);
        endmodule
    """) == E("""
        target a
        target k
        g <- k @0
        y <- a @0
        y <- g @0
    """)


def test_blocking_temporary(tmp_path):
    # y reads t's new value, a & b: y depends on a, b and k, not on t
    assert edges(tmp_path, """
        module m(input logic clk, a, b, k, output logic y);
          logic t;
          always_comb begin
            t = a & b;
            y = t | k;
          end
        endmodule
    """) == E("""
        target a
        target b
        target k
        t <- a @0
        t <- b @0
        y <- a @0
        y <- b @0
        y <- k @0
    """)


def test_bit_select_index_is_a_source(tmp_path):
    assert edges(tmp_path, """
        module m(input logic clk, input logic [3:0] v, input logic [1:0] sel, output logic y);
          assign y = v[sel];
        endmodule
    """) == E("""
        target v
        target sel
        y <- v @0
        y <- sel @0
    """)


def test_partial_register_write_keeps_other_bits(tmp_path):
    assert edges(tmp_path, """
        module m(input logic clk, a, output logic [3:0] r);
          always_ff @(posedge clk) r[0] <= a;
        endmodule
    """) == E("""
        target a
        r <- a @1
        r <- r @1
    """)


def test_async_reset(tmp_path):
    # an asynchronous reset changes q before the next sample (depth 0), and is also sampled at
    # the clock edge (depth 1); the clock is found whatever the order of the event list
    assert edges(tmp_path, """
        module m(input logic clk, rst, d, output logic q, q2);
          always_ff @(posedge clk or posedge rst)
            if (rst) q <= 1'b0; else q <= d;
          always_ff @(posedge rst or posedge clk)
            if (rst) q2 <= 1'b0; else q2 <= d;
        endmodule
    """) == E("""
        target rst
        target d
        q <- d @1
        q <- rst @0
        q <- rst @1
        q2 <- d @1
        q2 <- rst @0
        q2 <- rst @1
    """)


def test_for_loop_in_always_comb(tmp_path):
    # the loop variable is local to the procedure: not a signal
    assert edges(tmp_path, """
        module m(input logic clk, input logic [3:0] v, output logic y);
          always_comb begin
            y = 1'b0;
            for (int i = 0; i < 4; i++) y = y | v[i];
          end
        endmodule
    """) == E("""
        target v
        y <- v @0
    """)


def test_always_latch_is_unknown(tmp_path):
    # latches are not supported: q is unknown, and so is z, whose cone goes through q
    assert edges(tmp_path, """
        module m(input logic clk, en, d, a, output logic q, z);
          always_latch if (en) q = d;
          assign z = q & a;
        endmodule
    """) == E("""
        target en
        target d
        target a
        unknown q
        unknown z
    """)


def test_incomplete_always_comb_is_unknown(tmp_path):
    # y is not assigned on every path: a latch, so its cone is unknown
    assert edges(tmp_path, """
        module m(input logic clk, en, d, output logic y);
          always_comb if (en) y = d;
        endmodule
    """) == E("""
        target en
        target d
        unknown y
    """)


STRUCT_SV = """
    typedef struct packed { logic [1:0] mode; logic [2:0] val; } cfg_t;
    module m(input logic clk, input logic [1:0] mm, input logic [2:0] x, output cfg_t c,
             output logic [1:0] z);
      always_ff @(posedge clk) begin
        c.mode <= mm;
        c.val  <= x;
      end
      assign z = c.mode;
    endmodule
"""


def test_struct_fields_without_trace(tmp_path):
    # without --vcd, packed struct fields are signals (Verilator --trace-structs naming, D-013)
    assert edges(tmp_path, STRUCT_SV, recursion=1) == E("""
        target mm
        target x
        c::mode <- mm @1
        c::val <- x @1
        z <- c::mode @0
    """)


def test_struct_dumped_as_one_vector(tmp_path):
    # a trace that dumps c as one variable (e.g. Icarus): c is one signal, the union of its fields
    vcd = """
        $scope module tb $end
        $scope module dut $end
        $var wire 1 ! clk $end
        $var wire 2 " mm $end
        $var wire 3 # x $end
        $var wire 5 $ c $end
        $var wire 2 % z $end
        $upscope $end
        $upscope $end
        $enddefinitions $end
        #0
        0!
    """
    assert edges(tmp_path, STRUCT_SV, vcd=vcd, recursion=1) == E("""
        target mm
        target x
        c <- mm @1
        c <- x @1
        z <- c @0
    """)


def test_trace_signal_unknown_to_the_rtl(tmp_path):
    # a visible signal of the trace that the RTL analysis does not produce is unknown, never dropped
    vcd = """
        $scope module tb $end
        $scope module dut $end
        $var wire 1 ! clk $end
        $var wire 1 " a $end
        $var wire 1 # y $end
        $var wire 32 $ extra $end
        $upscope $end
        $upscope $end
        $enddefinitions $end
        #0
        0!
    """
    assert edges(tmp_path, """
        module m(input logic clk, a, output logic y);
          assign y = !a;
        endmodule
    """, vcd=vcd) == E("""
        target a
        y <- a @0
        unknown extra
    """)


def test_no_clock_found_is_an_error(tmp_path):
    src = tmp_path / "m.sv"
    src.write_text("module m(input logic a, output logic y); assign y = a; endmodule\n")
    rc = cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut",
                   "--vcd-recursion", "0", "-o", str(tmp_path / "coi.json")])
    assert rc != 0


def test_elaboration_error_is_an_error(tmp_path):
    src = tmp_path / "m.sv"
    src.write_text("module m(input logic clk, output logic y); assign y = nosuch; endmodule\n")
    rc = cli.main(["--top", "m", "--files", str(src), "--vcd-scope", "tb::dut",
                   "--vcd-recursion", "0", "-o", str(tmp_path / "coi.json")])
    assert rc != 0
