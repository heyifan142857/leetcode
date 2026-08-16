// Floyd-Warshall 算法用于求解带权图中任意两点之间的最短路径。
// 它允许负权边，但图中不能存在负权环。

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

class Graph {
public:
    using Distance = long long;

    struct FloydResult {
        vector<vector<Distance>> distances;
        vector<vector<int>> next;
        bool hasNegativeCycle = false;
    };

private:
    static constexpr Distance INF = numeric_limits<Distance>::max() / 4;
    vector<vector<Distance>> adjacencyMatrix;

    void checkVertex(int vertex) const {
        if (vertex < 0 || vertex >= static_cast<int>(adjacencyMatrix.size())) {
            throw out_of_range("顶点编号超出范围");
        }
    }

public:
    explicit Graph(int vertexCount) {
        if (vertexCount < 0) {
            throw invalid_argument("顶点数不能为负数");
        }

        adjacencyMatrix.assign(vertexCount, vector<Distance>(vertexCount, INF));
        for (int i = 0; i < vertexCount; ++i) {
            adjacencyMatrix[i][i] = 0;
        }
    }

    // 添加一条有向边；存在重边时只保留权重最小的一条。
    void addEdge(int from, int to, Distance weight) {
        checkVertex(from);
        checkVertex(to);
        adjacencyMatrix[from][to] = min(adjacencyMatrix[from][to], weight);
    }

    // 时间复杂度为 O(V^3)，空间复杂度为 O(V^2)。
    FloydResult floydWarshall() const {
        const int vertexCount = static_cast<int>(adjacencyMatrix.size());
        FloydResult result;
        result.distances = adjacencyMatrix;
        result.next.assign(vertexCount, vector<int>(vertexCount, -1));

        // next[i][j] 表示从 i 前往 j 的最短路径上的下一站。
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                if (result.distances[i][j] != INF) {
                    result.next[i][j] = j;
                }
            }
        }

        for (int middle = 0; middle < vertexCount; ++middle) {
            for (int from = 0; from < vertexCount; ++from) {
                if (result.distances[from][middle] == INF) {
                    continue;
                }

                for (int to = 0; to < vertexCount; ++to) {
                    if (result.distances[middle][to] == INF) {
                        continue;
                    }

                    const Distance throughMiddle =
                        result.distances[from][middle] + result.distances[middle][to];
                    if (throughMiddle < result.distances[from][to]) {
                        result.distances[from][to] = throughMiddle;
                        result.next[from][to] = result.next[from][middle];
                    }
                }
            }
        }

        // 若 dist[i][i] < 0，则顶点 i 位于某个负权环上。
        for (int i = 0; i < vertexCount; ++i) {
            if (result.distances[i][i] < 0) {
                result.hasNegativeCycle = true;
                break;
            }
        }

        return result;
    }

    // 根据 Floyd-Warshall 生成的 next 矩阵还原 from 到 to 的最短路径。
    vector<int> reconstructPath(int from, int to, const FloydResult& result) const {
        checkVertex(from);
        checkVertex(to);
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

    static void printDistances(const FloydResult& result) {
        cout << "任意两点之间的最短距离:" << endl;
        for (const auto& row : result.distances) {
            for (Distance distance : row) {
                if (distance == INF) {
                    cout << "INF\t";
                } else {
                    cout << distance << '\t';
                }
            }
            cout << endl;
        }
    }
};

int main() {
    // 构造一个包含 5 个顶点（0 到 4）的有向图。
    Graph graph(5);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 8);
    graph.addEdge(0, 4, -4);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 7);
    graph.addEdge(2, 1, 4);
    graph.addEdge(3, 0, 2);
    graph.addEdge(3, 2, -5);
    graph.addEdge(4, 3, 6);

    const Graph::FloydResult result = graph.floydWarshall();
    if (result.hasNegativeCycle) {
        cout << "图中存在负权环，无法得到有限的最短路径。" << endl;
        return 0;
    }

    Graph::printDistances(result);

    const int start = 0;
    const int destination = 2;
    const vector<int> path = graph.reconstructPath(start, destination, result);
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
    cout << endl;

    return 0;
}
