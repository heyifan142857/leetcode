// 3653. XOR After Range Multiplication Queries I
// Created automatically
// Created at 2026-04-08 10:28:49

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        static constexpr int MOD = 1'000'000'007;

        for (const auto& query : queries) {
            const int l = query[0];
            const int r = query[1];
            const int k = query[2];
            const int v = query[3];

            for (int idx = l; idx <= r; idx += k) {
                nums[idx] = static_cast<int>(1LL * nums[idx] * v % MOD);
            }
        }

        int ans = 0;
        for (int num : nums) {
            ans ^= num;
        }
        return ans;
    }
};
