//
// Created by user on 2025/8/31.
//

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) {
                                return true;
                            }
                            board[i][j] = '.'; // 回溯
                        }
                    }
                    return false; // 所有数字都试过了，无解
                }
            }
        }
        return true; // 所有单元格都已填满
    }

    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // 检查行
            if (board[row][i] == c) return false;
            // 检查列
            if (board[i][col] == c) return false;
            // 检查3x3宫格
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }
};