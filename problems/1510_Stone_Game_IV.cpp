// 1510. Stone Game IV
// Created automatically
// Created at 2026-08-10 21:27:10

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        for (int stones = 1; stones <= n; ++stones) {
            for (int removed = 1; removed * removed <= stones; ++removed) {
                if (!dp[stones - removed * removed]) {
                    dp[stones] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
