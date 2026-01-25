//
// Created by azote on 1/20/26.
//
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int left = 0;
        int sum = 0;
        int res = INT_MAX;
        int n = nums.size();

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            while (sum >= target) {
                res = min(res, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return res == INT_MAX ? 0 : res;
    }
};
