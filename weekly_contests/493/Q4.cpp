// Weekly Contest 493 - Q4
// Created automatically
// Created at 2026-03-21 16:21:44

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct DSU {
        vector<int> parent, sz;

        explicit DSU(int n) : parent(n), sz(n, 1) {
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x) {
            if (parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }

        void unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    };

    int maxActivated(vector<vector<int>>& points) {
        const int n = points.size();
        DSU dsu(n);
        unordered_map<int, int> firstX, firstY;

        for (int i = 0; i < n; ++i) {
            int x = points[i][0];
            int y = points[i][1];

            if (auto it = firstX.find(x); it != firstX.end()) {
                dsu.unite(i, it->second);
            } else {
                firstX[x] = i;
            }

            if (auto it = firstY.find(y); it != firstY.end()) {
                dsu.unite(i, it->second);
            } else {
                firstY[y] = i;
            }
        }

        unordered_map<int, int> compSize;
        for (int i = 0; i < n; ++i) {
            ++compSize[dsu.find(i)];
        }

        int best = 0, secondBest = 0;
        for (const auto& [root, size] : compSize) {
            if (size >= best) {
                secondBest = best;
                best = size;
            } else if (size > secondBest) {
                secondBest = size;
            }
        }

        return 1 + best + secondBest;
    }
};
