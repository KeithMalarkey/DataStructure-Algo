#include <stdio.h>
#include "tree_utils.h"
#include <stdlib.h>

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
  printf("data structure and algorithm implemened by C\n");
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

  // Test cousin nodes
  Node **cns = get_cousin_nodes(tree2, search(tree2, 'D'));
  if (cns != NULL) {
    printf("Cousin nodes of 'D': ");
    int cousin_count = 0;
    while (cns[cousin_count] != NULL)
      cousin_count++; // count cousins if NULL-terminated
    // If not NULL-terminated, use get_size(tree2) or track count in
    // get_cousin_nodes
    for (int i = 0; i < cousin_count; ++i) {
      printf("%c ", cns[i]->data);
    }
    printf("\n");
    free(cns);
  } else {
    printf("No cousin nodes found for 'D'.\n");
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

  // Test complete binary tree
  if (is_complete(tree)) {
    printf("Tree 0 is complete tree\n");
  } else {
    printf("Tree 0 is not complete tree\n");
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