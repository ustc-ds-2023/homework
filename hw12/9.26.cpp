#include <cassert>
#include <iostream>
#include <vector>

int Recurse(std::vector<int> &array, int target, int low, int high) {
  if (low > high) {
    return -1;
  }
  int middle = (low + high) / 2;
  if (array[middle] == target) {
    return middle;
  }
  if (array[middle] < target) {
    return Recurse(array, target, middle + 1, high);
  }
  return Recurse(array, target, low, middle - 1);
}

// Search `target` in `array` which is already sorted.
// Return the index if found, -1 otherwise.
// https://leetcode.cn/problems/binary-search/description/
int BinarySearch(std::vector<int> &array, int target) {
  return Recurse(array, target, 0, array.size() - 1);
}

int main() {
  std::vector<int> array;
  array = {};
  assert(BinarySearch(array, 0) == -1);
  array = {1};
  assert(BinarySearch(array, 0) == -1);
  assert(BinarySearch(array, 1) == 0);
  array = {0, 2, 3, 5, 5, 6, 7, 10};
  assert(BinarySearch(array, -1) == -1);
  assert(BinarySearch(array, 0) == 0);
  assert(BinarySearch(array, 5) == 3);
}
