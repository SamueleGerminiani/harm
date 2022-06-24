#############################################
# Configuration.
#############################################

SET(NAME antlr4MetricParserGrammar)


#############################################
# Sources.
#############################################
SET (ANTLR4_METRIC_PARSER_GRAMMAR
     src/metricLexer.cpp
     src/metricParser.cpp
     src/metricListener.cpp
     src/metricBaseListener.cpp
     )

 set_source_files_properties(
     ${ANTLR4_METRIC_PARSER_GRAMMAR}
     PROPERTIES
     COMPILE_FLAGS "-w"
     )

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_METRIC_PARSER_GRAMMAR})
target_include_directories(${NAME} PUBLIC
    include/
    ${ANTLR4CPP_INCLUDE_DIRS}  
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME})

