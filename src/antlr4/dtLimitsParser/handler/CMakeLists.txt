#############################################
# Configuration.
#############################################

SET(NAME antlr4DtLimitsParserHandler)


#############################################
# Sources.
#############################################
SET (ANTLR4_DTLIMITS_PARSER_HANDLER src/DTLimitsParserHandler.cc src/dtLimitsParsingUtils.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_DTLIMITS_PARSER_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} miner_utils)

