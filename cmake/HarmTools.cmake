# H11d: the simulation and synthesis tools used by the tests (Verilator, Icarus, yosys).
# The ones built by third_party/install_{verilator,iverilog,yosys}.sh are preferred; otherwise the
# ones on PATH. A tool that cannot do what the tests need is treated as missing (its tests are
# skipped, with a message), never registered to fail:
#   - Verilator < 5 has no --binary (the oracles' builds);
#   - yosys without read_slang cannot run the H5 cross-check (probe: HarmYosysProbe.cmake).
#
# harm_find_tools(<third_party dir> <work dir>) sets, in the caller's scope:
#   HARM_VERILATOR, HARM_IVERILOG, HARM_YOSYS   the programs ("" if missing or unusable)
#   HARM_VERILATOR_VERSION, HARM_IVERILOG_VERSION, HARM_YOSYS_VERSION
#   HARM_TOOLS_PATH                             their directories, to put first on each test's PATH
include(${CMAKE_CURRENT_LIST_DIR}/HarmYosysProbe.cmake)

function(_harm_find_one name tp out)
    find_program(_prog NAMES ${name} PATHS ${tp}/${name}/bin NO_DEFAULT_PATH NO_CACHE)
    if(NOT _prog)
        find_program(_prog NAMES ${name} NO_CACHE)
    endif()
    if(_prog)
        set(${out} ${_prog} PARENT_SCOPE)
    else()
        set(${out} "" PARENT_SCOPE)
    endif()
endfunction()

function(_harm_version prog flag regex out)
    set(${out} "" PARENT_SCOPE)
    if(prog)
        execute_process(COMMAND ${prog} ${flag} OUTPUT_VARIABLE txt ERROR_VARIABLE txt
                        RESULT_VARIABLE rc)
        if(txt MATCHES "${regex}")
            set(${out} ${CMAKE_MATCH_1} PARENT_SCOPE)
        endif()
    endif()
endfunction()

function(harm_find_tools tp work)
    set(path "")

    _harm_find_one(verilator ${tp} vprog)
    _harm_version("${vprog}" --version "Verilator ([0-9]+\\.[0-9]+)" vv)
    if(vprog AND (NOT vv OR vv VERSION_LESS 5))
        message(STATUS "Verilator ${vprog} (${vv}) is older than 5 (no --binary): treated as missing")
        set(vprog "")
    endif()

    _harm_find_one(iverilog ${tp} iprog)
    _harm_version("${iprog}" -V "Icarus Verilog version ([0-9]+\\.[0-9]+)" iv)

    _harm_find_one(yosys ${tp} yprog)
    _harm_version("${yprog}" -V "Yosys ([0-9]+\\.[0-9]+)" yv)
    if(yprog)
        harm_yosys_has_read_slang("${yprog}" ${work} slang)
        if(NOT slang)
            message(STATUS "yosys ${yprog} (${yv}) has no read_slang: treated as missing")
            set(yprog "")
        endif()
    endif()

    foreach(p vprog iprog yprog)
        if(${p})
            get_filename_component(d ${${p}} DIRECTORY)
            list(APPEND path ${d})
        endif()
    endforeach()
    list(REMOVE_DUPLICATES path)

    set(HARM_VERILATOR "${vprog}" PARENT_SCOPE)
    set(HARM_VERILATOR_VERSION "${vv}" PARENT_SCOPE)
    set(HARM_IVERILOG "${iprog}" PARENT_SCOPE)
    set(HARM_IVERILOG_VERSION "${iv}" PARENT_SCOPE)
    set(HARM_YOSYS "${yprog}" PARENT_SCOPE)
    set(HARM_YOSYS_VERSION "${yv}" PARENT_SCOPE)
    set(HARM_TOOLS_PATH "${path}" PARENT_SCOPE)
endfunction()
