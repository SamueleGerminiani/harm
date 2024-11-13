vlib work
vlog -sv ./rtl/cs/* ./rtl/tb/fft_tb.v
vsim -c -voptargs="+acc" -do "vcd file sim.vcd; vcd add -r /*; run -all; vcd flush; quit" work.fft_tb
rm -rf work
