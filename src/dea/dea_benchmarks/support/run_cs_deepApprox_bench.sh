#cd ./ffnn/
#bash scripts/simulateGolden.sh
#bash scripts/runDEA_cs.sh
#cd ..
#cp ./ffnn/dea_out/cs_nsga2.csv ./pending/ffnn/vsDeepApprox/

cd ./fft/
bash scripts/simulateGolden.sh
bash scripts/runDEA_cs.sh
cd ..
cp ./fft/dea_out/cs_nsga2.csv ./pending/fft/vsDeepApprox/


cd ./imsharp/
bash scripts/simulateGolden.sh
bash scripts/runDEA_cs.sh
cd ..
cp ./imsharp/dea_out/cs_nsga2.csv ./pending/imsharp/vsDeepApprox/

cd ./gauss_blur/
bash scripts/simulateGolden.sh
bash scripts/runDEA_cs.sh
cd ..
cp ./gauss_blur/dea_out/cs_nsga2.csv ./pending/gauss_blur/vsDeepApprox/

