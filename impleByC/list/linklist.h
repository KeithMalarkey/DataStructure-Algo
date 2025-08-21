#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct {
  int data;          // 数据域
  struct Node *next; // 指针域，指向下一个节点
} LinkNode;

#endif