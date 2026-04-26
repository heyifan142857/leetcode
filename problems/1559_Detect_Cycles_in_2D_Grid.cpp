// 1559. Detect Cycles in 2D Grid
// Created automatically
// Created at 2026-04-26 10:30:33

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<int> directions = {1, 0, -1, 0, 1};

        function<bool(int, int, int, int, char)> dfs = [&](int row, int col, int parentRow, int parentCol, char target) {
            visited[row][col] = true;

            for (int k = 0; k < 4; ++k) {
                int nextRow = row + directions[k];
                int nextCol = col + directions[k + 1];

                if (nextRow < 0 || nextRow >= m || nextCol < 0 || nextCol >= n) {
                    continue;
                }
                if (grid[nextRow][nextCol] != target) {
                    continue;
                }
                if (nextRow == parentRow && nextCol == parentCol) {
                    continue;
                }
                if (visited[nextRow][nextCol]) {
                    return true;
                }
                if (dfs(nextRow, nextCol, row, col, target)) {
                    return true;
                }
            }

            return false;
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j] && dfs(i, j, -1, -1, grid[i][j])) {
                    return true;
                }
            }
        }

        return false;
    }
};
