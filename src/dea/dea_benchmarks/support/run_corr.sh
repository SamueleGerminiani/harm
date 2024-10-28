nIterations=$1

find . -type f \( -name "diff_sr.csv" -o -name "diff_br.csv" \) -exec rm {} +
find . -type f \( -name "correlation_sr.csv" -o -name "correlation_br.csv" \) -exec rm {} +

cd ./sobel/
bash scripts/run_corr_sr.sh "$nIterations"
bash scripts/run_corr_br.sh "$nIterations"
cd ..

cd ./inversek2j/
bash scripts/run_corr_sr.sh "$nIterations"
bash scripts/run_corr_br.sh "$nIterations"
cd ..


cd ./brentKung32b/
bash scripts/run_corr_sr.sh "$nIterations"
bash scripts/run_corr_br.sh "$nIterations"
cd ..

cd ./fir/
bash scripts/run_corr_sr.sh "$nIterations"
bash scripts/run_corr_br.sh "$nIterations"
cd ..

cd ./ffnn/
bash scripts/run_corr_sr.sh "$nIterations"
bash scripts/run_corr_br.sh "$nIterations"
cd ..

#------------------------

echo "Sobel BR----------------------------"
cat ./sobel/dea_out/correlation_br.csv
echo "Sobel SR----------------------------"
cat ./sobel/dea_out/correlation_sr.csv
echo "===================================="

echo "Inversek2j BR----------------------------"
cat ./inversek2j/dea_out/correlation_br.csv
echo "Inversek2j SR----------------------------"
cat ./inversek2j/dea_out/correlation_sr.csv
echo "===================================="

echo "BrentKung32b BR----------------------------"
cat ./brentKung32b/dea_out/correlation_br.csv
echo "BrentKung32b SR----------------------------"
cat ./brentKung32b/dea_out/correlation_sr.csv
echo "===================================="

echo "FIR BR----------------------------"
cat ./fir/dea_out/correlation_br.csv
echo "FIR SR----------------------------"
cat ./fir/dea_out/correlation_sr.csv    

echo "FFNN BR----------------------------"
cat ./ffnn/dea_out/correlation_br.csv
echo "FFNN SR----------------------------"
cat ./ffnn/dea_out/correlation_sr.csv    
