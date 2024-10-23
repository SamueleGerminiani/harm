#ast
add_executable(ast EXCLUDE_FROM_ALL main.cc)
set_target_properties(ast PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

#link command line handler lib
target_link_libraries (ast stdc++fs all_utils logging exp commandLineParser temporalParser)
