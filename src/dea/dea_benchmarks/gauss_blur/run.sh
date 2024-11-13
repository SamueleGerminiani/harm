vlib work
vlog -sv ./rtl/cs/* ./rtl/tb/gauss_blur_tb.v
vsim -c -voptargs="+acc" -do "vcd file sim.vcd; vcd add -r /*; run -all; vcd flush; quit" work.gauss_blur_tb
rm -rf work

#gtkwave sim.vcd sf.gtkw

python3 scripts/grayscaleListTobmp.py --gs-list filtered/outPixel.txt --bmp filtered/lenaConvertedBack.bmp
feh filtered/lenaConvertedBack.bmp
