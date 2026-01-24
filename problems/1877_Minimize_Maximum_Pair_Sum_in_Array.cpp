//
// Created by azote on 1/24/26.
//
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int minPairSum(vector<int> &nums) {
        ranges::sort(nums);
        int mmps = INT_MIN;
        int left = 0;
        int right = nums.size() - 1;
        while (right > left) {
            mmps = max(mmps, nums[left] + nums[right]);
            left++;
            right--;
        }
        return mmps;
    }
};
