// Prim 算法从一个顶点开始，每次选择连接生成树与未访问顶点的最小权边，
// 直到构造出图的最小生成树。本示例使用邻接表和最小堆实现。

#include <functional>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// 最小生成树中的边
struct MstEdge {
    int u;
    int v;
    int weight;
};

struct PrimResult {
    vector<MstEdge> edges;
    long long totalWeight = 0;
    bool isConnected = false;
};

class Graph {
private:
    // adjacencyList[u] 中的元素为 {v, weight}
    vector<vector<pair<int, int>>> adjacencyList;

    void checkVertex(int vertex) const {
        if (vertex < 0 || vertex >= static_cast<int>(adjacencyList.size())) {
            throw out_of_range("顶点编号超出范围");
        }
    }

public:
    explicit Graph(int vertexCount) {
        if (vertexCount < 0) {
            throw invalid_argument("顶点数不能为负数");
        }
        adjacencyList.resize(vertexCount);
    }

    // Prim 算法适用于无向图，因此同时添加两个方向的边。
    void addEdge(int u, int v, int weight) {
        checkVertex(u);
        checkVertex(v);
        adjacencyList[u].push_back({v, weight});
        adjacencyList[v].push_back({u, weight});
    }

    // 从 start 开始构造最小生成树。
    // 时间复杂度为 O((V + E) log E)，空间复杂度为 O(V + E)。
    PrimResult prim(int start = 0) const {
        PrimResult result;
        const int vertexCount = static_cast<int>(adjacencyList.size());

        // 空图不需要选择任何边，视为已完成。
        if (vertexCount == 0) {
            result.isConnected = true;
            return result;
        }
        checkVertex(start);

        vector<bool> visited(vertexCount, false);

        // 堆中元素依次为 {边权, 起点, 终点}；priority_queue 配合 greater
        // 后会优先弹出权重最小的候选边。
        using CandidateEdge = tuple<int, int, int>;
        priority_queue<CandidateEdge, vector<CandidateEdge>, greater<CandidateEdge>> minHeap;
        minHeap.push({0, -1, start});

        int visitedCount = 0;
        while (!minHeap.empty() && visitedCount < vertexCount) {
            const auto [weight, from, to] = minHeap.top();
            minHeap.pop();

            // 一个顶点可能由多条候选边到达，只处理第一次弹出的最小权边。
            if (visited[to]) {
                continue;
            }

            visited[to] = true;
            ++visitedCount;

            // 起始顶点没有父边，不加入结果。
            if (from != -1) {
                result.edges.push_back({from, to, weight});
                result.totalWeight += weight;
            }

            for (const auto& [next, edgeWeight] : adjacencyList[to]) {
                if (!visited[next]) {
                    minHeap.push({edgeWeight, to, next});
                }
            }
        }

        result.isConnected = (visitedCount == vertexCount);
        return result;
    }
};

int main() {
    // 构造一个包含 5 个顶点（0 到 4）的无向连通图。
    Graph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 3, 4);
    graph.addEdge(0, 4, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 5);
    graph.addEdge(3, 4, 6);

    cout << "运行 Prim 算法..." << endl;
    const PrimResult result = graph.prim(0);

    if (!result.isConnected) {
        cout << "警告: 图不连通，无法生成完整的最小生成树!" << endl;
        return 0;
    }

    cout << "最小生成树包含的边:" << endl;
    cout << "顶点 U -- 顶点 V : 权重" << endl;
    cout << "------------------------" << endl;
    for (const MstEdge& edge : result.edges) {
        cout << "   " << edge.u << "  --  " << edge.v
             << " : " << edge.weight << endl;
    }
    cout << "------------------------" << endl;
    cout << "最小生成树总权重: " << result.totalWeight << endl;

    return 0;
}
