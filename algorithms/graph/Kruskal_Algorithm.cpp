// Kruskal 算法按边权从小到大选边，以构造图的最小生成树。
// 共享的并查集用于判断一条候选边是否会形成环。

#include "DisjointSet.h"
#include "Graph.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

struct KruskalResult {
    vector<algo::Edge> edges;
    algo::Weight totalWeight = 0;
    bool isConnected = false;
};

// 时间复杂度为 O(E log E)，主要开销来自边排序。
KruskalResult kruskal(const algo::Graph &graph) {
    if (graph.isDirected()) {
        throw invalid_argument("Kruskal 算法要求输入无向图");
    }

    vector<algo::Edge> sortedEdges = graph.edges();
    sort(sortedEdges.begin(), sortedEdges.end(),
         [](const algo::Edge &left, const algo::Edge &right) {
             return left.weight < right.weight;
         });

    algo::DisjointSet disjointSet(graph.vertexCount());
    KruskalResult result;

    for (const algo::Edge &edge : sortedEdges) {
        if (disjointSet.unite(edge.from, edge.to)) {
            result.edges.push_back(edge);
            result.totalWeight += edge.weight;

            if (result.edges.size() ==
                static_cast<size_t>(max(0, graph.vertexCount() - 1))) {
                break;
            }
        }
    }

    result.isConnected =
        graph.vertexCount() == 0 || disjointSet.componentCount() == 1;
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

    const KruskalResult result = kruskal(graph);
    if (!result.isConnected) {
        cout << "图不连通，无法生成完整的最小生成树。" << '\n';
        return 0;
    }

    cout << "Kruskal 最小生成树包含的边:" << '\n';
    for (const algo::Edge &edge : result.edges) {
        cout << "  " << edge.from << " -- " << edge.to << ": " << edge.weight
             << '\n';
    }
    cout << "总权重: " << result.totalWeight << '\n';

    return 0;
}
