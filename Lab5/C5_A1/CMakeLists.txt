# minimum cmake version (usually ok above 2.8)
cmake_minimum_required(VERSION 3.3)

# the name of this project
project(Container)

# make sure the compiler build c++11 code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add all .h and .cpp files to the source list
file(GLOB SOURCE_FILES "*.h" "*.cpp")

# the name of our target (executable)
set (TARGET_NAME "Container")

add_executable(${TARGET_NAME} ${SOURCE_FILES})