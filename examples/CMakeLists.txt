message("-- Including examples...")


set(WORK_DIR ${CMAKE_BINARY_DIR})
set(EXAMPLE_DIR ${CMAKE_BINARY_DIR}/../examples)



#examples
add_test(NAME bl_master10k COMMAND harm --vcd ${EXAMPLE_DIR}/bl_master/bl_master10k.vcd --clk wb_clk --conf ${EXAMPLE_DIR}/bl_master/bl_masterConfig.xml --vcd-ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master1k COMMAND harm --vcd ${EXAMPLE_DIR}/bl_master/bl_master1k.vcd --clk wb_clk --conf ${EXAMPLE_DIR}/bl_master/bl_masterConfig.xml --vcd-ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master1h COMMAND harm --vcd ${EXAMPLE_DIR}/bl_master/bl_master1h.vcd --clk wb_clk --conf ${EXAMPLE_DIR}/bl_master/bl_masterConfig.xml --vcd-ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME sub_platform1k COMMAND harm --vcd ${EXAMPLE_DIR}/sub_platform/sub_platform1k.vcd --clk CLK --conf ${EXAMPLE_DIR}/sub_platform/sub_platform.xml --vcd-ss ::sim1::p::slave_0::camallia_u WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME vendingMachine COMMAND harm --vcd ${EXAMPLE_DIR}/vendingMachine/vendingMachine.vcd --clk clk --conf ${EXAMPLE_DIR}/vendingMachine/vendingMachineConfig.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME fsm COMMAND harm --vcd ${EXAMPLE_DIR}/fsmSVT/fsm.vcd --clk clk --conf ${EXAMPLE_DIR}/fsmSVT/fsm.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME ncReps COMMAND harm --csv ${EXAMPLE_DIR}/ncReps/ncReps.csv --conf ${EXAMPLE_DIR}/ncReps/ncRepsConfig.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME multiTrace COMMAND harm --csv-dir ${EXAMPLE_DIR}/multiTrace/csv/ --conf ${EXAMPLE_DIR}/multiTrace/multiTrace.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME nonBoolDT COMMAND harm --csv ${EXAMPLE_DIR}/nonBoolDT/nonBooleanDT.csv --conf ${EXAMPLE_DIR}/nonBoolDT/nonBooleanDT.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME paperRE COMMAND harm --csv ${EXAMPLE_DIR}/paperRE/re.csv --conf ${EXAMPLE_DIR}/paperRE/reConfig.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME ex3 COMMAND harm --csv ${EXAMPLE_DIR}/ex3/ex3.csv --conf ${EXAMPLE_DIR}/ex3/ex3Config.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME faultCov COMMAND harm --csv ${EXAMPLE_DIR}/faultCov/fc.csv --conf ${EXAMPLE_DIR}/faultCov/fcConfig.xml --fd ${EXAMPLE_DIR}/faultCov/faultyTraces WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME csvCheck COMMAND harm --csv ${EXAMPLE_DIR}/csvCheck/harm_test_data.csv --conf ${EXAMPLE_DIR}/csvCheck/csvCheckConfig.xml --dump-to ${CMAKE_BINARY_DIR} WORKING_DIRECTORY ${WORK_DIR})

