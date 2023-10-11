#include <cassert>
#include <iostream>

#include "sequential_list.h"

void SwapPtr(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void SwapRef(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void Reverse(SqList &list) {
  for (int i = 0, j = list.length - 1; i < j; i++, j--) {
    // 茴香豆的“茴”有几种写法
    SwapPtr(&list.data[i], &list.data[j]);
    // SwapRef(list.data[i], list.data[j]);
    // std::swap(list.data[i], list.data[j]);
  }
}

int main() {
  SqList list({});
  list = SqList({1, 2, 3, 4, 5});
  Reverse(list);
  assert(list == SqList({5, 4, 3, 2, 1}));

  list = SqList({1, 2, 3, 4});
  Reverse(list);
  assert(list == SqList({4, 3, 2, 1}));

  list = SqList({1});
  Reverse(list);
  assert(list == SqList({1}));

  list = SqList({});
  Reverse(list);
  assert(list == SqList({}));
}
