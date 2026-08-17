// Bellman-Ford 算法用于求解带负权边的单源最短路径。
// 它通过反复松弛所有边更新距离，并能检测从源点可达的负权环。

#include "Graph.h"

#include <iostream>
#include <vector>

using namespace std;

struct BellmanFordResult {
    vector<algo::Weight> distances;
    bool hasNegativeCycle = false;
};

// 时间复杂度为 O(VE)，空间复杂度为 O(V)。
BellmanFordResult bellmanFord(const algo::Graph &graph, int source) {
    graph.neighbors(source); // 检查源点是否合法。

    BellmanFordResult result;
    result.distances.assign(graph.vertexCount(), algo::kInfinity);
    result.distances[source] = 0;

    for (int round = 1; round < graph.vertexCount(); ++round) {
        bool updated = false;
        for (const algo::Edge &edge : graph.arcs()) {
            if (result.distances[edge.from] == algo::kInfinity) {
                continue;
            }

            const algo::Weight candidate =
                result.distances[edge.from] + edge.weight;
            if (candidate < result.distances[edge.to]) {
                result.distances[edge.to] = candidate;
                updated = true;
            }
        }

        if (!updated) {
            break;
        }
    }

    for (const algo::Edge &edge : graph.arcs()) {
        if (result.distances[edge.from] != algo::kInfinity &&
            result.distances[edge.from] + edge.weight <
                result.distances[edge.to]) {
            result.hasNegativeCycle = true;
            break;
        }
    }

    return result;
}

void printDistances(const BellmanFordResult &result, int source) {
    cout << "从顶点 " << source << " 到各顶点的最短距离:" << '\n';
    for (size_t vertex = 0; vertex < result.distances.size(); ++vertex) {
        cout << "  " << vertex << ": ";
        if (result.distances[vertex] == algo::kInfinity) {
            cout << "不可达";
        } else {
            cout << result.distances[vertex];
        }
        cout << '\n';
    }
}

int main() {
    algo::Graph graph(5, true);
    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    const int source = 0;
    const BellmanFordResult result = bellmanFord(graph, source);
    if (result.hasNegativeCycle) {
        cout << "图中存在从源点可达的负权环。" << '\n';
    } else {
        printDistances(result, source);
    }

    return 0;
}
