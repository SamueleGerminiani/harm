# H11c, F-L3: is <yosys> able to run read_slang? yosys exits with 0 for 'help <unknown command>',
# so the probe runs read_slang on a one-line module instead.
# harm_yosys_has_read_slang(<yosys> <work dir> <result variable>)
function(harm_yosys_has_read_slang yosys work out)
    set(${out} FALSE PARENT_SCOPE)
    if(NOT yosys OR NOT EXISTS "${yosys}")
        return()
    endif()
    file(MAKE_DIRECTORY "${work}")
    set(sv "${work}/harm_yosys_probe.sv")
    file(WRITE "${sv}" "module harm_yosys_probe(input logic a, output logic y); assign y = a; endmodule\n")
    execute_process(COMMAND "${yosys}" -q -p "read_slang ${sv}"
                    RESULT_VARIABLE rc OUTPUT_QUIET ERROR_QUIET)
    if(rc EQUAL 0)
        set(${out} TRUE PARENT_SCOPE)
    endif()
endfunction()
