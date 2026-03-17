// 1727. Largest Submatrix With Rearrangements
// Created automatically
// Created at 2026-03-17 15:19:43

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) heights[j] += 1;
                else heights[j] = 0;
            }
            vector<int> sorted = heights;
            sort(sorted.begin(), sorted.end(), greater<int>());
            for (int k = 0; k < n; ++k) {
                if (sorted[k] == 0) break;
                ans = max(ans, sorted[k] * (k + 1));
            }
        }
        return ans;
    }
};