message("-- Including test cases...")

add_executable(gtests ./gtests.cc)
target_link_libraries(gtests gtest_main stdc++fs all_utils progresscpp logging exp commandLineParser templateParser miner )

set(WORD_DIR ${CMAKE_BINARY_DIR}/../tests)



add_test(NAME bl_master10k COMMAND harm --vcd bl_master/bl_master10k.vcd --clk wb_clk -c bl_master/bl_masterConfig.xml --vcd_ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME bl_master1k COMMAND harm --vcd bl_master/bl_master1k.vcd --clk wb_clk -c bl_master/bl_masterConfig.xml --vcd_ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME bl_master1h COMMAND harm --vcd bl_master/bl_master1h.vcd --clk wb_clk -c bl_master/bl_masterConfig.xml --vcd_ss ::sim1::p::core::master_interface WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME sub_platform1k COMMAND harm --vcd sub_platform/sub_platform1k.vcd --clk CLK -c sub_platform/sub_platform.xml --vcd_ss ::sim1::p::slave_0::camallia_u WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME vendingMachine COMMAND harm --vcd vendingMachine/vendingMachine.vcd --clk clk -c vendingMachine/vendingMachineConfig.xml WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME fsm COMMAND harm --vcd fsmSVT/fsm.vcd --clk clk -c fsmSVT/fsm.xml WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME ncReps COMMAND harm --csv ncReps/ncReps.csv -c ncReps/ncRepsConfig.xml WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME multiTrace COMMAND harm --csv_dir multiTrace/csv/ -c multiTrace/multiTrace.xml WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME nonBoolBDT COMMAND harm --csv nonBoolBDT/nonBooleanBDT.csv -c nonBoolBDT/nonBooleanBDT.xml WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME paperRE COMMAND harm --csv paperRE/re.csv -c paperRE/reConfig.xml WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME faultCov COMMAND harm --csv faultCov/fc.csv -c faultCov/fcConfig.xml --fd faultCov/faultyTraces WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME csvCheck COMMAND harm --csv csvCheck/harm_test_data.csv -c csvCheck/csvCheckConfig.xml --dumpTo ${CMAKE_BINARY_DIR} WORKING_DIRECTORY ${WORD_DIR})

#gTests
add_test(NAME NextAndTest COMMAND gtests --gtest_filter=NextAndTest* WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME ParserTest COMMAND gtests --gtest_filter=ParserTest* WORKING_DIRECTORY ${WORD_DIR})
add_test(NAME StuckAtTest COMMAND gtests --gtest_filter=StuckAtTest* WORKING_DIRECTORY ${WORD_DIR})

