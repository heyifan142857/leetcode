// 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum
// Created automatically
// Created at 2026-08-11 19:36:26

#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
    bool has_i(int i, vector<int> &nums) {
        for (auto const n : nums) {
            if (n == i) {
                return true;
            }
        }
        return false;
    }

public:
    int missingInteger(vector<int> &nums) {
        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        int sum = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }

        for (int i = sum; sum <= 50; i++) {
            if (!has_i(i, nums)) {
                return i;
            }
        }
        return sum;
    }
};
