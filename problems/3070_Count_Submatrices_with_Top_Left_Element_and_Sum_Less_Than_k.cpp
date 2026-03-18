// 3070. Count Submatrices with Top-Left Element and Sum Less Than k
// Created automatically
// Created at 2026-03-18 10:01:05

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();

        // Compute 2D prefix sums where ps[i+1][j+1] = sum of grid[0..i][0..j]
        vector<vector<long long>> ps(m+1, vector<long long>(n+1, 0));
        for (int i = 0; i < m; ++i) {
            long long rowSum = 0;
            for (int j = 0; j < n; ++j) {
                rowSum += grid[i][j];
                ps[i+1][j+1] = ps[i][j+1] + rowSum;
            }
        }

        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                long long sum00toIJ = ps[i+1][j+1];
                if (sum00toIJ <= (long long)k) ++count;
            }
        }
        return count;

    }
};