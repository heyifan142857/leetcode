// 3524. Find X Value of Array I
// Created automatically
// Created at 2026-09-21 16:40:12

#include <vector>
using namespace std;

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0), dp(k, 0);
        for (int num : nums) {
            const int value = num % k;
            // next[r] counts subarrays ending here with product remainder r.
            vector<long long> next(k, 0);
            next[value] = 1;
            for (int r = 0; r < k; ++r) {
                next[1LL * r * value % k] += dp[r];
            }
            for (int r = 0; r < k; ++r) {
                result[r] += next[r];
            }
            dp.swap(next);
        }
        return result;
    }
};
