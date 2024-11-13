#iterate $1 times
iterations=$1

for (( i = 0; i < $1; i++ )); do


python3 ../support/checkCorrelation.py --file dea_out/cs_dmg_vs_metric.csv --output dea_out/correlation_cs.csv
done
