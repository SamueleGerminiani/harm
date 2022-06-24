SET(NAME logging)
project(${NAME})

include_directories(include/)

SET(OTHER_SRC src/message.cc)

add_library(${NAME} ${OTHER_SRC})


