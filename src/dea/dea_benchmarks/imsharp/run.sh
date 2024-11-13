vlib work
vlog -sv ./rtl/cs/* ./rtl/tb/imsharp_tb.v
vsim -c -voptargs="+acc" -do "vcd file sim.vcd; vcd add -r /*; run -all; vcd flush; quit" work.imsharp_tb
rm -rf work
