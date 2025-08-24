#ifndef UTILS_H
#define UTILS_H

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct {
  Node **nodes;
  int depth;
} Stack;

// --------------------------stack-----------------------
Stack *create_stack();
void push(Stack *stack, Node *node);
Node *pop(Stack *stack);
Node *peek(Stack *stack);
bool is_empty_stack(Stack *stack);
void free_stack(Stack *stack);

// --------------------------binary tree------------------------
Node *create_tree();
Node *initialize_tree(int *source);
void free_tree(Node *node);
bool is_empty_tree(Node *tree);

void preorder_traversal(Node *node);
void not_incur_preorder_traversal(Node *node);
void inorder_traversal(Node *node);
void not_incur_inorder_traversal(Node *node);
void postorder_traversal(Node *node);
void not_incur_postorder_traversal(Node *node);
void level_order_traversal(Node *node);
Node *search(Node *root, int target);

// ------------------superior operation on binary tree-------------
int get_height(Node *root);              // 获取树高度
int get_size(Node *node);                // 获取树结点数
int get_leaf_size(Node *node);           // 获取叶子结点数
int get_k_level_size(Node *node, int k); // 获取第k层结点数
int get_level(Node *root, Node *key);    // 获取结点所在层数
Node *get_parent(Node *root, Node *key);

#endif
