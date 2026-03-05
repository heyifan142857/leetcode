// 289. Game of Life
// Created automatically
// Created at 2026-03-05 14:07:31

#include <vector>
using namespace std;

class Solution {
    int numberOfLiveNeighbors(const vector<vector<int>>& board, int row, int col) {
        int count = 0;
        int rows = board.size();
        int cols = board[0].size();
        
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue; // Skip the cell itself
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    count += board[newRow][newCol];
                }
            }
        }
        
        return count;
    }
public:
    void gameOfLife(vector<vector<int>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        vector<vector<int>> newBoard(rows, vector<int>(cols, 0));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int liveNeighbors = numberOfLiveNeighbors(board, i, j);
                if (board[i][j] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        newBoard[i][j] = 0;
                    } else {
                        newBoard[i][j] = 1;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        newBoard[i][j] = 1;
                    }
                }
            }
        }

        board = newBoard;
    }
};