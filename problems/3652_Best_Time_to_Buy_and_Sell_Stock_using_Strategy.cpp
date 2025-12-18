#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        
        // Precompute prefix sums
        // prefix_strategy_price[i] = sum of strategy[j] * prices[j] from 0 to i-1
        // prefix_price[i] = sum of prices[j] from 0 to i-1
        vector<long long> prefix_strategy_price(n + 1, 0);
        vector<long long> prefix_price(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefix_strategy_price[i + 1] = prefix_strategy_price[i] + (long long)strategy[i] * prices[i];
            prefix_price[i + 1] = prefix_price[i] + (long long)prices[i];
        }
        
        // Base profit is the sum of all strategy[i] * prices[i]
        long long baseProfit = prefix_strategy_price[n];
        
        // If k is 0 or larger than n, no modification possible
        if (k == 0 || k > n) {
            return baseProfit;
        }
        
        long long maxChange = 0; // Maximum profit change from any modification
        
        // Try all possible windows of size k
        for (int i = 0; i <= n - k; i++) {
            long long change = 0;
            
            // First k/2 elements: change from strategy[j] to 0 (hold)
            // Change = -sum(strategy[j] * prices[j]) for j in [i, i + k/2)
            int firstHalfEnd = i + k / 2;
            change -= (prefix_strategy_price[firstHalfEnd] - prefix_strategy_price[i]);
            
            // Last k/2 elements: change from strategy[j] to 1 (sell)
            // Change = sum((1 - strategy[j]) * prices[j]) for j in [i + k/2, i + k)
            // = sum(prices[j]) - sum(strategy[j] * prices[j])
            int secondHalfStart = i + k / 2;
            int secondHalfEnd = i + k;
            change += (prefix_price[secondHalfEnd] - prefix_price[secondHalfStart]) 
                    - (prefix_strategy_price[secondHalfEnd] - prefix_strategy_price[secondHalfStart]);
            
            maxChange = max(maxChange, change);
        }
        
        return baseProfit + maxChange;
    }
};