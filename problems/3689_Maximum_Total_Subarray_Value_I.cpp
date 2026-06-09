// 3689. Maximum Total Subarray Value I
// Created automatically
// Created at 2026-06-09 19:05:13

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        vector<int> sormadexin = nums;
        
        int max_val = INT_MIN;
        int min_val = INT_MAX;
        
        for (int num : nums) {
            max_val = max(max_val, num);
            min_val = min(min_val, num);
        }
        
        return (long long)k * (max_val - min_val);
    }
};