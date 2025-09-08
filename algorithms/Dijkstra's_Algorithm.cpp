//
// Created by user on 2025/9/8.
//
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// 定义图的边
struct Edge {
    int dest;   // 目标节点
    int weight; // 边的权重
};

// 定义图的节点
struct Node {
    int id;             // 节点ID
    int dist;           // 从起点到该节点的距离
    vector<Edge> edges; // 从该节点出发的边
};

// 用于优先队列的比较函数
struct CompareNode {
    bool operator()(const Node* a, const Node* b) {
        return a->dist > b->dist;
    }
};

class Graph {
private:
    vector<Node> nodes; // 图中的所有节点

public:
    Graph(int n) {
        nodes.resize(n);
        for (int i = 0; i < n; i++) {
            nodes[i].id = i;
            nodes[i].dist = INT_MAX;
        }
    }

    // 添加边
    void addEdge(int src, int dest, int weight) {
        Edge edge = {dest, weight};
        nodes[src].edges.push_back(edge);
    }

    // Dijkstra算法实现
    void dijkstra(int start) {
        // 初始化起点
        nodes[start].dist = 0;

        // 使用优先队列（最小堆）
        priority_queue<Node*, vector<Node*>, CompareNode> pq;
        pq.push(&nodes[start]);

        while (!pq.empty()) {
            Node* current = pq.top();
            pq.pop();

            // 遍历当前节点的所有邻接节点
            for (const Edge& edge : current->edges) {
                int newDist = current->dist + edge.weight;

                // 如果找到更短的路径，则更新
                if (newDist < nodes[edge.dest].dist) {
                    nodes[edge.dest].dist = newDist;
                    pq.push(&nodes[edge.dest]);
                }
            }
        }
    }

    // 打印结果
    void printDistances(int start) {
        cout << "从节点 " << start << " 到各节点的最短距离:" << endl;
        for (const Node& node : nodes) {
            if (node.dist == INT_MAX) {
                cout << "到节点 " << node.id << " 的距离: 不可达" << endl;
            } else {
                cout << "到节点 " << node.id << " 的距离: " << node.dist << endl;
            }
        }
    }
};

int main() {
    // 创建一个有6个节点的图
    Graph graph(6);

    // 添加边
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    // 从节点0开始执行Dijkstra算法
    graph.dijkstra(0);

    // 打印结果
    graph.printDistances(0);

    return 0;
}