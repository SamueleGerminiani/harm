message("-- Including test cases...")

add_executable(gtests ./traceTests.cc ./evalTests.cc)
target_link_libraries(gtests gtest_main stdc++fs all_utils progresscpp logging exp commandLineParser templateParser miner )

set(WORK_DIR ${CMAKE_BINARY_DIR})
set(TEST_DIR ${CMAKE_BINARY_DIR}/../tests)


#tests
add_test(NAME AllTests COMMAND gtests WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME TraceTest COMMAND gtests --gtest_filter=TraceTest* WORKING_DIRECTORY ${WORK_DIR})
add_test(NAME EvalTest COMMAND gtests --gtest_filter=EvalTest* WORKING_DIRECTORY ${WORK_DIR})
