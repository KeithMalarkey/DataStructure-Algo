#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int NULL_NODE = -(1 << 10);

typedef int NodeData;

typedef struct Node {
  NodeData data;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct {
  Node **nodes;
  int depth;
} Stack;

typedef struct QueueNode {
  Node *node;
  struct QueueNode *next;
} QueueNode;

typedef struct {
  int length;
  QueueNode *front;
  QueueNode *rear;
} Queue;


// -------------------------------queue--------------------------
Queue *create_queue();
Node *dequeue(Queue *queue);
Node *peek_front(Queue *queue);
void enqueue(Queue *queue, Node *node);
bool is_empty_queue(Queue *queue);
void free_queue(Queue *queue);

// -------------------------------binary tree--------------------
bool is_empty_tree(Node *root);
Node *create_tree_node(NodeData data);
Node *initialize_tree(NodeData *source);
void level_order_traversal(Node *root);
void pre_order_traversal(Node *root);
void in_order_traversal(Node *root);
void post_order_traversal(Node *root);
void free_tree(Node *node);

// -------------------------------bst-----------------------------
Node *search_on_bst(Node *root, int target);

#endif
