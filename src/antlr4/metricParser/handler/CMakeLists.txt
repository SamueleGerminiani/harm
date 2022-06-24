#############################################
# Configuration.
#############################################

SET(NAME antlr4MetricParserHandler)


#############################################
# Sources.
#############################################
SET (ANTLR4_METRIC_PARSER_HANDLER
     src/MetricParserHandler.cc
     src/metricParsingUtils.cc
     )


#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_METRIC_PARSER_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} exp miner_utils)

