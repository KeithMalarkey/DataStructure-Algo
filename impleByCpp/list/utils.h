#ifndef UTILS_H
#define UTILS_H

#include <vector>
typedef int NodeVal;
typedef struct ListNode {
  NodeVal data;
  struct ListNode *next;
} ListNode;

typedef struct {
  ListNode *head;
  ListNode *tail;
} LinkList;

void insert_on_tail(LinkList &list, const NodeVal &val);
void insert_on_head(LinkList &list, const NodeVal &val);
void print_list(const LinkList &list);
void reverse_list(LinkList &list);
void delete_node(LinkList &list, const NodeVal &val);
void delete_list(LinkList &list);
std::vector<int> &search_node(const LinkList &list, const NodeVal &val);
ListNode &create_node(const NodeVal &val);
LinkList &create_list_with_headinsert(const std::vector<NodeVal> &vals);
LinkList &create_list_with_tailinsert(const std::vector<NodeVal> &vals);

#endif