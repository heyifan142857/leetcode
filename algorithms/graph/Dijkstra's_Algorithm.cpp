// Dijkstra 算法用于求解非负权图中的单源最短路径。
// 本示例使用邻接表和最小堆，时间复杂度为 O((V + E) log V)。

#include "Graph.h"

#include <functional>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

vector<algo::Weight> dijkstra(const algo::Graph &graph, int source) {
    graph.neighbors(source); // 检查源点是否合法。
    for (const algo::Edge &edge : graph.arcs()) {
        if (edge.weight < 0) {
            throw invalid_argument("Dijkstra 算法不允许负权边");
        }
    }

    vector<algo::Weight> distances(graph.vertexCount(), algo::kInfinity);
    distances[source] = 0;

    using QueueItem = pair<algo::Weight, int>;
    priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        const auto [distance, vertex] = minHeap.top();
        minHeap.pop();

        if (distance != distances[vertex]) {
            continue; // 跳过已经过期的候选距离。
        }

        for (const algo::AdjacentEdge &edge : graph.neighbors(vertex)) {
            const algo::Weight candidate = distance + edge.weight;
            if (candidate < distances[edge.to]) {
                distances[edge.to] = candidate;
                minHeap.push({candidate, edge.to});
            }
        }
    }

    return distances;
}

void printDistances(const vector<algo::Weight> &distances, int source) {
    cout << "从顶点 " << source << " 到各顶点的最短距离:" << '\n';
    for (size_t vertex = 0; vertex < distances.size(); ++vertex) {
        cout << "  " << vertex << ": ";
        if (distances[vertex] == algo::kInfinity) {
            cout << "不可达";
        } else {
            cout << distances[vertex];
        }
        cout << '\n';
    }
}

int main() {
    algo::Graph graph(6, true);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    const int source = 0;
    printDistances(dijkstra(graph, source), source);

    return 0;
}
