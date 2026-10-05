# Regression tests on the examples (label `regression`) and determinism checks (label `determinism`).
#   ctest -L regression              baseline comparison
#   ctest -L determinism -LE slow    thread/run independence
# Rewrite baselines (with approval only): tests/regression/update_baseline.sh <build-dir> <set|ordered>

set(REGRESSION_DIR ${CMAKE_CURRENT_SOURCE_DIR})

function(harm_case name)
    cmake_parse_arguments(HC "SLOW;NO_BASELINE" "" "ARGS" ${ARGN})
    set(labels regression)
    if(HC_SLOW)
        list(APPEND labels slow)
    endif()

    if(NOT HC_NO_BASELINE)
        add_test(NAME regression_${name}
            COMMAND bash ${REGRESSION_DIR}/run_case.sh check $<TARGET_FILE:harm>
                    ${REGRESSION_DIR}/baseline/${name}.txt ${HC_ARGS})
        set_tests_properties(regression_${name} PROPERTIES LABELS "${labels}")
    endif()

    add_test(NAME determinism_${name}
        COMMAND bash ${REGRESSION_DIR}/determinism.sh $<TARGET_FILE:harm> ${HC_ARGS})
    list(REMOVE_ITEM labels regression)
    list(APPEND labels determinism)
    # determinism runs HARM four times, two of them with 8 threads: never run them in parallel
    set_tests_properties(determinism_${name} PROPERTIES LABELS "${labels}" RUN_SERIAL TRUE)
endfunction()

include(${REGRESSION_DIR}/cases.cmake)

# ---- H1 acceptance tests that are not baseline comparisons ----------------------------------------
# A4: a decision-tree operator in an invariant template is rejected with a clear message
add_test(NAME h1_invariant_needs_implication_for_dt
    COMMAND $<TARGET_FILE:harm> --csv ${CMAKE_SOURCE_DIR}/tests/input/h1/newops.csv
            --conf ${CMAKE_SOURCE_DIR}/tests/input/h1/invariant_dt.xml --psilent --max-threads 1)
set_tests_properties(h1_invariant_needs_implication_for_dt PROPERTIES
    LABELS regression
    PASS_REGULAR_EXPRESSION "Decision-tree operators need an implication")
# A7: --skip-invalid-props
add_test(NAME h1_skip_invalid_props
    COMMAND bash ${REGRESSION_DIR}/skip_invalid_props.sh $<TARGET_FILE:harm>
            ${CMAKE_SOURCE_DIR}/tests/input/h1/newops.csv
            ${CMAKE_SOURCE_DIR}/tests/input/h1/skip_invalid.xml
            ${CMAKE_SOURCE_DIR}/tests/input/h1/skip_invalid_ref.xml 2)
set_tests_properties(h1_skip_invalid_props PROPERTIES LABELS regression)
