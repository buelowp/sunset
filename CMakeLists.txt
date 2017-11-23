cmake_minimum_required (VERSION 3.0.0)
project (SUNSET)

add_library (sunset SHARED firmware/SunSet.cpp)

install (TARGETS sunset DESTINATION lib)
install (FILES "${PROJECT_BINARY_DIR}/firmware/SunSet.h" DESTINATION include)
