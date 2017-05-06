cmake_minimum_required (VERSION 3.0.0)
project (SUNSET)

set (CMAKE_CXX_STANDARD 11)
set (SOURCES firmware/SunSet.cpp)
set (HEADERS firmware/SunSet.h)

add_library (sunset SHARED ${SOURCES})

install (TARGETS sunset DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include)


