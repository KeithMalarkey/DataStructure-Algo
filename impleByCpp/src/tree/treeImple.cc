#include "core_api/tree_utils.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

namespace binary_tree {
/**
 * @brief Create a tree node.
 *
 * @param val
 * @return BTreeNode*
 */
BTreeNode *create_tree_node(const NodeVal &val) { return new BTreeNode(val); }

/**
 * @brief Create a binary tree from a vector of values.
 *
 * @param vals
 * @return BTreeNode*
 */
BTreeNode *create_tree(const std::vector<NodeVal> &vals) {
  if (vals.empty()) {
    return nullptr;
  }
  std::queue<BTreeNode *> q;
  BTreeNode *root = create_tree_node(vals[0]);
  q.push(root);
  int i = 1;
  while (!q.empty() && i < vals.size()) {
    BTreeNode *node = q.front();
    q.pop();
    if (i < vals.size() && vals[i] != NULL_NODE) {
      node->left = create_tree_node(vals[i]);
      q.push(node->left);
    }
    i++;
    if (i < vals.size() && vals[i] != NULL_NODE) {
      node->right = create_tree_node(vals[i]);
      q.push(node->right);
    }
    i++;
  }
  return root;
}

/**
 * @brief Check if a binary tree is empty.
 *
 * @param root
 * @return true
 * @return false
 */
bool is_empty(BTreeNode *root) {
  return root == nullptr || root->val == NULL_NODE;
}

/**
 * @brief pre order traversal of a binary tree.
 *
 * @param root
 * @return true traversed successfully.
 * @return false empty tree.
 */
bool preorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  std::cout << root->val << " ";
  preorderTraversal(root->left);
  preorderTraversal(root->right);
  return true;
}

/**
 * @brief inoreder traversal of a binary tree.
 *
 * @param root
 * @return true
 * @return false
 */
bool inorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  inorderTraversal(root->left);
  std::cout << root->val << " ";
  inorderTraversal(root->right);
  return true;
}

/**
 * @brief post order traversal of a binary tree.
 *
 * @param root
 * @return true
 * @return false
 */
bool postorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  std::cout << root->val << " ";
  return true;
}

/**
 * @brief Level order traversal of a binary tree.
 *
 * @param root
 * @return true
 * @return false
 */
bool levelorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  std::queue<BTreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    BTreeNode *node = q.front();
    q.pop();
    std::cout << node->val << " ";
    if (node->left) {
      q.push(node->left);
    }
    if (node->right) {
      q.push(node->right);
    }
  }
  return true;
}

/**
 * @brief pre order traversal of a binary tree without recursion.
 *
 * @param root
 * @return true
 * @return false
 */
bool norecursion_preorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  std::stack<BTreeNode *> s;
  s.push(root);
  while (!s.empty()) {
    BTreeNode *node = s.top();
    s.pop();
    std::cout << node->val << " ";
    if (node->right) {
      s.push(node->right);
    }
    if (node->left) {
      s.push(node->left);
    }
  }
  return true;
}

/**
 * @brief inorder traversal of a binary tree without recursion.
 *
 * @param root
 * @return true
 * @return false
 */
bool norecursion_inorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  std::stack<BTreeNode *> s;
  BTreeNode *node = root;
  while (!s.empty() || node) {
    if (node) {
      s.push(node);
      node = node->left;
    } else {
      node = s.top();
      s.pop();
      std::cout << node->val << " ";
      node = node->right;
    }
  }
  return true;
}

/**
 * @brief post order traversal of a binary tree without recursion.
 *
 * @param root
 * @return true
 * @return false
 */
bool norecursion_postorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return false;
  }
  std::stack<BTreeNode *> s1, s2;
  s1.push(root);
  while (!s1.empty()) {
    BTreeNode *node = s1.top();
    s1.pop();
    s2.push(node);
    if (node->left) {
      s1.push(node->left);
    }
    if (node->right) {
      s1.push(node->right);
    }
  }
  while (!s2.empty()) {
    std::cout << s2.top()->val << " ";
    s2.pop();
  }
  return true;
}

/**
 * @brief Search a value in a binary tree.
 *
 * @param root
 * @param val
 * @return BTreeNode*
 */
BTreeNode *search(BTreeNode *root, const NodeVal &val) {
  if (is_empty(root) || root->val == val) {
    return root;
  }
  BTreeNode *left = search(root->left, val);
  if (left) {
    return left;
  }
  return search(root->right, val);
}

/**
 * @brief Get the Parent node of a given value in a binary tree.
 *
 * @param root
 * @param val
 * @return BTreeNode*
 */
BTreeNode *getParent(BTreeNode *root, const NodeVal &val) {
  if (is_empty(root) || val == NULL_NODE) {
    return nullptr;
  }
  if (root->val == val) {
    return nullptr;
  }
  std::queue<BTreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    BTreeNode *current = q.front();
    q.pop();
    if (current->left) {
      if (current->left->val == val) {
        return current;
      }
      q.push(current->left);
    }
    if (current->right) {
      if (current->right->val == val) {
        return current;
      }
      q.push(current->right);
    }
  }
  return nullptr;
}

/**
 * @brief CHECK IF A BINARY TREE IS A VALID BST(binary search tree).
 *
 * @param root
 * @return true
 * @return false
 */
bool is_valid_bst(BTreeNode *root) {
  if (is_empty(root)) {
    return true;
  }
  if (root->left && root->left->val >= root->val) {
    return false;
  }
  if (root->right && root->right->val < root->val) {
    return false;
  }
  return is_valid_bst(root->left) && is_valid_bst(root->right);
}

/**
 * @brief Get the height of a binary tree.
 *
 * @param root
 * @return int
 */
int height(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  int lh = height(root->left);
  int rh = height(root->right);
  return std::max(lh, rh) + 1;
}

/**
 * @brief Check if a binary tree is balanced.
 *
 * @param root
 * @return true
 * @return false
 */
bool is_balanced(BTreeNode *root) {
  if (is_empty(root)) {
    return true;
  }
  int lh = height(root->left);
  int rh = height(root->right);
  if (std::abs(lh - rh) > 1) {
    return false;
  }
  return is_balanced(root->left) && is_balanced(root->right);
}

/**
 * @brief Get the number of nodes in a binary tree.
 *
 * @param root
 * @return int
 */
int node_size(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  return 1 + node_size(root->left) + node_size(root->right);
}

/**
 * @brief Get the number of leaf nodes in a binary tree.
 *
 * @param root
 * @return int
 */
int leaf_size(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return 1;
  }
  return leaf_size(root->left) + leaf_size(root->right);
}

/**
 * @brief Get the maximum depth of a binary tree.
 *
 * @param root
 * @return int
 */
int max_depth(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  int lh = max_depth(root->left);
  int rh = max_depth(root->right);
  return std::max(lh, rh) + 1;
}

/**
 * @brief Get the minimum depth of a binary tree.
 *
 * @param root
 * @return int
 */
int min_depth(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return 1;
  }
  int lh = min_depth(root->left);
  int rh = min_depth(root->right);
  return std::min(lh, rh) + 1;
}

/**
 * @brief Check if two binary trees (or subtrees) are mirror of each other.
 *
 * @param left
 * @param right
 * @return true
 * @return false
 */
bool is_mirror(BTreeNode *left, BTreeNode *right) {
  if (is_empty(left) && is_empty(right)) {
    return true;
  }
  if (is_empty(left) || is_empty(right)) {
    return false;
  }
  if (left->val != right->val) {
    return false;
  }
  return is_mirror(left->left, right->right) &&
         is_mirror(left->right, right->left);
}

/**
 * @brief Check if a binary tree is symmetric.
 *
 * @param root
 * @return true
 * @return false
 */
bool is_symmetric(BTreeNode *root) {
  if (is_empty(root)) {
    return true;
  }
  return is_mirror(root->left, root->right);
}

/**
 * @brief Get the level of a node in a binary tree.
 *
 * @param root
 * @param target
 * @return int
 */
int level(BTreeNode *root, const NodeVal &target) {
  if (is_empty(root)) {
    return -1;
  }
  if (root->val == target) {
    return 0;
  }
  int lh = level(root->left, target);
  if (lh != -1) {
    return lh + 1;
  }
  int rh = level(root->right, target);
  if (rh != -1) {
    return rh + 1;
  }
  return -1;
}

/**
 * @brief Lowest Common Ancestor of a Binary Tree.
 *
 * @param root
 * @param p target node #1 for searching the lowest common ancestor
 * @param q target node #2 for searching the lowest common ancestor
 * @return BTreeNode*
 */
BTreeNode *lowestCommonAncestor(BTreeNode *root, BTreeNode *p, BTreeNode *q) {
  if (is_empty(root) || root == p || root == q) {
    return root;
  }
  BTreeNode *left = lowestCommonAncestor(root->left, p, q);
  BTreeNode *right = lowestCommonAncestor(root->right, p, q);
  if (left && right) {
    return root;
  }
  return left ? left : right;
}

/**
 * @brief Check if a binary tree is complete.
 *
 * @param root
 * @return true
 * @return false
 */
bool is_complete(BTreeNode *root) {
  if (is_empty(root)) {
    return true;
  }

  std::queue<BTreeNode *> queue;
  queue.push(root);
  bool leafPhase = false; // phase flag for leaf nodes
  while (!queue.empty()) {
    BTreeNode *current = queue.front();
    queue.pop();
    if (current->left) {
      // leaf nodes have no left child, so it is not a complete
      if (leafPhase) {
        return false;
      }
      // for the nodes that are not leaves, into the queue by order that level
      // traversal
      queue.push(current->left);
    } else {
      leafPhase = true;
    }

    if (current->right) {
      if (leafPhase) {
        return false;
      }
      queue.push(current->right);
    } else {
      leafPhase = true;
    }
  }

  return true;
}

/**
 * @brief Check if a binary tree is a full binary tree.
 *
 * @param root
 * @return true
 * @return false
 */
bool is_full(BTreeNode *root) {
  if (is_empty(root)) {
    return true;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return true;
  }
  if (root->left == nullptr || root->right == nullptr) {
    return false;
  }
  return is_full(root->left) && is_full(root->right);
}

/**
 * @brief Collect all the leaves of a binary tree.
 *
 * @param root
 * @return std::vector<BTreeNode *>
 */
std::vector<BTreeNode *> collect_leaves(BTreeNode *root) {
  std::vector<BTreeNode *> leaves{};
  if (is_empty(root)) {
    return leaves;
  }
  if (root->left == nullptr && root->right == nullptr) {
    leaves.push_back(root);
    return leaves;
  }
  std::vector<BTreeNode *> leftLeaves = collect_leaves(root->left);
  std::vector<BTreeNode *> rightLeaves = collect_leaves(root->right);
  leaves.insert(leaves.end(), leftLeaves.begin(), leftLeaves.end());
  leaves.insert(leaves.end(), rightLeaves.begin(), rightLeaves.end());
  return leaves;
}

std::vector<BTreeNode *> collect_cousins(BTreeNode *root,
                                         const NodeVal &target) {
  std::vector<BTreeNode *> cousins{};
  if (is_empty(root)) {
    return cousins;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return cousins;
  }

  int target_level = level(root, target);
  if (target_level < 2) {
    // no cousins
    return cousins;
  }
  std::queue<BTreeNode *> queue;
  queue.push(root);
  while (!queue.empty()) {
    for (int i = 0; i < queue.size(); ++i) {
      BTreeNode *current = queue.front();
      queue.pop();
      // 检查当前结点的子结点是否和target同层且不是兄弟
      if (level(root, current->val) == target_level - 1) {
        // 当前结点的子结点在target层
        if (current->left && current->left != twin_node(root, target) &&
            current->left != search(root, target)) {
          cousins.push_back(current->left);
        }
        if (current->right && current->right != twin_node(root, target) &&
            current->right != search(root, target)) {
          cousins.push_back(current->right);
        }
      }
      if (current->left)
        queue.push(current->left);
      if (current->right)
        queue.push(current->right);
    }
  }
  return cousins;
}

/**
 * @brief Get the twin node of a given node in a binary tree.
 *
 * @param root
 * @param val
 * @return BTreeNode*
 */
BTreeNode *twin_node(BTreeNode *root, const NodeVal &val) {
  if (is_empty(root)) {
    return nullptr;
  }
  if (root->left && root->left->val == val) {
    return root->right;
  }
  if (root->right && root->right->val == val) {
    return root->left;
  }
  BTreeNode *left = twin_node(root->left, val);
  if (left) {
    return left;
  }
  return twin_node(root->right, val);
}

/**
 * @brief Get the width of a binary tree.
 *
 * @param root
 * @return int
 */
int width(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  int width_left = width(root->left);
  int width_right = width(root->right);
  return std::max(width_left, width_right) + 1;
}

/**
 * @brief Get the diameter of a binary tree.
 *
 * @param root
 * @return int
 */
int diameter(BTreeNode *root) {
  if (is_empty(root)) {
    return 0;
  }
  int lh = height(root->left);
  int rh = height(root->right);
  int ld = diameter(root->left);
  int rd = diameter(root->right);
  return std::max(lh + rh + 1, std::max(ld, rd));
}

std::vector<BTreeNode *> path_from_root_to_node(BTreeNode *root,
                                                const NodeVal &target) {
  std::vector<BTreeNode *> path{};
  if (is_empty(root)) {
    return path;
  }
  if (root->val == target) {
    path.push_back(root);
    return path;
  }
  std::vector<BTreeNode *> leftPath =
      path_from_root_to_node(root->left, target);
  if (!leftPath.empty()) {
    path.push_back(root);
    path.insert(path.end(), leftPath.begin(), leftPath.end());
    return path;
  }
  std::vector<BTreeNode *> rightPath =
      path_from_root_to_node(root->right, target);
  if (!rightPath.empty()) {
    path.push_back(root);
    path.insert(path.end(), rightPath.begin(), rightPath.end());
    return path;
  }
  return path;
}

std::vector<BTreeNode *> path_from_node_to_root(BTreeNode *root,
                                                const NodeVal &target) {
  std::vector<BTreeNode *> path{};
  if (is_empty(root)) {
    return path;
  }
  if (root->val == target) {
    path.push_back(root);
    return path;
  }
  std::vector<BTreeNode *> leftPath =
      path_from_node_to_root(root->left, target);
  if (!leftPath.empty()) {
    path.insert(path.end(), leftPath.begin(), leftPath.end());
    path.push_back(root);
    return path;
  }
  std::vector<BTreeNode *> rightPath =
      path_from_node_to_root(root->right, target);
  if (!rightPath.empty()) {
    path.insert(path.end(), rightPath.begin(), rightPath.end());
    path.push_back(root);
    return path;
  }
  return path;
}

/**
 * @brief Build a binary tree from preorder and inorder traversal.
 *
 * @param preorder
 * @param inorder
 * @return BTreeNode*
 */
BTreeNode *
build_tree_from_preorder_inorder(const std::vector<NodeVal> &preorder,
                                 const std::vector<NodeVal> &inorder) {
  if (preorder.empty() || inorder.empty()) {
    return nullptr;
  }
  BTreeNode *root = new BTreeNode(preorder[0]);
  std::vector<NodeVal>::const_iterator in_iter =
      std::find(inorder.begin(), inorder.end(), preorder[0]);
  int left_size = in_iter - inorder.begin();
  root->left = build_tree_from_preorder_inorder(
      std::vector<NodeVal>(preorder.begin() + 1,
                           preorder.begin() + 1 + left_size),
      std::vector<NodeVal>(inorder.begin(), in_iter));
  root->right = build_tree_from_preorder_inorder(
      std::vector<NodeVal>(preorder.begin() + 1 + left_size, preorder.end()),
      std::vector<NodeVal>(in_iter + 1, inorder.end()));
  return root;
}

/**
 * @brief Build a binary tree from inorder and postorder traversal.
 *
 * @param inorder
 * @param postorder
 * @return BTreeNode*
 */
BTreeNode *
build_tree_from_inorder_postorder(const std::vector<NodeVal> &inorder,
                                  const std::vector<NodeVal> &postorder) {
  if (inorder.empty() || postorder.empty()) {
    return nullptr;
  }
  BTreeNode *root = new BTreeNode(postorder.back());
  std::vector<NodeVal>::const_iterator in_iter =
      std::find(inorder.begin(), inorder.end(), postorder.back());
  int left_size = in_iter - inorder.begin();
  root->left = build_tree_from_inorder_postorder(
      std::vector<NodeVal>(inorder.begin(), in_iter),
      std::vector<NodeVal>(postorder.begin(), postorder.begin() + left_size));
  root->right = build_tree_from_inorder_postorder(
      std::vector<NodeVal>(in_iter + 1, inorder.end()),
      std::vector<NodeVal>(postorder.begin() + left_size, postorder.end() - 1));
  return root;
}
} // namespace binary_tree

namespace red_black_tree {
template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() {
  nil = new RBTreeNode<Key, Value>(Key(), Value(), Color::BLACK);
  root = nil;
}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
  destroyTree(root);
  delete nil;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::destroyTree(RBTreeNode<Key, Value> *node) {
  if (node != nil) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::leftRotate(RBTreeNode<Key, Value> *x) {
  RBTreeNode<Key, Value> *y = x->right;
  x->right = y->left;

  if (y->left != nil) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nil) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rightRotate(RBTreeNode<Key, Value> *y) {
  RBTreeNode<Key, Value> *x = y->left;
  y->left = x->right;

  if (x->right != nil) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == nil) {
    root = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else {
    y->parent->left = x;
  }

  x->right = y;
  y->parent = x;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key &key, const Value &value) {
  RBTreeNode<Key, Value> *z = new RBTreeNode<Key, Value>(key, value);
  RBTreeNode<Key, Value> *y = nil;
  RBTreeNode<Key, Value> *x = root;

  // 标准的BST插入
  while (x != nil) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;
  if (y == nil) {
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }

  z->left = nil;
  z->right = nil;
  z->color = Color::RED;

  insertFixup(z);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insertFixup(RBTreeNode<Key, Value> *z) {
  while (z->parent->color == Color::RED) {
    if (z->parent == z->parent->parent->left) {
      RBTreeNode<Key, Value> *y = z->parent->parent->right;

      // Case 1: 叔叔节点是红色
      if (y->color == Color::RED) {
        z->parent->color = Color::BLACK;
        y->color = Color::BLACK;
        z->parent->parent->color = Color::RED;
        z = z->parent->parent;
      } else {
        // Case 2: z是右孩子
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(z);
        }
        // Case 3: z是左孩子
        z->parent->color = Color::BLACK;
        z->parent->parent->color = Color::RED;
        rightRotate(z->parent->parent);
      }
    } else {
      // 对称的情况
      RBTreeNode<Key, Value> *y = z->parent->parent->left;

      if (y->color == Color::RED) {
        z->parent->color = Color::BLACK;
        y->color = Color::BLACK;
        z->parent->parent->color = Color::RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(z);
        }
        z->parent->color = Color::BLACK;
        z->parent->parent->color = Color::RED;
        leftRotate(z->parent->parent);
      }
    }
  }
  root->color = Color::BLACK;
}

template <typename Key, typename Value>
Value *RedBlackTree<Key, Value>::search(const Key &key) const {
  RBTreeNode<Key, Value> *current = root;

  while (current != nil) {
    if (key == current->key) {
      return &(current->value);
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return nullptr; // 没有找到
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::inOrderTraversal() const {
  inOrderHelper(root);
  std::cout << std::endl;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::inOrderHelper(
    RBTreeNode<Key, Value> *node) const {
  if (node != nil) {
    inOrderHelper(node->left);
    std::cout << "(" << node->key << ": " << node->value << ", "
              << (node->color == Color::RED ? "RED" : "BLACK") << ") ";
    inOrderHelper(node->right);
  }
}
} // namespace red_black_tree