#include <iostream>
#include <vector>

struct LinkedList {
  int data;
  LinkedList* next = nullptr;

  LinkedList(int data = 0) : data(data) {}

  // Create a linked list with placeholder head node
  LinkedList(std::vector<int> data) {
    LinkedList* tail = this;
    for (int x : data) {
      tail->next = new LinkedList(x);
      tail = tail->next;
    }
  }

  bool IsEqual(const LinkedList* other) {
    LinkedList* p1 = this->next;
    LinkedList* p2 = other->next;
    while (p1 != nullptr && p2 != nullptr) {
      if (p1->data != p2->data) {
        return false;
      }
      p1 = p1->next;
      p2 = p2->next;
    }
    if (p1 != nullptr || p2 != nullptr) {
      return false;
    }
    return true;
  }
};

std::ostream& operator<<(std::ostream& os, LinkedList* list) {
  LinkedList* p = list->next;
  while (p != nullptr) {
    os << p->data << " -> ";
    p = p->next;
  }
  os << "null";
  return os;
}
