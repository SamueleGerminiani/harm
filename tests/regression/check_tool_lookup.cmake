# H11d acceptance A2: the tools in third_party are preferred over PATH, and a Verilator older than
# 5 (no --binary) is treated as missing. Fake tools only (shell scripts).
# Usage: cmake -DSRC=<source dir> -DWORK=<dir> -P check_tool_lookup.cmake
include(${SRC}/cmake/HarmTools.cmake)
set(W ${WORK}/h11d_tool_lookup)
file(REMOVE_RECURSE ${W})

function(fake path text)   # a tool that prints <text> for --version/-V and accepts anything else
    file(WRITE ${path} "#!/bin/sh\ncase \"$*\" in *--version*|*-V*) echo \"${text}\" ;; esac\nexit 0\n")
    file(CHMOD ${path} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
endfunction()

# third_party: current versions; PATH: old ones first
foreach(t verilator iverilog yosys)
    file(MAKE_DIRECTORY ${W}/tp/${t}/bin ${W}/path)
endforeach()
fake(${W}/tp/verilator/bin/verilator "Verilator 5.052 2026-09-27 rev v5.052")
fake(${W}/tp/iverilog/bin/iverilog "Icarus Verilog version 13.0 (stable)")
fake(${W}/tp/yosys/bin/yosys "Yosys 0.69")
fake(${W}/path/verilator "Verilator 4.210 2021-07-07 rev v4.210")
fake(${W}/path/iverilog "Icarus Verilog version 11.0 (stable)")
file(COPY ${SRC}/tests/input/h11c/fake_yosys/no_slang DESTINATION ${W}/path)
file(RENAME ${W}/path/no_slang ${W}/path/yosys)
set(ENV{PATH} "${W}/path:$ENV{PATH}")

set(errors "")
harm_find_tools(${W}/tp ${W})
foreach(t VERILATOR IVERILOG YOSYS)
    string(TOLOWER ${t} l)
    if(NOT HARM_${t} STREQUAL "${W}/tp/${l}/bin/${l}")
        string(APPEND errors "\n  with third_party: HARM_${t} = '${HARM_${t}}', want the third_party one")
    endif()
endforeach()
if(NOT HARM_TOOLS_PATH STREQUAL "${W}/tp/verilator/bin;${W}/tp/iverilog/bin;${W}/tp/yosys/bin")
    string(APPEND errors "\n  HARM_TOOLS_PATH = '${HARM_TOOLS_PATH}'")
endif()

# no third_party: only the old ones on PATH -> Verilator 4 and the yosys without read_slang are
# treated as missing; Icarus has no minimum
harm_find_tools(${W}/none ${W})
if(HARM_VERILATOR)
    string(APPEND errors "\n  Verilator 4 accepted: '${HARM_VERILATOR}'")
endif()
if(HARM_YOSYS)
    string(APPEND errors "\n  yosys without read_slang accepted: '${HARM_YOSYS}'")
endif()
if(NOT HARM_IVERILOG STREQUAL "${W}/path/iverilog")
    string(APPEND errors "\n  without third_party: HARM_IVERILOG = '${HARM_IVERILOG}', want the PATH one")
endif()

if(errors)
    message(FATAL_ERROR "tool lookup:${errors}")
endif()
message(STATUS "PASS")
