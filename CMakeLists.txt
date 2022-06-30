# set the project name
project("HARM" CXX)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

### COMPILER FLAGS ###



if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_compile_options("-Wall")
    add_compile_options("-Wextra")
    add_compile_options("-Wpedantic")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8")
        message(FATAL_ERROR "gcc version must be >= 8")
    endif()
    add_compile_options("-fPIC")
    #    add_compile_options("-Wall")
    #    add_compile_options("-Wextra")
    #    add_compile_options("-Wpedantic")
endif()


### BUILD TYPE ###

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "${Green}Release mode${Reset}")
    add_compile_options("-O3")
    add_compile_options("-DNDEBUG")

elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "${Green}Debug mode${Reset}")
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_compile_options("-ggdb3")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options("-ggdb")
    else()
        add_compile_options("-g")
    endif()

elseif (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message(STATUS "${Green}Coverage Mode${Reset}")
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "--coverage")
        add_compile_options("--coverage")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

        add_compile_options("-fprofile-instr-generate")
        add_compile_options("-fcoverage-mapping")
        set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS}
            "-fprofile-instr-generate -fcoverage-mapping")
    endif()

    SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

endif()
message("Building for ${CMAKE_SYSTEM_NAME}")

#Custom targets

find_program(DOXYGEN_FOUND doxygen)
if (DOXYGEN_FOUND)
    set(current_targets ${current_targets} "docHarm\n")
    message(STATUS "${Blue}doxygen found!${Reset}")
    add_custom_target(docHarm COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen.cfg)
endif()



#############################################################################
# Basic configuration.
#############################################################################
include(FindPackageHandleStandardArgs)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#gtests
add_subdirectory(src/googletest EXCLUDE_FROM_ALL)

#globals
add_subdirectory(src/globals)
link_libraries(globals)



#main
SET(NAME harm)
SET(MAIN_SRC src/main.cc)

#Main executable
add_executable(${NAME} ${MAIN_SRC})

#z3
find_package(Z3)

target_link_libraries(${NAME} stdc++fs)
include_directories(src/utils/include src/logging/include/
    src/progress-cpp/include/progresscpp/
    src/globals/include/
    )

#All utils
add_subdirectory(src/utils)
link_libraries(all_utils)

#Progress bar
add_subdirectory(src/progress-cpp)
target_link_libraries(${NAME} progresscpp)
link_libraries(progresscpp)


#Logging
add_subdirectory(src/logging)
target_link_libraries(${NAME} logging)
link_libraries(logging)



#Exp
add_subdirectory(src/exp)
target_link_libraries(${NAME} exp)
link_libraries(exp)

#antlr4
find_package(ANTLR4 REQUIRED)
add_subdirectory(src/antlr4/varDeclarationParser)
add_subdirectory(src/antlr4/propositionParser)
add_subdirectory(src/antlr4/templateParser)
add_subdirectory(src/antlr4/metricParser)
add_subdirectory(src/antlr4/bdtLimitsParser)


#spotLTL
find_package(SPOTLTL REQUIRED)

#CSV parser
add_subdirectory(src/csv-parser)

#clustering
add_subdirectory(src/clustering)


#Command line parser
add_subdirectory(src/commandLineParser)
target_link_libraries(${NAME} commandLineParser)

#Table printer
add_subdirectory(src/fort)


#Miner
add_subdirectory(src/miner)
target_link_libraries(${NAME} miner templateParser)

#Trace generator
include_directories(src/traceGenerator/include/)
SET(TG_MAIN_SRC src/traceGenerator/traceGenerator.cc
    src/traceGenerator/src/z3TestCaseGenerator.cc)

add_executable(traceGenerator EXCLUDE_FROM_ALL ${TG_MAIN_SRC})
target_link_libraries(traceGenerator commandLineParser templateParser propositionParser varParser traceReader ${Z3_LIBRARY})

#Var estimator
add_executable(varEstimator EXCLUDE_FROM_ALL src/varEstimator/main.cc)
target_link_libraries(varEstimator estimator commandLineParser traceReader)


### TESTS ###
enable_testing()
include (CTest)
add_subdirectory(tests)
#############


#C++ API
SET(API_SRC src/api/cpp/src/harm.cc)
add_library(devharm SHARED ${API_SRC} )
target_include_directories(devharm PUBLIC src/api/cpp/include/)
target_link_libraries(devharm PUBLIC globals logging exp miner templateParser propositionParser varParser traceReader miner_utils ${Z3_LIBRARY})


#Update includes for api debug
file(COPY src/globals/include/globals.hh DESTINATION src/api/cpp/include/harm/)
file(COPY src/utils/include/colors.hh DESTINATION src/api/cpp/include/harm/)
file(COPY src/miner/utils/include/Assertion.hh DESTINATION src/api/cpp/include/harm/)
file(COPY src/miner/utils/include/Trinary.hh DESTINATION src/api/cpp/include/harm/)

INSTALL(FILES src/globals/include/globals.hh src/utils/include/colors.hh src/miner/utils/include/Assertion.hh src/miner/utils/include/Trinary.hh DESTINATION harm/include/harm)
INSTALL(FILES src/api/cpp/include/harm.hh DESTINATION harm/include)

INSTALL(TARGETS harm devharm 
    RUNTIME DESTINATION harm/bin
    LIBRARY DESTINATION harm/lib
    ARCHIVE DESTINATION harm/lib
    )

file(COPY ${SPOTLTL_LIB} DESTINATION ${CMAKE_INSTALL_PREFIX}/harm/lib FOLLOW_SYMLINK_CHAIN)
file(COPY ${ANTLR4_RUNTIME} DESTINATION ${CMAKE_INSTALL_PREFIX}/harm/lib FOLLOW_SYMLINK_CHAIN)
file(COPY ${Z3_LIBRARY} DESTINATION ${CMAKE_INSTALL_PREFIX}/harm/lib FOLLOW_SYMLINK_CHAIN)

INSTALL(PROGRAMS ${SPOTLTL_LIB} ${ANTLR4_RUNTIME} ${Z3_LIBRARY} DESTINATION harm/lib)

