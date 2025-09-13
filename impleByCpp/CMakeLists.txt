cmake_minimum_required(VERSION 4.1.1)
project(DS&Algo-impleByCpp)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 23)
add_library(lib src/array/arrayImple.cc src/graph/graphImple.cc src/list/listImple.cc src/others/unionset.cc src/search/searchImple.cc src/tree/treeImple.cc)
target_include_directories(lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(main src/main.cc)
target_link_libraries(main lib)

enable_testing()
add_subdirectory(tests)