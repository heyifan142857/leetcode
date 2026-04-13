// 1848. Minimum Distance to the Target Element
// Created automatically
// Created at 2026-04-13 15:29:08

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int n = nums.size();
        if (start < 0 || start >= n) {
            return -1;
        }
        int minDistance = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (nums[i] == target) {
                minDistance = min(minDistance, abs(i - start));
            }
        }
        return minDistance;
    }
};