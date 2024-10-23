SET(NAME varParser)

add_subdirectory(grammar)
add_subdirectory(handler)


add_library(${NAME} INTERFACE)
target_link_libraries(${NAME} INTERFACE varGrammar varDeclarationParserHandler)
target_include_directories(${NAME} INTERFACE .) 
