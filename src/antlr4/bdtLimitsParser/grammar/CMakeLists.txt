#############################################
# Configuration.
#############################################

SET(NAME antlr4BdtLimitsParserGrammar)


#############################################
# Sources.
#############################################
SET (ANTLR4_BDTLIMITS_PARSER_GRAMMAR
     src/limitsLexer.cpp
     src/limitsParser.cpp
     src/limitsListener.cpp
     src/limitsBaseListener.cpp
     )

 set_source_files_properties(
     ${ANTLR4_BDTLIMITS_PARSER_GRAMMAR}
     PROPERTIES
     COMPILE_FLAGS "-w"
     )

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_BDTLIMITS_PARSER_GRAMMAR})
target_include_directories(${NAME} PUBLIC
    include/
    ${ANTLR4CPP_INCLUDE_DIRS}  
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME})

