#include "core_api/list_utils.h"
#include <iostream>

/**
 * @brief Create a node object with the given value.
 *
 * @param val
 * @return ListNode&
 */
ListNode &create_node(const NodeVal &val) {
  ListNode *node = new ListNode(val);
  return *node;
}

void insert_on_tail(LinkList &list, const NodeVal &val) {
  ListNode &node = create_node(val);
  if (list.head == nullptr) {
    list.head = &node;
    list.tail = &node;
  } else {
    list.tail->next = &node;
    list.tail = &node;
  }
}

void insert_on_head(LinkList &list, const NodeVal &val) {
  ListNode &node = create_node(val);
  node.next = list.head;
  list.head = &node;
  if (list.tail == nullptr) {
    list.head = &node;
    list.tail = &node;
  }
}

void reverse_list(LinkList &list) {
  ListNode *record = list.head;
  ListNode *prev = nullptr;
  ListNode *curr = list.head;
  while (curr != nullptr) {
    ListNode *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  list.tail = record;
  list.head = prev;
}

std::vector<int> &search_node(const LinkList &list, const NodeVal &val) {
  std::vector<int> *result = new std::vector<int>();
  ListNode *node = list.head;
  int index = 0;
  while (node != nullptr) {
    if (node->data == val) {
      result->push_back(index);
    }
    node = node->next;
    index++;
  }
  return *result;
}

void print_list(const LinkList &list) {
  ListNode *node = list.head;
  while (node != nullptr) {
    std::cout << node->data << " ";
    node = node->next;
  }
  std::cout << std::endl;
}

/**
 * @brief Create a list with tailinsert method.
 *
 * @param vals values to be inserted.
 * @return LinkList&
 */
LinkList &create_list_with_tailinsert(const std::vector<NodeVal> &vals) {
  LinkList *list = new LinkList();
  if (list == nullptr) {
    std::cout << "memory allocation failure\n";
    std::exit(EXIT_FAILURE);
  }
  for (auto val : vals) {
    insert_on_tail(*list, val);
  }
  return *list;
}

/**
 * @brief Create a list with headinsert method.
 *
 * @param vals values to be inserted.
 * @return LinkList&
 */
LinkList create_list_with_headinsert(const std::vector<NodeVal> &vals) {
  LinkList list;
  for (auto &val : vals) {
    insert_on_head(list, val);
  }
  return list;
}

/**
 * @brief Delete the node with the given value from the linked list.
 *
 * @param list
 * @param val
 */
void delete_node(LinkList &list, const NodeVal &val) {
  ListNode *prev = nullptr;
  ListNode *curr = list.head;
  while (curr != nullptr) {
    if (curr->data == val) {
      if (prev == nullptr) {
        list.head = curr->next;
      } else {
        prev->next = curr->next;
      }
      if (curr == list.tail) {
        list.tail = prev;
      }
      ListNode *record = curr->next;
      delete curr;
      curr = record;
    }
    if (curr != nullptr) {
      prev = curr;
      curr = curr->next;
    }
  }
}

/**
 * @brief Delete the entire linked list.
 *
 * @param list
 */
void delete_list(LinkList &list) {
  ListNode *node = list.head;
  while (node != nullptr) {
    ListNode *next = node->next;
    delete node;
    node = next;
  }
  list.head = nullptr;
  list.tail = nullptr;
}

/**
 * @brief Get the mid node object of the given linked list.
 *
 * @param list
 * @return ListNode&
 */
ListNode &get_mid_node(const LinkList &list) {
  ListNode *slow = list.head;
  ListNode *fast = list.head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return *slow;
}