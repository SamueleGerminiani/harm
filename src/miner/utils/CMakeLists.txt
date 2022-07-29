SET(NAME miner_utils)
project(${NAME})


#############################################
# Sources.
#############################################

SET(MINER_UTILS_SRC src/Trace.cc src/DataType.cc src/Template.cc
    src/Automaton.cc
    src/TemplateEval.cc
	src/PermGenerator.cc
	src/Hstring.cc  src/EdgeProposition.cc
        src/DTAnd.cc
        src/DTNext.cc
        src/DTNCReps.cc
    src/DTNextAnd.cc
    src/minerUtils.cc
    src/Context.cc
    src/Assertion.cc
    src/DTUtils.cc
    )

#############################################
# Targets.
#############################################
add_library(${NAME} ${MINER_UTILS_SRC})
target_include_directories(miner_utils PUBLIC include/ ${SPOTLTLCPP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${SPOTLTL_LIB} fort clustering)


