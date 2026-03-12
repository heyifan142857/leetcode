// 3600. Maximize Spanning Tree Stability with Upgrades
// Created automatically
// Created at 2026-03-12 10:59:42
#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool cannotConnect = false;
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
        int comps;

    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            comps = n;
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int i) {
            if (parent[i] != i) {
                parent[i] = find(parent[i]);
            }
            return parent[i];
        }

        bool unite(int i, int j) {
            int rootI = find(i);
            int rootJ = find(j);

            if (rootI == rootJ) return false;

            if (rank[rootI] < rank[rootJ]) {
                parent[rootI] = rootJ;
            } else if (rank[rootI] > rank[rootJ]) {
                parent[rootJ] = rootI;
            } else {
                parent[rootJ] = rootI;
                rank[rootI]++;
            }
            comps--;
            return true;
        }

        int components() const { return comps; }
    };

    vector<vector<int>> kruskal(int n, vector<vector<int>>& edges) {
        vector<vector<int>> mst;
        
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        UnionFind uf(n);

        for (const auto& edge : edges) {
            if (edge.size() < 4) continue;
            
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            if (edge[3] == 1) {
                if (uf.find(u) == uf.find(v)) {
                    cannotConnect = true;
                    break;
                }
                mst.push_back(edge);
                uf.unite(u, v);
                continue;
            }

            if (uf.find(u) != uf.find(v)) {
                mst.push_back(edge);
                uf.unite(u, v);
                if (mst.size() == n - 1) break;
            }
        }

        return mst;
    }
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // Preliminary checks: must-edges should not form a cycle, and graph must be connected
        UnionFind ufCheck(n);
        for (const auto& e : edges) {
            if (e.size() < 4) continue;
            if (e[3] == 1) {
                if (!ufCheck.unite(e[0], e[1])) {
                    return -1; // must-edges form a cycle
                }
            }
        }

        UnionFind ufAll(n);
        for (const auto& e : edges) {
            if (e.size() < 4) continue;
            ufAll.unite(e[0], e[1]);
        }
        if (ufAll.components() != 1) return -1; // graph not connected at all

        long long maxS = 0;
        for (const auto& e : edges) if (e.size() >= 4) maxS = max(maxS, (long long)e[2]);

        long long lo = 0, hi = maxS * 2; // possible stability range

        auto feasible = [&](long long x)->bool {
            // all must edges must have s >= x
            UnionFind uf(n);
            for (const auto& e : edges) {
                if (e.size() < 4) continue;
                if (e[3] == 1) {
                    if (e[2] < x) return false;
                    uf.unite(e[0], e[1]);
                }
            }

            // use all free edges (non-must with s >= x)
            for (const auto& e : edges) {
                if (e.size() < 4) continue;
                if (e[3] == 1) continue;
                if ((long long)e[2] >= x) uf.unite(e[0], e[1]);
            }

            if (uf.components() == 1) return true;

            // collect upgradeable edges (non-must, s < x but 2*s >= x)
            vector<pair<int,int>> up;
            up.reserve(edges.size());
            for (const auto& e : edges) {
                if (e.size() < 4) continue;
                if (e[3] == 1) continue;
                long long s = e[2];
                if (s < x && s * 2 >= x) up.emplace_back(e[0], e[1]);
            }

            int used = 0;
            for (const auto &p : up) {
                if (uf.unite(p.first, p.second)) {
                    used++;
                    if (uf.components() == 1) break;
                    if (used > k) return false;
                }
            }

            return uf.components() == 1 && used <= k;
        };

        long long ans = 0;
        while (lo <= hi) {
            long long mid = (lo + hi) >> 1;
            if (feasible(mid)) {
                ans = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }

        return (int)ans;
    }
};