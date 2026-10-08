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
# H11d: Verilator, Icarus and yosys from third_party (install_{verilator,iverilog,yosys}.sh), else
# from PATH; unusable versions are treated as missing (cmake/HarmTools.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/HarmTools.cmake)
unset(VERILATOR_FOUND CACHE)   # cached by find_program before H11d
unset(HARM_COI_YOSYS CACHE)
harm_find_tools(${CMAKE_SOURCE_DIR}/third_party ${CMAKE_CURRENT_BINARY_DIR})
foreach(t VERILATOR IVERILOG YOSYS)
    if(HARM_${t})
        message(STATUS "${t}: ${HARM_${t}} (${HARM_${t}_VERSION})")
    else()
        message(STATUS "${t}: not found (third_party/install_all.sh installs it)")
    endif()
endforeach()
set(VERILATOR_FOUND ${HARM_VERILATOR})
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
    # H11e: the s_eventually control monitor against hand-labelled traces
    add_test(NAME verilator_replay_monitor_selftest
        COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/oracle/verilator_replay.py --self-test)
    set_tests_properties(verilator_replay_monitor_selftest PROPERTIES LABELS verilator)
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
# harm-coi needs Python >= 3.11 with pyslang (and pytest and jsonschema for the tests). Set HARM_COI_PYTHON to such an
# interpreter (e.g. a venv: python3.12 -m venv v && v/bin/pip install -e 'tools/harm-coi[test]');
# by default python3 is tried. Without it, the H5 tests are skipped with a message.
set(HARM_COI_PYTHON "${PYTHON3_FOUND}" CACHE FILEPATH "Python interpreter with pyslang and pytest, for harm-coi")
set(HARM_COI_OK FALSE)
if(HARM_COI_PYTHON)
    execute_process(COMMAND ${HARM_COI_PYTHON} -c "import pyslang, pytest, jsonschema"
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
    # yosys with read_slang (>= 0.67; third_party/install_yosys.sh) for the validation cross-check
    set(HARM_COI_YOSYS ${HARM_YOSYS})
    set(HARM_COI_XCHECK FALSE)
    if(HARM_YOSYS)
        set(HARM_COI_XCHECK TRUE)
    endif()
    if(NOT HARM_COI_XCHECK)
        message(STATUS "no yosys with read_slang: the H5 yosys cross-check is skipped")
    endif()
    # the H4 fixtures, and the H5 validation design (no hand-written cones: simulation and yosys only)
    foreach(design counter arbiter fsm hier structs multipath h5/constructs)
        if(design STREQUAL "h5/constructs")
            set(F ${CMAKE_SOURCE_DIR}/tests/input/h5/constructs)
            set(design constructs)
            set(R 1)
        else()
            set(F ${CMAKE_SOURCE_DIR}/tests/input/coi/${design})
            file(STRINGS ${F}/edges.txt R REGEX "^vcd_recursion")
            string(REGEX REPLACE "[^0-9]" "" R "${R}")
        endif()
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
        # validation: signal-level cross-check against yosys' netlist
        if(HARM_COI_XCHECK)
            file(GLOB rtl ${F}/rtl/*.sv)
            add_test(NAME h5_xcheck_yosys_${design}
                COMMAND ${HARM_COI_PYTHON} ${CMAKE_SOURCE_DIR}/tests/coi/xcheck_yosys.py
                        --yosys ${HARM_COI_YOSYS} --edges ${H5_OUT}/${design}_edges.txt
                        --top ${design} --recursion ${R} ${rtl})
            set_tests_properties(h5_xcheck_yosys_${design} PROPERTIES LABELS "coi;xcheck"
                                 FIXTURES_REQUIRED h5_coi_${design})
        endif()
    endforeach()
    if(VERILATOR_FOUND)
        add_test(NAME h5_reproduce_constructs
            COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/perturb.py reproduce
                    ${CMAKE_SOURCE_DIR}/tests/input/h5/constructs)
        set_tests_properties(h5_reproduce_constructs PROPERTIES LABELS "coi;slow")
    endif()
else()
    message(STATUS "HARM_COI_PYTHON (${HARM_COI_PYTHON}) lacks pyslang, pytest or jsonschema: the H5 harm-coi tests are skipped")
endif()

# ---- H8: depth-aware COI filter (A2-A4, A6 report; A5 errors) -------------------------------------
set(H8 ${CMAKE_SOURCE_DIR}/tests/input/h8)
foreach(case "rank_depth;depth applies only to mode=\"filter\"" "depth_value;Unknown <coi> depth")
    list(GET case 0 name)
    list(GET case 1 message)
    add_test(NAME h8_error_${name}
        COMMAND $<TARGET_FILE:harm> --vcd ${MP} --clk clk --vcd-ss tb::dut --conf ${H8}/error_${name}.xml
                --psilent --max-threads 1)
    set_tests_properties(h8_error_${name} PROPERTIES LABELS regression PASS_REGULAR_EXPRESSION "${message}")
endforeach()
if(PYTHON3_FOUND)
    foreach(design counter arbiter fsm multipath structs constructs)
        set(R 0)
        set(VCD ${CMAKE_SOURCE_DIR}/tests/input/coi/${design}/trace.vcd)
        if(design STREQUAL "structs")
            set(R 1)
        elseif(design STREQUAL "constructs")
            set(R 1)
            set(VCD ${CMAKE_SOURCE_DIR}/tests/input/h5/constructs/trace.vcd)
        endif()
        foreach(mode exact bounded)
            add_test(NAME h8_depth_${design}_${mode}
                COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/coi/check_depth.py $<TARGET_FILE:harm>
                        ${H8}/${design}.xml ${mode} --vcd ${VCD} --clk clk --vcd-ss tb::dut --vcd-r ${R})
            set_tests_properties(h8_depth_${design}_${mode} PROPERTIES LABELS "regression;coi")
        endforeach()
    endforeach()
endif()

# ---- H1d: printing fixes F7/F8, independent check with Spot's ltlfilt ------------------------------
set(H1D_LTLFILT ${CMAKE_SOURCE_DIR}/third_party/spot/bin/ltlfilt)
if(PYTHON3_FOUND AND EXISTS ${H1D_LTLFILT})
    add_test(NAME h1d_spot_equivalence
        COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/oracle/h1d_spot_equivalence.py ${H1D_LTLFILT})
    set_tests_properties(h1d_spot_equivalence PROPERTIES LABELS regression)
endif()

# ---- H9: out-of-cone report (A1-A4) --------------------------------------------------------------
if(PYTHON3_FOUND)
    set(H9 ${CMAKE_SOURCE_DIR}/tests/input/h9)
    set(CHECK_H9 ${CMAKE_SOURCE_DIR}/tests/coi/check_coi_report.py)
    set(COIF ${CMAKE_SOURCE_DIR}/tests/input/coi)
    set(CONS_VCD ${CMAKE_SOURCE_DIR}/tests/input/h5/constructs/trace.vcd)
    # A1, A2: hand-written expected reports
    add_test(NAME h9_expected_multipath COMMAND ${PYTHON3_FOUND} ${CHECK_H9} expected $<TARGET_FILE:harm>
             ${H9}/multipath.xml ${H9}/expected_multipath.json --vcd ${COIF}/multipath/trace.vcd --clk clk --vcd-ss tb::dut)
    add_test(NAME h9_expected_structs COMMAND ${PYTHON3_FOUND} ${CHECK_H9} expected $<TARGET_FILE:harm>
             ${H9}/structs.xml ${H9}/expected_structs.json --vcd ${COIF}/structs/trace.vcd --clk clk --vcd-ss tb::dut --vcd-r 1)
    add_test(NAME h9_expected_constructs COMMAND ${PYTHON3_FOUND} ${CHECK_H9} expected $<TARGET_FILE:harm>
             ${H9}/constructs.xml ${H9}/expected_constructs.json --vcd ${CONS_VCD} --clk clk --vcd-ss tb::dut --vcd-r 1)
    # A3: cross-check with the rule computed in Python, on H7's and H8's configurations
    foreach(design counter arbiter fsm multipath structs)
        set(R 0)
        if(design STREQUAL "structs")
            set(R 1)
        endif()
        add_test(NAME h9_crosscheck_${design} COMMAND ${PYTHON3_FOUND} ${CHECK_H9} crosscheck $<TARGET_FILE:harm>
                 ${CMAKE_SOURCE_DIR}/tests/input/h7/${design}.xml --vcd ${COIF}/${design}/trace.vcd --clk clk
                 --vcd-ss tb::dut --vcd-r ${R})
    endforeach()
    add_test(NAME h9_crosscheck_constructs COMMAND ${PYTHON3_FOUND} ${CHECK_H9} crosscheck $<TARGET_FILE:harm>
             ${CMAKE_SOURCE_DIR}/tests/input/h8/constructs.xml --vcd ${CONS_VCD} --clk clk --vcd-ss tb::dut --vcd-r 1)
    # A4: no effect on mining; a context without <coi>
    add_test(NAME h9_noeffect_multipath_rank COMMAND ${PYTHON3_FOUND} ${CHECK_H9} noeffect $<TARGET_FILE:harm>
             ${H9}/multipath.xml --vcd ${COIF}/multipath/trace.vcd --clk clk --vcd-ss tb::dut)
    add_test(NAME h9_noeffect_multipath_filter COMMAND ${PYTHON3_FOUND} ${CHECK_H9} noeffect $<TARGET_FILE:harm>
             ${CMAKE_SOURCE_DIR}/tests/input/h7/multipath.xml --vcd ${COIF}/multipath/trace.vcd --clk clk --vcd-ss tb::dut)
    add_test(NAME h9_noeffect_nocoi COMMAND ${PYTHON3_FOUND} ${CHECK_H9} noeffect $<TARGET_FILE:harm>
             ${H9}/nocoi.xml --vcd ${COIF}/multipath/trace.vcd --clk clk --vcd-ss tb::dut)
    set_tests_properties(h9_expected_multipath h9_expected_structs h9_expected_constructs
        h9_crosscheck_counter h9_crosscheck_arbiter h9_crosscheck_fsm h9_crosscheck_multipath
        h9_crosscheck_structs h9_crosscheck_constructs h9_noeffect_multipath_rank
        h9_noeffect_multipath_filter h9_noeffect_nocoi PROPERTIES LABELS "regression;coi")
endif()

# ---- H10: RTL predicate harvesting (A1, A2, A4; A3 is in h5_unit's pytest) ------------------------
if(HARM_COI_OK)
    foreach(design counter arbiter fsm multipath hier structs h5/constructs)
        if(design STREQUAL "h5/constructs")
            set(F ${CMAKE_SOURCE_DIR}/tests/input/h5/constructs)
            set(design constructs)
        else()
            set(F ${CMAKE_SOURCE_DIR}/tests/input/coi/${design})
        endif()
        add_test(NAME h10_predicates_${design}
            COMMAND ${HARM_COI_PYTHON} ${CMAKE_SOURCE_DIR}/tests/coi/check_predicates.py expected ${F}
                    ${CMAKE_SOURCE_DIR}/tests/input/h10/${design}_predicates.json
                    --python ${HARM_COI_PYTHON} --harm $<TARGET_FILE:harm>)
        add_test(NAME h10_emit_config_${design}
            COMMAND ${HARM_COI_PYTHON} ${CMAKE_SOURCE_DIR}/tests/coi/check_predicates.py harm ${F}
                    --python ${HARM_COI_PYTHON} --harm $<TARGET_FILE:harm>)
        set_tests_properties(h10_predicates_${design} h10_emit_config_${design} PROPERTIES LABELS coi)
    endforeach()
endif()

# ---- H1b: HARM's x/z semantics, documented and pinned (D-011 option a) ----------------------------
if(PYTHON3_FOUND)
    add_test(NAME h1b_x_semantics
        COMMAND ${PYTHON3_FOUND} ${REGRESSION_DIR}/check_x_semantics.py $<TARGET_FILE:harm>
                ${CMAKE_SOURCE_DIR}/tests/input/h1b/x_values.csv ${CMAKE_SOURCE_DIR}/tests/input/h1b/x_values.xml)
    set_tests_properties(h1b_x_semantics PROPERTIES LABELS regression)
endif()

# ---- H3b: atom premises (A4, A5 at the command line; A1-A3 are AtomPremiseTest) -------------------
set(H3B ${CMAKE_SOURCE_DIR}/tests/input/h3b)
add_test(NAME h3b_needs_reduce_implies
    COMMAND $<TARGET_FILE:harm> --csv ${H3B}/reduce.csv --conf ${H3B}/reduce.xml --atom-premises --psilent)
set_tests_properties(h3b_needs_reduce_implies PROPERTIES LABELS regression
    PASS_REGULAR_EXPRESSION "--atom-premises needs --reduce implies")
if(PYTHON3_FOUND)
    add_test(NAME h3b_atom_premises
        COMMAND ${PYTHON3_FOUND} ${REGRESSION_DIR}/check_atom_premises.py $<TARGET_FILE:harm>
                ${H3B}/reduce.csv ${H3B}/reduce.xml)
    set_tests_properties(h3b_atom_premises PROPERTIES LABELS regression)
endif()

# ---- H11: --version (A5) --------------------------------------------------------------------------
add_test(NAME h11_version COMMAND $<TARGET_FILE:harm> --version)
set_tests_properties(h11_version PROPERTIES LABELS regression
    PASS_REGULAR_EXPRESSION "^HARM (v[0-9][^ ]*|[0-9a-f]{7,})( \\(dirty\\))?\n")
# H11, A4: the README's command examples run
if(PYTHON3_FOUND)
    add_test(NAME h11_readme_commands
        COMMAND ${PYTHON3_FOUND} ${REGRESSION_DIR}/check_readme_commands.py $<TARGET_FILE:harm>
                ${CMAKE_SOURCE_DIR}/README.md)
    set_tests_properties(h11_readme_commands PROPERTIES LABELS regression)
endif()

# ---- H11c: the Linux findings F-L3, F-L4, F-L5 ------------------------------------------------------
# A1 (F-L3): the yosys probe accepts only a yosys that can run read_slang
add_test(NAME h11c_yosys_probe
    COMMAND ${CMAKE_COMMAND} -DSRC=${CMAKE_SOURCE_DIR} -DWORK=${CMAKE_CURRENT_BINARY_DIR}
            -P ${CMAKE_SOURCE_DIR}/tests/regression/check_yosys_probe.cmake)
# A2 (F-L4): a [1:10] vector mines the same assertions as the same values declared [9:0]
if(PYTHON3_FOUND)
    add_test(NAME h11c_vcd_ranges
        COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/regression/check_vcd_ranges.py
                $<TARGET_FILE:harm> ${CMAKE_SOURCE_DIR}/tests/input/h11c/ranges.vcd)
endif()
# A6 (F-L5): the configuration harm-coi emits next to a 1600-bit register is accepted by HARM
if(HARM_COI_OK)
    add_test(NAME h11c_emit_config_wide
        COMMAND ${HARM_COI_PYTHON} ${CMAKE_SOURCE_DIR}/tests/coi/check_predicates.py harm
                ${CMAKE_SOURCE_DIR}/tests/input/h11c/wide --python ${HARM_COI_PYTHON} --harm $<TARGET_FILE:harm>)
    set_tests_properties(h11c_emit_config_wide PROPERTIES LABELS coi)
endif()

# ---- H11d: Verilator, Icarus and yosys from third_party ---------------------------------------------
# A2: the third_party tools are preferred over PATH; Verilator < 5 and yosys without read_slang are
# treated as missing
add_test(NAME h11d_tool_lookup
    COMMAND ${CMAKE_COMMAND} -DSRC=${CMAKE_SOURCE_DIR} -DWORK=${CMAKE_CURRENT_BINARY_DIR}
            -P ${CMAKE_SOURCE_DIR}/tests/regression/check_tool_lookup.cmake)

# ---- H11g: the tool scripts on macOS (finding F-M1) -------------------------------------------------
# A1: after tools_setup on macOS, the compiler finds Homebrew flex's FlexLexer.h (macOS is faked, so
# this runs everywhere)
add_test(NAME h11g_tools_common_flex
    COMMAND bash ${CMAKE_SOURCE_DIR}/tests/regression/check_tools_common.sh ${CMAKE_SOURCE_DIR})

# ---- H12: the same assertions on every platform (finding F-M2) ------------------------------------
# A1: structs mines Linux x86_64's count (macOS arm64 gave 1,800 before H12: FMA in the DT score)
if(PYTHON3_FOUND)
    add_test(NAME h12_structs_count
        COMMAND ${PYTHON3_FOUND} ${REGRESSION_DIR}/check_mined_count.py $<TARGET_FILE:harm>
                ${CMAKE_SOURCE_DIR}/tests/input/coi/structs/trace.vcd tb::dut 1839)
    set_tests_properties(h12_structs_count PROPERTIES LABELS "regression;slow")
endif()

# ---- H11e: fixtures independent of the simulator ----------------------------------------------------
# A2: a fixture testbench gives the same stimulus under Verilator and Icarus (tests/input/stim.svh,
# finding F-L7). h5/constructs is not included: Icarus does not parse its RTL.
if(HARM_VERILATOR AND HARM_IVERILOG AND PYTHON3_FOUND)
    foreach(design counter arbiter fsm hier structs multipath)
        add_test(NAME h11e_stim_${design}
            COMMAND ${PYTHON3_FOUND} ${CMAKE_SOURCE_DIR}/tests/regression/check_stim.py
                    ${CMAKE_SOURCE_DIR}/tests/input/coi/${design} --iverilog ${HARM_IVERILOG})
        set_tests_properties(h11e_stim_${design} PROPERTIES LABELS coi)
    endforeach()
endif()

# H11d: every test here runs with the chosen tools first on PATH (the fixture scripts call
# verilator and iverilog by name), whatever the user's PATH is
if(HARM_TOOLS_PATH)
    set(_harm_env "")
    foreach(d ${HARM_TOOLS_PATH})
        list(APPEND _harm_env "PATH=path_list_prepend:${d}")
    endforeach()
    get_property(_harm_tests DIRECTORY PROPERTY TESTS)
    set_tests_properties(${_harm_tests} PROPERTIES ENVIRONMENT_MODIFICATION "${_harm_env}")
endif()

# ---- H13: no profiling output from a default build ----------------------------------------------------
if(NOT HARM_PROFILE)
    add_test(NAME h13_no_gmon COMMAND bash ${CMAKE_SOURCE_DIR}/tests/regression/check_no_gmon.sh $<TARGET_FILE:harm>)
    set_tests_properties(h13_no_gmon PROPERTIES LABELS regression)
endif()
