SET(NAME dtLimitsParser)

add_subdirectory(grammar)
add_subdirectory(handler)


add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE .)
target_link_libraries(${NAME} INTERFACE antlr4DtLimitsParserHandler antlr4DtLimitsParserGrammar)
