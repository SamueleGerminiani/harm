SET(NAME miner)
project(${NAME})



#############################################
# Sources.
#############################################

SET(MINER_SRC interface/src/Miner.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${MINER_SRC})
target_include_directories(miner PUBLIC modules/include/ interface/include)

add_subdirectory(utils)
add_subdirectory(modules)

target_link_libraries(${NAME} modules)



