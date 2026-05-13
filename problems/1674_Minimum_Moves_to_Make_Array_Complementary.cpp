// 1674. Minimum Moves to Make Array Complementary
// Created automatically
// Created at 2026-05-13 09:21:50

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();

        // 差分数组
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int x = nums[i];
            int y = nums[n - 1 - i];

            int low = min(x, y) + 1;
            int high = max(x, y) + limit;
            int sum = x + y;

            diff[2] += 2;
            diff[2 * limit + 1] -= 2;

            diff[low] -= 1;
            diff[high + 1] += 1;

            diff[sum] -= 1;
            diff[sum + 1] += 1;
        }

        int ans = INT_MAX;
        int cur = 0;

        for (int k = 2; k <= 2 * limit; k++) {
            cur += diff[k];
            ans = min(ans, cur);
        }

        return ans;
    }
};