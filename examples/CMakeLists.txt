message("-- Including examples...")


set(WORK_DIR ${CMAKE_BINARY_DIR})
set(EXAMPLE_DIR ${CMAKE_BINARY_DIR}/../examples)



#examples
add_test(NAME vendingMachine COMMAND harm --vcd ${EXAMPLE_DIR}/vendingMachine/vendingMachine.vcd --clk clk --conf ${EXAMPLE_DIR}/vendingMachine/vendingMachineConfig.xml --vcd-ss machine_bench::machine_ WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME fsm COMMAND harm --vcd ${EXAMPLE_DIR}/fsmSVT/fsm.vcd --clk clk --conf ${EXAMPLE_DIR}/fsmSVT/fsm.xml --vcd-r 1 --vcd-ss tbench_top WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME multiTrace COMMAND harm --csv-dir ${EXAMPLE_DIR}/multiTrace/csv/ --conf ${EXAMPLE_DIR}/multiTrace/multiTrace.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME nonBoolDT COMMAND harm --csv ${EXAMPLE_DIR}/nonBoolDT/nonBooleanDT.csv --conf ${EXAMPLE_DIR}/nonBoolDT/nonBooleanDT.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME simpleNonBoolDT COMMAND harm --csv ${EXAMPLE_DIR}/simpleNonBoolDT/simpleNonBoolDT.csv --conf ${EXAMPLE_DIR}/simpleNonBoolDT/simpleNonBoolDT.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME paperRE COMMAND harm --spotltl --csv ${EXAMPLE_DIR}/paperRE/re.csv --conf ${EXAMPLE_DIR}/paperRE/reConfig.xml WORKING_DIRECTORY ${WORK_DIR} )
add_test(NAME ex3 COMMAND harm --csv ${EXAMPLE_DIR}/ex3/ex3.csv --conf ${EXAMPLE_DIR}/ex3/ex3Config.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME faultCov COMMAND harm --csv ${EXAMPLE_DIR}/faultCov/fc.csv --conf ${EXAMPLE_DIR}/faultCov/fcConfig.xml --fd ${EXAMPLE_DIR}/faultCov/faultyTraces WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME csvCheck COMMAND harm --csv ${EXAMPLE_DIR}/csvCheck/harm_test_data.csv --conf ${EXAMPLE_DIR}/csvCheck/csvCheckConfig.xml --dump-to ${CMAKE_BINARY_DIR} WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME sub_platform1k COMMAND harm --vcd ${EXAMPLE_DIR}/sub_platform/sub_platform1k.vcd --clk CLK --conf ${EXAMPLE_DIR}/sub_platform/sub_platform.xml --vcd-ss sim1::p::slave_0::camallia_u --min-frank 0.9 WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master1h COMMAND harm --vcd ${EXAMPLE_DIR}/bl_master/bl_master1h.vcd --clk wb_clk --conf ${EXAMPLE_DIR}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9 --keep-vac-ass --dump-vac-ass vacAss.txt WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master1k COMMAND harm --vcd ${EXAMPLE_DIR}/bl_master/bl_master1k.vcd --clk wb_clk --conf ${EXAMPLE_DIR}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9 WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master10k COMMAND harm --vcd ${EXAMPLE_DIR}/bl_master/bl_master10k.vcd --clk wb_clk --conf ${EXAMPLE_DIR}/bl_master/bl_masterConfig.xml --vcd-ss sim1::p::core::master_interface --min-frank 0.9 WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME sobel COMMAND harm --vcd ${EXAMPLE_DIR}/sobel/sobel1k.vcd --clk sobel_tb::clk --conf ${EXAMPLE_DIR}/sobel/sobelConf.xml --dump-to ${EXAMPLE_DIR}/sobel/ass.txt --max-ass 1000 --sample-by-con --fd ${EXAMPLE_DIR}/sobel/faults/ --find-min-subset  WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME process COMMAND harm --csv-dir ${EXAMPLE_DIR}/process/traces --conf ${EXAMPLE_DIR}/process/processConfig.xml WORKING_DIRECTORY ${WORK_DIR})
