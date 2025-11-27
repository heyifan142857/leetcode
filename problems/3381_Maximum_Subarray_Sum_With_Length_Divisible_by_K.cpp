//
// Created by azote on 11/27/25.
//
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int> &nums, int k) {
        long long prefix = 0;
        vector<long long> minPrefix(k, LLONG_MAX);
        minPrefix[0] = 0;
        long long ans = LLONG_MIN;
        for (int i = 0; i < nums.size(); i++) {
            prefix += nums[i];
            const int mod = (i + 1) % k;
            if (minPrefix[mod] != LLONG_MAX) {
                ans = max(ans, prefix - minPrefix[mod]);
            }
            minPrefix[mod] = min(minPrefix[mod], prefix);
        }
        return ans;
    }
};
