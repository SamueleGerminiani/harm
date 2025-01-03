$HARM_ROOT/build/dea \
--csv \
--fd traces/ \
--ass-file ass/axc_ass.txt \
--tech "cs" \
--metric-name "PSNR" \
--bash "scripts/simulateCS.sh" \
--at-list info/csIDS.txt \
--dump-to dea_out/ \
--push \
--nsga2-nt 3 \
--cls-type "nsga2" \
--nsga2-mi 0.1 \
--max-push-time 600 \
--metric-direction 1 \
--gen-rand \
--wsilent \
--log \
--max-threads 16  
