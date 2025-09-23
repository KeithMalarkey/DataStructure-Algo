#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

namespace binary_tree {
const int NULL_NODE = -(1 << 10);

typedef int NodeVal;
typedef struct TreeNode {
  NodeVal val;
  struct TreeNode *left;
  struct TreeNode *right;
  TreeNode(NodeVal x) : val(x), left(nullptr), right(nullptr) {}
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
bool levelorderTraversal(BTreeNode *root);

int height(BTreeNode *root);
int width(BTreeNode *root);
int node_size(BTreeNode *root);
int leaf_size(BTreeNode *root);
int max_depth(BTreeNode *root);
int min_depth(BTreeNode *root);
int diameter(BTreeNode *root);
int level(BTreeNode *root, const NodeVal &target);
bool is_symmetric(BTreeNode *root);
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

/**
 * @brief 判断二叉树是否为空
 *
 * @tparam T
 * @param root
 * @return true
 * @return false
 */
template <typename T> bool is_empty(T *root) {
  return root == nullptr || root->val == NULL_NODE;
}

/**
 * @brief 判断二叉树是否为BST
 *
 * @tparam T
 * @param root
 * @param minNode
 * @param maxNode
 * @return true
 * @return false
 */
template <typename T>
bool is_valid_bst(T *root, T *minNode = nullptr, T *maxNode = nullptr) {
  if (root == nullptr || root->val == NULL_NODE) {
    return true;
  }

  // 检查当前节点是否在允许范围内
  if ((minNode && root->val < minNode->val) ||
      (maxNode && root->val >= maxNode->val)) {
    return false;
  }

  // 递归检查子树，更新范围限制
  return is_valid_bst(root->left, minNode, root) &&
         is_valid_bst(root->right, root, maxNode);
}

/**
 * @brief pre order traversal of a binary tree.
 *
 * @tparam T
 * @param root
 * @return true traversed successfully.
 * @return false empty tree.
 */
template <typename T> bool preorderTraversal(T *root) {
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
 * @tparam T
 * @param root
 * @return true
 * @return false
 */
template <typename T> bool inorderTraversal(T *root) {
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
 * @tparam T
 * @param root
 * @return true
 * @return false
 */
template <typename T> bool postorderTraversal(T *root) {
  if (is_empty(root)) {
    return false;
  }
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  std::cout << root->val << " ";
  return true;
}

/**
 * @brief pre order traversal of a binary tree without recursion.
 *
 * @tparam T
 * @param root
 * @return true
 * @return false
 */
template <typename T> bool norecursion_preorderTraversal(T *root) {
  if (is_empty(root)) {
    return false;
  }
  std::stack<T *> s;
  s.push(root);
  while (!s.empty()) {
    T *node = s.top();
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
 * @tparam T
 * @param root
 * @return true
 * @return false
 */
template <typename T> bool norecursion_inorderTraversal(T *root) {
  if (is_empty(root)) {
    return false;
  }
  std::stack<T *> s;
  T *node = root;
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
 * @tparam T
 * @param root
 * @return true
 * @return false
 */
template <typename T> bool norecursion_postorderTraversal(T *root) {
  if (is_empty(root)) {
    return false;
  }
  std::stack<T *> s1, s2;
  s1.push(root);
  while (!s1.empty()) {
    T *node = s1.top();
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

namespace binary_search_tree {
// 二叉搜索树
class BST {
private:
  BTreeNode *root;

public:
  BST();
  ~BST();
  void createTree(const std::vector<NodeVal> &vals);
  void destroyTree();
  void insert(const NodeVal &val);
  void remove(const NodeVal &val);
  bool search(const NodeVal &val) const;
  BTreeNode *getRoot() const { return root; }
  BTreeNode *minNode(BTreeNode *node) const;
  BTreeNode *maxNode(BTreeNode *node) const;
  BTreeNode *insertHelper(BTreeNode *node, const NodeVal &val);
  BTreeNode *removeHelper(BTreeNode *node, const NodeVal &key);
  BTreeNode *searchHelper(BTreeNode *node, const NodeVal &key) const;

  // bool isEmpty() const; // 在binary_tree中实现
  NodeVal successor(const NodeVal &val) const;
  NodeVal predecessor(const NodeVal &val) const;
};

} // namespace binary_search_tree

namespace huffman_tree {
const int NULL_NODE = '\0';
struct HuffmanNode {
  char character;
  // unsigned int weight; // 用整数表述访问次数也可
  float frequency; // 用浮点数表述访问频率也行
  HuffmanNode *left;
  HuffmanNode *right;

  // 用于叶子节点
  HuffmanNode(char ch, float frequency)
      : character(ch), frequency(frequency), left(nullptr), right(nullptr) {}

  // 用于内部节点
  HuffmanNode(float frequency, HuffmanNode *l, HuffmanNode *r)
      : character(NULL_NODE), frequency(frequency), left(l), right(r) {}

  bool isLeaf() const { return left == nullptr && right == nullptr; }
};

using MiniHeap =
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>,
                        decltype([](HuffmanNode *a, HuffmanNode *b) {
                          return a->frequency > b->frequency;
                        })>;

// 哈夫曼树
class HuffmanTree {
private:
  HuffmanNode *root_;
  std::unordered_map<char, std::string> encodingTable_; // huffman编码表
  std::unordered_map<std::string, char> decodingTable_; // huffman解码表

public:
  HuffmanTree();
  ~HuffmanTree();

  void buildFromFrequency(const std::unordered_map<char, float> &frequencyMap);
  void buildFromText(const std::string &text);

  std::string encode(const std::string &text) const;
  std::string decode(const std::string &encodedText) const;
  std::string getEncoding(char character) const;
  double getCompressionRatio(const std::string &originalText) const;
  void displayTree() const;

private:
  void buildEncodingTable(HuffmanNode *node, const std::string &code);
  void destroyTree(HuffmanNode *node);
  void displayTreeHelper(HuffmanNode *node, const std::string &code) const;
};
} // namespace huffman_tree
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

// 字典树/前缀树/trie树
namespace trie_tree {
struct TrieNode {
  char data_;
  int count_;                                          // 末端节点统计词频
  std::map<char, std::shared_ptr<TrieNode>> children_; // 子节点映射

  TrieNode(char data, int count = 0) : data_(data), count_(count) {}
};

class Trie {
private:
  std::shared_ptr<TrieNode> root_;

public:
  // 字典数的根节点不存储字符
  Trie() : root_(std::make_shared<TrieNode>('\0')) {}
  ~Trie() { clear(); }

  std::shared_ptr<TrieNode> create_trie_node(char ch);
  std::vector<std::string> startsWith(const std::string &prefix) const;
  void preOrder() const;
  void insert(const std::string &word);
  void remove(const std::string &word);
  void clear();
  int search(const std::string &word) const;

private:
  std::shared_ptr<TrieNode> insertHelper(const std::string &word);
  std::shared_ptr<TrieNode> searchHelper(const std::string &word) const;
  void preOrderHelper(std::shared_ptr<TrieNode> node, std::string word,
                      std::vector<std::string> &dictionary) const;
  void removeHelper(const std::string &word);
  void clearHelper(std::shared_ptr<TrieNode> node);
};
} // namespace trie_tree

#endif // TREE_UTILS_H