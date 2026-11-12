# H11: writes HARM's version (git describe) into ${OUT}, at every build, only if it changed.
execute_process(COMMAND git describe --tags --always --dirty
    WORKING_DIRECTORY ${SRC} OUTPUT_VARIABLE describe OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET RESULT_VARIABLE rc)
if(NOT rc EQUAL 0 OR describe STREQUAL "")
    set(describe "unknown")
endif()
string(REGEX REPLACE "-dirty$" " (dirty)" describe "${describe}")
set(content "#pragma once\n#define HARM_VERSION \"${describe}\"\n")
if(EXISTS ${OUT})
    file(READ ${OUT} old)
endif()
if(NOT "${old}" STREQUAL "${content}")
    file(WRITE ${OUT} "${content}")
endif()
