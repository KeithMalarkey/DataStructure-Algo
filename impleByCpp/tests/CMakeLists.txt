# 查找GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 添加测试可执行文件
add_executable(test_array test_array.cc)
add_executable(test_graph test_graph.cc)
add_executable(test_list test_list.cc)
add_executable(test_search test_search.cc)
add_executable(test_tree test_tree.cc)

# 链接库和gtest
target_link_libraries(test_array ${GTEST_LIBRARIES})
target_link_libraries(test_graph ${GTEST_LIBRARIES})
target_link_libraries(test_list ${GTEST_LIBRARIES})
target_link_libraries(test_search ${GTEST_LIBRARIES})
target_link_libraries(test_tree ${GTEST_LIBRARIES})


# 添加测试用例
target_link_libraries(test_array lib GTest::GTest GTest::Main)
target_link_libraries(test_graph lib GTest::GTest GTest::Main)
target_link_libraries(test_list lib GTest::GTest GTest::Main)
target_link_libraries(test_search lib GTest::GTest GTest::Main)
target_link_libraries(test_tree lib GTest::GTest GTest::Main)

# 添加测试用例
add_test(NAME ArrayTests COMMAND test_array)
add_test(NAME GraphTests COMMAND test_graph)
add_test(NAME ListTests COMMAND test_list)
add_test(NAME SearchTests COMMAND test_search)
add_test(NAME TreeTests COMMAND test_tree)
