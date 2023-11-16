#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

struct ThreadTreeNode {
  int val = 0;
  ThreadTreeNode* left = nullptr;
  ThreadTreeNode* right = nullptr;
  bool left_thread = false;   // whether the left child is a thread
  bool right_thread = false;  // whether the right child is a thread
  bool threadified = false;   // whether the tree has been threadified

  void Threadify() {
    assert(!threadified);
    std::stack<ThreadTreeNode*> stack;
    ThreadTreeNode* previous = nullptr;
    ThreadTreeNode* current = this;
    while (!stack.empty() || current != nullptr) {
      while (current != nullptr) {
        stack.push(current);
        current = current->left;
      }
      current = stack.top();
      stack.pop();
      if (previous != nullptr) {
        if (previous->right == nullptr) {
          previous->right = current;
          previous->right_thread = true;
        }
        if (current->left == nullptr) {
          current->left = previous;
          current->left_thread = true;
        }
      }
      previous = current;
      current = current->right;
    }
    threadified = true;
  }

  // return the first node in the inorder traversal sequence
  ThreadTreeNode* _GetLeftmost() {
    ThreadTreeNode* current = this;
    while (current->left != nullptr && !current->left_thread) {
      current = current->left;
    }
    return current;
  }

  std::vector<int> InorderTraversal() {
    assert(threadified);
    std::vector<int> results;
    ThreadTreeNode* current = _GetLeftmost();
    while (current != nullptr) {
      results.push_back(current->val);
      current = current->GetSuccessor();
    }
    return results;
  }

  // assume the whole tree is threadified
  ThreadTreeNode* GetPredecessor() {
    if (this->left_thread) {
      return this->left;
    }
    ThreadTreeNode* current = this->left;
    while (current != nullptr && !current->right_thread) {
      current = current->right;
    }
    return current;
  }

  // assume the whole tree is threadified
  ThreadTreeNode* GetSuccessor() {
    if (this->right_thread) {
      return this->right;
    }
    ThreadTreeNode* current = this->right;
    while (current != nullptr && !current->left_thread) {
      current = current->left;
    }
    return current;
  }
};

void Insert(ThreadTreeNode* p, ThreadTreeNode* x) {
  if (p->left_thread) {
    // p has no left children
    ThreadTreeNode* p_predecessor = p->GetPredecessor();
    ThreadTreeNode* x_leftmost = x->_GetLeftmost();

    p->left = x;

    x_leftmost->left_thread = true;
    x_leftmost->left = p_predecessor;
    p->left_thread = false;
    x->right_thread = true;
    x->right = p;
    return;
  }
  // p has left children
  ThreadTreeNode* p_left_leftmost = p->left->_GetLeftmost();
  ThreadTreeNode* p_left_predecessor = p_left_leftmost->GetPredecessor();
  ThreadTreeNode* x_leftmost = x->_GetLeftmost();

  x->right = p->left;
  p->left = x;

  x_leftmost->left_thread = true;
  x_leftmost->left = p_left_predecessor;
  p_left_leftmost->left_thread = true;
  p_left_leftmost->left = x;
}

int main() {
  // test case 1
  ThreadTreeNode* root = new ThreadTreeNode{
      1,
      new ThreadTreeNode{
          2,
          new ThreadTreeNode{4},
          new ThreadTreeNode{5},
      },
      new ThreadTreeNode{
          3,
          new ThreadTreeNode{
              6,
              new ThreadTreeNode{8},
              new ThreadTreeNode{9},
          },
          new ThreadTreeNode{7},
      },
  };
  root->Threadify();
  ThreadTreeNode* x = new ThreadTreeNode{
      10,
      new ThreadTreeNode{
          11,
          new ThreadTreeNode{12},
          new ThreadTreeNode{13},
      },

  };
  x->Threadify();
  ThreadTreeNode* p = root->right;
  Insert(p, x);
  assert((root->InorderTraversal() ==
          std::vector<int>{4, 2, 5, 1, 12, 11, 13, 10, 8, 6, 9, 3, 7}));

  // test case 2
  root = new ThreadTreeNode{
      1,
      new ThreadTreeNode{
          2,
          new ThreadTreeNode{
              4,
              new ThreadTreeNode{8},
              new ThreadTreeNode{9},
          },
          new ThreadTreeNode{5},
      },
      new ThreadTreeNode{
          3,
          new ThreadTreeNode{6},
          new ThreadTreeNode{7},
      },
  };
  root->Threadify();
  x = new ThreadTreeNode{
      10,
      new ThreadTreeNode{
          11,
          new ThreadTreeNode{12},
          new ThreadTreeNode{13},
      },

  };
  x->Threadify();
  p = root->left;
  Insert(p, x);
  assert((root->InorderTraversal() ==
          std::vector<int>{12, 11, 13, 10, 8, 4, 9, 2, 5, 1, 6, 3, 7}));

  // test case 3
  root = new ThreadTreeNode{
      1,
      new ThreadTreeNode{
          2,
          new ThreadTreeNode{4},
          new ThreadTreeNode{5},
      },
      new ThreadTreeNode{
          3,
          nullptr,
          new ThreadTreeNode{7},
      },
  };
  root->Threadify();
  x = new ThreadTreeNode{
      10,
      new ThreadTreeNode{
          11,
          new ThreadTreeNode{12},
          new ThreadTreeNode{13},
      },

  };
  x->Threadify();
  p = root->right;
  Insert(p, x);
  assert((root->InorderTraversal() ==
          std::vector<int>{4, 2, 5, 1, 12, 11, 13, 10, 3, 7}));
}
