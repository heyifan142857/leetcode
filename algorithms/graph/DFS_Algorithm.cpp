// 深度优先搜索（DFS）沿一条路径尽可能深入，再回溯访问其他分支。
// 本示例使用邻接表和递归实现，时间复杂度为 O(V + E)。

#include "Graph.h"

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void dfsFrom(const algo::Graph &graph, int vertex, vector<bool> &visited,
             vector<int> &order) {
    visited[vertex] = true;
    order.push_back(vertex);

    for (const algo::AdjacentEdge &edge : graph.neighbors(vertex)) {
        if (!visited[edge.to]) {
            dfsFrom(graph, edge.to, visited, order);
        }
    }
}

// 返回从 start 可达的所有顶点的 DFS 顺序。
vector<int> dfs(const algo::Graph &graph, int start) {
    graph.neighbors(start); // 检查起点是否合法。
    vector<bool> visited(graph.vertexCount(), false);
    vector<int> order;
    dfsFrom(graph, start, visited, order);
    return order;
}

// 遍历整张图：先访问 start 所在的连通分量，再依次访问其余分量。
vector<int> dfsAll(const algo::Graph &graph, int start = 0) {
    if (graph.vertexCount() == 0) {
        return {};
    }
    graph.neighbors(start);

    vector<bool> visited(graph.vertexCount(), false);
    vector<int> order;
    dfsFrom(graph, start, visited, order);

    for (int vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        if (!visited[vertex]) {
            dfsFrom(graph, vertex, visited, order);
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

    cout << "从顶点 0 开始的 DFS: ";
    printOrder(dfs(graph, 0));

    cout << "整张图的 DFS: ";
    printOrder(dfsAll(graph, 0));

    return 0;
}
