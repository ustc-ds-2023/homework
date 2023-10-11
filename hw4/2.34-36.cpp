#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

struct Node {
  int data;
  Node* ptr = nullptr;
};

struct LinkedList {
  // left and right are dummy head nodes containing no data
  Node* left = nullptr;
  Node* right = nullptr;

  LinkedList(std::vector<int> data) {
    this->left = new Node();
    this->right = new Node();
    this->left->ptr = this->right;
    this->right->ptr = this->left;
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
      this->Insert(0, *it);
    }
  }

  std::vector<int> LeftIterate() const {
    std::vector<int> data;
    Node* previous = this->left;
    Node* current = this->left->ptr;
    Node* next = nullptr;
    while ((next = (Node*)((uintptr_t)previous ^ (uintptr_t)current->ptr)) !=
           nullptr) {
      data.push_back(current->data);
      previous = current;
      current = next;
    }
    return data;
  }

  std::vector<int> RightIterate() const {
    std::vector<int> data;
    Node* previous = this->right;
    Node* current = this->right->ptr;
    Node* next = nullptr;
    while ((next = (Node*)((uintptr_t)previous ^ (uintptr_t)current->ptr)) !=
           nullptr) {
      data.push_back(current->data);
      previous = current;
      current = next;
    }
    return data;
  }

  // index the i-th element (zero-based, from left)
  std::tuple<Node*, Node*, Node*> Index(unsigned int i) {
    Node* previous = this->left;
    Node* current = this->left->ptr;
    Node* next = (Node*)((uintptr_t)previous ^ (uintptr_t)current->ptr);
    for (unsigned int j = 0; j < i; j++) {
      if (next == nullptr) {
        throw std::runtime_error("Wrong index");
      }
      previous = current;
      current = next;
      next = (Node*)((uintptr_t)previous ^ (uintptr_t)current->ptr);
    }
    return {previous, current, next};
  }

  // insert data into index i (zero-based, from left)
  void Insert(unsigned int i, int data) {
    auto [previous, current, next] = this->Index(i);
    // now insert node between previous and current
    Node* node = new Node{
        .data = data, .ptr = (Node*)((uintptr_t)previous ^ (uintptr_t)current)};
    previous->ptr = (Node*)((uintptr_t)previous->ptr ^ (uintptr_t)node ^
                            (uintptr_t)current);
    current->ptr = (Node*)((uintptr_t)previous ^ (uintptr_t)node ^
                           (uintptr_t)current->ptr);
  }

  // delete the node with index i (zero-based, from left)
  void Delete(unsigned int i) {
    auto [previous, current, next] = this->Index(i);
    if (next == nullptr) {
      throw std::runtime_error("Wrong index");
    }
    // now delete current node
    previous->ptr = (Node*)((uintptr_t)previous->ptr ^ (uintptr_t)current ^
                            (uintptr_t)next);
    next->ptr = (Node*)((uintptr_t)previous ^ (uintptr_t)current ^
                        (uintptr_t)next->ptr);
    delete current;
  }
};

std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
  os << "null <-> ";
  for (int x : list.LeftIterate()) {
    os << x << " <-> ";
  }
  os << "null";
  return os;
}

bool operator==(const LinkedList& lhs, const LinkedList& rhs) {
  return lhs.LeftIterate() == rhs.LeftIterate();
}

bool operator==(const LinkedList& lhs, const std::vector<int>& rhs) {
  return lhs.LeftIterate() == rhs;
}

int main() {
  LinkedList list({});
  list = LinkedList({1, 2, 3, 4});
  assert((list.LeftIterate() == std::vector<int>{1, 2, 3, 4}));
  assert((list.RightIterate() == std::vector<int>{4, 3, 2, 1}));
  list.Insert(0, 0);
  assert((list == std::vector<int>{0, 1, 2, 3, 4}));
  list.Insert(5, 6);
  assert((list == std::vector<int>{0, 1, 2, 3, 4, 6}));
  list.Insert(5, 5);
  assert((list == std::vector<int>{0, 1, 2, 3, 4, 5, 6}));
  list.Delete(0);
  assert((list == std::vector<int>{1, 2, 3, 4, 5, 6}));
  list.Delete(5);
  assert((list == std::vector<int>{1, 2, 3, 4, 5}));
  list.Delete(2);
  assert((list == std::vector<int>{1, 2, 4, 5}));
  list.Delete(0);
  assert((list == std::vector<int>{2, 4, 5}));
  list.Delete(0);
  assert((list == std::vector<int>{4, 5}));
  list.Delete(0);
  assert((list == std::vector<int>{5}));
  list.Delete(0);
  assert((list == std::vector<int>{}));
}
