SET(NAME fort)
project(${NAME})



#############################################
# Sources.
#############################################

SET(FORT_SRC ./src/fort.c)

#############################################
# Targets.
#############################################
add_library(${NAME} ${FORT_SRC})
target_include_directories(${NAME} PUBLIC ./include/)




