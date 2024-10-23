SET(NAME logging)
project(${NAME})

include_directories(include/)

SET(SRC src/message.cc)

add_library(${NAME} ${SRC})


