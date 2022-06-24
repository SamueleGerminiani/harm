#############################################
# Configuration.
#############################################

SET(NAME antlr4PropositionParserHandler)


#############################################
# Sources.
#############################################
SET (ANTLR4_PROPOSITION_PARSER_HANDLER
     src/PropositionParserHandler.cc
     src/propositionParsingUtils.cc
     )


#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_PROPOSITION_PARSER_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} exp miner_utils)

