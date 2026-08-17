// Floyd-Warshall 算法用于求解带权图中任意两点之间的最短路径。
// 它允许负权边，但图中不能存在负权环。

#include "Graph.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

struct FloydResult {
    vector<vector<algo::Weight>> distances;
    vector<vector<int>> next;
    bool hasNegativeCycle = false;
};

// 时间复杂度为 O(V^3)，空间复杂度为 O(V^2)。
FloydResult floydWarshall(const algo::Graph &graph) {
    const int vertexCount = graph.vertexCount();
    FloydResult result;
    result.distances.assign(vertexCount,
                            vector<algo::Weight>(vertexCount, algo::kInfinity));
    result.next.assign(vertexCount, vector<int>(vertexCount, -1));

    for (int vertex = 0; vertex < vertexCount; ++vertex) {
        result.distances[vertex][vertex] = 0;
        result.next[vertex][vertex] = vertex;
    }

    for (const algo::Edge &edge : graph.arcs()) {
        if (edge.weight < result.distances[edge.from][edge.to]) {
            result.distances[edge.from][edge.to] = edge.weight;
            result.next[edge.from][edge.to] = edge.to;
        }
    }

    for (int middle = 0; middle < vertexCount; ++middle) {
        for (int from = 0; from < vertexCount; ++from) {
            if (result.distances[from][middle] == algo::kInfinity) {
                continue;
            }

            for (int to = 0; to < vertexCount; ++to) {
                if (result.distances[middle][to] == algo::kInfinity) {
                    continue;
                }

                const algo::Weight candidate = result.distances[from][middle] +
                                               result.distances[middle][to];
                if (candidate < result.distances[from][to]) {
                    result.distances[from][to] = candidate;
                    result.next[from][to] = result.next[from][middle];
                }
            }
        }
    }

    for (int vertex = 0; vertex < vertexCount; ++vertex) {
        if (result.distances[vertex][vertex] < 0) {
            result.hasNegativeCycle = true;
            break;
        }
    }

    return result;
}

vector<int> reconstructPath(const FloydResult &result, int from, int to) {
    const int vertexCount = static_cast<int>(result.next.size());
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
        throw out_of_range("顶点编号超出范围");
    }
    if (result.hasNegativeCycle) {
        throw logic_error("存在负权环，最短路径没有定义");
    }
    if (result.next[from][to] == -1) {
        return {};
    }

    vector<int> path = {from};
    while (from != to) {
        from = result.next[from][to];
        path.push_back(from);
    }
    return path;
}

void printDistances(const FloydResult &result) {
    cout << "任意两点之间的最短距离:" << '\n';
    for (const auto &row : result.distances) {
        for (algo::Weight distance : row) {
            if (distance == algo::kInfinity) {
                cout << "INF\t";
            } else {
                cout << distance << '\t';
            }
        }
        cout << '\n';
    }
}

int main() {
    algo::Graph graph(5, true);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 8);
    graph.addEdge(0, 4, -4);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 7);
    graph.addEdge(2, 1, 4);
    graph.addEdge(3, 0, 2);
    graph.addEdge(3, 2, -5);
    graph.addEdge(4, 3, 6);

    const FloydResult result = floydWarshall(graph);
    if (result.hasNegativeCycle) {
        cout << "图中存在负权环，无法得到有限的最短路径。" << '\n';
        return 0;
    }

    printDistances(result);

    const int start = 0;
    const int destination = 2;
    const vector<int> path = reconstructPath(result, start, destination);
    cout << "从 " << start << " 到 " << destination << " 的最短路径: ";
    if (path.empty()) {
        cout << "不可达";
    } else {
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                cout << " -> ";
            }
            cout << path[i];
        }
    }
    cout << '\n';

    return 0;
}
