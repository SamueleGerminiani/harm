SET(NAME temporalParser)

add_subdirectory(grammarTemporal)
add_subdirectory(handler)


add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE ./)
target_link_libraries(${NAME} INTERFACE antlr4TemporalParserGrammar antlr4TemplateParserHandler)

