#include "utils.h"

// * 二叉搜索树
// * 二叉平衡树
// * 红黑树
// * 哈夫曼树/哈夫曼编码

int main() { return 0; }

// -------------------------------------------tree--------------------------------------------
Node *create_tree_node(NodeData data) {
  Node *root = malloc(sizeof(Node));
  if (root == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  root->data = data;
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
    return create_tree_node(NULL);
  }

  int len = sizeof(source) / sizeof(NodeData[0]);
  Node **nodes = malloc(len * sizeof(Node *));
  if (!nodes) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < len; ++i) {
    nodes[i] = create_tree_node(NULL);
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

bool is_empty_tree(Node *root) {
  return root == NULL || root->data == NULL_NODE;
}

void preorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  printf("%d ", node->data);
  preorder_traversal(node->left);
  preorder_traversal(node->right);
}

void inorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  inorder_traversal(node->left);
  printf("%d ", node->data);
  inorder_traversal(node->right);
}

void postorder_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  postorder_traversal(node->left);
  postorder_traversal(node->right);
  printf("%d ", node->data);
}

void level_order_traversal(Node *node) {
  if (is_empty_tree(node)) {
    return;
  }
  Queue *queue = create_queue();
  enqueue(queue, node);
  while (!is_empty_queue(queue)) {
    Node *front = dequeue(queue);
    printf("%d ", front->data);
    if (front->left != NULL) {
      enqueue(queue, front->left);
    }
    if (front->right != NULL) {
      enqueue(queue, front->right);
    }
  }
  free_queue(queue);
}

// -------------------------------------------BST--------------------------------------------

/**
 * @brief 二叉搜索树的搜索
 *
 * @param root
 * @param target
 * @return Node*
 */
Node *search_on_bst(Node *root, int target) {
  if (root == NULL || root->data == target) {
    return root;
  }
  if (target < root->data) {
    return search_on_bst(root->left, target); // 左子树
  } else {
    return search_on_bst(root->right, target); // 右子树
  }
}

// -------------------------------------------queue--------------------------------------------

/**
 * @brief Create a queue object
 *
 * @return Queue*
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

/**
 * @brief 入队
 *
 * @param queue
 * @param node
 */
void enqueue(Queue *queue, Node *node) {
  if (is_empty_queue(queue)) {
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
 * @brief 队列判空
 *
 * @param queue
 * @return true
 * @return false
 */
bool is_empty_queue(Queue *queue) {
  return queue == NULL || queue->length == 0;
}

/**
 * @brief 出队
 *
 * @param queue 队列
 * @return Node* 出队结点指针
 */
Node *dequeue(Queue *queue) {
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