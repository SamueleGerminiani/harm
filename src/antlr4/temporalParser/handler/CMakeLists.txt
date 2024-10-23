#############################################
# Configuration.
#############################################

SET(NAME antlr4TemplateParserHandler)


#############################################
# Sources.
#############################################
SET (ANTLR4_TEMPORAL_PARSER_HANDLER
     src/TemporalParserHandler.cc
     src/temporalParsingUtils.cc
     )


#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_TEMPORAL_PARSER_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME} antlr4TemporalParserGrammar propositionParser)

