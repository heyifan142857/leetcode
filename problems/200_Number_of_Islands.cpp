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

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        UnionFind uf(m * n);
        int cnt0 = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '0'){
                    cnt0++;
                }else{
                    int ufNum = i*n+j;
                    if(i>0 && grid[i-1][j] == '1'){
                        int postUfNum = (i-1)*n+j;
                        uf.unionSet(ufNum, postUfNum);
                    }
                    if(j>0 && grid[i][j-1] == '1'){
                        int postUfNum = i*n+j-1;
                        uf.unionSet(ufNum, postUfNum);
                    }
                }
            }
        }
        return (uf.getCount()-cnt0);
    }
};