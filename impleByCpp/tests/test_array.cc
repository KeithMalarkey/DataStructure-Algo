#include "core_api/array_utils.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

// bubble_sort
TEST(ArrayTest, bubble_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::bubble_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// quick_sort
TEST(ArrayTest, quick_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::quick_sort(list, 0, list.size() - 1);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// selection_sort
TEST(ArrayTest, selection_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::selection_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// insertion_sort
TEST(ArrayTest, insertion_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::insertion_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// heap_sort
TEST(ArrayTest, heap_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::heap_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// merge_sort
TEST(ArrayTest, merge_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::merge_sort(list, 0, list.size() - 1);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// shell_sort
TEST(ArrayTest, shell_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::shell_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// count_sort
TEST(ArrayTest, count_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::count_sort(list, *std::min_element(list.begin(), list.end()),
             *std::max_element(list.begin(), list.end()));
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// opt_bubble_sort
TEST(ArrayTest, opt_bubble_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::opt_bubble_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}

// radix_sort
TEST(ArrayTest, radix_sort) {
  std::vector<int> list{5, 3, 8, 6, 2, 7, 1, 9, 4};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayUtils::radix_sort(list);
  ArrayUtils::printList(list);
  EXPECT_TRUE(list == expected);
}
