#include "utils.h"

// ***********
// * 线索二叉树
// * 二叉搜索树
// * 二叉平衡树
// * 红黑树
// * 哈(霍)曼树/霍夫曼编码

int main() { return 0; }

// ***********线索化二叉树**********
void test_on_threaded_tree() {}

/**
 * @brief Create a Threaded Tree Node object
 * 
 * @param value value of the node.
 * @return ThreadedTreeNode* a node of Threaded Tree.
 */
ThreadedTreeNode *createThreadedTreeNode(NodeValue value) {
  ThreadedTreeNode *node = (ThreadedTreeNode *)malloc(sizeof(ThreadedTreeNode));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  node->isLeftThreaded = false;
  node->isRightThreaded = false;
  return node;
}

/**
 * @brief Create a Threaded Tree object from an array of values.
 *
 * @param values values inputed.
 * @param size values size.
 * @return ThreadedTreeNode*
 */
ThreadedTreeNode *createThreadedTree(NodeValue *values, int size) {
  if (values == NULL || size == 0) {
    return NULL;
  }
  ThreadedTreeNode *root = createThreadedTreeNode(values[0]);
  for (int i = 1; i < size; ++i) {
    ThreadedTreeNode *node = createThreadedTreeNode(values[i]);
    threaded_insert(&root, node);
  }
  return root;
}

/**
 * @brief left rotate a Threaded Tree.
 *
 * @param root root of the Threaded Binary Tree.
 */
void threaded_left_rotate(ThreadedTreeNode **root) {
  ThreadedTreeNode *x = *root;
  ThreadedTreeNode *y = x->right;
  x->right = y->left;
  if (y->left != NULL) {
    y->left->isLeftThreaded = false;
  }
  y->left = x;
  y->isLeftThreaded = x->isLeftThreaded;
  x->isLeftThreaded = true;
  *root = y;
}

/**
 * @brief right rotate a Threaded Tree.
 *
 * @param root same as above.
 */
void threaded_right_rotate(ThreadedTreeNode **root) {
  ThreadedTreeNode *x = *root;
  ThreadedTreeNode *y = x->left;
  x->left = y->right;
  if (y->right != NULL) {
    y->right->isRightThreaded = false;
  }
  y->right = x;
  y->isRightThreaded = x->isRightThreaded;
  x->isRightThreaded = true;
  *root = y;
}

/**
 * @brief insert a new node into the threaded binary tree.
 *
 * @param root root of the Threaded Tree.
 * @param node target node to be inserted.
 */
void threaded_insert(ThreadedTreeNode **root, ThreadedTreeNode *node) {
  ThreadedTreeNode *y = NULL;
  ThreadedTreeNode *x = *root;
  while (x != NULL) {
    y = x;
    if (node->value < x->value) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  node->left = NULL;
  node->right = NULL;
  node->isLeftThreaded = true;
  node->isRightThreaded = true;
  if (y == NULL) {
    *root = node;
  } else if (node->value < y->value) {
    y->left = node;
    y->isLeftThreaded = false;
  } else {
    y->right = node;
    y->isRightThreaded = false;
  }
}

/**
 * @brief Delete a node from a Threaded Tree.
 *
 * @param root root of the Threaded Tree.
 * @param node target node to be deleted.
 */
void threaded_delete(ThreadedTreeNode **root, ThreadedTreeNode *node) {
  ThreadedTreeNode *y = NULL;
  ThreadedTreeNode *x = *root;
  ThreadedTreeNode *z = NULL;
  while (x != node) {
    y = x;
    if (node->value < x->value) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  if (x->left == NULL || x->right == NULL) {
    z = x;
  } else {
    y = x;
    x = x->right;
    while (x->left != NULL) {
      y = x;
      x = x->left;
    }
    z = x;
  }
  if (z->left != NULL) {
    z->left->isLeftThreaded = false;
  }
  if (z->right != NULL) {
    z->right->isRightThreaded = false;
  }
  if (y == NULL) {
    *root = z->right;
  } else if (z == y->left) {
    y->left = z->right;
    y->isLeftThreaded = false;
  } else {
    y->right = z->right;
    y->isRightThreaded = false;
  }
  if (z != node) {
    node->value = z->value;
  }
  free(z);
}

/**
 * @brief Inorder traversal of a Threaded Tree.
 *
 * @param root
 */
void inorder_threaded_traversal(ThreadedTreeNode *root) {
  if (root == NULL) {
    return;
  }
  if (root->left != NULL) {
    inorder_threaded_traversal(root->left);
  }
  printf("%c", root->value);
  if (root->right != NULL) {
    inorder_threaded_traversal(root->right);
  }
}

/**
 * @brief preorder traversal of a Threaded Tree.
 *
 * @param root
 */
void preorder_threaded_traversal(ThreadedTreeNode *root) {
  if (root == NULL) {
    return;
  }
  printf("%c", root->value);
  if (root->left != NULL) {
    preorder_threaded_traversal(root->left);
  }
  if (root->right != NULL) {
    preorder_threaded_traversal(root->right);
  }
}

/**
 * @brief postorder traversal of a Threaded Tree.
 *
 * @param root
 */
void postorder_threaded_traversal(ThreadedTreeNode *root) {
  if (root == NULL) {
    return;
  }
  if (root->left != NULL) {
    postorder_threaded_traversal(root->left);
  }
  if (root->right != NULL) {
    postorder_threaded_traversal(root->right);
  }
  printf("%c", root->value);
}

// ***********二叉搜索树************

// ***********二叉平衡树************

// ***********红黑树****************