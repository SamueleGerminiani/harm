# Regression cases: the example command lines from examples/CMakeLists.txt, without --dump-to and
# --max-threads (run_case.sh adds both). Paths must be absolute: each case runs in a scratch directory.
#
# harm_case(<name> [SLOW] ARGS <harm args...>)

set(EX ${CMAKE_SOURCE_DIR}/examples)

harm_case(vendingMachine ARGS --vcd ${EX}/vendingMachine/vendingMachine.vcd --clk clk --conf ${EX}/vendingMachine/vendingMachineConfig.xml --vcd-ss machine_bench::machine_)
harm_case(fsm ARGS --vcd ${EX}/fsmSVT/fsm.vcd --clk clk --conf ${EX}/fsmSVT/fsm.xml --vcd-r 1 --vcd-ss tbench_top)
harm_case(multiTrace ARGS --csv-dir ${EX}/multiTrace/csv/ --conf ${EX}/multiTrace/multiTrace.xml)
harm_case(nonBoolDT ARGS --csv ${EX}/nonBoolDT/nonBooleanDT.csv --conf ${EX}/nonBoolDT/nonBooleanDT.xml)
harm_case(simpleNonBoolDT ARGS --csv ${EX}/simpleNonBoolDT/simpleNonBoolDT.csv --conf ${EX}/simpleNonBoolDT/simpleNonBoolDT.xml)
harm_case(paperRE ARGS --spotltl --csv ${EX}/paperRE/re.csv --conf ${EX}/paperRE/reConfig.xml)
harm_case(ex3 ARGS --csv ${EX}/ex3/ex3.csv --conf ${EX}/ex3/ex3Config.xml)
harm_case(faultCov ARGS --csv ${EX}/faultCov/fc.csv --conf ${EX}/faultCov/fcConfig.xml --fd ${EX}/faultCov/faultyTraces)
harm_case(csvCheck ARGS --csv ${EX}/csvCheck/harm_test_data.csv --conf ${EX}/csvCheck/csvCheckConfig.xml)
harm_case(sub_platform1k ARGS --vcd ${EX}/sub_platform/sub_platform1k.vcd --clk CLK --conf ${EX}/sub_platform/sub_platform.xml --vcd-ss sim1::p::slave_0::camallia_u --min-frank 0.9)
harm_case(bl_master1h ARGS --vcd ${EX}/bl_master/bl_master1h.vcd --clk wb_clk --conf ${EX}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9 --keep-vac-ass --dump-vac-ass vacAss.txt)
harm_case(bl_master1k ARGS --vcd ${EX}/bl_master/bl_master1k.vcd --clk wb_clk --conf ${EX}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9)
harm_case(bl_master10k SLOW ARGS --vcd ${EX}/bl_master/bl_master10k.vcd --clk wb_clk --conf ${EX}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9)
harm_case(sobel SLOW ARGS --vcd ${EX}/sobel/sobel1k.vcd --clk sobel_tb::clk --conf ${EX}/sobel/sobelConf.xml --max-ass 1000 --sample-by-con --fd ${EX}/sobel/faults/ --find-min-subset)
harm_case(process ARGS --sva --csv-dir ${EX}/process/traces --conf ${EX}/process/processConfig.xml)
harm_case(edit ARGS --csv ${EX}/edit/edit.csv --clk clk --conf ${EX}/edit/edit.xml --sva)
harm_case(svaFunctions ARGS --vcd ${EX}/svaFunctions/bl_master1h.vcd --clk wb_clk --conf ${EX}/svaFunctions/svaFunctionsConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9)

# A4: cut stability (ties at the --max-ass cut-off); determinism checks only
harm_case(ex3_cut10 NO_BASELINE ARGS --csv ${EX}/ex3/ex3.csv --conf ${EX}/ex3/ex3Config.xml --max-ass 10)
harm_case(bl_master1k_cut10 NO_BASELINE ARGS --vcd ${EX}/bl_master/bl_master1k.vcd --clk wb_clk --conf ${EX}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9 --max-ass 10)

# ---- H1 ------------------------------------------------------------------------------------------
set(H1 ${CMAKE_SOURCE_DIR}/tests/input/h1)
# A5: new operators and an invariant template, expected output written by hand
harm_case(h1_newops ARGS --csv ${H1}/newops.csv --conf ${H1}/newops.xml)
