cmake_minimum_required (VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)
project (Test)

add_subdirectory(../Lib build)

add_executable(exec TestDate.cpp)

target_link_libraries(exec Date)

