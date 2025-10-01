//
// Created by user on 2025/10/1.
//
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m+1, vector(n+1, 0));

        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }

        for (int i = 0; i <= n; ++i) {
            dp[0][i] = i;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(word1[i]==word2[j]){
                    dp[i+1][j+1] = min(dp[i][j], min(dp[i+1][j], dp[i][j+1])+1);
                } else{
                    dp[i+1][j+1] = min(dp[i][j], min(dp[i+1][j], dp[i][j+1]))+1;
                }
            }
        }
        return dp[m][n];
    }
};