#include <iostream>
#include <string>

struct TreeNode {
  int val = 0;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
};

std::string StringifyTree(TreeNode* root, int indent = 0) {
  std::string string;
  if (root == nullptr) {
    return string;
  }
  for (int i = 0; i < indent; i++) {
    string += "    ";
  }
  string += std::to_string(root->val);
  string += '\n';
  string += StringifyTree(root->left, indent + 1);
  string += StringifyTree(root->right, indent + 1);
  return string;
}

std::ostream& operator<<(std::ostream& os, TreeNode* root) {
  os << StringifyTree(root);
  return os;
}
