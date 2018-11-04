CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

add_subdirectory(Lib)

add_executable(Calendar Calendar.cpp)
target_link_libraries(Calendar Date)