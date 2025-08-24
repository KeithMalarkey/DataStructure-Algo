
#include "utils.h"
#include <stdbool.h>

/**
 * @brief SAMPLE
 *        A
 *      /   \
 *     B      C
 *    / \    /  \
 *   D   X  E   J
 *  /
 * M
 *        A
 *      /   \
 *     B      C
 *    / \    /  \
 *   D   #  #   J
 *  /
 * M
 * @return int for OS
 * @note: '#' represents NULL_NODE
 */
int main() {
  // Test initialize_tree and traversals
  char *source = "ABCDXEJM";
  // char *source = "ABCD##JM";
  Node *tree = initialize_tree(source);
  if (is_empty_tree(tree)) {
    printf("Tree is empty.\n");
  } else {
    printf("Tree is not empty.\n");
  }
  printf("Inorder traversal: ");
  inorder_traversal(tree);
  printf("\nPreorder traversal: ");
  preorder_traversal(tree);
  printf("\nPostorder traversal: ");
  postorder_traversal(tree);
  printf("\nLevel order traversal: ");
  level_order_traversal(tree);

  printf("\nNot incur Preorder traversal: ");
  not_incur_preorder_traversal(tree);
  printf("\nNot incur Inorder traversal: ");
  not_incur_inorder_traversal(tree);
  printf("\nNot incur Postorder traversal: ");
  not_incur_postorder_traversal(tree);

  // Test superior operations includes height, size, leaf size, level size, node
  // searching, parent searching, twin searching on binary tree
  printf("\nHeight of tree: %d\n", get_height(tree));     // tree height
  printf("Size of tree: %d\n", get_size(tree));           // tree nodes number
  printf("Leaf size of tree: %d\n", get_leaf_size(tree)); // leaf nodes number
  int k = 4;
  printf("Size of level %d: %d\n", k,
         get_k_level_size(tree, k)); // nodes number of k level

  Node *sr = search(tree, 'M'); // search result
  if (sr) {
    printf("Found node with data 'M': %c\n", sr->data);
    printf("Level of node 'M': %d\n", get_level(tree, sr)); // level of node 'M'
    Node *parent = get_parent(tree, sr);
    if (parent) {
      printf("Parent of node 'M': %c\n", parent->data);
    } else {
      printf("Node 'M' has no parent (it might be the root).\n");
    }
  } else {
    printf("Node with data 'M' not found.\n");
  }

  Node *key = search(tree, 'D');
  Node *twin = get_twin(tree, key);
  if (twin) {
    printf("Twin of node 'D': %c\n", twin->data);
  } else {
    printf("Node 'D' has no twin.\n");
  }

  // Test is_same_tree
  char *source2 = "ABCDXEJM";
  Node *tree2 = initialize_tree(source2);
  if (is_same_tree(tree, tree2)) {
    printf("The two trees are the same.\n");
  } else {
    printf("The two trees are different.\n");
  }

  // Test is_symmetric
  char *source3 = "ABCD##JM";
  char *source4 = "ABBDDDDC######C";
  Node **trees = initialize_trees((NodeData *[]){source3, source4, NULL});
  // Test is_same_tree on the two trees
  if (is_same_tree(trees[0], trees[1])) {
    printf("The two trees are the same.\n");
  } else {
    printf("The two trees are different.\n");
  }
  // Test is_symmetric on each tree
  for (int i = 0; trees[i] != NULL; ++i) {
    if (is_symmetric(trees[i])) {
      printf("Tree %d is symmetric.\n", i + 1);
    } else {
      printf("Tree %d is not symmetric.\n", i + 1);
    }
    free_tree(trees[i]);
  }

  // Test get lowest common ancestor
  Node *lca =
      get_lowest_common_ancestor(tree, search(tree, 'X'), search(tree, 'M'));
  if (lca != NULL) {
    printf("lowest common ancestor of 'M' & 'X': %c\n", lca->data);
  } else {
    printf("lowest common ancestor of 'M' & 'X' not found.\n");
  }

  // Test get leaves
  Node **leaves = get_leafs(tree, get_leaf_size(tree));
  printf("All specific leaves are:");
  for (int i = 0; i < get_leaf_size(tree); ++i) {
    printf("%c ", leaves[i]->data);
  }
  printf("\n");
  free(leaves);

  // Test tree width
  char *source5 = "ABC#DXF##KESYU#";
  Node *wt = initialize_tree(source5);
  printf("tree width is %d\n", max_width(wt));
  return 0;
}

// --------------------------queue-----------------------
/**
 * @brief Create a queue object
 *
 * @return Queue* 队列
 */
Queue *create_queue() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  if (queue == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  queue->length = 0;
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

bool is_empty_queue(Queue *queue) {
  return queue == NULL || queue->length == 0;
}

/**
 * @brief 树结点入队
 *
 * @param queue 入队
 * @param node 入队结点指针
 */
void queue_push(Queue *queue, Node *node) {
  if (queue == NULL) {
    fprintf(stderr, "Queue is not initialized\n");
    return;
  }
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->node = node;
  newNode->next = NULL;
  if (queue->length == 0) {
    queue->front = newNode;
    queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
  queue->length++;
}

/**
 * @brief 出队
 *
 * @param queue 队列
 * @return Node* 出队结点指针
 */
Node *queue_pop(Queue *queue) {
  if (is_empty_queue(queue)) {
    fprintf(stderr, "Queue is empty or not initialized\n");
    return NULL;
  }
  Node *node = queue->front->node;
  queue->front = queue->front->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  queue->length--;
  return node;
}

/**
 * @brief 取队头结点
 *
 * @param queue
 * @return Node*
 */
Node *peek_front(Queue *queue) {
  if (is_empty_queue(queue)) {
    fprintf(stderr, "Queue is empty or not initialized\n");
    return NULL;
  }
  return queue->front->node;
}

/**
 * @brief 释放队列内存
 *
 * @param queue
 */
void free_queue(Queue *queue) {
  if (queue == NULL) {
    return;
  }
  QueueNode *current = queue->front;
  while (current != NULL) {
    QueueNode *temp = current;
    current = current->next;
    free(temp);
  }
  free(queue);
}

// --------------------------stack-----------------------
/**
 * @brief Create a stack object
 *
 * @return Stack* 初始化后的栈指针
 */
Stack *create_stack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  if (stack == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  stack->nodes = NULL;
  stack->size = 0;
  return stack;
}

/**
 * @brief 栈判空
 *
 * @param stack 栈指针
 * @return true 空栈
 * @return false 非空栈
 */
bool is_empty_stack(Stack *stack) { return stack == NULL || stack->size == 0; }

/**
 * @brief 结点入栈
 *
 * @param stack 栈指针
 * @param node 入栈结点指针
 */
void push(Stack *stack, Node *node) {
  if (stack == NULL) {
    fprintf(stderr, "Stack is not initialized\n");
    return;
  }
  stack->nodes = realloc(stack->nodes, (stack->size + 1) * sizeof(Node *));
  if (stack->nodes == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  stack->nodes[stack->size++] = node;
}

/**
 * @brief 结点出栈
 *
 * @param stack 栈指针
 * @return Node*  出栈结点指针
 */
Node *pop(Stack *stack) {
  if (stack == NULL || stack->size == 0) {
    fprintf(stderr, "Stack is empty or not initialized\n");
    return NULL;
  }
  Node *node = stack->nodes[--stack->size];
  stack->nodes = realloc(stack->nodes, stack->size * sizeof(Node *));
  if (stack->nodes == NULL && stack->size > 0) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  return node;
}

/**
 * @brief 取栈顶结点
 *
 * @param stack
 * @return Node* 栈顶结点
 */
Node *peek(Stack *stack) {
  if (is_empty_stack(stack)) {
    fprintf(stderr, "Stack is empty or not initialized\n");
    return NULL;
  }
  return stack->nodes[stack->size - 1];
}

void free_stack(Stack *stack) {
  if (is_empty_stack(stack)) {
    return;
  }
  free(stack->nodes);
  free(stack);
}

// --------------------------binary tree------------------------
/**
 * @brief Create a tree object
 *
 * @return Node* 初始化后的树根root指针
 */
Node *create_tree() {
  Node *root = malloc(sizeof(Node));
  if (root == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  root->data = NULL_NODE;
  root->left = NULL;
  root->right = NULL;
  return root;
}

/**
 * @brief 若source中全为NULL_NODE,则视为单一字符模式
 *
 * @param source 构建字符数组
 * @return true 单一字符模式
 * @return false 非单一字符模式
 */
bool single_pattern(NodeData *source) {
  int len = strlen(source);
  for (int i = 0; i < len; ++i) {
    if (source[i] != NULL_NODE) {
      return false;
    }
  }
  return true;
}

/**
 * @brief 树初始化
 *
 * @param source 结点数据源
 * @return Node* root指针
 */
Node *initialize_tree(NodeData *source) {
  if (source == NULL || strlen(source) == 0 || single_pattern(source)) {
    return create_tree();
  }

  int len = strlen(source);
  Node **nodes = malloc(len * sizeof(Node *));
  if (!nodes) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < len; ++i) {
    nodes[i] = create_tree();
    nodes[i]->data = source[i];
  }

  for (int i = 0; i < len; ++i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < len)
      nodes[i]->left = nodes[left];
    if (right < len)
      nodes[i]->right = nodes[right];
  }

  Node *root = nodes[0];
  free(nodes);
  return root;
}

/**
 * @brief 初始化树群
 *
 * @param source 结点数据源数组
 * @return Node** 树群指针数组
 */
Node **initialize_trees(NodeData **source) {
  if (source == NULL) {
    return NULL;
  }

  int count = 0;
  while (source[count] != NULL) {
    count++;
  }

  Node **trees = malloc(count * sizeof(Node *));
  if (!trees) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < count; ++i) {
    trees[i] = initialize_tree(source[i]);
  }

  return trees;
}

/**
 * @brief 树判空
 *
 * @param root root结点指针
 * @return true 空树
 * @return false 非空树
 */
bool is_empty_tree(Node *root) {
  return root == NULL ||
         (root->data == NULL_NODE && root->left == NULL && root->right == NULL);
}

/**
 * @brief 清空树
 *
 * @param node root结点
 */
void free_tree(Node *node) {
  if (node == NULL) {
    return;
  }
  free_tree(node->left);
  free_tree(node->right);
  free(node);
}

/**
 * @brief 非递归先序遍历
 *
 * @param node root结点指针
 */
void not_incur_preorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }

  Stack *stack = create_stack();
  push(stack, node);
  while (!is_empty_stack(stack)) {
    Node *current = pop(stack);
    printf("%c ", current->data);

    if (current->right != NULL) {
      push(stack, current->right);
    }
    if (current->left != NULL) {
      push(stack, current->left);
    }
  }
  free_stack(stack);
}

/**
 * @brief 非递归中序遍历
 *
 * @param node root结点指针
 */
void not_incur_inorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }

  Stack *stack = create_stack();
  Node *current = node;
  while (current != NULL || !is_empty_stack(stack)) {
    while (current != NULL) {
      push(stack, current);
      current = current->left;
    }
    current = pop(stack);
    printf("%c ", current->data);
    current = current->right;
  }
  free_stack(stack);
}

/**
 * @brief 非递归后序遍历
 *
 * @param node root ptr
 */
void not_incur_postorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }

  Stack *stack = create_stack();
  Node *lastVisited = NULL;
  while (node != NULL || !is_empty_stack(stack)) {
    while (node != NULL) {
      push(stack, node);
      node = node->left;
    }
    node = peek(stack);

    if (node->right == NULL || node->right == lastVisited) {
      printf("%c ", node->data);
      lastVisited = node;
      pop(stack);
      node = NULL; // 避免重复访问
    } else {
      node = node->right;
    }
  }
  free_stack(stack);
}

/**
 * @brief 递归先序遍历
 *
 * @param node root ptr
 */
void preorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  printf("%c ", node->data);
  preorder_traversal(node->left);
  preorder_traversal(node->right);
}

/**
 * @brief 递归中序遍历
 *
 * @param node root ptr
 */
void inorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  inorder_traversal(node->left);
  printf("%c ", node->data);
  inorder_traversal(node->right);
}

/**
 * @brief 递归后序遍历
 *
 * @param node root根结点指针
 */
void postorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  postorder_traversal(node->left);
  postorder_traversal(node->right);
  printf("%c ", node->data);
}

/**
 * @brief 层序遍历
 *
 * @param node 根结点root
 */
void level_order_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }

  Queue *queue = create_queue();
  queue_push(queue, node);
  while (!is_empty_queue(queue)) {
    Node *current = queue_pop(queue);
    printf("%c ", current->data);

    if (current->left != NULL) {
      queue_push(queue, current->left);
    }
    if (current->right != NULL) {
      queue_push(queue, current->right);
    }
  }
  free_queue(queue);
}

/**
 * @brief 查找第一个匹配target的结点(先序)
 *
 * @param root 根结点指针
 * @param target 目标字符
 * @return Node* 目标结点指针,未找到返回NULL
 */
Node *search(Node *root, NodeData target) {
  if (root == NULL) {
    return NULL;
  }
  if (root->data == target) {
    return root;
  }
  Node *leftResult = search(root->left, target);
  if (leftResult != NULL) {
    return leftResult;
  }
  return search(root->right, target);
}

// ------------------superior operation on binary tree-------------
/**
 * @brief Get the parent node of key node
 *
 * @param root 根结点指针
 * @param key 目标结点指针
 * @return Node* 父亲结点指针,未找到返回NULL
 */
Node *get_parent(Node *root, Node *key) {
  if (root == NULL || key == NULL || root == key) {
    return NULL;
  }
  if (root->left == key || root->right == key) {
    return root;
  }
  Node *leftSearch = get_parent(root->left, key);
  if (leftSearch != NULL) {
    return leftSearch;
  }
  return get_parent(root->right, key);
}

/**
 * @brief Get the height of binary tree
 *
 * @param root root ptr
 * @return int height
 */
int get_height(Node *root) {
  if (is_empty_tree(root)) {
    return 0;
  }
  int leftHeight = get_height(root->left);
  int rightHeight = get_height(root->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

/**
 * @brief Get the size of binary tree
 *
 * @param node root ptr
 * @return int number of nodes
 */
int get_size(Node *node) {
  if (is_empty_tree(node)) {
    return 0;
  }
  return get_size(node->left) + get_size(node->right) + 1;
}

/**
 * @brief Get the leaf size object
 *
 * @param node root ptr
 * @return int number of leaf nodes
 */
int get_leaf_size(Node *node) {
  if (is_empty_tree(node)) {
    return 0;
  }
  if (node->left == NULL && node->right == NULL) {
    return 1;
  }
  return get_leaf_size(node->left) + get_leaf_size(node->right);
}

/**
 * @brief Get the k level size object
 *
 * @param node root ptr
 * @param k 第几层(1, 2, 3...)
 * @return int size of level k
 */
int get_k_level_size(Node *node, int k) {
  if (is_empty_tree(node) || k < 1) {
    return 0;
  }
  if (k == 1) {
    return 1;
  }
  return get_k_level_size(node->left, k - 1) +
         get_k_level_size(node->right, k - 1);
}

/**
 * @brief 目标结点的最小层级
 *
 * @param root root ptr
 * @param key target node ptr
 * @return int {1,2,3,..} level of key
 */
int get_level(Node *root, Node *key) {
  if (root == NULL || key == NULL) {
    return 0;
  }
  if (root == key) {
    return 1;
  }
  int leftLevel = get_level(root->left, key);
  if (leftLevel != 0) {
    return leftLevel + 1;
  }
  int rightLevel = get_level(root->right, key);
  if (rightLevel != 0) {
    return rightLevel + 1;
  }
  return 0;
}

/**
 * @brief 目标结点的兄弟结点
 *
 * @param root root ptr
 * @param key target node
 * @return Node* 目标结点的兄弟结点,未找到返回NULL
 */
Node *get_twin(Node *root, Node *key) {
  if (is_empty_tree(root) || key == NULL || root == key) {
    return NULL;
  }
  if (root->left == key) {
    return (root->right->data == NULL_NODE || root->right == NULL)
               ? NULL
               : root->right;
  }
  if (root->right == key) {
    return (root->left->data == NULL_NODE || root->left == NULL) ? NULL
                                                                 : root->left;
  }
  Node *leftSearch = get_twin(root->left, key);
  if (leftSearch != NULL) {
    return leftSearch;
  }
  return get_twin(root->right, key);
}

/**
 * @brief 判断两棵树是否相同
 *
 * @param s 树s根结点
 * @param t 树t根结点
 * @return true 相同
 * @return false 不同
 */
bool is_same_tree(Node *s, Node *t) {
  if (is_empty_tree(s) && is_empty_tree(t)) {
    return true;
  }
  if (is_empty_tree(s) || is_empty_tree(t)) {
    return false;
  }
  if (s->data != t->data) {
    return false;
  }
  if (!is_same_tree(s->left, t->left)) {
    return false;
  }
  if (!is_same_tree(s->right, t->right)) {
    return false;
  }
  return true;
}

/**
 * @brief 获取结点a,b的公共前驱结点
 *
 * @param root 根结点
 * @param a 结点a
 * @param b 结点b
 * @return Node* 公共前驱结点,未找到返回NULL
 */
Node *get_lowest_common_ancestor(Node *root, Node *a, Node *b) {
  if (is_empty_tree(root) || a == NULL || b == NULL) {
    return NULL;
  }
  if (root == a || root == b) {
    return root;
  }

  // 左右子树递归查找a和b
  Node *left = get_lowest_common_ancestor(root->left, a, b);
  Node *right = get_lowest_common_ancestor(root->right, a, b);

  // 左右子树分别找到目标a和b,则返回最低公共祖先root
  if (left != NULL && right != NULL) {
    return root;
  }

  // 只有一边找到目标a和b,那就返回检索结果
  return left != NULL ? left : right;
}

/**
 * @brief 判断是否为对称树
 *
 * @param root 根结点
 * @return true 对称
 * @return false 不对称
 */
bool is_symmetric(Node *root) {
  if (is_empty_tree(root)) {
    return true;
  }

  Stack *stack = create_stack();
  push(stack, root->left);
  push(stack, root->right);

  while (!is_empty_stack(stack)) {
    Node *node1 = pop(stack);
    Node *node2 = pop(stack);

    if (node1 == NULL && node2 == NULL) {
      continue;
    }
    if (node1 == NULL || node2 == NULL) {
      free_stack(stack);
      return false;
    }
    if (node1->data != node2->data) {
      free_stack(stack);
      return false;
    }

    push(stack, node1->left);
    push(stack, node2->right);
    push(stack, node1->right);
    push(stack, node2->left);
  }

  free_stack(stack);
  return true;
}

/**
 * @brief collect leaf nodes
 *
 * @param root root ptr
 * @param leaves collector of leaf nodes
 * @param count counter
 */
void collect_leaves(Node *root, Node *leaves[], int *count) {
  if (is_empty_tree(root))
    return;

  if (root->left == NULL && root->right == NULL && root->data != NULL_NODE) {
    leaves[*count] = root;
    (*count)++;
    return;
  }

  // 递归遍历左右子树
  collect_leaves(root->left, leaves, count);
  collect_leaves(root->right, leaves, count);
}

/**
 * @brief 叶子结点数组
 *
 * @param root root ptr
 * @param leaf_size number of leaf node
 * @return Node** 叶子数组
 */
Node **get_leafs(Node *root, int leaf_size) {
  if (is_empty_tree(root)) {
    return NULL;
  }

  // memory allocation for leaves collector
  Node **leaves = (Node **)malloc(leaf_size * sizeof(Node *));
  if (!leaves) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  int collected = 0;
  collect_leaves(root, leaves, &collected);
  return leaves;
}

/**
 * @brief 二叉树宽度
 *
 * @param root root ptr
 * @return int tree width
 */
int max_width(Node *root) {
  if (is_empty_tree(root)) {
    return 0;
  }

  int maxWidth = 0;
  Queue *queue = create_queue();
  queue_push(queue, root);
  while (!is_empty_queue(queue)) {
    int levelSize = queue->length;
    if (levelSize > maxWidth) {
      maxWidth = levelSize;
    }
    for (int i = 0; i < levelSize; ++i) {
      Node *current = queue_pop(queue);
      if (current->left != NULL && current->left->data != NULL_NODE) {
        queue_push(queue, current->left);
      }
      if (current->right != NULL && current->right->data != NULL_NODE) {
        queue_push(queue, current->right);
      }
    }
  }
  free_queue(queue);
  return maxWidth;
}

/**
 * @brief 最小深度
 *
 * @param root root ptr
 * @return int min depth
 */
int min_depth(Node *root) {
  if (is_empty_tree(root)) {
    return 0;
  }
  if (root->left == NULL && root->right == NULL) {
    return 1;
  }
  int leftDepth = min_depth(root->left);
  int rightDepth = min_depth(root->right);
  return (leftDepth < rightDepth ? leftDepth : rightDepth) + 1;
}

/**
 * @brief 镜像二叉树
 *
 * @param root root ptr
 */
void invert_tree(Node *root) {
  if (root == NULL) {
    return;
  }
  invert_tree(root->left);
  invert_tree(root->right);
  Node *temp = root->left;
  root->left = root->right;
  root->right = temp;
}

bool is_balanced(Node *root) {
  if (is_empty_tree(root)) {
    return true;
  }
  int leftDepth = get_height(root->left);
  int rightDepth = get_height(root->right);
  if (leftDepth == -1 || rightDepth == -1) {
    return false;
  }
  if (abs(leftDepth - rightDepth) > 1) {
    return false;
  }
  return is_balanced(root->left) && is_balanced(root->right);
}