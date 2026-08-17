// Prim 算法从一个顶点开始，每次选择连接生成树与未访问顶点的最小权边。
// 本示例使用邻接表和最小堆实现。

#include "Graph.h"

#include <functional>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <vector>

using namespace std;

struct PrimResult {
    vector<algo::Edge> edges;
    algo::Weight totalWeight = 0;
    bool isConnected = false;
};

// 时间复杂度为 O((V + E) log E)，空间复杂度为 O(V + E)。
PrimResult prim(const algo::Graph &graph, int start = 0) {
    if (graph.isDirected()) {
        throw invalid_argument("Prim 算法要求输入无向图");
    }

    PrimResult result;
    if (graph.vertexCount() == 0) {
        result.isConnected = true;
        return result;
    }
    graph.neighbors(start); // 检查起点是否合法。

    vector<bool> visited(graph.vertexCount(), false);
    using CandidateEdge = tuple<algo::Weight, int, int>;
    priority_queue<CandidateEdge, vector<CandidateEdge>, greater<CandidateEdge>>
        minHeap;
    minHeap.push({0, -1, start});

    int visitedCount = 0;
    while (!minHeap.empty()) {
        const auto [weight, from, to] = minHeap.top();
        minHeap.pop();

        if (visited[to]) {
            continue;
        }

        visited[to] = true;
        ++visitedCount;
        if (from != -1) {
            result.edges.push_back({from, to, weight});
            result.totalWeight += weight;
        }

        for (const algo::AdjacentEdge &edge : graph.neighbors(to)) {
            if (!visited[edge.to]) {
                minHeap.push({edge.weight, to, edge.to});
            }
        }
    }

    result.isConnected = visitedCount == graph.vertexCount();
    return result;
}

int main() {
    algo::Graph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 3, 4);
    graph.addEdge(0, 4, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 5);
    graph.addEdge(3, 4, 6);

    const PrimResult result = prim(graph, 0);
    if (!result.isConnected) {
        cout << "图不连通，无法生成完整的最小生成树。" << '\n';
        return 0;
    }

    cout << "Prim 最小生成树包含的边:" << '\n';
    for (const algo::Edge &edge : result.edges) {
        cout << "  " << edge.from << " -- " << edge.to << ": " << edge.weight
             << '\n';
    }
    cout << "总权重: " << result.totalWeight << '\n';

    return 0;
}
