#include <algorithm>
#include <stack>
#include <vector>

#include "binary_tree.h"

std::vector<int> PreorderTraversal(TreeNode *root) {
  std::vector<int> results;
  std::stack<TreeNode *> stack;
  stack.push(root);
  while (!stack.empty()) {
    TreeNode *node = stack.top();
    stack.pop();
    if (node == nullptr) {
      continue;
    }
    // root, left, right
    results.push_back(node->val);
    stack.push(node->right);
    stack.push(node->left);
  }
  return results;
}

std::vector<int> PostorderTraversal(TreeNode *root) {
  std::vector<int> results;
  std::stack<TreeNode *> stack;
  stack.push(root);
  while (!stack.empty()) {
    TreeNode *node = stack.top();
    stack.pop();
    if (node == nullptr) {
      continue;
    }
    // root, right, left
    results.push_back(node->val);
    stack.push(node->left);
    stack.push(node->right);
  }
  // left, right, root
  std::reverse(results.begin(), results.end());
  return results;
}

int main() {
  // https://leetcode.cn/problems/binary-tree-postorder-traversal/
}
