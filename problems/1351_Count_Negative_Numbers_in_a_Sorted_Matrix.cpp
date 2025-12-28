#include <vector>
using namespace std;

class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        
        // Start from top-right corner
        int row = 0;
        int col = n - 1;
        
        while (row < m && col >= 0) {
            if (grid[row][col] < 0) {
                // All elements below in this column are negative
                count += (m - row);
                col--; // Move left
            } else {
                row++; // Move down
            }
        }
        
        return count;
    }
};