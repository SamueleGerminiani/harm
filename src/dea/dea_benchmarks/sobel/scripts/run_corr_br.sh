#iterate $1 times
iterations=$1

for (( i = 0; i < $1; i++ )); do
$HARM_ROOT/build/dea --vcd --clk "sobel_tb::clk" --fd traces/ --ass-file ass/axc_ass.txt --tech "br" --metric-name "SSIM" --bash "scripts/simulateBR.sh" --at-list info/brIDS.txt --dump-to dea_out/ --cls-type "nsga2" --nsga2-mi 0.1 --min-time 30 --dump-dmg-vs-metric --metric-direction 1 --max-threads 16 --dont-plot --recover-diff


python3 ../support/checkCorrelation.py --file dea_out/br_dmg_vs_metric.csv --output dea_out/correlation_br.csv
done
