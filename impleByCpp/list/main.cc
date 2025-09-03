#include "utils.h"


int main() {
  ListNode &node = create_node(10);
  std::cout << node.data << std::endl;
  std::vector<NodeVal> vals{21, 53, 14, 85, 91, 14};
  LinkList &list = create_list_with_tailinsert(vals);
  print_list(list);
  std::cout << get_mid_node(list).data << std::endl;
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
  std::cout << "mid node data: " << get_mid_node(list).data << std::endl;
  delete_list(list);

  return 0;
}

/**
 * @brief Create a node object with the given value.
 *
 * @param val
 * @return ListNode&
 */
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

void insert_on_tail(LinkList &list, const NodeVal &val) {
  ListNode &node= create_node(val);
  if (list.head == nullptr) {
    list.head = &node;
    list.tail = &node;
  } else {
    list.tail->next = &node;
    list.tail = &node;
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



/**
 * @brief Create a list with tailinsert method.
 * 
 * @param vals values to be inserted.
 * @return LinkList& 
 */
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

/**
 * @brief Create a list with headinsert method.
 * 
 * @param vals values to be inserted.
 * @return LinkList& 
 */
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
      delete curr;
      curr = nullptr;
    }
    prev = curr;
    if (curr != nullptr) {
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