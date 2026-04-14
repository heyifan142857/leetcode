// 2463. Minimum Total Distance Traveled
// Created automatically
// Created at 2026-04-14 15:30:08

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        const int robotCount = static_cast<int>(robot.size());
        const int factoryCount = static_cast<int>(factory.size());
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(factoryCount + 1, vector<long long>(robotCount + 1, INF));
        dp[0][0] = 0;

        for (int i = 1; i <= factoryCount; ++i) {
            dp[i][0] = 0;

            const long long position = factory[i - 1][0];
            const int limit = factory[i - 1][1];

            for (int j = 1; j <= robotCount; ++j) {
                dp[i][j] = dp[i - 1][j];

                long long cost = 0;
                for (int used = 1; used <= limit && used <= j; ++used) {
                    cost += llabs(static_cast<long long>(robot[j - used]) - position);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - used] + cost);
                }
            }
        }

        return dp[factoryCount][robotCount];
    }
};
