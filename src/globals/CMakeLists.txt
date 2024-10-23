SET(NAME globals)
project(${NAME})

include_directories(include/)

#############################################
# Sources.
#############################################

SET(SRC src/globals.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${SRC})


