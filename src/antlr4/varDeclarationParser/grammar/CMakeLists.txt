#############################################
# Configuration.
#############################################

SET(NAME varGrammar)


#############################################
# Sources.
#############################################
SET (ANTLR4_VAR_DECLARATION_GRAMMAR
     src/varDeclarationLexer.cpp
     src/varDeclarationParser.cpp
     src/varDeclarationListener.cpp
     src/varDeclarationBaseListener.cpp
     )

 set_source_files_properties(
     ${ANTLR4_VAR_DECLARATION_GRAMMAR}
     PROPERTIES
     COMPILE_FLAGS "-w"
     )

#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_VAR_DECLARATION_GRAMMAR})
target_include_directories(${NAME} PUBLIC
    include/
    ${ANTLR4CPP_INCLUDE_DIRS}  
)
target_link_libraries(${NAME} ${ANTLR4_RUNTIME})

