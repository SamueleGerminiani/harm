SET(NAME set_cover)



#############################################
# Sources.
#############################################

SET(SRC ./set_cover/set_cover_wrapper.cpp)

#############################################
# Targets.
#############################################
add_library(${NAME} ${SRC})
target_include_directories(${NAME} PUBLIC .)




