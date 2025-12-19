#include <vector>
#include <string>
using namespace std;

class Solution {
    public:
        int minDeletionSize(vector<string>& strs) {
            int n = strs.size();
            if (n == 0) return 0;
            
            int m = strs[0].length();
            int deletions = 0;
            
            // Check each column
            for (int col = 0; col < m; col++) {
                // Check if this column is sorted (non-decreasing)
                for (int row = 1; row < n; row++) {
                    if (strs[row][col] < strs[row-1][col]) {
                        deletions++;
                        break;  // Column is unsorted, move to next column
                    }
                }
            }
            
            return deletions;
        }
    };