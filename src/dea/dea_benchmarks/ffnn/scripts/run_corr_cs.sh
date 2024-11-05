#iterate $1 times
iterations=$1

for (( i = 0; i < $1; i++ )); do
$HARM_ROOT/build/dea --csv --clk "clk" --fd traces/ --ass-file ass/axc_ass.txt --tech "cs" --metric-name "EP" --bash "scripts/simulateCS.sh" --at-list info/csIDS.txt --dump-to dea_out/ --cls-type "nsga2" --nsga2-mi 0.1 --min-time 60 --dump-dmg-vs-metric --metric-direction 0 --max-threads 16 --dont-plot --recover-diff  


python3 ../support/checkCorrelation.py --file dea_out/cs_dmg_vs_metric.csv --output dea_out/correlation_cs.csv
done
