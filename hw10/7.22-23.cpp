#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using Graph = std::vector<std::vector<int>>;

// Return whether `end` is accessible from `start`
bool DFS(Graph &graph, int start, int end) {
  std::unordered_set<int> visited;
  std::stack<int> stack;
  stack.push(start);
  while (!stack.empty()) {
    int node = stack.top();
    stack.pop();
    if (visited.find(node) != visited.end()) {
      continue;
    }
    visited.insert(node);

    std::cout << "visit new node " << node << std::endl;
    if (node == end) {
      return true;
    }

    for (int i : graph[node]) {
      stack.push(i);
    }
  }
  return false;
}

// Return whether `end` is accessible from `start`
bool BFS(Graph &graph, int start, int end) {
  std::unordered_set<int> visited;
  std::queue<int> queue;
  queue.push(start);
  while (!queue.empty()) {
    int node = queue.front();
    queue.pop();
    if (visited.find(node) != visited.end()) {
      continue;
    }
    visited.insert(node);

    std::cout << "visit new node " << node << std::endl;
    if (node == end) {
      return true;
    }

    for (int i : graph[node]) {
      queue.push(i);
    }
  }
  return false;
}

int main() {
  Graph graph = {{1, 2, 3}, {}, {3, 5}, {2, 4}, {}, {}};
  assert(DFS(graph, 0, 5) && BFS(graph, 0, 5));
  assert(DFS(graph, 2, 4) && BFS(graph, 2, 4));
  assert(!DFS(graph, 3, 1) && !BFS(graph, 3, 1));
}
