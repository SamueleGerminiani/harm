# H11c, F-L3 acceptance A1: the yosys probe registers the cross-check only for a yosys that can
# run read_slang. Usage: cmake -DSRC=<source dir> -DWORK=<dir> -P check_yosys_probe.cmake
include(${SRC}/cmake/HarmYosysProbe.cmake)
set(fake ${SRC}/tests/input/h11c/fake_yosys)
harm_yosys_has_read_slang(${fake}/no_slang ${WORK} no)
harm_yosys_has_read_slang(${fake}/with_slang ${WORK} yes)
if(no OR NOT yes)
    message(FATAL_ERROR "probe: no_slang -> ${no} (want FALSE), with_slang -> ${yes} (want TRUE)")
endif()
message(STATUS "PASS")
