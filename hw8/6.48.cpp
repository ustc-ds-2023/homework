#include "binary_tree.h"

// Case 1: if both p and q are in the tree, return the lowest common ancestor
// Case 2: if only one of p or q is in the tree, return that node
// Case 3: if both p and q are not in the tree, return nullptr
// If return value is not nullptr, either p or q, or both, are in the tree
TreeNode* LowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (root == nullptr) {
    return nullptr;  // case 3
  }
  if (root == p || root == q) {
    return root;  // case 1, case 2
  }
  TreeNode* left = LowestCommonAncestor(root->left, p, q);
  TreeNode* right = LowestCommonAncestor(root->right, p, q);
  if (left != nullptr && right != nullptr) {
    return root;  // case 1
  }
  if (left != nullptr) {
    return left;  // case 1, case 2
  }
  if (right != nullptr) {
    return right;  // case 1, case 2
  }
  return nullptr;  // case 3
}

int main() {
  // https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
}