#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdbool.h>

// ---------Singly Linked List
typedef int NodeData;
typedef char _NodeData;
typedef struct Node {
  NodeData data;
  struct Node *next;
} LinkNode;

typedef struct {
  int size;
  LinkNode *head;
  LinkNode *tail;
} LinkList;

// ---------Doubly Linked List
typedef struct DNode {
  NodeData data;
  struct DNode *prev;
  struct DNode *next;
} DNode;

typedef struct {
  int size;
  DNode *head;
  DNode *tail;
} DLinkList;

// ---------Doubly Circular Linked List
typedef struct CNode {
  NodeData data;
  struct CNode *prev;
  struct CNode *next;
} CNode;

typedef struct {
  int size;
  struct CNode *head;
} CLinkList;

// ---------utils
struct MapEntry {
  int pos;
  LinkNode *node;
};

typedef struct {
  int size;
  int capacity;
  struct MapEntry *entries;
} Map;

void test_on_linklist(); // 测试单链表

//-------------------------------LinkList-------------------------
void free_map(Map *map);                                // 释放map
void print_map(Map *map);                               // 打印map
bool isEmptyList(const LinkList *list);                 // 判断链表是否为空
LinkNode *create_node(NodeData *data);                  // 创建node
LinkList *initList();                                   // 创建链表
void print_list(LinkList *list);                        // 打印链表
void create_list(int arr[]);                            // 创建链表
void destroyList(LinkList *list);                       // 销毁链表
void insertNode2head(LinkList *list, LinkNode *node);   // 插入结点到head
void insertNode2tail(LinkList *list, LinkNode *node);   // 插入结点到tail
int map_append(Map *map, int position, LinkNode *data); // 向map中添加元素
void deleteNode(LinkList *list, NodeData data); // 删除所有data为data的结点
void _deleteNode(LinkList *list, int position); // 删除指定位置的结点
void deletehead(LinkList *list);                // 删除head结点
void deletetail(LinkList *list);                // 删除tail结点
void map_init(Map *map);                        // 初始化map
void reverse_list(LinkList *list);              // 反转链表
Map *checkin_node(LinkList *list);              // 选择链表中data为data的结点

//-------------------------------TLinkList-------------------------

#endif
