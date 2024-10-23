set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_NO_SYSTEM_PATHS ON)
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/third_party/boost)
set(BOOST_INCLUDEDIR ${CMAKE_SOURCE_DIR}/third_party/boost/include )
set(BOOST_LIBRARYDIR ${CMAKE_SOURCE_DIR}/third_party/boost/lib )

find_package(Boost 1.83 COMPONENTS regex) 

set(BoostLinkedLibaries)
foreach(lib_target ${Boost_LIBRARIES})
    get_target_property(lib_location ${lib_target} LOCATION)
    list(APPEND BoostLinkedLibaries ${lib_location})
endforeach()
