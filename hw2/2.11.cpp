#include <cassert>
#include <iostream>

#include "sequential_list.h"

// Insert `value` into ordered `list`
void Insert(SqList &list, int value) {
  list.Enlarge(1);
  for (int i = list.length - 2; i >= 0; i--) {
    if (list.data[i] > value) {
      list.data[i + 1] = list.data[i];
    } else {
      list.data[i + 1] = value;
      return;
    }
  }
  list.data[0] = value;
}

int main() {
  SqList list({});
  list = SqList({1, 2, 2, 4, 10});
  Insert(list, 3);
  assert(list == SqList({1, 2, 2, 3, 4, 10}));

  list = SqList({1, 2, 2, 4, 10});
  Insert(list, 0);
  assert(list == SqList({0, 1, 2, 2, 4, 10}));

  list = SqList({1, 2, 2, 4, 10});
  Insert(list, 2);
  assert(list == SqList({1, 2, 2, 2, 4, 10}));

  list = SqList({1, 2, 2, 4, 10});
  Insert(list, 13);
  assert(list == SqList({1, 2, 2, 4, 10, 13}));

  list = SqList({});
  Insert(list, 1);
  assert(list == SqList({1}));
}
