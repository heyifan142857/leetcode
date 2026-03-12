#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // 用于 std::iota

using namespace std;

// 定义边的结构体
struct Edge {
    int u, v, weight;
    
    // 重载 < 运算符，以便使用 std::sort 进行排序
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 并查集 (Union-Find) 类
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank; // 用于按秩合并，保持树平衡

public:
    // 初始化并查集，n 为节点数量 (假设节点编号从 0 到 n-1)
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // 初始时，每个节点的父节点是自己
        iota(parent.begin(), parent.end(), 0);
    }

    // 查找根节点 (带路径压缩优化)
    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]); // 递归压缩路径
        }
        return parent[i];
    }

    // 合并两个集合 (带按秩合并优化)
    void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);

        if (rootI != rootJ) {
            // 将秩小的树挂到秩大的树下
            if (rank[rootI] < rank[rootJ]) {
                parent[rootI] = rootJ;
            } else if (rank[rootI] > rank[rootJ]) {
                parent[rootJ] = rootI;
            } else {
                parent[rootJ] = rootI;
                rank[rootI]++;
            }
        }
    }
};

// Kruskal 算法主函数
// n: 顶点数, edges: 所有边的列表
// 返回: 最小生成树的边列表
vector<Edge> kruskal(int n, vector<Edge>& edges) {
    vector<Edge> mst;
    
    // 1. 将所有边按权重从小到大排序
    sort(edges.begin(), edges.end());

    // 2. 初始化并查集
    UnionFind uf(n);

    // 3. 遍历排序后的边
    for (const auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;

        // 如果两个顶点不在同一个集合中 (即加入该边不会形成环)
        if (uf.find(u) != uf.find(v)) {
            mst.push_back(edge); // 加入 MST
            uf.unite(u, v);      // 合并集合
            
            // 优化：如果已经选够了 n-1 条边，可以提前结束
            if (mst.size() == n - 1) {
                break;
            }
        }
    }

    return mst;
}

int main() {
    // --- 测试数据 ---
    // 假设我们有 5 个顶点 (0 到 4)
    int numVertices = 5;
    
    // 定义边: {u, v, weight}
    // 图结构示例:
    // 0 --(1)-- 1
    // | \     / |
    // 4  4   2  3
    // |   \ /   |
    // 3 --(5)-- 2
    // (注意：这里手动构造了一个简单的连通图)
    vector<Edge> edges = {
        {0, 1, 1},
        {0, 3, 4},
        {0, 4, 4},
        {1, 2, 3},
        {1, 3, 2},
        {2, 3, 5},
        {3, 4, 6} 
    };

    cout << "运行 Kruskal 算法..." << endl;

    vector<Edge> result = kruskal(numVertices, edges);

    // 输出结果
    int totalWeight = 0;
    cout << "最小生成树包含的边:" << endl;
    cout << "顶点 U -- 顶点 V : 权重" << endl;
    cout << "------------------------" << endl;
    
    if (result.size() != numVertices - 1) {
        cout << "警告: 图不连通，无法生成完整的最小生成树!" << endl;
    } else {
        for (const auto& edge : result) {
            cout << "   " << edge.u << "  --  " << edge.v 
                 << " : " << edge.weight << endl;
            totalWeight += edge.weight;
        }
        cout << "------------------------" << endl;
        cout << "最小生成树总权重: " << totalWeight << endl;
    }

    return 0;
}