// 2553. Separate the Digits in an Array
// Created automatically
// Created at 2026-05-12 14:20:39

#include <bits/stdc++.h>
using namespace std;

class Solution {
    void _separateDigits(vector<int>& nums, const int num) {
        if (num <= 0) {
            return;
        }

        int lastDigit = num % 10;
        _separateDigits(nums, num / 10);
        nums.push_back(lastDigit);
    }
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;

        for (const auto &num : nums) {
            _separateDigits(ans, num);
        }

        return ans;
    }
};