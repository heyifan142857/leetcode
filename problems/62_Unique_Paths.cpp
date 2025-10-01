//
// Created by user on 2025/10/1.
//
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector(n, 0));
        dp[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(i<m-1){
                    dp[i+1][j] += dp[i][j];
                }
                if(j<n-1){
                    dp[i][j+1] += dp[i][j];
                }
            }
        }
        return dp[m-1][n-1];
    }
};