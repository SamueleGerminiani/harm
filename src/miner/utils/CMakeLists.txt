SET(NAME miner_utils)
project(${NAME})


#############################################
# Sources.
#############################################

SET(MINER_UTILS_SRC
    src/Trace.cc
    src/VarDeclaration.cc
    src/TemplateImplication.cc
    src/Automaton.cc
    src/Evaluator.cc
    src/AutomataBasedEvaluator.cc
    src/Permutator.cc
    src/EdgeProposition.cc
    src/DTAnd.cc
    src/DTNext.cc
    src/DTNCReps.cc
    src/DTNextAnd.cc
    src/minerUtils.cc
    src/Context.cc
    src/Assertion.cc
    src/DTUtils.cc
    )

SET(METRIC_SRC
    src/Metric.cc
    )

#############################################
# Targets.
#############################################
add_library(metric ${METRIC_SRC})
target_link_libraries(metric propositionParser)

add_library(${NAME} ${MINER_UTILS_SRC})
target_include_directories(${NAME} PUBLIC include/ ${SPOTLTLCPP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${SPOTLTL_LIB} fort clustering temporalParser metric)

