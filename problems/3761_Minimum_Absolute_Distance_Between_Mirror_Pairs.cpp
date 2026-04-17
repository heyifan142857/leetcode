// 3761. Minimum Absolute Distance Between Mirror Pairs
// Created automatically
// Created at 2026-04-17 10:04:04

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMirrorPairDistance(vector<int>& nums) {
        auto revInt = [&](int x) {
            int r = 0;
            while (x > 0) {
                r = r * 10 + (x % 10);
                x /= 10;
            }
            return r;
        };

        unordered_map<int, int> lastIdx;
        lastIdx.reserve(nums.size() * 2);

        int ans = INT_MAX;
        for (int j = 0; j < static_cast<int>(nums.size()); ++j) {
            auto it = lastIdx.find(nums[j]);
            if (it != lastIdx.end()) {
                ans = min(ans, j - it->second);
            }
            lastIdx[revInt(nums[j])] = j;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
