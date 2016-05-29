cmake_minimum_required(VERSION 3.5)
project(codeperf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES counter.cpp counter.h interval.cpp interval.h stats.cc stats.h)

add_library(codeperf ${SOURCE_FILES})

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
add_executable(test-codeperf test.cpp)
target_link_libraries(test-codeperf codeperf ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(all test-codeperf)

file(GLOB INSTALL_HEADERS "${PROJECT_SOURCE_DIR}/*.h")
install(FILES ${INSTALL_HEADERS}
        DESTINATION include/codeperf)
install(TARGETS codeperf
        ARCHIVE DESTINATION lib)
