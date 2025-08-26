//
// Created by user on 2025/7/28.
//
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((sum + target) % 2 != 0 || sum < abs(target)) return 0;
        int new_target = (sum + target) / 2;

        vector<int> dp(new_target + 1, 0);
        dp[0] = 1;

        for (int num : nums) {
            for (int j = new_target; j >= num; --j) {
                dp[j] += dp[j - num];
            }
        }

        return dp[new_target];
    }
};


//时间超限
//class Solution {
//public:
//    int findTargetSumWays(vector<int>& nums, int target) {
//        int n = nums.size();
//        int count = 0;
//        for (int mask = 0; mask < (1 << n); ++mask) {
//            int sum = 0;
//            for (int i = 0; i < n; ++i) {
//                if (mask & (1 << i)) {
//                    sum += nums[i];
//                }else{
//                    sum -= nums[i];
//                }
//            }
//            if(sum == target){
//                count++;
//            }
//        }
//        return count;
//    }
//};