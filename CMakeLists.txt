cmake_policy (SET CMP0054 NEW)
cmake_minimum_required (VERSION 3.0.0)
project (sunset)

option (PACKAGE_TESTING "Build google tests" OFF)

set (CMAKE_CXX_STANDARD 14)
set (SOURCES src/SunSet.cpp)
set (HEADERS src/SunSet.h)
set (CMAKE_CXX_FLAGS -pthread)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

FILE (GLOB TESTS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(PROJ_VERSION_MAJOR 1)
set(PROJ_VERSION_MINOR 0)
set(PROJ_VERSION_PATCH 0)
set(PROJ_VERSION ${PROJ_VERSION_MAJOR}.${PROJ_VERSION_MINOR}.${PROJ_VERSION_PATCH} )

add_library (${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJ_VERSION} SOVERSION ${PROJ_VERSION_MAJOR} )

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include)

if (PACAKGE_TESTING)
    enable_testing()
    find_package (GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIR})
    add_executable(${PROJECT_NAME}-test ${TESTS} ${HEADERS})
    target_link_libraries(${PROJECT_NAME}-test ${GTEST_LIBRARIES} ${PROJECT_NAME})
endif()


