//
// Created by user on 2025/9/11.
//
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 表示图中的边
struct Edge {
    int src, dest, weight;
};

// 表示图
class Graph {
public:
    int V, E; // 顶点数和边数
    vector<Edge> edges; // 边的列表

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    // 添加边
    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }

    // Bellman-Ford 算法实现
    void bellmanFord(int src) {
        // 初始化距离数组
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // 松弛所有边 V-1 次
        for (int i = 1; i <= V - 1; i++) {
            for (int j = 0; j < E; j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // 检查是否存在负权环
        for (int i = 0; i < E; i++) {
            int u = edges[i].src;
            int v = edges[i].dest;
            int weight = edges[i].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "图中存在负权环!" << endl;
                return;
            }
        }

        // 打印结果
        cout << "顶点\t距离源点的最短距离" << endl;
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                cout << i << "\t不可达" << endl;
            } else {
                cout << i << "\t" << dist[i] << endl;
            }
        }
    }
};

int main() {
    // 创建图
    int V = 5; // 顶点数
    int E = 8; // 边数
    Graph graph(V, E);

    // 添加边
    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    // 从顶点 0 开始执行 Bellman-Ford 算法
    graph.bellmanFord(0);

    return 0;
}
