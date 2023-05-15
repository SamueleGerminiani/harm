
#dea

add_executable(dea EXCLUDE_FROM_ALL main.cc)
set_target_properties(dea PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

SET(EVALUATOR_SRC src/evaluator.cc)
add_library(evaluator ${EVALUATOR_SRC})
target_include_directories(evaluator PUBLIC include/)

#link harm libs
target_link_libraries(evaluator traceReader templateParser propositionParser)

#link command line handler lib
target_link_libraries(dea evaluator commandLineParser)
