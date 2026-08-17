// 广度优先搜索（BFS）从起点开始逐层访问图中的顶点。
// 本示例使用邻接表和队列实现，时间复杂度为 O(V + E)。

#include "Graph.h"

#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void bfsFrom(const algo::Graph &graph, int start, vector<bool> &visited,
             vector<int> &order) {
    queue<int> pending;
    visited[start] = true;
    pending.push(start);

    while (!pending.empty()) {
        const int vertex = pending.front();
        pending.pop();
        order.push_back(vertex);

        for (const algo::AdjacentEdge &edge : graph.neighbors(vertex)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true; // 入队时标记，避免重复入队。
                pending.push(edge.to);
            }
        }
    }
}

// 返回从 start 可达的所有顶点的 BFS 顺序。
vector<int> bfs(const algo::Graph &graph, int start) {
    graph.neighbors(start); // 检查起点是否合法。
    vector<bool> visited(graph.vertexCount(), false);
    vector<int> order;
    bfsFrom(graph, start, visited, order);
    return order;
}

// 遍历整张图：先访问 start 所在的连通分量，再依次访问其余分量。
vector<int> bfsAll(const algo::Graph &graph, int start = 0) {
    if (graph.vertexCount() == 0) {
        return {};
    }
    graph.neighbors(start);

    vector<bool> visited(graph.vertexCount(), false);
    vector<int> order;
    bfsFrom(graph, start, visited, order);

    for (int vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        if (!visited[vertex]) {
            bfsFrom(graph, vertex, visited, order);
        }
    }
    return order;
}

void printOrder(const vector<int> &order) {
    for (size_t i = 0; i < order.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << order[i];
    }
    cout << '\n';
}

int main() {
    // 顶点 0 到 5 连通，顶点 6 单独构成另一个连通分量。
    algo::Graph graph(7);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);

    cout << "从顶点 0 开始的 BFS: ";
    printOrder(bfs(graph, 0));

    cout << "整张图的 BFS: ";
    printOrder(bfsAll(graph, 0));

    return 0;
}
