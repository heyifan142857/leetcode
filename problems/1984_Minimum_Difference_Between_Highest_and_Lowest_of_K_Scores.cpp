//
// Created by azote on 1/25/26.
//
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int> &nums, int k) {
        int res = INT_MAX;
        ranges::sort(nums);
        for (int i = 0; i < nums.size() - k + 1; ++i) {
            res = min(res, nums[i + k - 1] - nums[i]);
        }
        return res;
    }
};
