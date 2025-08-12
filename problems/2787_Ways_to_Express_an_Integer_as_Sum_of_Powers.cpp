//
// Created by user on 2025/8/12.
//

#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Solution {
    const int MOD = 1000000007;
public:
    int numberOfWays(int n, int x) {
        vector<int> powers;
        for (int i = 1; ; i++) {
            long long val = pow(i, x);
            if (val > n) break;
            powers.push_back((int)val);
        }

        vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (int p : powers) {
            for (int sum = n; sum >= p; sum--) {
                dp[sum] = (dp[sum] + dp[sum - p]) % MOD;
            }
        }

        return dp[n];

    }
};