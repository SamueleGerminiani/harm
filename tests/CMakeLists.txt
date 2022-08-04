message("-- Including test cases...")

add_executable(gtests ./gtests.cc)
target_link_libraries(gtests gtest_main stdc++fs all_utils progresscpp logging exp commandLineParser templateParser miner )

set(WORK_DIR ${CMAKE_BINARY_DIR})
set(TEST_DIR ${CMAKE_BINARY_DIR}/../tests)



add_test(NAME bl_master10k COMMAND harm --vcd ${TEST_DIR}/bl_master/bl_master10k.vcd --clk wb_clk -c ${TEST_DIR}/bl_master/bl_masterConfig.xml --vcd_ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master1k COMMAND harm --vcd ${TEST_DIR}/bl_master/bl_master1k.vcd --clk wb_clk -c ${TEST_DIR}/bl_master/bl_masterConfig.xml --vcd_ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME bl_master1h COMMAND harm --vcd ${TEST_DIR}/bl_master/bl_master1h.vcd --clk wb_clk -c ${TEST_DIR}/bl_master/bl_masterConfig.xml --vcd_ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME sub_platform1k COMMAND harm --vcd ${TEST_DIR}/sub_platform/sub_platform1k.vcd --clk CLK -c ${TEST_DIR}/sub_platform/sub_platform.xml --vcd_ss ::sim1::p::slave_0::camallia_u WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME vendingMachine COMMAND harm --vcd ${TEST_DIR}/vendingMachine/vendingMachine.vcd --clk clk -c ${TEST_DIR}/vendingMachine/vendingMachineConfig.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME fsm COMMAND harm --vcd ${TEST_DIR}/fsmSVT/fsm.vcd --clk clk -c ${TEST_DIR}/fsmSVT/fsm.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME ncReps COMMAND harm --csv ${TEST_DIR}/ncReps/ncReps.csv -c ${TEST_DIR}/ncReps/ncRepsConfig.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME multiTrace COMMAND harm --csv_dir ${TEST_DIR}/multiTrace/csv/ -c ${TEST_DIR}/multiTrace/multiTrace.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME nonBoolDT COMMAND harm --csv ${TEST_DIR}/nonBoolDT/nonBooleanDT.csv -c ${TEST_DIR}/nonBoolDT/nonBooleanDT.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME paperRE COMMAND harm --csv ${TEST_DIR}/paperRE/re.csv -c ${TEST_DIR}/paperRE/reConfig.xml WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME faultCov COMMAND harm --csv ${TEST_DIR}/faultCov/fc.csv -c ${TEST_DIR}/faultCov/fcConfig.xml --fd ${TEST_DIR}/faultCov/faultyTraces WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME csvCheck COMMAND harm --csv ${TEST_DIR}/csvCheck/harm_test_data.csv -c ${TEST_DIR}/csvCheck/csvCheckConfig.xml --dumpTo ${CMAKE_BINARY_DIR} WORKING_DIRECTORY ${WORK_DIR})

#gTests
add_test(NAME NextAndTest COMMAND gtests --gtest_filter=NextAndTest* WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME ParserTest COMMAND gtests --gtest_filter=ParserTest* WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME StuckAtTest COMMAND gtests --gtest_filter=StuckAtTest* WORKING_DIRECTORY ${WORK_DIR})

