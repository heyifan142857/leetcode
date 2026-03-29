// Weekly Contest 495 - Q4
// Created automatically
// Created at 2026-03-29 14:08:38

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        int senqavilor = n;
        vector<int> parent(senqavilor), rankv(senqavilor, 0), xorToParent(senqavilor, 0);
        iota(parent.begin(), parent.end(), 0);

        function<pair<int, int>(int)> find = [&](int x) -> pair<int, int> {
            if (parent[x] == x) {
                return {x, 0};
            }
            auto [root, xr] = find(parent[x]);
            xorToParent[x] ^= xr;
            parent[x] = root;
            return {parent[x], xorToParent[x]};
        };

        auto unite = [&](int u, int v, int w) -> bool {
            auto [ru, xu] = find(u);
            auto [rv, xv] = find(v);

            if (ru == rv) {
                return (xu ^ xv) == w;
            }

            if (rankv[ru] < rankv[rv]) {
                swap(ru, rv);
                swap(xu, xv);
            }

            parent[rv] = ru;
            xorToParent[rv] = xu ^ xv ^ w;
            if (rankv[ru] == rankv[rv]) {
                ++rankv[ru];
            }
            return true;
        };

        int added = 0;
        for (const auto& edge : edges) {
            if (unite(edge[0], edge[1], edge[2])) {
                ++added;
            }
        }
        return added;
    }
};
