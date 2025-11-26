//
// Created by azote on 11/26/25.
//
#include <vector>
using namespace std;

class Solution {
public:
    int numberOfPaths(vector<vector<int> > &grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<vector<long long> > > dp(m, vector<vector<long long> >(n, vector<long long>(k, 0)));
        dp[m - 1][n - 1][grid[m - 1][n - 1] % k] = 1;

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                for (int l = 0; l < k; ++l) {
                    int nl = (l + grid[i][j]) % k;
                    long long num = dp[i][j][nl];
                    num += ((i < (m - 1)) ? dp[i + 1][j][l] : 0);
                    num += ((j < (n - 1)) ? dp[i][j + 1][l] : 0);
                    num %= 1000000007;
                    dp[i][j][nl] = num;
                }
            }
        }
        return dp[0][0][0] % 1000000007;
    }
};
