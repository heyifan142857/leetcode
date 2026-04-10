// 3740. Minimum Distance Between Three Equal Elements I
// Created automatically
// Created at 2026-04-10 10:25:59

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> pos;
        for (int i = 0; i < (int)nums.size(); ++i) pos[nums[i]].push_back(i);

        int ans = INT_MAX;
        for (auto &kv : pos) {
            auto &v = kv.second;
            if (v.size() < 3) continue;
            for (int i = 0; i + 2 < (int)v.size(); ++i) {
                int d = v[i+2] - v[i];
                ans = min(ans, 2 * d);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};