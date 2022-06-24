#############################################
# Configuration.
#############################################

SET(NAME antlr4TemplateParserHandler)


#############################################
# Sources.
#############################################
SET (ANTLR4_PSL_PARSER_HANDLER
     src/SpotParserHandler.cc
     src/SpotToSVAhandler.cc
     src/templateParsingUtils.cc
     )


#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_PSL_PARSER_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME} antlr4SpotParserGrammar antlr4SVAParserGrammar exp miner_utils propositionParser)

