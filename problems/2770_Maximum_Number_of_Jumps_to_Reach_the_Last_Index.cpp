// 2770. Maximum Number of Jumps to Reach the Last Index
// Created automatically
// Created at 2026-05-12 12:06:12

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> dp(n, -1);
        dp[0] = 0;

        long long limit = target;
        for (int i = 0; i < n; i++) {
            if (dp[i] == -1) {
                continue;
            }

            for (int j = i + 1; j < n; j++) {
                long long diff = static_cast<long long>(nums[j]) - nums[i];
                if (-limit <= diff && diff <= limit) {
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
        }

        return dp[n - 1];
    }
};
