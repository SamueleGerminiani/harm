$HARM_ROOT/build/dea \
--vcd \
--clk "sobel_tb::clk" \
--fd traces/ \
--ass-file ass/axc_ass.txt \
--tech "br" \
--metric-name "SSIM" \
--bash "scripts/simulateBR.sh" \
--at-list info/brIDS.txt \
--dump-to dea_out/ \
--push \
--cls-type "nsga2" \
--nsga2-mi 0.1 \
--min-time 30 \
--max-push-time 3600 \
--metric-direction 1 \
--gen-rand \
--max-threads 16 \
--log 
