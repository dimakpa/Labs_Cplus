cmake_minimum_required(VERSION 3.20)
project(Lab4_3_Map_)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


add_executable(Lab4_3_Map_ test.cpp Maap.h)

target_link_libraries(Lab4_3_Map_ gtest gtest_main)
