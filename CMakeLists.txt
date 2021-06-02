cmake_minimum_required(VERSION 3.0.0)
project(abi-break)

include_directories(${CMAKE_SOURCE_DIR}/includes/)

add_library(simple_string SHARED ${CMAKE_SOURCE_DIR}/src/simple_string.cpp)

add_executable(abi-break ${CMAKE_SOURCE_DIR}/src/abi_break.cpp)

target_link_libraries(abi-break simple_string)
