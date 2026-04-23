// 2615. Sum of Distances
// Created automatically
// Created at 2026-04-23 10:50:44

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> ans(n, 0);
        unordered_map<int, vector<int>> positions;

        for (int i = 0; i < n; ++i) {
            positions[nums[i]].push_back(i);
        }

        for (auto& [_, idxs] : positions) {
            int m = idxs.size();
            vector<long long> prefix(m + 1, 0);

            for (int i = 0; i < m; ++i) {
                prefix[i + 1] = prefix[i] + idxs[i];
            }

            for (int i = 0; i < m; ++i) {
                long long left = 1LL * idxs[i] * i - prefix[i];
                long long right = (prefix[m] - prefix[i + 1]) - 1LL * idxs[i] * (m - i - 1);
                ans[idxs[i]] = left + right;
            }
        }

        return ans;
    }
};
