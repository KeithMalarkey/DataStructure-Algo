#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <vector>

namespace binary_tree {
const int NULL_NODE = -(1 << 10);

typedef int NodeVal;
typedef struct TreeNode {
  NodeVal val;
  struct TreeNode *left;
  struct TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  ~TreeNode() {
    if (left)
      delete left;
    if (right)
      delete right;
    std::cout << "delete node " << val << std::endl;
  }
} BTreeNode;

BTreeNode *create_tree_node(const NodeVal &val);
BTreeNode *create_tree(const std::vector<NodeVal> &vals);
BTreeNode *getParent(BTreeNode *root, const NodeVal &val);
BTreeNode *lowestCommonAncestor(BTreeNode *root, BTreeNode *p, BTreeNode *q);
BTreeNode *search(BTreeNode *root, const NodeVal &val);
BTreeNode *twin_node(BTreeNode *root, const NodeVal &val);
BTreeNode *
build_tree_from_preorder_inorder(const std::vector<NodeVal> &preorder,
                                 const std::vector<NodeVal> &inorder);
BTreeNode *
build_tree_from_inorder_postorder(const std::vector<NodeVal> &inorder,
                                  const std::vector<NodeVal> &postorder);
bool is_empty(BTreeNode *root);
bool preorderTraversal(BTreeNode *root);
bool inorderTraversal(BTreeNode *root);
bool postorderTraversal(BTreeNode *root);
bool levelorderTraversal(BTreeNode *root);
bool norecursion_preorderTraversal(BTreeNode *root);
bool norecursion_inorderTraversal(BTreeNode *root);
bool norecursion_postorderTraversal(BTreeNode *root);

int height(BTreeNode *root);
int width(BTreeNode *root);
int node_size(BTreeNode *root);
int leaf_size(BTreeNode *root);
int max_depth(BTreeNode *root);
int min_depth(BTreeNode *root);
int diameter(BTreeNode *root);
int level(BTreeNode *root, const NodeVal &target);
bool is_symmetric(BTreeNode *root);
bool is_valid_bst(BTreeNode *root);
bool is_balanced(BTreeNode *root);
bool is_complete(BTreeNode *root);
bool is_mirror(BTreeNode *left, BTreeNode *right);
bool is_full(BTreeNode *root);

std::vector<BTreeNode *> collect_branches(BTreeNode *root);
std::vector<BTreeNode *> collect_leaves(BTreeNode *root);
std::vector<BTreeNode *> collect_cousins(BTreeNode *root,
                                         const NodeVal &target);
std::vector<BTreeNode *> path_from_root_to_node(BTreeNode *root,
                                                const NodeVal &target);
std::vector<BTreeNode *> path_from_node_to_root(BTreeNode *root,
                                                const NodeVal &target);
} // namespace binary_tree

namespace red_black_tree {
enum class Color { RED, BLACK };

template <typename Key, typename Value> struct RBTreeNode {
  Key key;
  Value value;
  Color color;
  RBTreeNode *left;
  RBTreeNode *right;
  RBTreeNode *parent;

  RBTreeNode(Key k, Value v, Color c = Color::RED)
      : key(k), value(v), color(c), left(nullptr), right(nullptr),
        parent(nullptr) {}
};

template <typename Key, typename Value> class RedBlackTree {
private:
  RBTreeNode<Key, Value> *root;
  RBTreeNode<Key, Value> *nil; // 哨兵节点，代表NIL叶子节点

public:
  RedBlackTree();
  ~RedBlackTree();

  // 基本操作
  void insert(const Key &key, const Value &value);
  void remove(const Key &key);
  Value *search(const Key &key) const;

  // 辅助操作
  Key minimum() const;
  Key maximum() const;
  void inOrderTraversal() const;

private:
  void leftRotate(RBTreeNode<Key, Value> *x);
  void rightRotate(RBTreeNode<Key, Value> *y);
  void insertFixup(RBTreeNode<Key, Value> *z);
  void deleteFixup(RBTreeNode<Key, Value> *x);
  void transplant(RBTreeNode<Key, Value> *u, RBTreeNode<Key, Value> *v);
  RBTreeNode<Key, Value> *minimum(RBTreeNode<Key, Value> *node) const;
  RBTreeNode<Key, Value> *maximum(RBTreeNode<Key, Value> *node) const;
  void destroyTree(RBTreeNode<Key, Value> *node);
  void inOrderHelper(RBTreeNode<Key, Value> *node) const;
};

} // namespace red_black_tree

#endif // TREE_UTILS_H