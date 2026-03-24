// 2906. Construct Product Matrix
// Created automatically
// Created at 2026-03-24 13:44:35

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        const int MOD = 12345;
        int total = n * m;
        vector<int> prefix(total, 1), suffix(total, 1);
        vector<vector<int>> productMatrix(n, vector<int>(m));

        for (int idx = 1; idx < total; idx++) {
            int prev = idx - 1;
            prefix[idx] = (1LL * prefix[prev] * grid[prev / m][prev % m]) % MOD;
        }

        for (int idx = total - 2; idx >= 0; idx--) {
            int next = idx + 1;
            suffix[idx] = (1LL * suffix[next] * grid[next / m][next % m]) % MOD;
        }

        for (int idx = 0; idx < total; idx++) {
            productMatrix[idx / m][idx % m] = (1LL * prefix[idx] * suffix[idx]) % MOD;
        }

        return productMatrix;
    }
};
