// 931. Minimum Falling Path Sum
// Created automatically
// Created at 2026-03-06 19:37:54
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        if (n == 1) return *min_element(matrix[0].begin(), matrix[0].end());

        const int INF = numeric_limits<int>::max() / 4;
        vector<int> dp = matrix[0];

        for (int i = 1; i < n; ++i) {
            vector<int> cur(n, INF);
            for (int j = 0; j < n; ++j) {
                int best = dp[j];
                if (j > 0) best = min(best, dp[j-1]);
                if (j + 1 < n) best = min(best, dp[j+1]);
                cur[j] = matrix[i][j] + best;
            }
            dp.swap(cur);
        }

        return *min_element(dp.begin(), dp.end());
    }
};