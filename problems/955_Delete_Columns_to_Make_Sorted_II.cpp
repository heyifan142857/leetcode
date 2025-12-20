#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) return 0;
        int m = strs[0].length();
        
        // Track which adjacent pairs are already sorted (distinguished)
        vector<bool> sorted(n - 1, false);
        int deletions = 0;
        
        // Process each column from left to right
        for (int col = 0; col < m; col++) {
            bool mustDelete = false;
            
            // Check if keeping this column would violate lexicographic order
            for (int i = 0; i < n - 1; i++) {
                // Only check pairs that are not yet distinguished
                if (!sorted[i]) {
                    if (strs[i][col] > strs[i + 1][col]) {
                        // This column would violate order, must delete
                        mustDelete = true;
                        break;
                    }
                }
            }
            
            if (mustDelete) {
                deletions++;
            } else {
                // Keep this column - mark newly distinguished pairs
                for (int i = 0; i < n - 1; i++) {
                    if (!sorted[i] && strs[i][col] < strs[i + 1][col]) {
                        sorted[i] = true;
                    }
                }
            }
        }
        
        return deletions;
    }
};