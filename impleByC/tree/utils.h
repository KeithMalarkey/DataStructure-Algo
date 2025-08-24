#ifndef UTILS_H
#define UTILS_H
#define NULL_NODE '#'

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char NodeData;
// typedef int NodeData; // alternative data type
typedef struct Node {
  NodeData data;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct {
  Node **nodes;
  int size; // depth of the stack
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

// --------------------------utils-----------------------
void dfs(Node *node); // 深度优先遍历

// --------------------------stack-----------------------
Stack *create_stack();               // 创建栈
void push(Stack *stack, Node *node); // 入栈
Node *pop(Stack *stack);             // 出栈
Node *peek(Stack *stack);            // 取栈顶结点
bool is_empty_stack(Stack *stack);   // 判空栈
void free_stack(Stack *stack);       // 释放栈内存

// --------------------------queue-----------------------
Queue *create_queue();                     // 创建队列
void queue_push(Queue *queue, Node *node); // 入队
Node *queue_pop(Queue *queue);             // 出队
Node *peek_front(Queue *queue);            // 取队头
bool is_empty_queue(Queue *queue);         // 判空队列
void free_queue(Queue *queue);             // 释放队列内存

// --------------------------binary tree------------------------
bool single_pattern(NodeData *source);      // 是否为单一字符模式
Node *create_tree();                        // 创建树
Node *initialize_tree(NodeData *source);    // 初始化树
Node **initialize_trees(NodeData **source); // 初始化树群
void free_tree(Node *node);                 // 置空树
bool is_empty_tree(Node *tree);             // 判空树

void preorder_traversal(Node *node);            // 递归先序遍历
void not_incur_preorder_traversal(Node *node);  // 非递归先序遍历
void inorder_traversal(Node *node);             // 递归中序遍历
void not_incur_inorder_traversal(Node *node);   // 非递归中序遍历
void postorder_traversal(Node *node);           // 递归后序遍历
void not_incur_postorder_traversal(Node *node); // 非递归后序遍历
void level_order_traversal(Node *node);         // 层序遍历
Node *search(Node *root, NodeData target);      // 查找结点

// ------------------superior operation on binary tree-------------
bool is_same_tree(Node *s, Node *t);     // 判断两棵树是否相同
bool is_symmetric(Node *root);           // 判断是否为对称树
bool is_balanced(Node *root);            // 判断是否为平衡树
bool is_complete(Node *root);            // 判断是否为完全二叉树
bool is_valid_bst(Node *root);           // 判断是否为合法的二叉搜索树
bool is_valid_bst_util(Node *root, Node *min_node, Node *max_node); // 辅助函数
bool is_valid_bst_rec(Node *root);       // 递归判断是否为合法的二叉搜索树
bool is_valid_bst_iter(Node *root);      // 迭代判断是否为合法的二叉搜索树
bool is_valid_bst_rec_util(Node *root, Node *min_node, Node *max_node,
                           int *count); // 辅助函数
bool is_valid_bst_iter_util(Node *root, Node *min_node, Node *max_node,
                            int *count); // 迭代辅助函数
bool is_valid_bst_rec_util_v2(Node *root, Node *min_node, Node *max_node,
                              int *count); // 迭代辅助函数
int get_height(Node *root);              // 获取树高度
int get_size(Node *node);                // 获取树结点数
int get_leaf_size(Node *node);           // 获取叶子结点数
int get_k_level_size(Node *node, int k); // 获取第k层结点数
int get_level(Node *root, Node *key);    // 获取结点所在层数
int max_width(Node *root);               // 获取二叉树的宽度
int min_depth(Node *root);               // 获取二叉树的最小深度
void invert_tree(Node *root);            // 镜像翻转二叉树
void collect_leaves(Node *root, Node *leaves[], int *count); // 收集叶子节点
Node *get_parent(Node *root, Node *key);                     // 获取结点的父结点
Node *get_twin(Node *root, Node *key); // 获取结点的兄弟结点
Node *get_lowest_common_ancestor(Node *root, Node *a,
                                 Node *b);   // 获取结点a,b的公共前驱结点
Node **get_leafs(Node *root, int leaf_size); // 获取所有叶子结点数组

#endif