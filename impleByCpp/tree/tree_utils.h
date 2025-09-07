#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <vector>

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
void preorderTraversal(BTreeNode *root);
void inorderTraversal(BTreeNode *root);
void postorderTraversal(BTreeNode *root);
void levelorderTraversal(BTreeNode *root);
void norecursion_preorderTraversal(BTreeNode *root);
void norecursion_inorderTraversal(BTreeNode *root);
void norecursion_postorderTraversal(BTreeNode *root);

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

#endif