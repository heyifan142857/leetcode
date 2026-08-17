// 1140. Stone Game II
// Created automatically
// Created at 2026-08-09 20:41:22

#include <algorithm>
#include <bits/stdc++.h>
#include <functional>
#include <vector>
using namespace std;

class Solution {
public:
    int stoneGameII(vector<int> &piles) {
        const int n = piles.size();
        vector<int> suffix(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        function<int(int, int)> dfs = [&](int i, int m) -> int {
            if (i + 2 * m >= n) {
                return suffix[i];
            }

            int &result = memo[i][m];
            if (result != -1) {
                return result;
            }

            result = 0;
            for (int x = 1; x <= 2 * m; ++x) {
                result = max(result, suffix[i] - dfs(i + x, max(m, x)));
            }
            return result;
        };

        return dfs(0, 1);
    }
};
