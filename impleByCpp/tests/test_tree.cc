#include "core_api/tree_utils.h"
#include "gtest/gtest.h"
#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace binary_tree;

std::vector<NodeVal> _vals{3, 1, 8, 4, 7, 5, 2, 6, NULL_NODE, NULL_NODE, 11};
BTreeNode *root = create_tree(_vals);

TEST(tree_test, create_tree) { EXPECT_TRUE(root != nullptr); }

TEST(tree_test, preorderTraversal) {
  std::cout << "Preorder Traversal: ";
  EXPECT_FALSE(!preorderTraversal(root));
}

TEST(tree_test, inorderTraversal) {
  std::cout << "Inorder Traversal: ";
  EXPECT_FALSE(!inorderTraversal(root));
}

TEST(tree_test, postorderTraversal) {
  std::cout << "Postorder Traversal: ";
  EXPECT_FALSE(!postorderTraversal(root));
}

TEST(tree_test, levelorderTraversal) {
  std::cout << "Levelorder Traversal: ";
  EXPECT_TRUE(levelorderTraversal(root));
}

TEST(tree_test, norecursion_preorderTraversal) {
  std::cout << "No recursion Preorder Traversal: ";
  EXPECT_TRUE(norecursion_preorderTraversal(root));
}

TEST(tree_test, norecursion_inorderTraversal) {
  std::cout << "No recursion Inorder Traversal: ";
  EXPECT_TRUE(norecursion_inorderTraversal(root));
}

TEST(tree_test, norecursion_postorderTraversal) {
  std::cout << "No recursion Postorder Traversal: ";
  EXPECT_TRUE(norecursion_postorderTraversal(root));
}

TEST(tree_test, height) { EXPECT_EQ(4, height(root)); }

TEST(tree_test, width) { EXPECT_EQ(4, width(root)); }

TEST(tree_test, catch_level) {
  // note : root的level是0
  EXPECT_EQ(1, level(root, 8));
}

TEST(tree_test, search_value) {
  BTreeNode *node = search(root, 8);
  EXPECT_TRUE(node != nullptr);
  EXPECT_EQ(8, node->val);
  EXPECT_EQ(node->left->val, 5);

  BTreeNode *node2 = search(root, 12);
  EXPECT_TRUE(node2 == nullptr);
}

TEST(tree_test, get_parent) {
  BTreeNode *node = search(root, 11);
  BTreeNode *parent = getParent(root, 11);
  EXPECT_TRUE(parent->val == 7);
}

TEST(tree_test, collect_leaves) {
  std::vector<BTreeNode *> leaves = collect_leaves(root);
  std::set<BTreeNode *> set_leaves(leaves.begin(), leaves.end());
  EXPECT_EQ(leaves.size(), 4);
  std::set<int> expected_leaves{6, 2, 5, 11};
  for (auto leaf : set_leaves) {
    expected_leaves.erase(leaf->val);
  }
  EXPECT_TRUE(expected_leaves.empty());
}

TEST(tree_test, diameter) { EXPECT_EQ(6, diameter(root)); }

TEST(tree_test, is_balanced) { EXPECT_TRUE(is_balanced(root)); }

TEST(tree_test, is_valid_bst) { EXPECT_FALSE(is_valid_bst(root)); }

TEST(tree_test, is_complete_tree) { EXPECT_FALSE(is_complete(root)); }

TEST(tree_test, LCA) {
  BTreeNode *lca =
      lowestCommonAncestor(root, search(root, 11), search(root, 4));
  EXPECT_TRUE(lca->val == 1);
}

TEST(tree_test, twin) {
  BTreeNode *twin = twin_node(root, 2);
  EXPECT_TRUE(twin->val == 5);
}

TEST(tree_test, node_count) { EXPECT_EQ(5, node_size(root->left)); }

TEST(tree_test, cousins) {
  std::vector<BTreeNode *> cousins = collect_cousins(root, 4);
  EXPECT_EQ(2, cousins.size());
  for (const auto &node : cousins) {
    EXPECT_TRUE(node->val == 2 || node->val == 5);
  }
}

std::string text = "hello world";
huffman_tree::HuffmanTree hft;

TEST(huffman_test, Buildfromtext) {
  hft.buildFromText(text);
  hft.displayTree();
}

TEST(huffman_test, getCode) {
  hft.buildFromText(text);
  std::string code = hft.getEncoding('l');
  std::set<std::string> latent_res{"10", "01"};
  EXPECT_TRUE(latent_res.find(code) != latent_res.end());
}

TEST(huffman_test, compressionRatio) {
  hft.buildFromText(text);
  double ratio = hft.getCompressionRatio(text);
  EXPECT_TRUE(ratio < .4); // 压缩率小于40%, ratio越小越好
}

/**
 * @brief
 *(entirw bst)     3
 *               /   \
 *             1      8
 *             \    / \
 *              2  4   10
 *                  \
 *                   7
 *                  /
 *                 5
 *                  \
 *                   6
 */

TEST(BST_test, bst_tree_inorder) {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6, 10, 7};
  binary_tree::binary_search_tree::BST bst;
  bst.createTree(vals);
  bool res = binary_tree::inorderTraversal(bst.getRoot());
  EXPECT_TRUE(res);
}

TEST(BST_test, bst_tree_remove) {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6, 10, 7};
  binary_tree::binary_search_tree::BST bst;
  bst.createTree(vals);
  bst.remove(10);
  bool res = binary_tree::inorderTraversal(bst.getRoot());
  EXPECT_TRUE(res);
}

TEST(BST_test, bst_tree_search) {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6, 10, 7};
  binary_tree::binary_search_tree::BST bst;
  bst.createTree(vals);
  EXPECT_FALSE(!bst.search(10));
}

TEST(BST_test, bst_tree_insert) {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6, 10, 7};
  binary_tree::binary_search_tree::BST bst;
  bst.createTree(vals);
  bst.insert(9);
  bool res = binary_tree::inorderTraversal(bst.getRoot());
  EXPECT_TRUE(res);
}

TEST(BST_test, bst_tree_successor) {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6, 10, 7};
  binary_tree::binary_search_tree::BST bst;
  bst.createTree(vals);
  NodeVal suc = bst.successor(7);
  EXPECT_EQ(8, suc);
  // suc = bst.successor(11);
  // suc = bst.successor(10);
}

TEST(BST_test, bst_tree_predecessor) {
  std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6, 10, 7};
  binary_tree::binary_search_tree::BST bst;
  bst.createTree(vals);
  NodeVal pre = bst.predecessor(7);
  EXPECT_EQ(6, pre);
  // pre = bst.predecessor(1);
}

TEST(trie_test, trie_insert_search) {
  trie_tree::Trie trie;
  trie.insert("hello");
  trie.insert("hello");
  trie.insert("hell");
  trie.insert("heaven");
  trie.insert("heavy");

  EXPECT_EQ(2, trie.search("hello"));
  EXPECT_EQ(1, trie.search("hell"));
  EXPECT_EQ(1, trie.search("heaven"));
  EXPECT_EQ(1, trie.search("heavy"));
  EXPECT_EQ(0, trie.search("he"));
  EXPECT_EQ(0, trie.search("helloo"));
}

TEST(trie_test, preorder_traversal) {
  trie_tree::Trie trie;
  trie.insert("hello");
  trie.insert("hello");
  trie.insert("hell");
  trie.insert("china");
  trie.insert("keith");
  trie.insert("heaven");
  trie.insert("heavy");
  trie.preOrder();
}

TEST(trie_test, remove_word1) {
  trie_tree::Trie trie;
  trie.insert("hello");
  trie.insert("hello");
  trie.insert("hell");
  trie.insert("china");
  trie.insert("keith");
  trie.insert("heaven");
  trie.insert("heavy");
  trie.preOrder();
  trie.remove("hello");
  trie.preOrder();
}

TEST(trie_test, remove_word2) {
  trie_tree::Trie trie;
  trie.insert("hello");
  trie.insert("hello");
  trie.insert("hell");
  trie.insert("china");
  trie.insert("keith");
  trie.insert("heaven");
  trie.insert("heavy");
  trie.preOrder();
  trie.remove("heavy");
  trie.preOrder();
}

TEST(trie_test, startWith) {
  trie_tree::Trie trie;
  trie.insert("hello");
  trie.insert("hello");
  trie.insert("hell");
  trie.insert("china");
  trie.insert("keith");
  trie.insert("heaven");
  trie.insert("heavy");
  std::vector<std::string> res = trie.startsWith("hea");
  std::set<std::string> expected_res{"heaven", "heavy"};
  EXPECT_EQ(res.size(), expected_res.size());
  for (const auto &word : res) {
    expected_res.erase(word);
  }
  EXPECT_TRUE(expected_res.empty());
}
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
 * pre: 3 1 4 6 7 11 8 5 2
 * in: 6 4 1 7 11 3 5 8 2
 * post: 6 4 11 7 1 5 2 8 3
 * level: 3 1 8 4 7 5 2 6 11
 */

// int main() {
//   std::vector<NodeVal> vals{3, 1, 8, 4, 7, 5, 2, 6};
//   std::vector<NodeVal> _vals{3, 1, 8, 4, 7, 5, 2, 6, NULL_NODE, NULL_NODE,
//   11}; BTreeNode *root = create_tree(_vals); BTreeNode *_root =
//   create_tree(vals); std::cout << "Preorder Traversal: ";
//   preorderTraversal(root);
//   std::cout << std::endl;
//   std::cout << "Inorder Traversal: ";
//   inorderTraversal(root);
//   std::cout << std::endl;
//   std::cout << "Postorder Traversal: ";
//   postorderTraversal(root);
//   std::cout << std::endl;
//   std::cout << "Levelorder Traversal: ";
//   levelorderTraversal(root);
//   std::cout << std::endl;
//   std::cout << "No recursion Preorder Traversal: ";
//   norecursion_preorderTraversal(root);
//   std::cout << std::endl;
//   std::cout << "No recursion Inorder Traversal: ";
//   norecursion_inorderTraversal(root);
//   std::cout << std::endl;
//   std::cout << "No recursion Postorder Traversal: ";
//   norecursion_postorderTraversal(root);
//   std::cout << std::endl;

//   std::cout << "Height: " << height(root) << std::endl;
//   std::cout << "Is balanced: " << is_balanced(root) << std::endl;
//   std::cout << "Is valid BST: " << is_valid_bst(root) << std::endl;
//   BTreeNode *parent = getParent(root, 7);
//   std::cout << "Parent of 7: " << parent->val << std::endl;

//   std::cout << "Node size: " << node_size(root) << std::endl;
//   std::cout << "Leaf size: " << leaf_size(root) << std::endl;
//   std::cout << "Max depth: " << max_depth(root) << std::endl;
//   std::cout << "Min depth: " << min_depth(root) << std::endl;
//   std::cout << "Width: " << width(root) << std::endl;

//   BTreeNode *left = create_tree_node(6);
//   BTreeNode *right = create_tree_node(11);
//   BTreeNode *root2 = create_tree_node(3);
//   root2->left = left;
//   root2->right = right;
//   std::cout << "Is mirror: " << is_mirror(root, root2) << std::endl;
//   std::cout << "Is symmetric: " << is_symmetric(root) << std::endl;
//   std::cout << "Level of 6: " << level(root, 6) << std::endl;

//   // note: if u create new nodes, may they don't have common ancestor.
//   // u have to search and catch the ptr of target nodes for searching LCA.
//   BTreeNode *lca = lowestCommonAncestor(root, left, right);
//   BTreeNode *lca2 =
//       lowestCommonAncestor(root, search(root, 6), search(root, 11));
//   if (lca) {
//     std::cout << "Fake!Lowest common ancestor of 6 and 11: " << lca->val
//               << std::endl;
//   } else {
//     std::cout << "Fake! Lowest common ancestor of 6 and 11: NULL" <<
//     std::endl;
//   }
//   if (lca2) {
//     std::cout << "Lowest common ancestor of 6 and 11: " << lca2->val
//               << std::endl;
//   } else {
//     std::cout << "Lowest common ancestor of 6 and 11: NULL" << std::endl;
//   }

//   std::cout << "Is full: " << is_full(root) << std::endl;
//   std::cout << "Is complete(_root): " << is_complete(_root) << std::endl;

//   std::vector<BTreeNode *> leaves = collect_leaves(root);
//   std::cout << "Leaves: ";
//   for (auto leaf : leaves) {
//     std::cout << leaf->val << " ";
//   }
//   std::cout << std::endl;

//   BTreeNode *tn = twin_node(root, 5);
//   if (tn) {
//     std::cout << "Twin node of 5: " << tn->val << std::endl;
//   } else {
//     std::cout << "Twin node of 5: NULL" << std::endl;
//   }

//   std::vector<BTreeNode *> cousins = collect_cousins(root, 6);
//   std::cout << "Cousins of 6: ";
//   for (auto cousin : cousins) {
//     std::cout << cousin->val << " ";
//   }
//   std::cout << std::endl;

//   int target;
//   std::cout << "Enter target node value: ";
//   std::cin >> target;
//   auto path = path_from_root_to_node(root, target);
//   std::cout << "Path from root to " << target << ": ";
//   for (auto node : path) {
//     std::cout << node->val << " ";
//   }
//   std::cout << std::endl;

//   auto path2 = path_from_node_to_root(root, target);
//   std::cout << "Path from " << target << " to root: ";
//   for (auto node : path2) {
//     std::cout << node->val << " ";
//   }
//   std::cout << std::endl;

//   //          41
//   //         /   \
//   //       29     36
//   //      /  \     \
//   //     92  35    26
//   //         / \
//   //        17 5
//   std::vector<NodeVal> preorder{41, 29, 92, 35, 17, 5, 36, 26};
//   std::vector<NodeVal> inorder{92, 29, 17, 35, 5, 41, 36, 26};
//   std::vector<NodeVal> postorder{92, 17, 5, 35, 29, 26, 36, 41};
//   BTreeNode *new_root = build_tree_from_preorder_inorder(preorder,
//   inorder); std::cout << "Preorder Traversal of new tree: ";
//   postorderTraversal(new_root);
//   std::cout << std::endl;
//   BTreeNode *new_root2 = build_tree_from_inorder_postorder(inorder,
//   postorder); std::cout << "Inorder Traversal of new tree: ";
//   preorderTraversal(new_root2);
//   std::cout << std::endl;

//   delete root;
//   return 0;
// }