#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int NodeValue;
typedef struct TreeNode {
  NodeValue value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

// -------- Threaded Binary Tree

typedef struct ThreadedTreeNode {
  NodeValue value;
  struct ThreadedTreeNode *left;
  struct ThreadedTreeNode *right;
  bool isLeftThreaded;  // true if left child is threaded
  bool isRightThreaded; // true if right child is threaded
} ThreadedTreeNode;

ThreadedTreeNode *createThreadedTreeNode(NodeValue value);
void deleteThreadedTreeNode(ThreadedTreeNode *node);

// -------- AVL
ThreadedTreeNode *createThreadedTreeNode(NodeValue value);
ThreadedTreeNode *initThreadedBinaryTree(ThreadedTreeNode *root, int size);
void threaded_left_rotate(ThreadedTreeNode **root);
void threaded_right_rotate(ThreadedTreeNode **root);
void threaded_insert(ThreadedTreeNode **root, ThreadedTreeNode *node);
void threaded_delete(ThreadedTreeNode **root, ThreadedTreeNode *node);
void inorder_threaded_traversal(ThreadedTreeNode *root);
void preorder_threaded_traversal(ThreadedTreeNode *root);
void postorder_threaded_traversal(ThreadedTreeNode *root);

// -------- BST

// -------- Huffman

#endif