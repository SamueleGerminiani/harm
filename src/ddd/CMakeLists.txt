#############################################
# Configuration.
#############################################

SET(NAME ddd)


#############################################
# Sources.
#############################################
SET (DDD_SRCS
    src/ddd.cc
    )

#############################################
# Targets.
#############################################
add_library(${NAME} ${DDD_SRCS})

target_include_directories( ${NAME} PUBLIC include/)
target_link_libraries(${NAME} SQLiteCpp)


