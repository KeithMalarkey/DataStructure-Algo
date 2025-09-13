#include "core_api/list_utils.h"
#include <gtest/gtest.h>

// #1 create_node
TEST(ListTest, create_node) {
  ListNode &node = create_node(10);
  EXPECT_EQ(node.data, 10);
  EXPECT_EQ(node.next, nullptr);
}

// #2 create_list_with_headinsert
TEST(ListTest, create_list_with_headinsert) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList list = create_list_with_headinsert(vals);
  EXPECT_EQ(list.head->data, 14);
  EXPECT_EQ(list.tail->data, 21);
  EXPECT_EQ(list.head->next->data, 91);
  EXPECT_EQ(list.head->next->next->data, 85);
  EXPECT_EQ(list.head->next->next->next->data, 14);
  EXPECT_EQ(list.head->next->next->next->next->data, 53);
  delete_list(list);
}

// #3 create_list_with_tailinsert
TEST(ListTest, create_list_with_tailinsert) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  EXPECT_EQ(list.head->data, 21);
  EXPECT_EQ(list.tail->data, 14);
  EXPECT_EQ(list.head->next->data, 53);
  EXPECT_EQ(list.head->next->next->data, 14);
  EXPECT_EQ(list.head->next->next->next->data, 85);
  delete_list(list);
}
// #4 print_list
TEST(ListTest, print_list) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  print_list(list);
  delete_list(list);
}

// #5 get_mid_node
TEST(ListTest, get_mid_node) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  std::vector<NodeVal> _vals{21, 53, 14, 75, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  LinkList &list1 = create_list_with_tailinsert(_vals);
  EXPECT_EQ(get_mid_node(list).data, 85); // note: mid node is 85
  EXPECT_EQ(get_mid_node(list1).data, 75);
  delete_list(list);
  delete_list(list1);
}

// #6 reverse_list
TEST(ListTest, reverse_list) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  print_list(list);
  reverse_list(list);
  print_list(list);
  EXPECT_EQ(list.head->data, 14);
  EXPECT_EQ(list.tail->data, 21);
  delete_list(list);
}

// #7 search_node
TEST(ListTest, search_node) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  std::vector<int> &result = search_node(list, 14);
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0], 2);
  EXPECT_EQ(result[1], 5);
  delete_list(list);
}

// #8 delete_node
TEST(ListTest, delete_node) {
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  delete_node(list, 14);
  EXPECT_EQ(list.head->data, 21);
  EXPECT_EQ(list.tail->data, 91);
  delete_node(list, 21);
  EXPECT_EQ(list.head->data, 53);
  delete_list(list);
}
