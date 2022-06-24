#############################################
# Configuration.
#############################################

SET(NAME antlr4PropositionParserGrammar)


#############################################
# Sources.
#############################################
SET (ANTLR4_PROPOSITION_PARSER_GRAMMAR
     src/propositionLexer.cpp
     src/propositionParser.cpp
     src/propositionListener.cpp
     src/propositionBaseListener.cpp
     )

 set_source_files_properties(
     ${ANTLR4_PROPOSITION_PARSER_GRAMMAR}
     PROPERTIES
     COMPILE_FLAGS "-w"
     )

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_PROPOSITION_PARSER_GRAMMAR})
target_include_directories(${NAME} PUBLIC
    include/
    ${ANTLR4CPP_INCLUDE_DIRS}  
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME})

