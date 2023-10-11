#include <cassert>
#include <iostream>

#include "linked_list.h"

LinkedList* Intersect(LinkedList* A, LinkedList* B) {
  LinkedList* head = new LinkedList();
  LinkedList* tail = head;
  LinkedList* p1 = A->next;
  LinkedList* p2 = B->next;
  while (p1 != nullptr && p2 != nullptr) {
    if (p1->data < p2->data) {
      p1 = p1->next;
    } else if (p1->data > p2->data) {
      p2 = p2->next;
    } else {
      // equal values found,
      // create new node and append to C
      tail->next = new LinkedList(p1->data);
      tail = tail->next;
      p1 = p1->next;
      p2 = p2->next;
    }
  }
  return head;
}

int main() {
  LinkedList *A, *B, *C;
  A = new LinkedList({0, 2, 3, 4});
  B = new LinkedList({0, 1, 2, 4});
  C = Intersect(A, B);
  assert(C->IsEqual(new LinkedList({0, 2, 4})));

  A = new LinkedList({0, 1, 2, 3, 4});
  B = new LinkedList({0, 1, 2, 3, 4});
  C = Intersect(A, B);
  assert(C->IsEqual(new LinkedList({0, 1, 2, 3, 4})));

  A = new LinkedList({0, 1, 2, 3, 4});
  B = new LinkedList(std::vector<int>{6});
  C = Intersect(A, B);
  assert(C->IsEqual(new LinkedList(std::vector<int>{})));

  A = new LinkedList(std::vector<int>{});
  B = new LinkedList(std::vector<int>{});
  C = Intersect(A, B);
  assert(C->IsEqual(new LinkedList(std::vector<int>{})));
}
