from heapq import heappush, heappop

names = ['a', 'b', 'c', 'd', 'e', 'f', 'g']


def dijkstra(graph, start):
    """
    Dijkstra's shortest path algorithm.
    Return the minimum distances to all the nodes (`float('inf')` if not reachable).
    All edge weights should be non-negative.
    Time complexity: O(ElogE)
    """
    results = [float('inf')] * len(graph)
    results[start] = 0
    visited = set()
    heap = [(0, start)]
    while len(heap) > 0:
        cost, node = heappop(heap)
        if node in visited:
            continue
        visited.add(node)
        print(f'节点 {names[node]} 的最短距离为 {cost}，尝试以该节点为源点优化路径')

        for i, x in graph[node].items():
            if (new_cost := cost + x) < results[i]:
                print(
                    f'\t从节点 {names[node]} 到节点 {names[i]} 可使节点 {names[i]} 距离更近（{results[i]} -> {new_cost})，更新节点 {names[i]} 距离'
                )
                results[i] = new_cost
                heappush(heap, (new_cost, i))
    return results


if __name__ == "__main__":
    # Graph is in the format of adjacency dict.
    # graph = [{node:cost, node:cost}, {...}, ... {...}]
    graph = [{
        1: 15,
        2: 2,
        3: 12
    }, {
        4: 6
    }, {
        4: 8,
        5: 4
    }, {
        6: 3
    }, {
        6: 9
    }, {
        3: 5,
        6: 10
    }, {
        1: 4
    }]
    print(dijkstra(graph, 0))
