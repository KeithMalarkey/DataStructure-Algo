#include "tree_utils.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

/**
 * @input 3 1 8 4 7 5 2 6
 *        3
 *      /   \
 *    1      8
 *   / \     / \
 *  4   7   5   2
 * /
 *6
 *
 *        3
 *      /   \
 *    1      8
 *   / \     / \
 *  4   7   5   2
 * /    \
 *6     11
 *
 */

int main() {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6};
  std::vector<NodeVal> _vals{3, 1, 8, 4, 7, 5, 2, 6, NULL_NODE, NULL_NODE, 11};
  BTreeNode *root = create_tree(_vals);
  BTreeNode *_root = create_tree(vals);
  std::cout << "Preorder Traversal: ";
  preorderTraversal(root);
  std::cout << std::endl;
  std::cout << "Inorder Traversal: ";
  inorderTraversal(root);
  std::cout << std::endl;
  std::cout << "Postorder Traversal: ";
  postorderTraversal(root);
  std::cout << std::endl;
  std::cout << "Levelorder Traversal: ";
  levelorderTraversal(root);
  std::cout << std::endl;
  std::cout << "No recursion Preorder Traversal: ";
  norecursion_preorderTraversal(root);
  std::cout << std::endl;
  std::cout << "No recursion Inorder Traversal: ";
  norecursion_inorderTraversal(root);
  std::cout << std::endl;
  std::cout << "No recursion Postorder Traversal: ";
  norecursion_postorderTraversal(root);
  std::cout << std::endl;

  std::cout << "Height: " << height(root) << std::endl;
  std::cout << "Is balanced: " << is_balanced(root) << std::endl;
  std::cout << "Is valid BST: " << is_valid_bst(root) << std::endl;
  BTreeNode *parent = getParent(root, 7);
  std::cout << "Parent of 7: " << parent->val << std::endl;

  std::cout << "Node size: " << node_size(root) << std::endl;
  std::cout << "Leaf size: " << leaf_size(root) << std::endl;
  std::cout << "Max depth: " << max_depth(root) << std::endl;
  std::cout << "Min depth: " << min_depth(root) << std::endl;
  std::cout << "Width: " << width(root) << std::endl;

  BTreeNode *left = create_tree_node(6);
  BTreeNode *right = create_tree_node(11);
  BTreeNode *root2 = create_tree_node(3);
  root2->left = left;
  root2->right = right;
  std::cout << "Is mirror: " << is_mirror(root, root2) << std::endl;
  std::cout << "Is symmetric: " << is_symmetric(root) << std::endl;
  std::cout << "Level of 6: " << level(root, 6) << std::endl;

  // note: if u create new nodes, may they don't have common ancestor.
  // u have to search and catch the ptr of target nodes for searching LCA.
  BTreeNode *lca = lowestCommonAncestor(root, left, right);
  BTreeNode *lca2 =
      lowestCommonAncestor(root, search(root, 6), search(root, 11));
  if (lca) {
    std::cout << "Fake!Lowest common ancestor of 6 and 11: " << lca->val
              << std::endl;
  } else {
    std::cout << "Fake! Lowest common ancestor of 6 and 11: NULL" << std::endl;
  }
  if (lca2) {
    std::cout << "Lowest common ancestor of 6 and 11: " << lca2->val
              << std::endl;
  } else {
    std::cout << "Lowest common ancestor of 6 and 11: NULL" << std::endl;
  }

  std::cout << "Is full: " << is_full(root) << std::endl;
  std::cout << "Is complete(_root): " << is_complete(_root) << std::endl;

  std::vector<BTreeNode *> leaves = collect_leaves(root);
  std::cout << "Leaves: ";
  for (auto leaf : leaves) {
    std::cout << leaf->val << " ";
  }
  std::cout << std::endl;

  BTreeNode *tn = twin_node(root, 5);
  if (tn) {
    std::cout << "Twin node of 5: " << tn->val << std::endl;
  } else {
    std::cout << "Twin node of 5: NULL" << std::endl;
  }

  std::vector<BTreeNode *> cousins = collect_cousins(root, 6);
  std::cout << "Cousins of 6: ";
  for (auto cousin : cousins) {
    std::cout << cousin->val << " ";
  }
  std::cout << std::endl;

  int target;
  std::cout << "Enter target node value: ";
  std::cin >> target;
  auto path = path_from_root_to_node(root, target);
  std::cout << "Path from root to " << target << ": ";
  for (auto node : path) {
    std::cout << node->val << " ";
  }
  std::cout << std::endl;

  auto path2 = path_from_node_to_root(root, target);
  std::cout << "Path from " << target << " to root: ";
  for (auto node : path2) {
    std::cout << node->val << " ";
  }
  std::cout << std::endl;

  //          41
  //         /   \
  //       29     36
  //      /  \     \
  //     92  35    26
  //         / \
  //        17 5
  std::vector<NodeVal> preorder{41, 29, 92, 35, 17, 5, 36, 26};
  std::vector<NodeVal> inorder{92, 29, 17, 35, 5, 41, 36, 26};
  std::vector<NodeVal> postorder{92, 17, 5, 35, 29, 26, 36, 41};
  BTreeNode *new_root = build_tree_from_preorder_inorder(preorder, inorder);
  std::cout << "Preorder Traversal of new tree: ";
  postorderTraversal(new_root);
  std::cout << std::endl;
  BTreeNode *new_root2 = build_tree_from_inorder_postorder(inorder, postorder);
  std::cout << "Inorder Traversal of new tree: ";
  preorderTraversal(new_root2);
  std::cout << std::endl;

  delete root;
  return 0;
}

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
 */
void preorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
  }
  std::cout << root->val << " ";
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

/**
 * @brief inoreder traversal of a binary tree.
 *
 * @param root
 */
void inorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
  }
  inorderTraversal(root->left);
  std::cout << root->val << " ";
  inorderTraversal(root->right);
}

/**
 * @brief post order traversal of a binary tree.
 *
 * @param root
 */
void postorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
  }
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  std::cout << root->val << " ";
}

/**
 * @brief Level order traversal of a binary tree.
 *
 * @param root
 */
void levelorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
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
}

/**
 * @brief pre order traversal of a binary tree without recursion.
 *
 * @param root
 */
void norecursion_preorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
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
}

/**
 * @brief inorder traversal of a binary tree without recursion.
 *
 * @param root
 */
void norecursion_inorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
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
}

/**
 * @brief post order traversal of a binary tree without recursion.
 *
 * @param root
 */
void norecursion_postorderTraversal(BTreeNode *root) {
  if (is_empty(root)) {
    return;
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
    BTreeNode *tmp = q.front();
    q.pop();
    if (tmp->left->val == val || tmp->right->val == val) {
      return tmp;
    }
    if (tmp->left) {
      q.push(tmp->left);
    }
    if (tmp->right) {
      q.push(tmp->right);
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