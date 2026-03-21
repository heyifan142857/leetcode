// Weekly Contest 493 - Q3
// Created automatically
// Created at 2026-03-21 16:21:44

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestArithmetic(vector<int>& nums) {
        const int n = nums.size();
        if (n <= 2) return n;

        vector<int> left(n, 1), right(n, 1);
        left[1] = 2;
        for (int i = 2; i < n; ++i) {
            long long d1 = 1LL * nums[i] - nums[i - 1];
            long long d2 = 1LL * nums[i - 1] - nums[i - 2];
            left[i] = (d1 == d2 ? left[i - 1] + 1 : 2);
        }

        right[n - 2] = 2;
        for (int i = n - 3; i >= 0; --i) {
            long long d1 = 1LL * nums[i + 1] - nums[i];
            long long d2 = 1LL * nums[i + 2] - nums[i + 1];
            right[i] = (d1 == d2 ? right[i + 1] + 1 : 2);
        }

        int ans = *max_element(left.begin(), left.end());
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (i > 0 ? left[i - 1] : 0) + 1);
            ans = max(ans, 1 + (i + 1 < n ? right[i + 1] : 0));

            // If nums[i] is the modified element inside the chosen subarray,
            // the common difference is forced by its two neighbors.
            if (i == 0 || i == n - 1) continue;

            long long gap = 1LL * nums[i + 1] - nums[i - 1];
            if (gap % 2 != 0) continue;

            long long d = gap / 2;
            int l = 1;
            if (i >= 2 && 1LL * nums[i - 1] - nums[i - 2] == d) {
                l = left[i - 1];
            }

            int r = 1;
            if (i + 2 < n && 1LL * nums[i + 2] - nums[i + 1] == d) {
                r = right[i + 1];
            }

            ans = max(ans, l + 1 + r);
        }

        return ans;
    }
};
