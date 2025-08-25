#ifndef LINKLIST_H
#define LINKLIST_H

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

//-------------------------------LinkList-------------------------
LinkNode *create_node(NodeData *data);                // 创建node
LinkList *initList();                                 // 创建链表
void destroyList(LinkList *list);                     // 销毁链表
void insertNode2head(LinkList *list, LinkNode *node); // 插入结点到head
void insertNode2tail(LinkList *list, LinkNode *node); // 插入结点到tail
void deleteNode(LinkList *list, NodeData data); // 删除所有data为data的结点
//-------------------------------TLinkList-------------------------

#endif