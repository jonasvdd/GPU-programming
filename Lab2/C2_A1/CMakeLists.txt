cmake_minimum_required(VERSION 3.9)
project(Verify)

set(VERIY_SRCS  Check.h Check.cpp
                Name.h Name.cpp
                Verify.h Verify.cpp
                ZipInfo.h ZipInfo.cpp)

set(LIB_TYPE STATIC)
add_library(verify_lib ${LIB_TYPE} ${VERIY_SRCS})

set(CMAKE_CXX_STANDARD 11)

include_directories ("${PROJECT_SOURCE_DIR}")
add_executable(Verify.exe BootstrapVerify.cpp)

target_link_libraries(Verify.exe verify_lib)
add_dependencies(Verify.exe verify_lib)