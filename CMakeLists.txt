cmake_policy (SET CMP0054 NEW)
cmake_minimum_required (VERSION 3.0.2)
project (sunset)

option (BUILD_TESTS "Build Google test capability (default OFF)" OFF)
option (SUNSET_BUILD_SHARED "Build as a shared object (default ON)" ON)

file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file (GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

set (CMAKE_CXX_STANDARD 14)

set(PROJ_VERSION_MAJOR 1)
set(PROJ_VERSION_MINOR 1)
set(PROJ_VERSION_PATCH 5)
set(PROJ_VERSION ${PROJ_VERSION_MAJOR}.${PROJ_VERSION_MINOR}.${PROJ_VERSION_PATCH} )

if(SUNSET_BUILD_SHARED)
    add_library (${PROJECT_NAME} SHARED ${SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJ_VERSION} SOVERSION ${PROJ_VERSION_MAJOR} )
else()
    add_library (${PROJECT_NAME} STATIC ${SOURCES})
endif()
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wno-long-long -pedantic)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include)

if (BUILD_TESTS)
    enable_testing()
    find_package (GTest REQUIRED)
    find_package(Threads REQUIRED)

    file (GLOB TESTS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
    
    if(THREADS_HAVE_PTHREAD_ARG)
        target_compile_options(${PROJECT_NAME}-test PUBLIC "-pthread")
    endif()
    
    include_directories(${GTEST_INCLUDE_DIR})
    add_executable(${PROJECT_NAME}-test ${TESTS} ${HEADERS})
    target_link_libraries(${PROJECT_NAME}-test ${GTEST_LIBRARIES} ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()


