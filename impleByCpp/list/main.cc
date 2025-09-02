#include "utils.h"
#include <iostream>

int main() {
  ListNode &node = create_node(10);
  std::cout << node.data << std::endl;
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  print_list(list);
  reverse_list(list);
  print_list(list);
  std::vector<int> &result = search_node(list, 14);
  for (auto index : result) {
    std::cout << index << " ";
  }
  std::cout << std::endl;
  delete_node(list, 14);
  if (list.head == nullptr) {
    std::cout << "list is empty\n";
  } else {
    print_list(list);
  }
  delete_list(list);

  return 0;
}

void insert_on_tail(LinkList &list, const NodeVal &val) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  if (node == nullptr) {
    std::cout << "memory allocation failure\n";
    std::exit(EXIT_FAILURE);
  }
  node->data = val;
  node->next = nullptr;
  if (list.head == nullptr) {
    list.head = node;
    list.tail = node;
  } else {
    list.tail->next = node;
    list.tail = node;
  }
}

void insert_on_head(LinkList &list, const NodeVal &val) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  if (node == nullptr) {
    std::cout << "memory allocation failure\n";
    std::exit(EXIT_FAILURE);
  }
  node->data = val;
  node->next = list.head;
  list.head = node;
}

void reverse_list(LinkList &list) {
  ListNode *prev = nullptr;
  ListNode *curr = list.head;
  while (curr != nullptr) {
    ListNode *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
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

ListNode &create_node(const NodeVal &val) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  if (node == nullptr) {
    std::cout << "memory allocation failure\n";
    std::exit(EXIT_FAILURE);
  }
  node->data = val;
  node->next = nullptr;
  return *node;
}

LinkList &create_list_with_tailinsert(const std::vector<NodeVal> &vals) {
  LinkList *list = (LinkList *)malloc(sizeof(LinkList));
  if (list == nullptr) {
    std::cout << "memory allocation failure\n";
    std::exit(EXIT_FAILURE);
  }
  list->head = nullptr;
  list->tail = nullptr;
  for (auto val : vals) {
    insert_on_tail(*list, val);
  }
  return *list;
}

LinkList &create_list_with_headinsert(const std::vector<NodeVal> &vals) {
  LinkList *list = (LinkList *)malloc(sizeof(LinkList));
  if (list == nullptr) {
    std::cout << "memory allocation failure\n";
    std::exit(EXIT_FAILURE);
  }
  list->head = nullptr;
  list->tail = nullptr;
  for (auto val : vals) {
    insert_on_head(*list, val);
  }
  return *list;
}

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
      delete curr;
      curr = nullptr;
    }
    prev = curr;
    if (curr != nullptr) {
      curr = curr->next;
    }
  }
}

void delete_list(LinkList &list) {
  ListNode *node = list.head;
  while (node != nullptr) {
    ListNode *next = node->next;
    free(node);
    node = next;
  }
  list.head = nullptr;
  list.tail = nullptr;
}