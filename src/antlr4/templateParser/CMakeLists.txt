SET(NAME templateParser)

add_subdirectory(grammarSpot)
add_subdirectory(grammarSVA)
add_subdirectory(handler)


add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE ./)
target_link_libraries(${NAME} INTERFACE antlr4SpotParserGrammar antlr4SVAParserGrammar antlr4TemplateParserHandler)

