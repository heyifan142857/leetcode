//
// Created by user on 2025/9/23.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int curMin = INT_MAX;
        int profit = 0;
        for (auto price: prices) {
            profit = max(profit, price-curMin);
            curMin = min(curMin, price);
        }
        return profit;
    }
};