set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_NO_SYSTEM_PATHS ON)
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/third_party/boost)
set(BOOST_INCLUDEDIR ${CMAKE_SOURCE_DIR}/third_party/boost/include )
set(BOOST_LIBRARYDIR ${CMAKE_SOURCE_DIR}/third_party/boost/lib )

find_package(Boost 1.83 COMPONENTS regex) 

set(BoostLinkedLibraries)
foreach(lib_target IN LISTS Boost_LIBRARIES)
    if(TARGET ${lib_target})
        # It's a CMake target (e.g., Boost::regex)
        get_target_property(lib_location ${lib_target} IMPORTED_LOCATION_RELEASE)
        if(NOT lib_location)
            get_target_property(lib_location ${lib_target} IMPORTED_LOCATION)
        endif()
    else()
        # Not a target – assume it's a full path or library name
        set(lib_location ${lib_target})
    endif()

    list(APPEND BoostLinkedLibraries ${lib_location})
endforeach()

message(STATUS "All Boost linked libraries: ${BoostLinkedLibraries}")
