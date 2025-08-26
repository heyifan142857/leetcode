//
// Created by user on 2025/7/24.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maximumOr(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> after(n+1, 0);

        for (int i = n-1; i >= 0; --i) {
            after[i] = after[i+1] | nums[i];
        }

        long long maxOr = 0;
        long long before = 0;

        for (int i = 0;i < nums.size();i++) {
            long long val = nums[i];
            long long newVal = val << k;
            long long total = before | newVal | after[i+1];

            maxOr = max(total, maxOr);
            before |= nums[i];
        }
        return maxOr;
    }
};