#include <cassert>
#include <cmath>
#include <iostream>
#include <stack>
#include <tuple>

int akm_recursive(int m, int n) {
  assert(m >= 0 && n >= 0);
  if (m == 0) {
    return n + 1;
  }
  if (n == 0) {
    return akm_recursive(m - 1, 1);
  }
  return akm_recursive(m - 1, akm_recursive(m, n - 1));
}

std::ostream& operator<<(std::ostream& os,
                         std::stack<std::pair<int, int>>& stack) {
  std::stack<std::pair<int, int>> temp;
  while (!stack.empty()) {
    temp.push(stack.top());
    stack.pop();
  }
  while (!temp.empty()) {
    std::pair<int, int> top = temp.top();
    os << "(" << top.first << ", " << top.second << ") ";
    stack.push(top);
    temp.pop();
  }
  return os;
}

int akm_stack(int m, int n, bool verbose = false) {
  assert(m >= 0 && n >= 0);
  std::stack<std::pair<int, int>> stack;
  stack.push({m, n});

  while (true) {
    if (verbose) {
      std::cout << stack << std::endl;
    }
    assert(!stack.empty());
    std::tie(m, n) = stack.top();
    stack.pop();

    if (m == 0) {
      if (stack.empty()) {
        return n + 1;
      }
      assert(stack.top().second == -1);
      stack.top().second = n + 1;
      continue;
    }
    if (n == 0) {
      stack.push({m - 1, 1});
      continue;
    }
    stack.push({m - 1, -1});
    stack.push({m, n - 1});
  }
}

int main() {
  for (int m = 0; m < 4; m++) {
    for (int n = 0; n < 4; n++) {
      int result = akm_recursive(m, n);
      assert(result == akm_stack(m, n));
      if (m == 0) {
        assert(result == n + 1);
      } else if (m == 1) {
        assert(result == n + 2);
      } else if (m == 2) {
        assert(result == 2 * n + 3);
      } else if (m == 3) {
        assert(result == std::pow(2, n + 3) - 3);
      }
    }
  }
  akm_stack(2, 1, true);
  // (2, 1)
  // (1, -1) (2, 0)
  // (1, -1) (1, 1)
  // (1, -1) (0, -1) (1, 0)
  // (1, -1) (0, -1) (0, 1)
  // (1, -1) (0, 2)
  // (1, 3)
  // (0, -1) (1, 2)
  // (0, -1) (0, -1) (1, 1)
  // (0, -1) (0, -1) (0, -1) (1, 0)
  // (0, -1) (0, -1) (0, -1) (0, 1)
  // (0, -1) (0, -1) (0, 2)
  // (0, -1) (0, 3)
  // (0, 4)
}
