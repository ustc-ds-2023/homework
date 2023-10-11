#include <cassert>
#include <iostream>

#include "sequential_list.h"

// Remove intersect(B,C) from A
void RemoveIntersection(SqList &A, SqList &B, SqList &C) {
  unsigned int i = 0;     // B
  unsigned int j = 0;     // C
  unsigned int fast = 0;  // A (fast)
  unsigned int slow = 0;  // A (slow)
  while (i < B.length && j < C.length && fast < A.length) {
    // Ignore duplicates in B and C
    if (i != B.length - 1 && B.data[i] == B.data[i + 1]) {
      i++;
      continue;
    }
    if (j != C.length - 1 && C.data[j] == C.data[j + 1]) {
      j++;
      continue;
    }

    if (B.data[i] < C.data[j]) {
      i++;
    } else if (B.data[i] > C.data[j]) {
      j++;
    } else {
      // equal values found,
      // remove that value from A (if exists)
      int value = B.data[i];
      // 注意：短路时两个条件的顺序
      while (fast < A.length && A.data[fast] < value) {
        A.data[slow] = A.data[fast];
        fast++;
        slow++;
      }
      while (fast < A.length && A.data[fast] == value) {
        fast++;
      }
      i++;
      j++;
    }
  }

  while (fast < A.length) {
    A.data[slow] = A.data[fast];
    fast++;
    slow++;
  }
  A.length = slow;
}

int main() {
  SqList A({}), B({}), C({});
  A = SqList({1, 2, 2, 2, 3, 3, 4, 5, 5, 5});
  B = SqList({2, 3, 3, 4, 4});
  C = SqList({3, 4, 4, 5, 5, 5});
  // intersect(B,C) = {3, 4}
  RemoveIntersection(A, B, C);
  assert(A == SqList({1, 2, 2, 2, 5, 5, 5}));

  A = SqList({1, 2, 2, 2, 3, 3, 4, 5, 5, 5});
  B = SqList({2});
  C = SqList({3, 4, 4, 5, 5, 5});
  // intersect(B,C) = {}
  RemoveIntersection(A, B, C);
  assert(A == SqList({1, 2, 2, 2, 3, 3, 4, 5, 5, 5}));

  A = SqList({1, 2, 2, 2, 3, 3, 4, 5, 5, 5});
  B = SqList({1, 2, 3, 4, 5, 6, 7});
  C = SqList({0, 1, 2, 3, 4, 5, 5});
  // intersect(B,C) = {1, 2, 3, 4, 5}
  RemoveIntersection(A, B, C);
  assert(A == SqList({}));
}
