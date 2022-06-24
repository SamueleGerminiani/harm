SET(NAME commandLineParser)

SET (COMMANDLINE_PARSER_SRCS src/commandLineParser.cc)

add_library(${NAME} ${COMMANDLINE_PARSER_SRCS})
target_include_directories(${NAME} PUBLIC
    include/
)

