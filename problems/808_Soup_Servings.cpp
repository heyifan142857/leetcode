//
// Created by user on 2025/8/8.
//

#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double soupServings(int n) {
        if (n > 4800) return 1.0;
        int m = (n + 24) / 25;

        vector<vector<double>> dp(m + 1, vector<double>(m + 1, -1.0));

        function<double(int,int)> dfs = [&](int a, int b) -> double {
            if (a <= 0 && b <= 0) return 0.5;
            if (a <= 0) return 1.0;
            if (b <= 0) return 0.0;
            if (dp[a][b] >= 0.0) return dp[a][b];

            double ans = 0.0;
            ans += dfs(a - 4, b)     * 0.25;
            ans += dfs(a - 3, b - 1) * 0.25;
            ans += dfs(a - 2, b - 2) * 0.25;
            ans += dfs(a - 1, b - 3) * 0.25;

            return dp[a][b] = ans;
        };

        return dfs(m, m);
    }
};