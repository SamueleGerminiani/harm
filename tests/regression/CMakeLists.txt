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

# ---- H1 validation: Verilator replay of HARM's SVA output (only if Verilator and Python exist) -----
find_program(VERILATOR_FOUND verilator)
find_program(PYTHON3_FOUND python3)
if(VERILATOR_FOUND AND PYTHON3_FOUND)
    function(verilator_replay name csv conf)
        add_test(NAME verilator_replay_${name}
            COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/oracle/verilator_replay.py
                    --harm $<TARGET_FILE:harm> --csv ${csv} --conf ${conf})
        set_tests_properties(verilator_replay_${name} PROPERTIES LABELS "verilator;slow")
    endfunction()
    set(H1 ${CMAKE_SOURCE_DIR}/tests/input/h1)
    verilator_replay(newops ${H1}/newops.csv ${H1}/newops.xml)
    verilator_replay(temporal2v ${H1}/temporal2v.csv ${H1}/temporal2v.xml)
    verilator_replay(edit ${CMAKE_SOURCE_DIR}/examples/edit/edit.csv ${CMAKE_SOURCE_DIR}/examples/edit/edit.xml)
    verilator_replay(ex3 ${CMAKE_SOURCE_DIR}/examples/ex3/ex3.csv ${CMAKE_SOURCE_DIR}/examples/ex3/ex3Config.xml)
else()
    message(STATUS "Verilator or python3 not found: the verilator_replay validation tests are skipped")
endif()

# ---- H4: COI contract and fixture corpus (label coi) ---------------------------------------------
if(PYTHON3_FOUND)
    add_test(NAME coi_invalid_documents
        COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/test_invalid.py)
    set_tests_properties(coi_invalid_documents PROPERTIES LABELS coi)
    foreach(design counter arbiter fsm hier structs multipath)
        set(F ${CMAKE_SOURCE_DIR}/tests/input/coi/${design})
        add_test(NAME coi_valid_${design}
            COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/check_coi.py ${F}/expected_coi.json
                    --vcd ${F}/trace.vcd --harm $<TARGET_FILE:harm>)
        set_tests_properties(coi_valid_${design} PROPERTIES LABELS coi)
        if(VERILATOR_FOUND)
            add_test(NAME coi_reproduce_${design}
                COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/perturb.py reproduce ${F})
            add_test(NAME coi_influence_${design}
                COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/perturb.py influence ${F})
            add_test(NAME coi_depths_${design}
                COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/perturb.py depths ${F})
            set_tests_properties(coi_reproduce_${design} coi_influence_${design} PROPERTIES LABELS "coi;slow")
            set_tests_properties(coi_depths_${design} PROPERTIES LABELS "coi;slow;report")
        endif()
    endforeach()
endif()
