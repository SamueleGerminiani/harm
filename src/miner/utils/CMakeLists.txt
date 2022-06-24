SET(NAME miner_utils)
project(${NAME})


#############################################
# Sources.
#############################################

SET(MINER_UTILS_SRC src/Trace.cc src/DataType.cc src/Template.cc
    src/TemplateEval.cc
	src/PermGenerator.cc
	src/Hstring.cc  src/EdgeProposition.cc
        src/BDTAnd.cc
        src/BDTNext.cc
        src/BDTNCReps.cc
    src/BDTNextAnd.cc
    src/minerUtils.cc
    src/Context.cc
    src/Assertion.cc
    )

#############################################
# Targets.
#############################################
add_library(${NAME} ${MINER_UTILS_SRC})
target_include_directories(miner_utils PUBLIC include/ ${SPOTLTLCPP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${SPOTLTL_LIB} fort clustering)


