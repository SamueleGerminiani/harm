vlib work
vlog -sv ./rtl/tb/fir_tb.v ./rtl/sr/fir_original.v
vsim -c -voptargs="+acc" -do "vcd file sim.vcd; vcd add /*; run -all; vcd flush; quit" work.fir_tb
rm -rf work
