#############################################
# Configuration.
#############################################

SET(NAME antlr4SpotParserGrammar)


#############################################
# Sources.
#############################################
SET (ANTLR4_SPOT_PARSER_GRAMMAR
     src/spotLexer.cpp
     src/spotParser.cpp
     src/spotListener.cpp
     src/spotBaseListener.cpp
     )

 set_source_files_properties(
     ${ANTLR4_SPOT_PARSER_GRAMMAR}
     PROPERTIES
     COMPILE_FLAGS "-w"
     )

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_SPOT_PARSER_GRAMMAR})
target_include_directories(${NAME} PUBLIC
    include/
    ${ANTLR4CPP_INCLUDE_DIRS}
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME})


