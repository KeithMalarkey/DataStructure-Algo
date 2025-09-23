#include "core_api/tree_utils.h"
#include <memory>
#include <string>
#include <vector>

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
      // 检查当前节点的子节点是否和target同层且不是兄弟
      if (level(root, current->val) == target_level - 1) {
        // 当前节点的子节点在target层
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

namespace binary_tree::huffman_tree {
HuffmanTree::HuffmanTree() : root_(nullptr) {}

HuffmanTree::~HuffmanTree() { destroyTree(root_); }

void HuffmanTree::destroyTree(HuffmanNode *node) {
  if (node == nullptr)
    return;
  delete root_;
  root_ = nullptr;
  // std::cout << "huffman tree destroyed" << std::endl;
}

/**
 * @brief Huffman Code with Binary {0, 1}.
 *
 * @param node
 * @param code
 */
void HuffmanTree::buildEncodingTable(HuffmanNode *node,
                                     const std::string &code) {
  if (node == nullptr)
    return;

  if (node->isLeaf()) {
    encodingTable_[node->character] = code;
    decodingTable_[code] = node->character;
  } else {
    buildEncodingTable(node->left, code + "0");
    buildEncodingTable(node->right, code + "1");
  }
}

/**
 * @brief Build a Huffman Tree from the original text.
 *
 * @param text
 */
void HuffmanTree::buildFromText(const std::string &text) {
  std::unordered_map<char, std::pair<int, float>> fm;
  std::unordered_map<char, float> freqMap;
  for (char ch : text) {
    fm[ch].first++;
  }
  for (auto &p : fm) {
    p.second.second = static_cast<float>(p.second.first) / text.length();
    freqMap[p.first] = p.second.second;
  }
  buildFromFrequency(freqMap);
}

/**
 * @brief Build a Huffman Tree from a frequency map.
 *
 * @param frequencyMap
 */
void HuffmanTree::buildFromFrequency(
    const std::unordered_map<char, float> &frequencyMap) {
  MiniHeap minHeap; // 小顶堆

  for (const auto &pair : frequencyMap) {
    minHeap.push(new HuffmanNode(pair.first, pair.second));
  }

  // 构建哈夫曼树
  while (minHeap.size() > 1) {
    HuffmanNode *left = minHeap.top();
    minHeap.pop();
    HuffmanNode *right = minHeap.top();
    minHeap.pop();

    float combinedFreq = left->frequency + right->frequency;
    HuffmanNode *internalNode = new HuffmanNode(combinedFreq, left, right);
    minHeap.push(internalNode);
  }

  root_ = minHeap.top();
  minHeap.pop();

  // 构建编码表
  buildEncodingTable(root_, "");
}

/**
 * @brief Get encoding table of a Huffman Tree.
 *  std::string encoded = huffmanTree.encode(text); 你会得到编码后的字符串
 * @param text
 * @return std::string
 */
std::string HuffmanTree::encode(const std::string &text) const {
  std::string encodedText;
  for (char ch : text) {
    encodedText += encodingTable_.at(ch);
  }
  return encodedText;
}

/**
 * @brief decoding original text using encoding table of a Huffman Tree.
 * std::string decoded = huffmanTree.decode(encoded); 你会得到解码后的字符串
 * @param encodedText 编码后的bits
 * @return std::string
 */
std::string HuffmanTree::decode(const std::string &encodedText) const {
  std::string decodedText;
  std::string currentCode;

  for (char bit : encodedText) {
    currentCode += bit;
    if (decodingTable_.find(currentCode) != decodingTable_.end()) {
      decodedText += decodingTable_.at(currentCode);
      currentCode.clear();
    }
  }

  return decodedText;
}

/**
 * @brief Get the encoding of a character in the Huffman Tree.
 *
 * @param character
 * @return std::string
 */
std::string HuffmanTree::getEncoding(char character) const {
  if (encodingTable_.find(character) != encodingTable_.end()) {
    return encodingTable_.at(character);
  }
  return ""; // 字符不存在
}

/**
 * @brief Get the compression ratio of a text using the Huffman Tree.
 *
 * @param originalText origin string represented by ASCII.
 * @return double
 */
double HuffmanTree::getCompressionRatio(const std::string &originalText) const {
  if (originalText.empty())
    return 0.0;

  std::string encoded = encode(originalText);
  double originalBits = originalText.length() * 8.0; // 假设原始是ASCII
  double compressedBits = encoded.length();

  return compressedBits / originalBits;
}

void HuffmanTree::displayTree() const {
  std::cout << "哈夫曼树结构（含编码）:" << std::endl;
  displayTreeHelper(root_, "");
}

/**
 * @brief
 *
 * @param node root node of the Huffman Tree.
 * @param code current encoding table of the Huffman Tree.
 */
void HuffmanTree::displayTreeHelper(HuffmanNode *node,
                                    const std::string &code) const {
  if (node == nullptr)
    return;

  if (node->isLeaf()) {
    std::cout << "字符: '" << node->character << "' 频率: " << node->frequency
              << " 编码: " << code << std::endl;
  } else {
    // 递归左子树（添加'0'）
    displayTreeHelper(node->left, code + "0");
    // 递归右子树（添加'1'）
    displayTreeHelper(node->right, code + "1");
  }
}

} // namespace binary_tree::huffman_tree

namespace binary_tree::binary_search_tree {
BST::BST() : root(nullptr) {}
BST::~BST() { destroyTree(); }

void BST::createTree(const std::vector<NodeVal> &values) {
  for (const NodeVal &value : values) {
    insert(value);
  }
}

void BST::destroyTree() {
  if (root != nullptr) {
    delete root;
    root = nullptr;
  }
}

bool BST::search(const NodeVal &key) const {
  return searchHelper(root, key) != nullptr;
}

void BST::insert(const NodeVal &key) { root = insertHelper(root, key); }

void BST::remove(const NodeVal &key) {
  if (!search(key))
    return;
  root = removeHelper(root, key);
}

/**
 * @brief Insert a node into a binary search tree.
 *
 * @param node
 * @param key
 * @return BTreeNode* root of the modified binary search tree.
 */
BTreeNode *BST::insertHelper(BTreeNode *node, const NodeVal &key) {
  if (node == nullptr) {
    return new BTreeNode(key);
  }

  if (key < node->val) {
    node->left = insertHelper(node->left, key);
  } else if (key > node->val) {
    node->right = insertHelper(node->right, key);
  }

  return node;
}

/**
 * @brief Remove a node from a binary search tree.
 *
 * @param node
 * @param key
 * @return BTreeNode*
 */
BTreeNode *BST::removeHelper(BTreeNode *node, const NodeVal &key) {
  if (node == nullptr)
    return nullptr;

  if (key < node->val) {
    node->left = removeHelper(node->left, key);
  } else if (key > node->val) {
    node->right = removeHelper(node->right, key);
  } else {
    // 找到要删除的节点
    if (node->left == nullptr) {
      //  case 1: 无左子树
      BTreeNode *temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      // case 2: 无右子树
      BTreeNode *temp = node->left;
      delete node;
      return temp;
    } else {
      // case 3: 有两个子节点
      BTreeNode *temp = minNode(node->right);             // 找后继节点
      node->val = temp->val;                              // 用后继节点的值替换
      node->right = removeHelper(node->right, temp->val); // 删除后继节点
      // 这里使用右子树中序后继节点的值替换当前节点的值，然后删除后继节点;
      // 当然,也可以考虑用左子树的最大前驱替换,然后删除左子树的最大前驱
      // BTreeNode *temp = maxNode(node->left);
      // node->val = temp->val;
      // node->left = removeHelper(node->left, temp->val);
    }
  }
  return node;
}

/**
 * @brief Search for a node in a binary search tree.
 *
 * @param node
 * @param key TARGET KEY
 * @return BTreeNode*
 */
BTreeNode *BST::searchHelper(BTreeNode *node, const NodeVal &key) const {
  if (node == nullptr || node->val == key) {
    return node;
  }

  if (key <= node->val) {
    return searchHelper(node->left, key);
  } else {
    return searchHelper(node->right, key);
  }
}

/**
 * @brief Find the minimum node in a binary search tree.
 *
 * @param node
 * @return BTreeNode*
 */
BTreeNode *BST::minNode(BTreeNode *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  // 找最左边的节点就是最小的
  BTreeNode *current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

/**
 * @brief Find the maximum node in a binary search tree.
 *
 * @param node
 * @return BTreeNode*
 */
BTreeNode *BST::maxNode(BTreeNode *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  // 找最右边的节点就是最大的
  BTreeNode *current = node;
  while (current->right != nullptr) {
    current = current->right;
  }
  return current;
}

/**
 * @brief return the node value of successor corresponding to a given node in a
 * binary search tree.
 *
 * @param val 目标结点值
 * @return NodeVal
 */
NodeVal BST::successor(const NodeVal &val) const {
  BTreeNode *current = searchHelper(root, val);
  if (current == nullptr) {
    throw std::runtime_error("Key value not found in the tree.");
  }
  if (current->right != nullptr) {
    return minNode(current->right)->val;
  } else {
    // 方式一:由于没有右子树,所以需要从根节点开始向下搜索;
    // 可以确定的是,后继节点一定是当前节点的某个祖先/父母节点.且在该节点的右侧(目标节点在后记节点左侧);
    // 方式二:向上搜索祖先节点,在右翼最左侧的节点就是后继节点.会用到getParent函数,效率较低;
    BTreeNode *successor = nullptr;
    BTreeNode *ancestor = root;
    while (ancestor != current) {
      if (current->val <= ancestor->val) {
        successor = ancestor; // so far this is the deepest node for which
                              // current node is in left
        ancestor = ancestor->left;
      } else {
        ancestor = ancestor->right;
      }
    }
    if (successor == nullptr) {
      throw std::runtime_error("No successor exists (it's the maximum node).");
    }
    return successor->val;
  }
}

/**
 * @brief return the node value of predecessor corresponding to a given node in
 * a binary search tree.
 *
 * @param val
 * @return NodeVal
 */
NodeVal BST::predecessor(const NodeVal &val) const {
  BTreeNode *current = searchHelper(root, val);
  if (current == nullptr) {
    throw std::runtime_error("Key value not found in the tree.");
  }
  if (current->left != nullptr) {
    return maxNode(current->left)->val;
  } else {
    // 方式一:由于没有左子树,所以需要从根节点开始向下搜索;
    // 可以确定的是,前驱节点一定是当前节点的某个祖先/父母节点.且在该节点的左侧(目标节点在前驱节点右侧);
    // 方式二:向上搜索祖先节点,在左翼最右侧的节点就是前驱节点.会用到getParent函数,效率较低;
    BTreeNode *predecessor = nullptr;
    BTreeNode *ancestor = root;
    while (ancestor != current) {
      if (current->val > ancestor->val) {
        predecessor = ancestor; // so far this is the deepest node for which
                                // current node is in right
        ancestor = ancestor->right;
      } else {
        ancestor = ancestor->left;
      }
    }
    if (predecessor == nullptr) {
      throw std::runtime_error(
          "No predecessor exists (it's the minimum node).");
    }
    return predecessor->val;
  }
}

} // namespace binary_tree::binary_search_tree

namespace trie_tree {
std::shared_ptr<TrieNode> Trie::create_trie_node(char ch) {
  return std::make_shared<TrieNode>(ch);
}

void Trie::remove(const std::string &word) { removeHelper(word); }

void Trie::clear() { clearHelper(root_); }

void Trie::removeHelper(const std::string &to_remove_word) {
  if (to_remove_word.empty()) {
    throw std::invalid_argument("Cannot remove an empty word.");
  }

  std::shared_ptr<TrieNode> current = root_;
  std::vector<std::shared_ptr<TrieNode>> nodes_on_path;
  nodes_on_path.emplace_back(root_);

  for (char ch : to_remove_word) {
    if (current->children_.find(ch) == current->children_.end()) {
      throw std::runtime_error("Word not found in Trie.");
    }
    current = current->children_[ch];
    nodes_on_path.emplace_back(current);
  }

  if (current->count_ == 0) {
    throw std::runtime_error("Word not found in Trie.");
  }

  current->count_--;

  // If the word is still present, no need to delete nodes
  if (current->count_ > 0) {
    return;
  }

  // Remove nodes if they are no longer needed
  for (int i = nodes_on_path.size() - 1; i > 0; --i) {
    char ch = to_remove_word[i - 1];
    std::shared_ptr<TrieNode> parent = nodes_on_path[i - 1];
    std::shared_ptr<TrieNode> child = nodes_on_path[i];

    if (child->children_.empty() && child->count_ == 0) {
      parent->children_.erase(ch);
    } else {
      break; // Stop if the node has other children or is the end of another
             // word
    }
  }
}

std::vector<std::string> Trie::startsWith(const std::string &prefix) const {
  std::vector<std::string> results;
  std::shared_ptr<TrieNode> current = root_;

  for (char ch : prefix) {
    if (current->children_.find(ch) == current->children_.end()) {
      return results;
    }
    current = current->children_.at(ch);
  }
  auto children = current->children_;
  for (const auto &child_pair : children) {
    std::string word = prefix + child_pair.first;
    if (child_pair.second->count_ > 0) {
      results.emplace_back(word);
    }
    // 递归查找所有以该前缀开头的单词
    std::vector<std::string> sub_results = startsWith(word);
    results.insert(results.end(), sub_results.begin(), sub_results.end());
  }
  return results;
}

void Trie::clearHelper(std::shared_ptr<TrieNode> node) {
  if (node == nullptr)
    return;

  // 递归删除所有子节点
  for (auto &[ch, child] : node->children_) {
    clearHelper(child);
  }

  // 清空子节点映射
  node->children_.clear();
}

std::shared_ptr<TrieNode> Trie::insertHelper(const std::string &word) {
  std::shared_ptr<TrieNode> current = root_;
  for (char ch : word) {
    if (current->children_.find(ch) == current->children_.end()) {
      current->children_[ch] = create_trie_node(ch);
      current = current->children_[ch];
    } else {
      current = current->children_[ch];
    }
  }
  current->count_++; // Increment the count for the complete word
  return current;
}

void Trie::insert(const std::string &word) { insertHelper(word); }

/**
 * @brief Search a word in the Trie and return its occurrence count.
 *
 * @param word
 * @return int occurrence count of the word in the Trie, 0 if not found.
 */
int Trie::search(const std::string &word) const {
  return searchHelper(word) ? searchHelper(word)->count_ : 0;
}

std::shared_ptr<TrieNode> Trie::searchHelper(const std::string &word) const {
  std::shared_ptr<TrieNode> current = root_;
  for (char ch : word) {
    if (current->children_.find(ch) == current->children_.end()) {
      return nullptr;
    }
    current = current->children_.at(ch);
  }
  return current;
}

/**
 * @brief Helper function for pre-order traversal of the Trie.
 *
 * @param curr_node
 * @param word recorder of the current word formed by the path from root to the
 * current node
 * @param dictionary vector to store all words in the Trie in dictionary order
 */
void Trie::preOrderHelper(std::shared_ptr<TrieNode> curr_node, std::string word,
                          std::vector<std::string> &dictionary) const {
  if (curr_node == nullptr) {
    throw std::runtime_error("Root node is null.");
  }

  if (curr_node != root_) {
    word.push_back(curr_node->data_);
    if (curr_node->count_ > 0) {
      dictionary.emplace_back(word);
    }
  }

  for (const auto &child_pair : curr_node->children_) {
    preOrderHelper(child_pair.second, word, dictionary);
  }
}

/**
 * @brief Pre-order traversal of the Trie to display all words in dictionary
 * order.
 *
 */
void Trie::preOrder() const {
  std::vector<std::string> dictionary;
  preOrderHelper(root_, "", dictionary);
  std::cout << "Trie Pre-order Traversal (Dictionary):" << std::endl;
  for (const auto &word : dictionary) {
    std::cout << word << std::endl;
  }
}
} // namespace trie_tree

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