cmake_minimum_required(VERSION 4.1)
set(CMAKE_C_COMPILER "gcc")
project(DS-Algo VERSION 1.0.0 LANGUAGES C DESCRIPTION "Data Structure and Algorithm")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE srcs "${CMAKE_SOURCE_DIR}/src/*.c")
add_library(lib SHARED ${srcs})
target_include_directories(lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} lib)


