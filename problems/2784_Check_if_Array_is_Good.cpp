// 2784. Check if Array is Good
// Created automatically
// Created at 2026-05-14 09:49:16

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isGood(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] != i + 1) {
                return false;
            }
        }
        return nums[n - 1] == n - 1;
    }
};