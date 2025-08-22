#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct Node {
  int data;          // 数据域
  struct Node *next; // 指针域，指向下一个节点
} LinkNode;

typedef struct {
  LinkNode *head; // 链表头指针
} LinkList;

LinkList *createList();                    // 创建链表
void destroyList(LinkList *list);          // 销毁链表
void insertNode(LinkList *list, int data); // 插入节点
void deleteNode(LinkList *list, int data); // 删除节点
#endif