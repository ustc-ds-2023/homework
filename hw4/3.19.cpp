#include <cassert>
#include <iostream>
#include <stack>
#include <string>

// https://leetcode.cn/problems/valid-parentheses/
bool IsMatch(std::string expression) {
  std::stack<char> stack;
  for (char c : expression) {
    if (c == '(' || c == '[' || c == '{') {
      stack.push(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (stack.empty()) {
        return false;
      }
      if (c == ')' && stack.top() != '(') {
        return false;
      }
      if (c == ']' && stack.top() != '[') {
        return false;
      }
      if (c == '}' && stack.top() != '{') {
        return false;
      }
      stack.pop();
    }
  }
  return stack.empty();
}

int main() {
  assert(IsMatch("()[]{}"));
  assert(IsMatch("(a)[b]{()}."));
  assert(IsMatch("abc"));
  assert(IsMatch(""));
  assert(!IsMatch(")[b]{()}."));
  assert(!IsMatch("(}"));
}
