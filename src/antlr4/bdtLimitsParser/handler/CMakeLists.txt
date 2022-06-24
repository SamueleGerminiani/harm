#############################################
# Configuration.
#############################################

SET(NAME antlr4BdtLimitsParserHandler)


#############################################
# Sources.
#############################################
SET (ANTLR4_BDTLIMITS_PARSER_HANDLER src/BDTLimitsParserHandler.cc src/bdtLimitsParsingUtils.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_BDTLIMITS_PARSER_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} miner_utils)

