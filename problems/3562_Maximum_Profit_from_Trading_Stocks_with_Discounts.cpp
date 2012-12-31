#include <vector>
#include <algorithm>
#include <climits>
#include <functional>
#include <map>
using namespace std;

class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        // Build the tree structure
        vector<vector<int>> children(n + 1);
        for (const auto& edge : hierarchy) {
            int boss = edge[0];
            int employee = edge[1];
            children[boss].push_back(employee);
        }
        
        // Memoization: node -> pair of (dp when parent didn't buy, dp when parent bought)
        map<int, pair<vector<int>, vector<int>>> memo;
        
        // DFS function: returns both dp arrays (when parent didn't buy, when parent bought)
        function<pair<vector<int>, vector<int>>(int)> dfs = [&](int node) -> pair<vector<int>, vector<int>> {
            if (memo.count(node)) {
                return memo[node];
            }
            
            // Calculate cost and profit for this node
            int costWithoutDiscount = present[node - 1];
            int costWithDiscount = present[node - 1] / 2;
            int profitWithoutDiscount = future[node - 1] - present[node - 1];
            int profitWithDiscount = future[node - 1] - costWithDiscount;
            
            // Get children's DP results (compute once, use for both states)
            vector<pair<vector<int>, vector<int>>> childResults;
            for (int child : children[node]) {
                childResults.push_back(dfs(child));
            }
            
            // Helper function to merge children's DP arrays (optimized knapsack)
            auto mergeChildren = [&](const vector<vector<int>>& childDps) -> vector<int> {
                if (childDps.empty()) {
                    return vector<int>(budget + 1, 0);
                }
                vector<int> merged = childDps[0];
                for (int i = 1; i < childDps.size(); i++) {
                    vector<int> newMerged(budget + 1, 0);
                    // Optimized: iterate backwards for knapsack
                    for (int b = budget; b >= 0; b--) {
                        for (int c = 0; c <= b; c++) {
                            newMerged[b] = max(newMerged[b], merged[b - c] + childDps[i][c]);
                        }
                    }
                    merged = newMerged;
                }
                return merged;
            };
            
            // Prepare child DPs for both scenarios
            vector<vector<int>> childDpsNoDiscount, childDpsWithDiscount;
            for (const auto& childRes : childResults) {
                childDpsNoDiscount.push_back(childRes.first);  // parent didn't buy
                childDpsWithDiscount.push_back(childRes.second); // parent bought
            }
            
            // Merge children once for each scenario (reuse results)
            vector<int> mergedNoDiscount = mergeChildren(childDpsNoDiscount);
            vector<int> mergedWithDiscount = mergeChildren(childDpsWithDiscount);
            
            // Compute result when parent didn't buy
            vector<int> resultNoBuyParent(budget + 1, 0);
            for (int b = 0; b <= budget; b++) {
                // Option 1: Don't buy this node
                int profit1 = mergedNoDiscount[b];
                
                // Option 2: Buy this node (no discount)
                int profit2 = INT_MIN;
                if (b >= costWithoutDiscount) {
                    profit2 = profitWithoutDiscount + mergedWithDiscount[b - costWithoutDiscount];
                }
                
                resultNoBuyParent[b] = max({profit1, profit2, 0});
            }
            
            // Compute result when parent bought (we get discount)
            vector<int> resultParentBought(budget + 1, 0);
            for (int b = 0; b <= budget; b++) {
                // Option 1: Don't buy this node
                int profit1 = mergedNoDiscount[b];
                
                // Option 2: Buy this node (with discount)
                int profit2 = INT_MIN;
                if (b >= costWithDiscount) {
                    profit2 = profitWithDiscount + mergedWithDiscount[b - costWithDiscount];
                }
                
                resultParentBought[b] = max({profit1, profit2, 0});
            }
            
            memo[node] = {resultNoBuyParent, resultParentBought};
            return {resultNoBuyParent, resultParentBought};
        };
        
        auto result = dfs(1); // CEO has no parent
        return result.first[budget]; // CEO has no parent, so use first result
    }
};