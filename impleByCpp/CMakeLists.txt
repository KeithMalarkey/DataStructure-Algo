cmake_minimum_required(VERSION 4.1.1)
project(impleByCpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(array)
include_directories(list)

add_executable(impleByCpp
        array/array_utils.h
        array/main.cc
        list/main.cc
        list/utils.h)
