#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        // Build a map: (left, right) -> list of possible top blocks
        unordered_map<string, vector<char>> patterns;
        for (const string& pattern : allowed) {
            string key = pattern.substr(0, 2);
            patterns[key].push_back(pattern[2]);
        }
        
        // Memoization: cache results for each bottom string
        unordered_set<string> memo;
        
        return dfs(bottom, patterns, memo);
    }
    
private:
    bool dfs(string bottom, unordered_map<string, vector<char>>& patterns,
             unordered_set<string>& memo) {
        // If we've reached a single block, we've successfully built the pyramid
        if (bottom.length() == 1) {
            return true;
        }
        
        // Check memoization
        if (memo.count(bottom)) {
            return false; // Already tried and failed
        }
        
        // Build next row using backtracking - try all possible combinations
        string nextRow;
        if (buildNextRow(bottom, 0, nextRow, patterns, memo)) {
            return true;
        }
        
        // Mark as failed and return false
        memo.insert(bottom);
        return false;
    }
    
    bool buildNextRow(const string& bottom, int index, string& nextRow,
                     unordered_map<string, vector<char>>& patterns,
                     unordered_set<string>& memo) {
        // Base case: we've built a complete next row, recursively check it
        if (index == bottom.length() - 1) {
            return dfs(nextRow, patterns, memo);
        }
        
        // Get the current pair of blocks
        string key = bottom.substr(index, 2);
        
        // If no pattern exists for this pair, we can't build further
        if (patterns.find(key) == patterns.end()) {
            return false;
        }
        
        // Try each possible top block for this pair
        for (char top : patterns[key]) {
            nextRow.push_back(top);
            if (buildNextRow(bottom, index + 1, nextRow, patterns, memo)) {
                return true;
            }
            nextRow.pop_back(); // Backtrack
        }
        
        return false;
    }
};