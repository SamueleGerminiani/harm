SET(NAME all_utils)
project(${NAME})

add_library(${NAME} INTERFACE )

target_include_directories(all_utils INTERFACE include/)

