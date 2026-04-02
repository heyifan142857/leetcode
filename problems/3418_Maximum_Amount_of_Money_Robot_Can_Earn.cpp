// 3418. Maximum Amount of Money Robot Can Earn
// Created automatically
// Created at 2026-04-02 10:18:21

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        if (m == 0) return 0;
        int n = coins[0].size();
        const long long NEG = LLONG_MIN / 4;
        vector<vector<array<long long,3>>> dp(m, vector<array<long long,3>>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                dp[i][j].fill(NEG);

        // initialize (0,0)
        int v0 = coins[0][0];
        if (v0 >= 0) dp[0][0][0] = v0;
        else {
            dp[0][0][0] = v0; // without neutralizing
            dp[0][0][1] = 0;  // neutralize this robber
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                int val = coins[i][j];

                // from top
                if (i > 0) {
                    for (int k = 0; k <= 2; ++k) {
                        long long prev = dp[i-1][j][k];
                        if (prev == NEG) continue;
                        if (val >= 0) {
                            dp[i][j][k] = max(dp[i][j][k], prev + val);
                        } else {
                            // not neutralize
                            dp[i][j][k] = max(dp[i][j][k], prev + val);
                            // neutralize here if possible
                            if (k + 1 <= 2) dp[i][j][k+1] = max(dp[i][j][k+1], prev + 0);
                        }
                    }
                }

                // from left
                if (j > 0) {
                    for (int k = 0; k <= 2; ++k) {
                        long long prev = dp[i][j-1][k];
                        if (prev == NEG) continue;
                        if (val >= 0) {
                            dp[i][j][k] = max(dp[i][j][k], prev + val);
                        } else {
                            dp[i][j][k] = max(dp[i][j][k], prev + val);
                            if (k + 1 <= 2) dp[i][j][k+1] = max(dp[i][j][k+1], prev + 0);
                        }
                    }
                }
            }
        }

        long long ans = NEG;
        for (int k = 0; k <= 2; ++k) ans = max(ans, dp[m-1][n-1][k]);
        return (int)ans;
    }
};