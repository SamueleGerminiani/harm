vlib work
vlog ./rtl/cs/* ./rtl/tb/ffnn_tb.v +define+cs0 +define+SUB_cs0="mul16u_BMC"
vsim -c -voptargs="+acc" -do "vcd file sim.vcd; vcd add /*; run -all; vcd flush; quit" work.ffnn_tb
rm -rf work
