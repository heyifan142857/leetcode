// 3643. Flip Square Submatrix Vertically
// Created automatically
// Created at 2026-03-21 16:00:05

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        for (int top = 0; top < k / 2; ++top) {
            int bottom = k - 1 - top;
            for (int col = 0; col < k; ++col) {
                swap(grid[x + top][y + col], grid[x + bottom][y + col]);
            }
        }
        return grid;
    }
};
