vlib work
vlog ./rtl/tb/tb_fir_v.v ./rtl/original/fir_v.v
vsim -c -voptargs="+acc" -do "vcd file sim.vcd; vcd add /*; run -all; vcd flush; quit" work.tb_FIR
rm -rf work
