#include <cassert>
#include <iostream>

#include "linked_list.h"

void Delete(LinkedList* list, int mink, int maxk) {
  assert(mink <= maxk);
  LinkedList* previous = list;
  LinkedList* current = list->next;
  while (current != nullptr) {
    if (current->data > mink && current->data < maxk) {
      // remove current
      previous->next = current->next;
      delete current;
      current = previous->next;
    } else {
      previous = current;
      current = current->next;
    }
  }
}

int main() {
  LinkedList* list;
  list = new LinkedList({0, 2, 4, 4, 5, 5, 10});
  Delete(list, 2, 6);
  assert(list->IsEqual(new LinkedList({0, 2, 10})));

  list = new LinkedList({0, 2, 4, 4, 5, 5, 10});
  Delete(list, 5, 5);
  assert(list->IsEqual(new LinkedList({0, 2, 4, 4, 5, 5, 10})));

  list = new LinkedList({0, 2, 4, 4, 5, 5, 10});
  Delete(list, -1, 10);
  assert(list->IsEqual(new LinkedList(std::vector<int>{10})));

  list = new LinkedList({0, 2, 4, 4, 5, 5, 10});
  Delete(list, -1, 11);
  assert(list->IsEqual(new LinkedList(std::vector<int>{})));
}
