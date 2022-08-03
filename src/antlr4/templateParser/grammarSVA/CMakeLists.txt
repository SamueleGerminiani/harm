#PSL############################################
# Configuration.
#############################################

SET(NAME antlr4SVAParserGrammar)


#############################################
# Sources.
#############################################
SET (ANTLR4_SVA_PARSER_GRAMMAR
     src/svaLexer.cpp
     src/svaParser.cpp
     src/svaListener.cpp
     src/svaBaseListener.cpp
     )

 set_source_files_properties(
     ${ANTLR4_SVA_PARSER_GRAMMAR}
     PROPERTIES
     COMPILE_FLAGS "-w"
     )

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_SVA_PARSER_GRAMMAR})
target_include_directories(${NAME} PUBLIC
    include/
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME})


