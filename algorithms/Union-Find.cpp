//
// Created by user on 2025/9/8.
//
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent; // 存储每个元素的父节点
    vector<int> rank;   // 存储每个集合的秩（近似树高度）
    int count;          // 连通分量数量

public:
    // 构造函数，初始化n个元素的并查集
    UnionFind(int n) : count(n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // 初始时每个元素自成一个集合
        }
    }

    // 查找元素x的根节点，带路径压缩优化
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    // 合并元素x和y所在的集合，按秩合并优化
    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return; // 已经在同一集合中

        // 按秩合并：将秩较小的树合并到秩较大的树
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++; // 秩相同时，合并后秩增加
        }
        count--; // 连通分量数量减1
    }

    // 判断元素x和y是否属于同一集合
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // 返回连通分量的数量
    int getCount() {
        return count;
    }
};

int main() {
    // 创建一个包含10个元素的并查集 (0-9)
    UnionFind uf(10);

    // 执行一些合并操作
    uf.unionSet(1, 2);
    uf.unionSet(2, 5);
    uf.unionSet(5, 6);
    uf.unionSet(3, 4);
    uf.unionSet(4, 7);

    // 测试连通性
    cout << "1和6是否连通: " << (uf.connected(1, 6) ? "是" : "否") << endl;
    cout << "1和3是否连通: " << (uf.connected(1, 3) ? "是" : "否") << endl;
    cout << "3和7是否连通: " << (uf.connected(3, 7) ? "是" : "否") << endl;

    // 输出连通分量数量
    cout << "连通分量数量: " << uf.getCount() << endl;

    // 合并更多集合
    uf.unionSet(6, 7);

    cout << "合并后1和3是否连通: " << (uf.connected(1, 3) ? "是" : "否") << endl;
    cout << "合并后连通分量数量: " << uf.getCount() << endl;

    return 0;
}
