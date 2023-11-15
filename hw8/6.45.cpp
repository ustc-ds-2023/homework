#include <cassert>
#include <iostream>

#include "binary_tree.h"

// Free the memory allocated for the tree.
void DeleteNode(TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  DeleteNode(root->left);
  DeleteNode(root->right);
  delete root;
}

// Remove the node with value x (and all its children) from the tree.
TreeNode *RemoveNode(TreeNode *root, int x) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->val == x) {
    DeleteNode(root);
    return nullptr;
  }
  root->left = RemoveNode(root->left, x);
  root->right = RemoveNode(root->right, x);
  return root;
}

int main() {
  TreeNode *root = new TreeNode{
      1,
      new TreeNode{
          2,
          new TreeNode{4},
          new TreeNode{5},
      },
      new TreeNode{
          3,
          new TreeNode{2},
          new TreeNode{7},
      },
  };
  std::cout << "Before:\n" << root;
  std::cout << "After:\n" << RemoveNode(root, 2);
  // Before:
  // 1
  //     2
  //         4
  //         5
  //     3
  //         2
  //         7
  // After:
  // 1
  //     3
  //         7
}