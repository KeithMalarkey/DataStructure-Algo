#include "core_api/array_utils.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

// bubble_sort
TEST(ArrayTest, bubble_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  bubble_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// quick_sort
TEST(ArrayTest, quick_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  quick_sort(list, 0, list.size() - 1);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// selection_sort
TEST(ArrayTest, selection_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  selection_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// insertion_sort
TEST(ArrayTest, insertion_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  insertion_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// heap_sort
TEST(ArrayTest, heap_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  heap_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// merge_sort
TEST(ArrayTest, merge_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  merge_sort(list, 0, list.size() - 1);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// shell_sort
TEST(ArrayTest, shell_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  shell_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// count_sort
TEST(ArrayTest, count_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  count_sort(list, *std::min_element(list.begin(), list.end()),
             *std::max_element(list.begin(), list.end()));
  printList(list);
  EXPECT_TRUE(list == expected);
}

// opt_bubble_sort
TEST(ArrayTest, opt_bubble_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  opt_bubble_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}

// radix_sort
TEST(ArrayTest, radix_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  radix_sort(list);
  printList(list);
  EXPECT_TRUE(list == expected);
}
