include(FindPackageHandleStandardArgs)

#Manual definition of antlr4 runtime and include path
if(DEFINED ANTRL4_INCLUDE_PATH AND DEFINED ANTRL4_LIB_PATH)
    set(ANTLR4_RUNTIME ${ANTRL4_LIB_PATH})
    set(ANTLR4CPP_INCLUDE_DIRS ${ANTRL4_INCLUDE_PATH})
else()
    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif()

    if(LINUX) 
        set(libruntime "libantlr4-runtime.so")
    elseif(APPLE)
        set(libruntime "libantlr4-runtime.dylib")
    endif()

    find_library(ANTLR4_RUNTIME NAMES ${libruntime}
        HINTS /usr/local/lib/antlr4 /usr/lib/antlr4 /usr/local/lib /usr/lib
        PATHS ${CMAKE_SOURCE_DIR}/third_party/antlr4/lib)

    find_path(ANTLR4CPP_INCLUDE_DIRS
        NAMES antlr4-runtime.h
        HINTS /usr/local/include/antlr4-runtime /usr/include/antlr4-runtime /usr/local/include /usr/include
        PATHS ${CMAKE_SOURCE_DIR}/third_party/antlr4/include/antlr4-runtime/
        DOC "ANTLR4 C++ headers"
        )

endif()

find_package_handle_standard_args(ANTLR4 REQUIRED_VARS ANTLR4_RUNTIME ANTLR4CPP_INCLUDE_DIRS)
