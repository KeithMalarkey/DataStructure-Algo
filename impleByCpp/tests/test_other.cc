#include "utils/skiplist.h"
#include "gtest/gtest.h"
#include <string>

TEST(SKIP_TEST, INSERT) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");
  skipList.display();
}

TEST(SKIP_TEST, SEARCH) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");

  EXPECT_TRUE(skipList.search(3));
  EXPECT_TRUE(skipList.search(1));
  EXPECT_TRUE(skipList.search(5));
  EXPECT_FALSE(skipList.search(6));
}

TEST(SKIP_TEST, REMOVE) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");

  EXPECT_TRUE(skipList.remove(3));
  EXPECT_FALSE(skipList.search(3));
  EXPECT_TRUE(skipList.remove(1));
  EXPECT_FALSE(skipList.search(1));
  EXPECT_TRUE(skipList.remove(5));
  EXPECT_FALSE(skipList.search(5));
  EXPECT_TRUE(skipList.remove(2));
  EXPECT_FALSE(skipList.search(2));
  EXPECT_TRUE(skipList.remove(4));
}

TEST(SKIP_TEST, RANGE_QUERY) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");

  std::vector<std::pair<int, std::string>> result = skipList.rangeQuery(2, 4);
  EXPECT_EQ(result.size(), 3); // actual size should be 3
  EXPECT_EQ(result[0].first, 2);
  EXPECT_EQ(result[0].second, "Date");
  EXPECT_EQ(result[1].first, 3);
  EXPECT_EQ(result[1].second, "Apple");
}

TEST(SKIP_TEST, GET_VALUE) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");

  EXPECT_TRUE(*skipList.get(2) == "Date");
}

TEST(SKIP_TEST, MIN_MAX) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");

  EXPECT_EQ(skipList.minimum(), 1);
  EXPECT_EQ(skipList.maximum(), 5);
}

TEST(SKIP_TEST, SIZE) {
  SkipList<int, std::string> skipList;
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");
  skipList.display();
  skipList.insert(4, "Blueberry");
  skipList.display();

  EXPECT_EQ(skipList.size(), 5);
}

TEST(SKIP_TEST, EMPTY_CLEAR) {
  SkipList<int, std::string> skipList;
  EXPECT_TRUE(skipList.empty());
  skipList.insert(3, "Apple");
  skipList.insert(1, "Banana");
  skipList.insert(5, "Cherry");
  skipList.insert(2, "Date");
  skipList.insert(4, "Elderberry");
  EXPECT_FALSE(skipList.empty());
  skipList.clear();
}
