cmake_minimum_required (VERSION 3.0.0)
project (sunset)

set (CMAKE_CXX_STANDARD 11)
set (SOURCES src/SunSet.cpp)
set (HEADERS src/SunSet.h)

add_library (${PROJECT_NAME} SHARED ${SOURCES})

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include)
