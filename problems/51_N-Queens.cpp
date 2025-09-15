//
// Created by user on 2025/9/15.
//
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
    int size = 0;
    vector<string> grid;
    vector<vector<string>> solution;

    bool canDeploy(int row, int col) {
        for (int i = 0; i < row; ++i) {
            if (grid[i][col] == 'Q') return false;
        }
        for (int i=row-1, j=col-1; i>=0 && j>=0; --i, --j) {
            if (grid[i][j] == 'Q') return false;
        }
        for (int i=row-1, j=col+1; i>=0 && j<size; --i, ++j) {
            if (grid[i][j] == 'Q') return false;
        }
        return true;
    }

    void _solveNQueens(int row) {
        if (row == size) {
            solution.push_back(grid);
            return;
        }
        for (int col = 0; col < size; ++col) {
            if (canDeploy(row, col)) {
                grid[row][col] = 'Q';
                _solveNQueens(row + 1);
                grid[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        size = n;
        string stars(n, '.');
        grid = vector<string>(n, stars);
        _solveNQueens(0);
        return solution;
    }
};
