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

# ---- H6: COI rank mode ----------------------------------------------------------------------------
set(H6 ${CMAKE_SOURCE_DIR}/tests/input/h6)
set(MP ${CMAKE_SOURCE_DIR}/tests/input/coi/multipath/trace.vcd)
# A3: configuration errors
foreach(case "no_coi;needs a <coi> element" "coi_mode;Unknown <coi> mode"
             "coi_missing;Cannot open coi file" "coi_version;unsupported coi.json version")
    list(GET case 0 name)
    list(GET case 1 message)
    add_test(NAME h6_error_${name}
        COMMAND $<TARGET_FILE:harm> --vcd ${MP} --clk clk --vcd-ss tb::dut --conf ${H6}/${name}.xml
                --psilent --max-threads 1)
    set_tests_properties(h6_error_${name} PROPERTIES LABELS regression PASS_REGULAR_EXPRESSION "${message}")
endforeach()
# A4: --dump-assertion-info values
if(PYTHON3_FOUND)
    add_test(NAME h6_assertion_info
        COMMAND ${PYTHON3_FOUND} ${REGRESSION_DIR}/check_assertion_info.py $<TARGET_FILE:harm>
                ${H6}/multipath_rank_expected.txt --vcd ${MP} --clk clk --vcd-ss tb::dut
                --conf ${H6}/multipath_rank.xml)
    set_tests_properties(h6_assertion_info PROPERTIES LABELS regression)
endif()

# ---- H3: --dump-implications ----------------------------------------------------------------------
if(PYTHON3_FOUND)
    add_test(NAME h3_dump_implications
        COMMAND ${PYTHON3_FOUND} ${REGRESSION_DIR}/check_implications.py $<TARGET_FILE:harm>
                ${CMAKE_SOURCE_DIR}/tests/input/h3/reduce_implications_expected.txt
                --csv ${CMAKE_SOURCE_DIR}/tests/input/h3/reduce.csv
                --conf ${CMAKE_SOURCE_DIR}/tests/input/h3/reduce.xml)
    set_tests_properties(h3_dump_implications PROPERTIES LABELS regression)
endif()

# ---- H1c: end-of-trace semantics, independent oracle (IEEE 1800 Annex F) ---------------------------
if(PYTHON3_FOUND)
    add_test(NAME h1c_annex_f_oracle
        COMMAND bash -c "H1C_DUMP=h1c_annex_f_dump.txt $<TARGET_FILE:EndOfTraceTest> --gtest_filter=*dumpForOracle* > /dev/null && ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/oracle/sva_finite_semantics.py check h1c_annex_f_dump.txt"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set_tests_properties(h1c_annex_f_oracle PROPERTIES LABELS regression)
endif()

# ---- H7: COI filter mode (A1-A3, A5 warning) ------------------------------------------------------
if(PYTHON3_FOUND)
    foreach(design counter arbiter fsm multipath structs)
        set(R 0)
        if(design STREQUAL "structs")
            set(R 1)
        endif()
        add_test(NAME h7_filter_${design}
            COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/check_filter.py $<TARGET_FILE:harm>
                    ${CMAKE_SOURCE_DIR}/tests/input/h7/${design}.xml
                    --vcd ${CMAKE_SOURCE_DIR}/tests/input/coi/${design}/trace.vcd --clk clk
                    --vcd-ss tb::dut --vcd-r ${R})
        set_tests_properties(h7_filter_${design} PROPERTIES LABELS "regression;coi")
    endforeach()
endif()
set_tests_properties(regression_h7_small_domain PROPERTIES TIMEOUT 60)

# ---- H5: harm-coi generator (A1-A4) ----------------------------------------------------------------
# harm-coi needs Python >= 3.11 with pyslang (and pytest for A4). Set HARM_COI_PYTHON to such an
# interpreter (e.g. a venv: python3.12 -m venv v && v/bin/pip install -e 'tools/harm-coi[test]');
# by default python3 is tried. Without it, the H5 tests are skipped with a message.
set(HARM_COI_PYTHON "${PYTHON3_FOUND}" CACHE FILEPATH "Python interpreter with pyslang and pytest, for harm-coi")
set(HARM_COI_OK FALSE)
if(HARM_COI_PYTHON)
    execute_process(COMMAND ${HARM_COI_PYTHON} -c "import pyslang, pytest"
                    RESULT_VARIABLE harm_coi_probe OUTPUT_QUIET ERROR_QUIET)
    if(harm_coi_probe EQUAL 0)
        set(HARM_COI_OK TRUE)
    endif()
endif()
if(HARM_COI_OK)
    set(H5_OUT ${CMAKE_BINARY_DIR}/h5)
    # A4: constructs outside the fixtures (pytest)
    add_test(NAME h5_unit
        COMMAND ${HARM_COI_PYTHON} -m pytest -q -p no:cacheprovider ${CMAKE_SOURCE_DIR}/tools/harm-coi/tests)
    set_tests_properties(h5_unit PROPERTIES LABELS coi)
    foreach(design counter arbiter fsm hier structs multipath)
        set(F ${CMAKE_SOURCE_DIR}/tests/input/coi/${design})
        # A1 + A2: equal to the hand-written expected_coi.json and edges.txt; valid for the trace
        add_test(NAME h5_generator_${design}
            COMMAND ${HARM_COI_PYTHON} ${CMAKE_SOURCE_DIR}/tests/coi/check_generator.py ${F}
                    --python ${HARM_COI_PYTHON} --harm $<TARGET_FILE:harm> --out ${H5_OUT})
        set_tests_properties(h5_generator_${design} PROPERTIES LABELS coi FIXTURES_SETUP h5_coi_${design})
        # A3: simulation non-influence, on the generator's output
        if(VERILATOR_FOUND)
            add_test(NAME h5_influence_${design}
                COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/perturb.py influence ${F}
                        --coi ${H5_OUT}/${design}_coi.json)
            set_tests_properties(h5_influence_${design} PROPERTIES LABELS "coi;slow"
                                 FIXTURES_REQUIRED h5_coi_${design})
        endif()
    endforeach()
else()
    message(STATUS "HARM_COI_PYTHON (${HARM_COI_PYTHON}) lacks pyslang or pytest: the H5 harm-coi tests are skipped")
endif()
