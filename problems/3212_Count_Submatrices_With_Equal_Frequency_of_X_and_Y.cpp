// 3212. Count Submatrices With Equal Frequency of X and Y
// Created automatically
// Created at 2026-03-19 10:34:12

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();

        vector<vector<int>> prefX(n+1, vector<int>(m+1, 0));
        vector<vector<int>> prefY(n+1, vector<int>(m+1, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                prefX[i+1][j+1] = prefX[i][j+1] + prefX[i+1][j] - prefX[i][j] + (grid[i][j] == 'X');
                prefY[i+1][j+1] = prefY[i][j+1] + prefY[i+1][j] - prefY[i][j] + (grid[i][j] == 'Y');
            }
        }

        long long ans = 0;
        // Any submatrix that contains cell (0,0) must have top-left at (0,0),
        // so we only need to consider rectangles (0,0) .. (i,j).
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cx = prefX[i+1][j+1];
                int cy = prefY[i+1][j+1];
                if (cx > 0 && cx == cy) ++ans;
            }
        }

        return (int)ans;
    }
};