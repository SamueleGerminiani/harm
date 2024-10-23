SET(NAME all_utils)

SET(SRC src/Limits.cc)
add_library(${NAME} ${SRC})

target_include_directories(${NAME} PUBLIC include/ ${Boost_INCLUDE_DIRS})

