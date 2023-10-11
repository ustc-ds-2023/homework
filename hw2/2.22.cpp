#include <cassert>
#include <iostream>

#include "linked_list.h"

void Reverse(LinkedList* list) {
  LinkedList* previous = nullptr;
  LinkedList* current = list->next;
  while (current != nullptr) {
    LinkedList* temp = current->next;  // 暂存 next 值
    current->next = previous;          // 反转 previous 和 current
    // previous 和 current 前进
    previous = current;
    current = temp;
  }
  list->next = previous;
}

void ReverseHead(LinkedList* list) {
  LinkedList* head = nullptr;  // head of the new list
  LinkedList* current = list->next;
  while (current != nullptr) {
    LinkedList* temp = current->next;  // 暂存 next 值
    // 头插：将 current 作为新的头，插入到 head 前
    current->next = head;
    head = current;
    current = temp;  // current 前进
  }
  list->next = head;
}

int main() {
  LinkedList* list;
  list = new LinkedList({1, 2, 3, 4, 5});
  Reverse(list);
  assert(list->IsEqual(new LinkedList({5, 4, 3, 2, 1})));

  list = new LinkedList({1, 2, 3, 4});
  Reverse(list);
  assert(list->IsEqual(new LinkedList({4, 3, 2, 1})));

  list = new LinkedList(std::vector<int>{1});
  Reverse(list);
  assert(list->IsEqual(new LinkedList(std::vector<int>{1})));

  list = new LinkedList(std::vector<int>{});
  Reverse(list);
  assert(list->IsEqual(new LinkedList(std::vector<int>{})));
}
