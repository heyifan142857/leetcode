//
// Created by azote on 1/19/26.
//
#include <vector>
using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxSize = min(m, n);
        
        // Try all possible sizes from largest to smallest
        for (int k = maxSize; k >= 1; k--) {
            // Try all possible top-left positions for a k x k square
            for (int i = 0; i <= m - k; i++) {
                for (int j = 0; j <= n - k; j++) {
                    if (isMagicSquare(grid, i, j, k)) {
                        return k;
                    }
                }
            }
        }
        
        return 1; // At least 1x1 is always a magic square
    }
    
private:
    bool isMagicSquare(vector<vector<int>>& grid, int row, int col, int k) {
        // Calculate the target sum (use first row as reference)
        int targetSum = 0;
        for (int j = col; j < col + k; j++) {
            targetSum += grid[row][j];
        }
        
        // Check all rows
        for (int i = row; i < row + k; i++) {
            int rowSum = 0;
            for (int j = col; j < col + k; j++) {
                rowSum += grid[i][j];
            }
            if (rowSum != targetSum) {
                return false;
            }
        }
        
        // Check all columns
        for (int j = col; j < col + k; j++) {
            int colSum = 0;
            for (int i = row; i < row + k; i++) {
                colSum += grid[i][j];
            }
            if (colSum != targetSum) {
                return false;
            }
        }
        
        // Check main diagonal (top-left to bottom-right)
        int diag1Sum = 0;
        for (int d = 0; d < k; d++) {
            diag1Sum += grid[row + d][col + d];
        }
        if (diag1Sum != targetSum) {
            return false;
        }
        
        // Check anti-diagonal (top-right to bottom-left)
        int diag2Sum = 0;
        for (int d = 0; d < k; d++) {
            diag2Sum += grid[row + d][col + k - 1 - d];
        }
        if (diag2Sum != targetSum) {
            return false;
        }
        
        return true;
    }
};