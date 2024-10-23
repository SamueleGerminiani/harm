#############################################
# Configuration.
#############################################

SET(NAME varDeclarationParserHandler)

#############################################
# Sources.
#############################################
SET (ANTLR4_VAR_DECLARATION_HANDLER
     src/VarDeclarationParserHandler.cc
     )


#############################################
# Targets.
#############################################
add_library(${NAME} ${ANTLR4_VAR_DECLARATION_HANDLER})
target_include_directories(${NAME} PUBLIC
    include
    ../grammar/include
    ${ANTLR4CPP_INCLUDE_DIRS}  
)


