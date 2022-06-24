SET(NAME globals)
project(${NAME})

include_directories(include/)

#############################################
# Sources.
#############################################

SET(OTHER_SRC src/globals.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${OTHER_SRC})


